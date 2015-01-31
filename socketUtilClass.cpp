/* 
 * File:   socketUtilClass.cpp
 * Author: root
 * 
 * Created on Streda, 2015, január 28, 9:58
 */

#include "socketUtilClass.h"

socketUtilClass::socketUtilClass() {
}

const char *  socketUtilClass::createJsonAgentId_IdSpustenia(int id, int idSpustenia) {
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"AGENTID\"");
    
    json.append(",\n\"ID\" : ");
    json.append(std::to_string(id));
    
    json.append(",\n\"ID_SPUSTENIA\" : ");
    json.append(std::to_string(idSpustenia));
    
    json.append("\n}\n");
        
    return json.c_str();
}

const char *  socketUtilClass::createJsonServerQuit() {
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"SERVER_QUIT\"");
    
    json.append("\n}\n");
        
    return json.c_str();
}

const char * socketUtilClass::parseClassTypeFromJson(const char *json) {
    rapidjson::Document document;
    document.Parse<0>(json);
    
    std::string ctype = document["CLASSTYPE"].GetString();
    
    return ctype.c_str();
}

int socketUtilClass::parseIdFromQuit(const char *json) {
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

socketUtilClass::~socketUtilClass() {
}

