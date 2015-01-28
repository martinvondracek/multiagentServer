/* 
 * File:   socketClass.h
 * Author: root
 *
 * Created on Streda, 2015, január 7, 21:08
 */

#ifndef SOCKETCLASS_H
#define	SOCKETCLASS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <list>

class socketClass {
public:
    socketClass();
    socketClass(int portNum);
    virtual ~socketClass();
    
    int connect(); // pripoji sa na socket
    int disconnect(); // odpoji sa zo socketu
    int disconnectFd(int sockfd); // odpoji zadany sockFd
    int sendJson(int sockfd, const char *jsonData);
    int receiveJson(int sockfd, char *buffer, int bufSize);
    int waitAndAcceptClient();
    
    bool getConnected();
    int getPortNumber();
    void setPortNumber(int portNum);
    
    void test();
private:
    int sockfd;
    struct sockaddr_in serv_addr;
    
    bool connected = false;
    int portNumber; //cislo portu na ktorom server caka
};

#endif	/* SOCKETCLASS_H */

