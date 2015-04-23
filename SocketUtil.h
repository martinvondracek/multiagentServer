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
    
    static std::string  createJsonAgentId_IdSpustenia(int id, int idSpustenia);
    static std::string  createJsonIdSpustenia(int idSpustenia);
    static std::string  createJsonNewIdPrekazky(int idPrekazky);
    static std::string  createJsonServerQuit();
    static std::string  createJsonStartMapping();
    static std::string  createJsonStopMapping();
    
    static std::string parseClassTypeFromJson(const char *json);
    static int parseIdFromQuit(const char *json);
    static int parseAgentIdFromInvalidKoorSur(const char *json);
private:

};

#endif	/* SOCKETUTILCLASS_H */

