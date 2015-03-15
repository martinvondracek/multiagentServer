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

class SocketUtil {
public:
    SocketUtil();
    virtual ~SocketUtil();
    
    static const char *  createJsonAgentId_IdSpustenia(int id, int idSpustenia);
    static const char *  createJsonIdSpustenia(int idSpustenia);
    static const char *  createJsonNewIdPrekazky(int idPrekazky);
    static const char *  createJsonServerQuit();
    static const char *  createJsonStartMapping();
    static const char *  createJsonStopMapping();
    
    static std::string parseClassTypeFromJson(const char *json);
    static int parseIdFromQuit(const char *json);
private:

};

#endif	/* SOCKETUTILCLASS_H */

