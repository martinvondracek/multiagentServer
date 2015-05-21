/* 
 * File:   serverForm.h
 * Author: root
 *
 * Created on Pondelok, 2015, január 5, 23:20
 * 
 * GUI form
 */

#ifndef _SERVERFORM_H
#define	_SERVERFORM_H

#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <list>

#include "ui_serverForm.h"
#include "Server.h"


class serverForm : public QDialog {
    Q_OBJECT
public:
    serverForm();
    virtual ~serverForm();
public slots:
    void startServerClicked(); // starts server
    void startMappingClicked(); //starts mapping
    void stopMappingClicked(); // stops mapping
private:
    Ui::serverForm widget;
    
    Server *server;
    komunikacia_shm *shm_S_GUI; //shm between gui and server
};

#endif	/* _SERVERFORM_H */
