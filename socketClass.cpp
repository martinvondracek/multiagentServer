/* 
 * File:   socketClass.cpp
 * Author: root
 * 
 * Created on Streda, 2015, január 7, 21:08
 */

#include "socketClass.h"

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
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //vytvori novy socket
    if (sockfd < 0) {
        std::cout << "error opening socket\n";
        return -1;
    }
    bzero((char *) &serv_addr, sizeof (serv_addr)); //sets all values in a buffer to zero
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNumber); //converts a port number in host byte order to a port number in network byte order
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) { // naviaze socket na adresu
        std::cout << "ERROR on binding\n";
        return -1;
    }
    listen(sockfd, 5); //kolko moze cakat na spojenie
    
    std::cout << "server started on port " << portNumber << "\n";
    connected = true;
    return 0;
}

int socketClass::disconnect() {
    // todo odpojime zo socketu ak je pripojeny
    if (!connected) {
        return -1;
    }
    
    close(sockfd);
    connected = false;
    std::cout << "server stopped\n";
    return 0;
}

int socketClass::disconnectFd(int sockfd) {
    close(sockfd);
    return 0;
}

int socketClass::sendJson(int sockfd, const char *jsonData) {
    std::string str2 = jsonData;
    int n;
    
    std::string str = "";
    str.append(str2);
    str.append("KKK");
    const char * data = str.c_str();
    n = write(sockfd, data, strlen(data));
    usleep(10*1000);
    if (n < 0) {
        std::cout << "ERROR writing to socket\n";
        return -1;
    }
    return n; // vratime pocet poslanych
}

int socketClass::receiveJson(int sockfd, char *buffer, int bufSize) {
    int n;
    
    bzero(buffer, bufSize);
    n = read(sockfd, buffer, bufSize);
    if (n < 0) {
        std::cout << "ERROR reading from socket";
        return n;
    }
    //printf("Here is the message: %s\n", buffer);
    return n;
}

int socketClass::waitAndAcceptClient() {
    if (!connected) {
        return -1;
    }
    
    int newSockfd;
    socklen_t clilen; //velkost adresy clienta
    struct sockaddr_in cli_addr;
    
    clilen = sizeof (cli_addr);
    newSockfd = accept(sockfd,
            (struct sockaddr *) &cli_addr,
            &clilen);
    if (newSockfd < 0) {
        std::cout << "ERROR on accept\n";
    }
    
    return newSockfd;
}

void socketClass::test() {
    int newsoc = waitAndAcceptClient();
    char buf[256];
    receiveJson(newsoc, buf, 255);
    std::cout << buf << "\n";
    sendJson(newsoc, "I got your message");
    close(newsoc);
}

socketClass::~socketClass() {
    std::cout << "destruktor socketClass\n";
    disconnect();
}

