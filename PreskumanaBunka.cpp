/* 
 * File:   PreskumanaBunka.cpp
 * Author: root
 * 
 * Created on Nedeľa, 2015, marec 29, 9:37
 */

#include "PreskumanaBunka.h"

PreskumanaBunka::PreskumanaBunka(int id, int idSpustenia, int x0, int y0, int radius, int n, int rozmerBunky, int k, int l, bool obsadene) {
    this->id = id;
    this->idSpustenia = idSpustenia;
    this->x0 = x0;
    this->y0 = y0;
    this->radius = radius;
    this->n = n;
    this->rozmerBunky = rozmerBunky;
    this->k = k;
    this->l = l;
    this->obsadene = obsadene;
}

int PreskumanaBunka::GetId() {
    return id;
}

void PreskumanaBunka::SetId(int id) {
    this->id = id;
}

int PreskumanaBunka::GetIdSpustenia() {
    return idSpustenia;
}

void PreskumanaBunka::SetIdSpustenia(int idSpustenia) {
    this->idSpustenia = idSpustenia;
}

int PreskumanaBunka::GetK() {
    return k;
}

void PreskumanaBunka::SetK(int k) {
    this->k = k;
}

int PreskumanaBunka::GetL() {
    return l;
}

void PreskumanaBunka::SetL(int l) {
    this->l = l;
}

int PreskumanaBunka::GetN() {
    return n;
}

void PreskumanaBunka::SetN(int n) {
    this->n = n;
}

bool PreskumanaBunka::IsObsadene() {
    return obsadene;
}

void PreskumanaBunka::SetObsadene(bool obsadene) {
    this->obsadene = obsadene;
}

int PreskumanaBunka::GetRadius() {
    return radius;
}

void PreskumanaBunka::SetRadius(int radius) {
    this->radius = radius;
}

int PreskumanaBunka::GetRozmerBunky() {
    return rozmerBunky;
}

void PreskumanaBunka::SetRozmerBunky(int rozmerBunky) {
    this->rozmerBunky = rozmerBunky;
}

int PreskumanaBunka::GetX0() {
    return x0;
}

void PreskumanaBunka::SetX0(int x0) {
    this->x0 = x0;
}

int PreskumanaBunka::GetY0() {
    return y0;
}

void PreskumanaBunka::SetY0(int y0) {
    this->y0 = y0;
}

PreskumanaBunka::~PreskumanaBunka() {
}

