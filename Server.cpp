/* 
 * File:   serverClass.cpp
 * Author: root
 * 
 * Created on Utorok, 2015, január 27, 17:16
 */

#include "Server.h"
#include "serverForm.h"
#include "CoordinationPosition.h"
#include "NavigationUtil.h"

void *vlaknoZrusitMapovanie(void *arg) {
    serverForm *server = (serverForm *) arg;

    server->stopMappingClicked();
    usleep(600 * 1000);
}

void *vlaknoPrijimanieDatAgentov(void *arg) {
    int n;

    param_vlakno_prijimanie *param = (param_vlakno_prijimanie *) arg;
    komunikacia_shm *shm_S_GUI = param->shm_S_A;
    agent_in_shm agent = param->agent_info;
    while (1) {
        char jsonData[50001];
        bzero(jsonData, 50000);
        n = shm_S_GUI->socket->receiveJson(agent.sockFd, jsonData, 50000);
        //std::cout << "rawdata=" << jsonData << "=KONIEC\n";
        if (n > 0) { //musia byt prijate byty
            //std::cout << "data=" << jsonData << "=KONIEC\n";

            //ak pride viacej dat naraz tak ich rozdelime
            std::string s = jsonData;
            std::string delimiter = "KKK";
            size_t pos = 0;
            std::string token;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                if(token.length()<3 || token.empty() || token.at(0)!='{') {
                    continue;
                }
                //std::cout << "data token=" << token << "=KONIEC\n";

                //rozparsovat a spracovat, ulozit do db
                std::string ctype = SocketUtil::parseClassTypeFromJson(token.c_str());
                //std::cout << "ctype=" << ctype << "\n";

                // ak pride ukoncenie agenta
                if (ctype.compare("QUIT") == 0) {
                    //vymazeme agenta z listu
                    //pri odpojeni agenta treba dekrementovat pocet pripojenych a pripojit dalsich
                    int id = SocketUtil::parseIdFromQuit(token.c_str());
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
                
                // ak pride ze koor sur neni validna
                if (ctype.compare("INVALID_KOOR_SUR") == 0) {
                    // nastavie jeho koor sur na invalid
                    //std::cout << "invalid koor\n";
                    int id = SocketUtil::parseAgentIdFromInvalidKoorSur(token.c_str());
                    std::list<agent_in_shm>::iterator i;
                    for (i = shm_S_GUI->agentsList.begin(); i != shm_S_GUI->agentsList.end(); ++i) {
                        if (i->id == id) {
                            i->koordinacnaSuradnica->setInvalid();
                            std::cout << "nastavujeme invalid koor\n";
                        }
                    }
                }
                
                // ak pride ze koor sur je inaccesible
                if (ctype.compare("INACCESIBLE_KOOR_SUR") == 0) {
                    // nastavie jeho koor sur na invalid
                    std::cout << "inaccesible koor\n";
                    int id = SocketUtil::parseAgentIdFromInaccesibleKoorSur(token.c_str());
                    std::list<agent_in_shm>::iterator i;
                    for (i = shm_S_GUI->agentsList.begin(); i != shm_S_GUI->agentsList.end(); ++i) {
                        if (i->id == id) {
                            // pridame do inaccesible
                            shm_S_GUI->oblasti->addInaccesibleKoorSur(i->koordinacnaSuradnica);
                            i->koordinacnaSuradnica->setInvalid();
                            std::cout << "nastavujeme invalid koor koli inaccesible\n";
                        }
                    }
                }

                // ak pride poloha
                if (ctype.compare("POLOHACLASS") == 0) {
                    // rozparsujeme a ulozime do premennej aj DB
                    Position *poloha = Position::fromJson(token.c_str());
                    shm_S_GUI->dbConnector->savePosition(poloha);
                    // zaroven ju posleme ostatnym robotom
                    std::list<agent_in_shm>::iterator i;
                    for (i = shm_S_GUI->agentsList.begin(); i != shm_S_GUI->agentsList.end(); ++i) {
                        if (i->id != poloha->GetRobot()) {
                            shm_S_GUI->socket->sendJson(i->sockFd, token.c_str());
                            //std::cout << "preposielam polohu od:" << poloha->GetRobot() << " k:" << i->id << "\n";
                        } else {
                            //std::cout << "ignorujem preposlanie\n";
                            // ak je to on tak mu ulozim polohu
                            i->aktPoloha = Position::fromJson(token.c_str());
                        }
                    }
                    // ulozime do uz zmapovanych casti priestoru
                    shm_S_GUI->oblasti->addPosition(poloha);
                }

                // ak pride prekazka
                if (ctype.compare("PREKAZKACLASS") == 0) {
                    // rozparsujeme a ulozime do premennej aj DB
                    Obstacle *prekazka = Obstacle::fromJson(token.c_str());
                    shm_S_GUI->dbConnector->saveObstacle(prekazka);
                    // zaroven ju posleme ostatnym robotom
                    std::list<agent_in_shm>::iterator i;
                    for (i = shm_S_GUI->agentsList.begin(); i != shm_S_GUI->agentsList.end(); ++i) {
                        if (i->id != prekazka->GetRobot()) {
                            shm_S_GUI->socket->sendJson(i->sockFd, token.c_str());
                            //std::cout << "preposielam prekazku od:" << prekazka->GetRobot() << " k:" << i->id << "\n";
                        } else {
                            //std::cout << "ignorujem preposlanie\n";
                        }
                    }
                }
                
                // ak pride ziadost o nove id prekazky
                if (ctype.compare("NEW_ID_PREKAZKY") == 0) {
                    //ziskame z DB a posleme spat
                    int idPrekazky = shm_S_GUI->dbConnector->getNewObstacleId(shm_S_GUI->idSpustenia);
                    std::cout << "nove id prekazky: " << idPrekazky << " id spustenia " << shm_S_GUI->idSpustenia << " agent id=" << agent.id << "\n";
                    shm_S_GUI->socket->sendJson(agent.sockFd, SocketUtil::createJsonNewIdPrekazky(idPrekazky));
                    //std::cout << "poslane nove id prekazky: " << idPrekazky << "\n";
                }
                
                s.erase(0, pos + delimiter.length());
            }
        }
        usleep(300 * 1000);
    }

}

