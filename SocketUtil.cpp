/* 
 * File:   socketUtilClass.cpp
 * Author: root
 * 
 * Created on Streda, 2015, január 28, 9:58
 */

#include "SocketUtil.h"

SocketUtil::SocketUtil() {
}

std::string  SocketUtil::createJsonAgentId_IdSpustenia(int id, int idSpustenia) {
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"AGENTID\"");
    
    json.append(",\n\"ID\" : ");
    json.append(std::to_string(id));
    
    json.append(",\n\"ID_SPUSTENIA\" : ");
    json.append(std::to_string(idSpustenia));
    
    json.append("\n}\n");
        
    return json;
}

std::string  SocketUtil::createJsonIdSpustenia(int idSpustenia) {
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"ID_SPUSTENIA\"");
    
    json.append(",\n\"ID_SPUSTENIA\" : ");
    json.append(std::to_string(idSpustenia));
    
    json.append("\n}\n");
        
    return json;
}

std::string  SocketUtil::createJsonNewIdPrekazky(int idPrekazky) {
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"NEW_ID_PREKAZKY\"");
    
    json.append(",\n\"ID_PREKAZKY\" : ");
    json.append(std::to_string(idPrekazky));
    
    json.append("\n}\n");
        
    return json;
}

std::string  SocketUtil::createJsonServerQuit() {
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"SERVER_QUIT\"");
    
    json.append("\n}\n");
        
    return json;
}

std::string  SocketUtil::createJsonStartMapping() {
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"SPUSTIT_MAPOVANIE\"");
    
    json.append("\n}\n");
        
    return json;
}

std::string  SocketUtil::createJsonStopMapping() {
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"STOP_MAPOVANIE\"");
    
    json.append("\n}\n");
        
    return json;
}

std::string SocketUtil::parseClassTypeFromJson(const char *json) {
    rapidjson::Document document;
    document.Parse<0>(json);
    
    std::string ctype = document["CLASSTYPE"].GetString();
    //std::cout << "classtype=" << ctype.c_str() << "\n";
    
    return ctype;
}

int SocketUtil::parseIdFromQuit(const char *json) {
    int id;
    
    rapidjson::Document document;
    document.Parse<0>(json);
    
    std::string ctype = document["CLASSTYPE"].GetString();
    if (ctype.compare("QUIT") == 0) {
        id = document["ID"].GetInt();
        return id;
    } else {
        return -1;
    }
}

int SocketUtil::parseAgentIdFromInvalidKoorSur(const char *json) {
    int id;
    
    rapidjson::Document document;
    document.Parse<0>(json);
    
    std::string ctype = document["CLASSTYPE"].GetString();
    if (ctype.compare("INVALID_KOOR_SUR") == 0) {
        id = document["AGENTID"].GetInt();
        return id;
    } else {
        return -1;
    }
}

SocketUtil::~SocketUtil() {
}

