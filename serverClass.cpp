/* 
 * File:   serverClass.cpp
 * Author: root
 * 
 * Created on Utorok, 2015, január 27, 17:16
 */

#include "serverClass.h"
#include "serverForm.h"

void *vlaknoZrusitMapovanie(void *arg) {
    serverForm *server = (serverForm *) arg;
    
    server->stopMappingClicked();
    usleep(300*1000);
}

void *vlaknoPrijimanieDatAgentov(void *arg) {
    int n;

    param_vlakno_prijimanie *param = (param_vlakno_prijimanie *) arg;
    komunikacia_shm *shm_S_GUI = param->shm_S_A;
    agent_in_shm agent = param->agent_info;
    while (1) {
        char jsonData[1001];
        bzero(jsonData, 1000);
        n = shm_S_GUI->socket->receiveJson(agent.sockFd, jsonData, 1000);
        if (n > 0) { //musia byt prijate byty
            std::cout << "data=" << jsonData << "=KONIEC\n";
            //rozparsovat a spracovat, ulozit do db
            std::string ctype = socketUtilClass::parseClassTypeFromJson(jsonData);
            std::cout << "ctype=" << ctype << "\n";
            
            // ak pride ukoncenie agenta
            if (ctype.compare("QUIT") == 0) {
                //vymazeme agenta z listu
                //pri odpojeni agenta treba dekrementovat pocet pripojenych a pripojit dalsich
                int id = socketUtilClass::parseIdFromQuit(jsonData);
                std::list<agent_in_shm>::iterator i;
                for (i = shm_S_GUI->agentsList.begin(); i != shm_S_GUI->agentsList.end(); ++i) {
                    if (i->id == id) {
                        shm_S_GUI->agentsList.erase(i);
                        shm_S_GUI->connectedAgentsCount--;
                        shm_S_GUI->widget->agentCountLabel->setText(std::to_string(shm_S_GUI->connectedAgentsCount).c_str());
                        //ak neni pripojeny agent zakazeme spustenie mapovania
                        if (!(shm_S_GUI->connectedAgentsCount > 0)) {
                            shm_S_GUI->widget->startMappingButton->setEnabled(false);
                            //ak neni ziaden agent pripojeny tak treba zrusit pripadne mapovanie
                            pthread_t thr1;
                            pthread_attr_t parametre;
                            if (pthread_attr_init(&parametre)) {
                                std::cout << "chyba v attr_init\n";
                            }
                            pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);
                            if (pthread_create(&thr1, &parametre, vlaknoZrusitMapovanie, (void*) shm_S_GUI->serverForm)) {
                                std::cout << "chyba vo vytvarani vlakna na odpojenie\n";
                            }
                            
                        }
                        //break;
                        return 0;
                    }
                }
            }
            
            // ak pride poloha
            if (ctype.compare("POLOHACLASS") == 0) {
                // rozparsujeme a ulozime do premennej aj DB
                polohaClass *poloha = polohaClass::fromJson(jsonData);
                shm_S_GUI->dbConnector->savePoloha(poloha);
            }
            
            // ak pride prekazka
            if (ctype.compare("PREKAZKACLASS") == 0) {
                // rozparsujeme a ulozime do premennej aj DB
                prekazkaClass *prekazka = prekazkaClass::fromJson(jsonData);
                shm_S_GUI->dbConnector->savePrekazka(prekazka);
            }
        }
        usleep(300 * 1000);
    }

}

void *vlaknoNavigaciaMapovania(void *arg) {
    komunikacia_shm *shm_S_GUI = (komunikacia_shm *) arg;
    
    // z DB ziskame nove id spustenia a posleme ho spolu s info o zacati mapovania
    shm_S_GUI->idSpustenia = shm_S_GUI->dbConnector->getNewSpustenieId();
    std::list<agent_in_shm>::iterator i;
    for (i = shm_S_GUI->agentsList.begin(); i != shm_S_GUI->agentsList.end(); ++i) {
        shm_S_GUI->socket->sendJson(i->sockFd, socketUtilClass::createJsonStartMapping());
        shm_S_GUI->socket->sendJson(i->sockFd, socketUtilClass::createJsonIdSpustenia(shm_S_GUI->idSpustenia));
    }
    
    while (shm_S_GUI->ukonci_ulohu == false) {
        std::cout << "vlakno navigacia\n";
        // todo implementovat riadiaci algoritmus
        usleep(1000 * 1000);
    }
}

