/* 
 * File:   socketClass.h
 * Author: root
 *
 * Created on Streda, 2015, január 7, 21:08
 * 
 * connector to socket
 * for communication via tcp/ip socket
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

class SocketConnector {
public:
    SocketConnector();
    SocketConnector(int portNum);
    virtual ~SocketConnector();
    
    int connect(); // connects to socket
    int disconnect(); // disconnects from socket
    int disconnectFd(int sockfd); // disconnects from given sockfd
    //int sendJson(int sockfd, const char *jsonData);
    int sendJson(int sockfd, std::string jsonData); // sends json as string
    int receiveJson(int sockfd, char *buffer, int bufSize); //receives json as string
    int waitAndAcceptClient(); // waits and accepts new agent
    
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

