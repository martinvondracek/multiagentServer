/* 
 * File:   serverClass.cpp
 * Author: root
 * 
 * Created on Utorok, 2015, január 27, 17:16
 */

#include "serverClass.h"

void *vlaknoCakanieNaAgentov(void *arg) {
    int newSocketFd;
    
    komunikacia_shm *shm_S_GUI = (komunikacia_shm *) arg;
    while (shm_S_GUI->connectedAgentsCount < shm_S_GUI->maxAgents) {
        newSocketFd = shm_S_GUI->socketUtil->waitAndAcceptClient();
        std::cout << "dalsi agent pripojeny\n";
        shm_S_GUI->connectedAgentsCount++;
        shm_S_GUI->widget->agentCountLabel->setText(std::to_string(shm_S_GUI->connectedAgentsCount).c_str());
        // todo autentifikovat
        // todo zistit id agenta a ulozit Fd agenta
    }
    std::cout << "max pocet agentov dosiahnuty\n";
    
}

serverClass::serverClass(komunikacia_shm *shm_S_GUI) {
    this->shm_S_GUI = shm_S_GUI;
    this->dbUtil = new dbConnectorClass();
    this->socketUtil = new socketClass();
    this->shm_S_GUI->socketUtil = socketUtil;
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
    
    socketUtil->connect();
    if (socketUtil->getConnected()) {
        serverRunning = true;
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
    // zrusime vlakno cakajuce na novych agentov
    pthread_cancel(vlaknoCakanieAgentov);
    // todo poodpajat agentov
    if (socketUtil->getConnected()) {
        socketUtil->disconnect();
    }
    serverRunning = false;
}

bool serverClass::isServerRunning() {
    //serverRunning = socketUtil->getConnected(); //asi nema byt
    return serverRunning;
}

int serverClass::doMapping() {
    // todo implementovat
}

bool serverClass::isMapping() {
    return shm_S_GUI->mappingNow;
}

serverClass::~serverClass() {
    stopServer();
}

