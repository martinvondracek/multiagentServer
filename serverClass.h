/* 
 * File:   serverClass.h
 * Author: root
 *
 * Created on Utorok, 2015, január 27, 17:16
 */

#ifndef SERVERCLASS_H
#define	SERVERCLASS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>

#include "socketClass.h"
#include "socketUtilClass.h"
#include "dbConnectorClass.h"
#include "ui_serverForm.h"

struct agent_in_shm {
    int id;
    int sockFd;
    pthread_t vlaknoPrijimanie; // na vlakno ktore prijima info z agentov
};

struct komunikacia_shm {
    int idSpustenia;
    bool ukonci_ulohu;
    bool mappingNow;
    int maxAgents;
    int connectedAgentsCount;
    int lastAgentId;
    socketClass *socket;
    dbConnectorClass *dbConnector;
    Ui::serverForm *widget;
    std::list<agent_in_shm> agentsList;
};

struct param_vlakno_prijimanie {
    agent_in_shm agent_info;
    komunikacia_shm *shm_S_A;
};

class serverClass {
public:
    serverClass(komunikacia_shm *shm_S_GUI);
    virtual ~serverClass();
    
    int getPortNumber();
    int getMaxAgents();
    int getConnectedAgentsCount();
    
    int startServer(int portNumber, int maxAgents);
    int stopServer();
    bool isServerRunning();
    
    int doMapping();
    int stopMapping();
    bool isMapping();
    
private:
    int portNumber;
    int maxAgents;
    bool serverRunning = false;
    int spustenieId;
    
    pthread_t vlaknoCakanieAgentov;
    pthread_t vlaknoMapovanie;
    
    komunikacia_shm *shm_S_GUI;
    socketClass * socket; //objekt pre komunikáciu cez socket
    dbConnectorClass *dbConnector;
    
};

#endif	/* SERVERCLASS_H */

