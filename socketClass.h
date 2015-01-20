/* 
 * File:   socketClass.h
 * Author: root
 *
 * Created on Streda, 2015, január 7, 21:08
 */

#ifndef SOCKETCLASS_H
#define	SOCKETCLASS_H

class socketClass {
public:
    socketClass();
    socketClass(int portNum);
    virtual ~socketClass();
    
    int connect();
    int disconnect();
    int sendPacket();
    int receivePacket();
    int waitForClient();
    
    bool getConnected();
    int getPortNumber();
    void setPortNumber(int portNum);
    
    void test();
private:
    bool connected = false;
    int portNumber;
};

#endif	/* SOCKETCLASS_H */

