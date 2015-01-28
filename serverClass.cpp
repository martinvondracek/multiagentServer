/* 
 * File:   serverClass.cpp
 * Author: root
 * 
 * Created on Utorok, 2015, január 27, 17:16
 */

#include "serverClass.h"

void *vlaknoPrijimanieDatAgentov(void *arg) {
    komunikacia_shm *shm_S_GUI = (komunikacia_shm *) arg;
    while (1) {
        std::cout << "vlakno prijimanie dat\n";
        usleep(1000*1000);
    }
    
    //todo pri odpojeni agenta treba dekrementovat pocet pripojenych a pripojit dalsich
}

void *vlaknoNavigaciaMapovania(void *arg) {
    komunikacia_shm *shm_S_GUI = (komunikacia_shm *) arg;
    while (1) {
        std::cout << "vlakno navigacia\n";
        usleep(1000*1000);
    }
}

void *vlaknoCakanieNaAgentov(void *arg) {
    int newSocketFd;
    
    komunikacia_shm *shm_S_GUI = (komunikacia_shm *) arg;
    while (shm_S_GUI->connectedAgentsCount < shm_S_GUI->maxAgents) {
        newSocketFd = shm_S_GUI->socket->waitAndAcceptClient();
        shm_S_GUI->connectedAgentsCount++;
        shm_S_GUI->widget->agentCountLabel->setText(std::to_string(shm_S_GUI->connectedAgentsCount).c_str());
        // todo autentifikovat
        agent_in_shm agent;
        agent.id = shm_S_GUI->connectedAgentsCount;
        agent.sockFd = newSocketFd;
        const char *jsondata = socketUtilClass::createJsonAgentId_IdSpustenia(agent.id, shm_S_GUI->idSpustenia);
        shm_S_GUI->socket->sendJson(agent.sockFd, jsondata);
        // todo vytvorit vlakno na prijimanie
        pthread_attr_t parametre;
        if (pthread_attr_init(&parametre)) {
            std::cout << "chyba v attr_init\n";
            continue;
        }
        pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);
        if (pthread_create(&(agent.vlaknoPrijimanie), &parametre, vlaknoPrijimanieDatAgentov, (void*) shm_S_GUI)) {
            std::cout << "chyba vo vytvarani vlakna na prijimanie\n";
            continue;
        }
        shm_S_GUI->agentsList.push_back(agent);
        std::cout << "dalsi agent pripojeny\n";
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
        // todo implementovat čakacie vlákno
        pthread_attr_t parametre;
        if (pthread_attr_init(&parametre)) exit(-1);
        pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);
        if (pthread_create(&vlaknoCakanieAgentov, &parametre, vlaknoCakanieNaAgentov, (void*) shm_S_GUI)) exit(-2);
        return 0;
    }
    return -1;
}

int serverClass::stopServer() {
    //todo zrusime mapovanie
    
    // zrusime vlakno cakajuce na novych agentov
    pthread_cancel(vlaknoCakanieAgentov);
    //poodpajame agentov - zrusime newSocketFd a vlakno prijimanie
    std::list<agent_in_shm>::iterator i;
    for(i=shm_S_GUI->agentsList.begin(); i != shm_S_GUI->agentsList.end(); ++i) {
        std::cout << "agent id=" << i->id << " ukoncujem" << "\n";
        // todo poslat ukoncovaci string agentovi
        pthread_cancel(i->vlaknoPrijimanie);
        socket->disconnectFd(i->sockFd);
    }
    if (socket->getConnected()) {
        socket->disconnect();
    }
    serverRunning = false;
}

bool serverClass::isServerRunning() {
    //serverRunning = socket->getConnected(); //asi nema byt
    return serverRunning;
}

int serverClass::doMapping() {
    // todo implementovat
}

bool serverClass::isMapping() {
    return shm_S_GUI->mappingNow;
}

serverClass::~serverClass() {
    std::cout << "destruktor serverClass\n";
    stopServer();
}