void *vlaknoCakanieNaAgentov(void *arg) {
    int newSocketFd;

    komunikacia_shm *shm_S_GUI = (komunikacia_shm *) arg;
    while (1) {
        if (shm_S_GUI->connectedAgentsCount < shm_S_GUI->maxAgents) {
            newSocketFd = shm_S_GUI->socket->waitAndAcceptClient();
            shm_S_GUI->connectedAgentsCount++;
            shm_S_GUI->lastAgentId++;
            shm_S_GUI->widget->agentCountLabel->setText(std::to_string(shm_S_GUI->connectedAgentsCount).c_str());
            // todo autentifikovat
            agent_in_shm agent;
            agent.id = shm_S_GUI->lastAgentId;
            agent.sockFd = newSocketFd;
            std::cout << "newsocfd " << newSocketFd << "\n";
            const char *jsondata = socketUtilClass::createJsonAgentId_IdSpustenia(agent.id, shm_S_GUI->idSpustenia);
            shm_S_GUI->socket->sendJson(agent.sockFd, jsondata);
            //vytvorime vlakno na prijimanie
            param_vlakno_prijimanie param;
            param.shm_S_A = shm_S_GUI;
            param.agent_info = agent;
            pthread_attr_t parametre;
            if (pthread_attr_init(&parametre)) {
                std::cout << "chyba v attr_init\n";
                continue;
            }
            pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);
            if (pthread_create(&(agent.vlaknoPrijimanie), &parametre, vlaknoPrijimanieDatAgentov, (void*) (&param))) {
                std::cout << "chyba vo vytvarani vlakna na prijimanie\n";
                continue;
            }
            shm_S_GUI->agentsList.push_back(agent);
            //ak je pripojenych viac agetov povolime mapovanie
            if (shm_S_GUI->connectedAgentsCount > 0) {
                shm_S_GUI->widget->startMappingButton->setEnabled(true);
            }
            usleep(200 * 1000);
            std::cout << "dalsi agent pripojeny\n";
        } else {
            usleep(500*1000);
        }
    }
    std::cout << "max pocet agentov dosiahnuty\n";

}

serverClass::serverClass(komunikacia_shm *shm_S_GUI) {
    this->shm_S_GUI = shm_S_GUI;
    this->dbConnector = new dbConnectorClass();
    this->socket = new socketClass();
    this->shm_S_GUI->socket = socket;
    this->shm_S_GUI->dbConnector = dbConnector;
}

int serverClass::getPortNumber() {
    return portNumber;
}

int serverClass::getMaxAgents() {
    return maxAgents;
}

int serverClass::getConnectedAgentsCount() {
    return shm_S_GUI->connectedAgentsCount;
}

int serverClass::startServer(int portNumber, int maxAgents) {
    this->portNumber = portNumber;
    this->maxAgents = maxAgents;
    shm_S_GUI->ukonci_ulohu = 0;
    shm_S_GUI->mappingNow = 0;
    shm_S_GUI->connectedAgentsCount = 0;
    shm_S_GUI->maxAgents = maxAgents;

    socket->connect();
    if (socket->getConnected()) {
        serverRunning = true;
        shm_S_GUI->idSpustenia = dbConnector->getNewSpustenieId();
        std::cout << "idSpustenia: " << this->shm_S_GUI->idSpustenia << "\n";
        pthread_attr_t parametre;
        if (pthread_attr_init(&parametre)) exit(-1);
        pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);
        if (pthread_create(&vlaknoCakanieAgentov, &parametre, vlaknoCakanieNaAgentov, (void*) shm_S_GUI)) exit(-2);
        return 0;
    }
    return -1;
}

int serverClass::stopServer() {
    std::cout << "stopping server\n";
    if (serverRunning) {
        //zrusime mapovanie
        stopMapping();

        // zrusime vlakno cakajuce na novych agentov
        pthread_cancel(vlaknoCakanieAgentov);
        //poodpajame agentov - zrusime newSocketFd a vlakno prijimanie
        std::list<agent_in_shm>::iterator i;
        for (i = shm_S_GUI->agentsList.begin(); i != shm_S_GUI->agentsList.end(); ++i) {
            std::cout << "agent id=" << i->id << " ukoncujem" << "\n";
            // posleme ukoncovaci string agentovi
            shm_S_GUI->socket->sendJson(i->sockFd, socketUtilClass::createJsonServerQuit());
            pthread_cancel(i->vlaknoPrijimanie);
            socket->disconnectFd(i->sockFd);
        }
        if (socket->getConnected()) {
            socket->disconnect();
        }
    }
    serverRunning = false;
    
}

bool serverClass::isServerRunning() {
    //serverRunning = socket->getConnected(); //asi nema byt
    return serverRunning;
}

int serverClass::doMapping() {
    if (shm_S_GUI->mappingNow == false) {
        pthread_attr_t parametre;
        if (pthread_attr_init(&parametre)) {
            return -1;
        }
        pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);
        if (pthread_create(&vlaknoMapovanie, &parametre, vlaknoNavigaciaMapovania, (void*) shm_S_GUI)) {
            return -1;
        }
    }
    
    shm_S_GUI->mappingNow = true;
    return 0;
}

int serverClass::stopMapping() {
    if (shm_S_GUI->mappingNow) {
        std::cout << "stopping mapping\n";
        std::list<agent_in_shm>::iterator i;
        for (i = shm_S_GUI->agentsList.begin(); i != shm_S_GUI->agentsList.end(); ++i) {
            socket->sendJson(i->sockFd, socketUtilClass::createJsonStopMapping());
        }
        // zrusime mapovaci thread - sam sa ukonci
        shm_S_GUI->ukonci_ulohu = true;
    }
    shm_S_GUI->mappingNow = false;
}

bool serverClass::isMapping() {
    return shm_S_GUI->mappingNow;
}

serverClass::~serverClass() {
    std::cout << "destruktor serverClass\n";
    stopServer(); //zastavi server aj mapovanie
}

