/*
 * File:   serverForm.cpp
 * Author: root
 *
 * Created on Pondelok, 2015, január 5, 23:20
 */

#include "serverForm.h"
#include "dbConnectorClass.h"

#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

serverForm::serverForm() {
    widget.setupUi(this);
    widget.infoLabel->setText("");
    widget.portEdit->setText("17005");
    widget.maxAgentEdit->setText("5");
    widget.agentCountLabel->setText("0");
    widget.startMappingButton->setEnabled(false);
    widget.stopMappingButton->setEnabled(false);
    
    socketUtil = new socketClass();
    
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);
    std::string str1 ("wlan0");
    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
            if (str1.compare(ifa->ifa_name)==0) {
                widget.ipLabel->setText(addressBuffer);
            }
        } else if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
        } 
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
}

void serverForm::startServerClicked() {
    std::cout << "startServerClicked\n";
    
    socketUtil->setPortNumber(widget.portEdit->text().toInt());
    socketUtil->connect();
    
    if (socketUtil->getConnected()) {
        widget.portEdit->setEnabled(false);
        widget.maxAgentEdit->setEnabled(false);
        widget.startMappingButton->setEnabled(true);
        widget.stopMappingButton->setEnabled(false);
        widget.startServerButton->setEnabled(false);
        
        // TODO spustit nove vlakno na cakanie

        serverStarted = true;
        widget.infoLabel->setText("Server uspesne spusteny");
    } else {
        std::cout << "failed to start server\n";
        widget.infoLabel->setText("Nepodarilo sa spustit server");
    }
    
//    dbConnectorClass *db = new dbConnectorClass();
//    //std::cout << "connected " << db->isConnected() << "\n";
//    //std::cout << "newSpustenieId " << db->getNewSpustenieId() << "\n";
//    //std::cout << "newPrekazkaId " << db->getNewPrekazkaId(18) << "\n";
//    //db->test();
//    delete db;
}

void serverForm::startMappingClicked() {
    std::cout << "startMappingClicked\n";
    
    if (!serverStarted) {
        widget.infoLabel->setText("Najskor spustite server");
        return;
    }
    if (mappingNow) {
        widget.infoLabel->setText("Uz prebieha mapovanie");
        return;
    }
    
    mappingNow = true;
    widget.infoLabel->setText("Mapovanie spustene");
    widget.startMappingButton->setEnabled(false);
    widget.stopMappingButton->setEnabled(true);
    
    
    char buf[256];
    int newFd = socketUtil->waitAndAcceptClient();
    socketUtil->receiveJson(newFd, buf, 255);
    std::cout << buf;
    socketUtil->sendJson(newFd, "i got it!");
}

void serverForm::stopMappingClicked() {
    std::cout << "stopMappingClicked\n";
    
    if (!serverStarted) {
        widget.infoLabel->setText("Najskor spustite server");
        return;
    }
    if (!mappingNow) {
        widget.infoLabel->setText("Neprebieha ziadne mapovanie");
        return;
    }
    
    mappingNow = false;
    widget.infoLabel->setText("Mapovanie ukoncene");
    widget.startMappingButton->setEnabled(true);
    widget.stopMappingButton->setEnabled(false);
}

serverForm::~serverForm() {
    std::cout << "destruktor serverForm\n";
    //ak je server spusteny tak ho zastavime
    //ak prebieha mapovanie tak ho ukoncime
    if (serverStarted) {
        if (mappingNow) {
            // TODO zastavime mapovanie
        }
        // TODO ukoncime server
        delete socketUtil;
    }
}
