/* 
 * File:   prekazkaClass.cpp
 * Author: root
 * 
 * Created on Sobota, 2015, január 24, 10:45
 */

#include "prekazkaClass.h"

prekazkaClass::prekazkaClass(int id, int id_spustenia, int prekazka, int robot,
        float x_rob, float y_rob, float fi_rob, float x_p, float y_p,
        bool naraz_vpravo, bool naraz_vlavo, bool naraz_vpredu) {
    this->id = id;
    this->id_spustenia = id_spustenia;
    this->prekazka = prekazka;
    this->robot = robot;
    this->x_rob = x_rob;
    this->y_rob = y_rob;
    this->fi_rob = fi_rob;
    this->x_p = x_p;
    this->y_p = y_p;
    this->naraz_vpravo = naraz_vpravo;
    this->naraz_vlavo = naraz_vlavo;
    this->naraz_vpredu = naraz_vpredu;
}

float prekazkaClass::GetFi_rob() const {
    return fi_rob;
}

void prekazkaClass::SetFi_rob(float fi_rob) {
    this->fi_rob = fi_rob;
}

int prekazkaClass::GetId() const {
    return id;
}

void prekazkaClass::SetId(int id) {
    this->id = id;
}

int prekazkaClass::GetId_spustenia() const {
    return id_spustenia;
}

void prekazkaClass::SetId_spustenia(int id_spustenia) {
    this->id_spustenia = id_spustenia;
}

bool prekazkaClass::IsNaraz_vlavo() const {
    return naraz_vlavo;
}

void prekazkaClass::SetNaraz_vlavo(bool naraz_vlavo) {
    this->naraz_vlavo = naraz_vlavo;
}

bool prekazkaClass::IsNaraz_vpravo() const {
    return naraz_vpravo;
}

void prekazkaClass::SetNaraz_vpravo(bool naraz_vpravo) {
    this->naraz_vpravo = naraz_vpravo;
}

bool prekazkaClass::IsNaraz_vpredu() const {
    return naraz_vpredu;
}

void prekazkaClass::SetNaraz_vpredu(bool naraz_vpredu) {
    this->naraz_vpredu = naraz_vpredu;
}

int prekazkaClass::GetPrekazka() const {
    return prekazka;
}

void prekazkaClass::SetPrekazka(int prekazka) {
    this->prekazka = prekazka;
}

int prekazkaClass::GetRobot() const {
    return robot;
}

void prekazkaClass::SetRobot(int robot) {
    this->robot = robot;
}

float prekazkaClass::GetX_p() const {
    return x_p;
}

void prekazkaClass::SetX_p(float x_p) {
    this->x_p = x_p;
}

float prekazkaClass::GetX_rob() const {
    return x_rob;
}

void prekazkaClass::SetX_rob(float x_rob) {
    this->x_rob = x_rob;
}

float prekazkaClass::GetY_p() const {
    return y_p;
}

void prekazkaClass::SetY_p(float y_p) {
    this->y_p = y_p;
}

float prekazkaClass::GetY_rob() const {
    return y_rob;
}

void prekazkaClass::SetY_rob(float y_rob) {
    this->y_rob = y_rob;
}

prekazkaClass::~prekazkaClass() {
}

