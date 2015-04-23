/* 
 * File:   polohaClass.cpp
 * Author: root
 * 
 * Created on Sobota, 2015, január 24, 10:45
 */

#include "Poloha.h"

Poloha::Poloha(int id, int id_spustenia, int robot, float x, float y, float fi) {
    this->id = id;
    this->id_spustenia = id_spustenia;
    this->robot = robot;
    this->x = x;
    this->y = y;
    this->fi = fi;
}

float Poloha::GetFi() {
    return fi;
}

void Poloha::SetFi(float fi) {
    this->fi = fi;
}

int Poloha::GetId() {
    return id;
}

void Poloha::SetId(int id) {
    this->id = id;
}

int Poloha::GetId_spustenia() {
    return id_spustenia;
}

void Poloha::SetId_spustenia(int id_spustenia) {
    this->id_spustenia = id_spustenia;
}

int Poloha::GetRobot() {
    return robot;
}

void Poloha::SetRobot(int robot) {
    this->robot = robot;
}

float Poloha::GetX() {
    return x;
}

void Poloha::SetX(float x) {
    this->x = x;
}

float Poloha::GetY() {
    return y;
}

void Poloha::SetY(float y) {
    this->y = y;
}

const char * Poloha::toJson() {
    std::string pom;
    
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"POLOHACLASS\"");
    
    json.append(",\n\"ID\" : ");
    json.append(std::to_string(id));
    
    json.append(",\n\"ID_SPUSTENIA\" : ");
    json.append(std::to_string(id_spustenia));
    
    json.append(",\n\"ROBOT\" : ");
    json.append(std::to_string(robot));
    
    json.append(",\n\"X\" : ");
    pom = std::to_string(x);
    std::replace( pom.begin(), pom.end(), ',', '.');
    json.append(pom);
    
    json.append(",\n\"Y\" : ");
    pom = std::to_string(y);
    std::replace( pom.begin(), pom.end(), ',', '.');
    json.append(pom);
    
    json.append(",\n\"FI\" : ");
    pom = std::to_string(fi);
    std::replace( pom.begin(), pom.end(), ',', '.');
    json.append(pom);
    
    json.append("\n}\n");
        
    return json.c_str();
}

Poloha * Poloha::fromJson(const char *json) {
    int id;
    int id_spustenia;
    int robot;
    float x;
    float y;
    float fi;
    
    rapidjson::Document document;
    document.Parse<0>(json);
    
    id = document["ID"].GetInt();
    id_spustenia = document["ID_SPUSTENIA"].GetInt();
    robot = document["ROBOT"].GetInt();
    x = document["X"].GetDouble();
    y = document["Y"].GetDouble();
    fi = document["FI"].GetDouble();
    
    return new Poloha(id, id_spustenia, robot, x, y, fi);
}

float Poloha::getVzdialenost(Poloha *p2) {
    return sqrt((x-p2->GetX())*(x-p2->GetX()) + (y-p2->GetY())*(y-p2->GetY()));
}

float Poloha::getVzdialenost(KoordinacnaSur *koorSur) {
    return sqrt((x-koorSur->GetX())*(x-koorSur->GetX()) + (y-koorSur->GetY())*(y-koorSur->GetY()));
}

const char * Poloha::toString() {
    return toJson();
}

Poloha::~Poloha() {
}

