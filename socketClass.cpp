/* 
 * File:   socketClass.cpp
 * Author: root
 * 
 * Created on Streda, 2015, január 7, 21:08
 */

#include "socketClass.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

socketClass::socketClass() {
    this->portNumber = 17005;
}

socketClass::socketClass(int portNum) {
    this->portNumber = portNum;
}

bool socketClass::getConnected() {
    return this->connected;
}

int socketClass::getPortNumber() {
    return this->portNumber;
}

void socketClass::setPortNumber(int portNum) {
    this->portNumber = portNum;
}

int socketClass::connect() {
    std::cout << "starting socket localhost, port: " << portNumber << "\n";
    
    // TODO implementovat
    connected = true;
}

void socketClass::test() {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) std::cerr << "error opening socket";
    bzero((char *) &serv_addr, sizeof (serv_addr));
    portno = 17005; //portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof (serv_addr)) < 0) std::cerr << "ERROR on binding";
    //std::cout << "serv_addr" << inet_ntoa(serv_addr.sin_addr) << "\n";
    listen(sockfd, 5);
    clilen = sizeof (cli_addr);
    using namespace std;
    newsockfd = accept(sockfd,
            (struct sockaddr *) &cli_addr,
            &clilen);
    if (newsockfd < 0) std::cerr << "ERROR on accept";
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);
    if (n < 0) std::cerr << "ERROR reading from socket";
    printf("Here is the message: %s\n", buffer);
    n = write(newsockfd, "I got your message", 18);
    if (n < 0) std::cerr << "ERROR writing to socket";
    close(newsockfd);
    close(sockfd);
}

socketClass::~socketClass() {
}

