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
    
    static std::string  createJsonAgentId_IdSpustenia(int id, int idSpustenia); // creates agent his id and id of mapping
    static std::string  createJsonIdSpustenia(int idSpustenia); // creates agent new id of mapping
    static std::string  createJsonNewIdPrekazky(int idPrekazky); // creates agent new id of obstacle
    static std::string  createJsonServerQuit(); // creates agent server quits
    static std::string  createJsonStartMapping(); // creates json for starting mapping
    static std::string  createJsonStopMapping(); // creates json for stopping mapping
    
    static std::string parseClassTypeFromJson(const char *json); // parse type of json information
    static int parseIdFromQuit(const char *json); //parse id of agent that quits
    static int parseAgentIdFromInvalidKoorSur(const char *json); // parse agent id sending invalid coordiantion position
    static int parseAgentIdFromInaccesibleKoorSur(const char *json);// parse agent id sending inaccesible coordiantion position
private:

};

#endif	/* SOCKETUTILCLASS_H */