void *vlaknoNavigaciaMapovania(void *arg) {
    std::cout << "vlakno navigacia\n";
    komunikacia_shm *shm_S_GUI = (komunikacia_shm *) arg;

    // z DB ziskame nove id spustenia a posleme ho spolu s info o zacati mapovania
    shm_S_GUI->idSpustenia = shm_S_GUI->dbConnector->getNewMappingId();
    shm_S_GUI->widget->idSpusteniaLabel->setText(std::to_string(shm_S_GUI->idSpustenia).c_str());
    int radius = shm_S_GUI->widget->radiusEdit->text().toInt();
    shm_S_GUI->oblasti = new CoveredAreas(0, 0, radius, shm_S_GUI->idSpustenia);
    
    // spustime mapovanie v agentoch
    std::list<agent_in_shm>::iterator i;
    for (i = shm_S_GUI->agentsList.begin(); i != shm_S_GUI->agentsList.end(); ++i) {
        shm_S_GUI->socket->sendJson(i->sockFd, SocketUtil::createJsonIdSpustenia(shm_S_GUI->idSpustenia));
        shm_S_GUI->socket->sendJson(i->sockFd, SocketUtil::createJsonStartMapping());
    }

    int cyklus = 1;
    //najskôr po cca 1s vypočítame prvotné koorSur (ked uz pozname polohy robotov))
    while (shm_S_GUI->ukonci_ulohu==false && cyklus<=3) {
        cyklus ++;
        if (cyklus == 3) { 
            std::cout << "navigacia inicializuje koor sur\n";
            // inicializujeme koorSur a posleme ich agentom
            NavigationUtil::initializeKoorSuradnice(shm_S_GUI->oblasti, &(shm_S_GUI->agentsList));
            std::list<agent_in_shm>::iterator i;
            for (i = shm_S_GUI->agentsList.begin(); i != shm_S_GUI->agentsList.end(); ++i) {
                shm_S_GUI->socket->sendJson(i->sockFd, i->koordinacnaSuradnica->toJson());
            }
        }
        
        usleep(300 * 1000);
    }
    bool ukoncujeme = false;
    while (shm_S_GUI->ukonci_ulohu == false) {
        cyklus ++;
        if (cyklus > 10) {
            cyklus = 1;
        }
        
        if (cyklus == 10) { // každé 3 sekundy počítame
            // updatneme koorSur a posleme ich agentom
            std::cout << "navigacia\n";
            NavigationUtil::updateKoorSuradnice(shm_S_GUI->oblasti, &(shm_S_GUI->agentsList));
            std::list<agent_in_shm>::iterator i;
            for (i = shm_S_GUI->agentsList.begin(); i != shm_S_GUI->agentsList.end(); ++i) {
                shm_S_GUI->socket->sendJson(i->sockFd, i->koordinacnaSuradnica->toJson());
            }
            
        }
        
        // ak je coverage 100% ukoncime mapovanie
        if (shm_S_GUI->oblasti->getCoverage()==100 && ukoncujeme==false) {
            // TODO
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
        
        usleep(300 * 1000);
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
            agent.koordinacnaSuradnica = CoordinationPosition::newInvalid();
            agent.aktPoloha = new Position(0, shm_S_GUI->idSpustenia, agent.id, 0, 0, 0);
            std::cout << "newsocfd " << newSocketFd << "\n";
            std::string jsondata = SocketUtil::createJsonAgentId_IdSpustenia(agent.id, shm_S_GUI->idSpustenia);
            shm_S_GUI->socket->sendJson(agent.sockFd, jsondata);
            //std::cout << "sending " << jsondata << "\n";
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
            usleep(500 * 1000);
        }
    }
    std::cout << "max pocet agentov dosiahnuty\n";

}

