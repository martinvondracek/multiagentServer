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

#include "socketClass.h"
#include "dbConnectorClass.h"
#include "ui_serverForm.h"

struct komunikacia_shm {
    bool ukonci_ulohu;
    bool mappingNow;
    int maxAgents;
    int connectedAgentsCount;
    socketClass *socketUtil;
    Ui::serverForm *widget;
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
    bool isMapping();
    
private:
    int portNumber;
    int maxAgents;
    bool serverRunning = false;
    int spustenieId;
    
    pthread_t vlaknoCakanieAgentov;
    
    komunikacia_shm *shm_S_GUI;
    socketClass * socketUtil; //objekt pre komunikáciu cez socket
    dbConnectorClass *dbUtil;
    
};

#endif	/* SERVERCLASS_H */

