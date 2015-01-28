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

socketUtilClass::~socketUtilClass() {
}

