/* 
 * File:   koordSuradClass.cpp
 * Author: root
 * 
 * Created on Nedeľa, 2015, február 8, 15:53
 */

#include "KoordSurad.h"

KoordSurad::KoordSurad(float x, float y) {
    this->x = x;
    this->y = y;
}

const char * KoordSurad::toJson() {
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

KoordSurad * KoordSurad::fromJson(const char *json) {
    float x;
    float y;
    
    rapidjson::Document document;
    document.Parse<0>(json);
    
    x = document["X"].GetDouble();
    y = document["Y"].GetDouble();
    
    return new KoordSurad(x, y);
}

const char * KoordSurad::toString() {
    return toJson();
}

float KoordSurad::getX() {
    return x;
}

void KoordSurad::setX(float x) {
    this->x = x;
}

float KoordSurad::getY() {
    return y;
}

void KoordSurad::setY(float y) {
    this->y = y;
}

KoordSurad::~KoordSurad() {
}

