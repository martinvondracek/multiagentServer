/* 
 * File:   PreskumanaBunka.cpp
 * Author: root
 * 
 * Created on Nedeľa, 2015, marec 29, 9:37
 */

#include "CoveredArea.h"

CoveredArea::CoveredArea(int id, int idSpustenia, int x0, int y0, int radius, int n, int rozmerBunky, int k, int l, bool obsadene) {
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

int CoveredArea::GetId() {
    return id;
}

void CoveredArea::SetId(int id) {
    this->id = id;
}

int CoveredArea::GetIdMapping() {
    return idSpustenia;
}

void CoveredArea::SetIdMapping(int idSpustenia) {
    this->idSpustenia = idSpustenia;
}

int CoveredArea::GetK() {
    return k;
}

void CoveredArea::SetK(int k) {
    this->k = k;
}

int CoveredArea::GetL() {
    return l;
}

void CoveredArea::SetL(int l) {
    this->l = l;
}

int CoveredArea::GetN() {
    return n;
}

void CoveredArea::SetN(int n) {
    this->n = n;
}

bool CoveredArea::IsCovered() {
    return obsadene;
}

void CoveredArea::SetCovered(bool obsadene) {
    this->obsadene = obsadene;
}

int CoveredArea::GetRadius() {
    return radius;
}

void CoveredArea::SetRadius(int radius) {
    this->radius = radius;
}

int CoveredArea::GetRozmerBunky() {
    return rozmerBunky;
}

void CoveredArea::SetRozmerBunky(int rozmerBunky) {
    this->rozmerBunky = rozmerBunky;
}

int CoveredArea::GetX0() {
    return x0;
}

void CoveredArea::SetX0(int x0) {
    this->x0 = x0;
}

int CoveredArea::GetY0() {
    return y0;
}

void CoveredArea::SetY0(int y0) {
    this->y0 = y0;
}

CoveredArea::~CoveredArea() {
}

