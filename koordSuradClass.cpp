/* 
 * File:   koordSuradClass.cpp
 * Author: root
 * 
 * Created on Nedeľa, 2015, február 8, 15:53
 */

#include "koordSuradClass.h"

koordSuradClass::koordSuradClass(float x, float y) {
    this->x = x;
    this->y = y;
}

const char * koordSuradClass::toJson() {
    std::string pom;
    
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"KOORDINACNA_SURADNICA\"");
    
    json.append(",\n\"X\" : ");
    pom = std::to_string(x);
    std::replace( pom.begin(), pom.end(), ',', '.');
    json.append(pom);
    
    json.append(",\n\"Y\" : ");
    pom = std::to_string(y);
    std::replace( pom.begin(), pom.end(), ',', '.');
    json.append(pom);
    
    json.append("\n}\n");
        
    return json.c_str();
}

koordSuradClass * koordSuradClass::fromJson(const char *json) {
    float x;
    float y;
    
    rapidjson::Document document;
    document.Parse<0>(json);
    
    x = document["X"].GetDouble();
    y = document["Y"].GetDouble();
    
    return new koordSuradClass(x, y);
}

const char * koordSuradClass::toString() {
    return toJson();
}

float koordSuradClass::getX() {
    return x;
}

void koordSuradClass::setX(float x) {
    this->x = x;
}

float koordSuradClass::getY() {
    return y;
}

void koordSuradClass::setY(float y) {
    this->y = y;
}

koordSuradClass::~koordSuradClass() {
}

