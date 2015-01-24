/* 
 * File:   polohaClass.cpp
 * Author: root
 * 
 * Created on Sobota, 2015, január 24, 10:45
 */

#include "polohaClass.h"

polohaClass::polohaClass(int id, int id_spustenia, int robot, float x, float y, float fi) {
    this->id = id;
    this->id_spustenia = id_spustenia;
    this->robot = robot;
    this->x = x;
    this->y = y;
    this->fi = fi;
}

float polohaClass::GetFi() {
    return fi;
}

void polohaClass::SetFi(float fi) {
    this->fi = fi;
}

int polohaClass::GetId() {
    return id;
}

void polohaClass::SetId(int id) {
    this->id = id;
}

int polohaClass::GetId_spustenia() {
    return id_spustenia;
}

void polohaClass::SetId_spustenia(int id_spustenia) {
    this->id_spustenia = id_spustenia;
}

int polohaClass::GetRobot() {
    return robot;
}

void polohaClass::SetRobot(int robot) {
    this->robot = robot;
}

float polohaClass::GetX() {
    return x;
}

void polohaClass::SetX(float x) {
    this->x = x;
}

float polohaClass::GetY() {
    return y;
}

void polohaClass::SetY(float y) {
    this->y = y;
}

polohaClass::~polohaClass() {
}

