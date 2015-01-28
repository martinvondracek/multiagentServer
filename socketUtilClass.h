/* 
 * File:   socketUtilClass.h
 * Author: root
 *
 * Created on Streda, 2015, január 28, 9:58
 */

#ifndef SOCKETUTILCLASS_H
#define	SOCKETUTILCLASS_H

#include <rapidjson/document.h>
#include <cstdio>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <iostream>

class socketUtilClass {
public:
    socketUtilClass();
    virtual ~socketUtilClass();
    
    static const char *  createJsonAgentId_IdSpustenia(int id, int idSpustenia);
private:

};

#endif	/* SOCKETUTILCLASS_H */