Server::Server(komunikacia_shm *shm_S_GUI) {
    this->shm_S_GUI = shm_S_GUI;
    this->dbConnector = new DbConnector();
    this->socket = new SocketConnector();
    this->shm_S_GUI->socket = socket;
    this->shm_S_GUI->dbConnector = dbConnector;
    this->shm_S_GUI->oblasti = new CoveredAreas(0, 0, 4000, 0);
}

int Server::getPortNumber() {
    return portNumber;
}

int Server::getMaxAgents() {
    return maxAgents;
}

int Server::getConnectedAgentsCount() {
    return shm_S_GUI->connectedAgentsCount;
}

int Server::startServer(int portNumber, int maxAgents) {
    this->portNumber = portNumber;
    this->maxAgents = maxAgents;
    shm_S_GUI->ukonci_ulohu = 0;
    shm_S_GUI->mappingNow = 0;
    shm_S_GUI->lastAgentId = 0;
    shm_S_GUI->connectedAgentsCount = 0;
    shm_S_GUI->maxAgents = maxAgents;

    socket->connect();
    if (socket->getConnected()) {
        serverRunning = true;
        shm_S_GUI->idSpustenia = dbConnector->getNewMappingId();
        std::cout << "idSpustenia: " << this->shm_S_GUI->idSpustenia << "\n";
        pthread_attr_t parametre;
        if (pthread_attr_init(&parametre)) exit(-1);
        pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);
        if (pthread_create(&vlaknoCakanieAgentov, &parametre, vlaknoCakanieNaAgentov, (void*) shm_S_GUI)) exit(-2);
        return 0;
    }
    return -1;
}

int Server::stopServer() {
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
            shm_S_GUI->socket->sendJson(i->sockFd, SocketUtil::createJsonServerQuit());
            pthread_cancel(i->vlaknoPrijimanie);
            socket->disconnectFd(i->sockFd);
        }
        if (socket->getConnected()) {
            socket->disconnect();
        }
    }
    serverRunning = false;

}

bool Server::isServerRunning() {
    //serverRunning = socket->getConnected(); //asi nema byt
    return serverRunning;
}

int Server::doMapping() {
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

int Server::stopMapping() {
    if (shm_S_GUI->mappingNow) {
        std::cout << "stopping mapping\n";
        std::list<agent_in_shm>::iterator i;
        for (i = shm_S_GUI->agentsList.begin(); i != shm_S_GUI->agentsList.end(); ++i) {
            socket->sendJson(i->sockFd, SocketUtil::createJsonStopMapping());
        }
        // zrusime mapovaci thread - sam sa ukonci
        shm_S_GUI->dbConnector->saveCoveredAreas(shm_S_GUI->oblasti);
        shm_S_GUI->dbConnector->updateMappingEnd(shm_S_GUI->idSpustenia);
        shm_S_GUI->ukonci_ulohu = true;
        shm_S_GUI->oblasti->print();
    }
    shm_S_GUI->mappingNow = false;
}

bool Server::isMapping() {
    return shm_S_GUI->mappingNow;
}

Server::~Server() {
    std::cout << "destruktor serverClass\n";
    stopServer(); //zastavi server aj mapovanie
}

