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
    return 0;
}

int socketClass::disconnectFd(int sockfd) {
    close(sockfd);
    return 0;
}

int socketClass::sendJson(int sockfd, const char *jsonData) {
    int n;
    
    n = write(sockfd, jsonData, strlen(jsonData));
    if (n < 0) {
        std::cout << "ERROR writing to socket\n";
        return -1;
    }
    return n; // vratime pocet poslanych
}

const char * socketClass::receiveJson(int sockfd, char *buffer, int bufSize) {
    int n;
    
    bzero(buffer, bufSize);
    n = read(sockfd, buffer, bufSize);
    if (n < 0) {
        std::cout << "ERROR reading from socket";
    }
    printf("Here is the message: %s\n", buffer);
    return buffer;
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
    std::cout << "destruktor socketClass\n";
    disconnect();
}

