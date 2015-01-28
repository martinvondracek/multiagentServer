/* 
 * File:   socketUtilClass.cpp
 * Author: root
 * 
 * Created on Streda, 2015, január 28, 9:58
 */

#include "socketUtilClass.h"

socketUtilClass::socketUtilClass() {
}

const char *  socketUtilClass::createJsonAgentId(int id) {
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"AGENTID\"");
    
    json.append(",\n\"ID\" : ");
    json.append(std::to_string(id));
    
    json.append("\n}\n");
        
    return json.c_str();
}

socketUtilClass::~socketUtilClass() {
}

