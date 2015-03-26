/* 
 * File:   PreskumaneOblasti.cpp
 * Author: root
 * 
 * Created on Utorok, 2015, marec 24, 23:10
 */

#include "PreskumaneOblasti.h"

PreskumaneOblasti::PreskumaneOblasti(int x, int y, int radius, int idSpustnia) {
    this->x0 = x;
    this->y0 = y;
    this->radius = radius;
    this->idSpustnia = idSpustnia;
    
    if (radius%1000 > 0) {
        n = radius / 1000 + 1;
    } else {
        n = radius / 1000;
    }
}

void PreskumaneOblasti::addPoloha(Poloha *poloha) {
    int k;
    int l;
    
    if (floor(poloha->GetX())-x0 > 0) {
        l = (floor(poloha->GetX())-x0) + n/2 + 1;
    } else {
        l = (floor(poloha->GetX())-x0) + n/2;
    }
    
    if (floor(poloha->GetY())-x0 > 0) {
        k = (floor(poloha->GetY())-y0) + n/2 + 1;
    } else {
        k = (floor(poloha->GetY())-y0) + n/2;
    }
    
    if (k>=0 && k<=n && l>=0 && l<=n) {
        pole[k*n+l]=true;
    }
}

bool PreskumaneOblasti::isCovered(int x, int y) {
    if (x>=0 && x<=n && y>=0 && y<=n) {
        return pole[y*n+x];
    } else {
        return false;
    }
}

float PreskumaneOblasti::getCoverage() {
    int i;
    int count = 0;
    
    for(i=0; i<(n*n); i++) {
        if (pole[i]) {
            count++;
        }
    }
    
    return ((float)count) / (n*n) *100;
}

int PreskumaneOblasti::getRadius() {
    return radius;
}

int PreskumaneOblasti::getX() {
    return x0;
}

int PreskumaneOblasti::getY() {
    return y0;
}

PreskumaneOblasti::~PreskumaneOblasti() {
}

