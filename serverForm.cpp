/*
 * File:   serverForm.cpp
 * Author: root
 *
 * Created on Pondelok, 2015, január 5, 23:20
 */

#include "serverForm.h"

serverForm::serverForm() {
    widget.setupUi(this);
    widget.infoLabel->setText("");
    widget.portEdit->setText("17005");
    widget.maxAgentEdit->setText("5");
    widget.agentCountLabel->setText("0");
    widget.startMappingButton->setEnabled(false);
    widget.stopMappingButton->setEnabled(false);
    
    shm_S_GUI = new komunikacia_shm;
    shm_S_GUI->ukonci_ulohu = 0;
    shm_S_GUI->mappingNow = 0;
    shm_S_GUI->widget = &widget;
    server = new serverClass(shm_S_GUI);
    
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
    
    server->startServer(widget.portEdit->text().toInt(), widget.maxAgentEdit->text().toInt());
    if (server->isServerRunning()) {
        widget.portEdit->setEnabled(false);
        widget.maxAgentEdit->setEnabled(false);
        widget.startMappingButton->setEnabled(false);
        widget.stopMappingButton->setEnabled(false);
        widget.startServerButton->setEnabled(false);
        widget.infoLabel->setText("Server uspesne spusteny");
    } else {
        std::cout << "failed to start server\n";
        widget.infoLabel->setText("Nepodarilo sa spustit server");
    }
}

void serverForm::startMappingClicked() {
    std::cout << "startMappingClicked\n";
    
    if (!server->isServerRunning()) {
        widget.infoLabel->setText("Najskor spustite server");
        return;
    }
    if (server->isMapping()) {
        widget.infoLabel->setText("Uz prebieha mapovanie");
        return;
    }
    
    server->doMapping();
    
    shm_S_GUI->ukonci_ulohu = false;
    shm_S_GUI->mappingNow = true;
    
    widget.infoLabel->setText("Mapovanie spustene");
    widget.startMappingButton->setEnabled(false);
    widget.stopMappingButton->setEnabled(true);
    
}

void serverForm::stopMappingClicked() {
    std::cout << "stopMappingClicked\n";
    
    if (!server->isServerRunning()) {
        widget.infoLabel->setText("Najskor spustite server");
        return;
    }
    if (!server->isMapping()) {
        widget.infoLabel->setText("Neprebieha ziadne mapovanie");
        return;
    }
    
    shm_S_GUI->ukonci_ulohu = true;
    server->stopMapping();
    usleep(1000*1000);
    shm_S_GUI->mappingNow = false;
    widget.infoLabel->setText("Mapovanie ukoncene");
    if (shm_S_GUI->connectedAgentsCount > 0) {
        widget.startMappingButton->setEnabled(true);
    }
    widget.stopMappingButton->setEnabled(false);
    
}

serverForm::~serverForm() {
    std::cout << "destruktor serverForm\n";
    //ak je server spusteny tak ho zastavime
    //ak prebieha mapovanie tak ho ukoncime
    if (server->isServerRunning()) {
        if (server->isMapping()) {
            stopMappingClicked();
            usleep(500*1000);
        }
    }
    delete server;
    delete shm_S_GUI;
}
