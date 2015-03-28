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
    n*=2;
    
    this->pole = new bool[n*n];
    for(int i=0; i<(n*n); i++) {
        pole[i] = false;
    }
    
}

void PreskumaneOblasti::addPoloha(Poloha *poloha) {
    int k;
    int l;
    
    l =(int) (trunc(poloha->GetX())-x0)/1000 + n/2;
    if ((poloha->GetX()-x0)-(trunc((poloha->GetX()-x0)/1000)*1000) < 0) {
        l--;
    }
    if (l>n-1) l=n-1;
    if (l<0) l=0;
    
    k = (int) (trunc(poloha->GetY())-y0)/1000 + n/2;
    if ((poloha->GetY()-y0)-(trunc((poloha->GetY()-y0)/1000)*1000) < 0) {
        k--;
    }
    if (k>n-1) k=n-1;
    if (k<0) k=0;
    
    if (k>=0 && k<n && l>=0 && l<n) {
        pole[k*n+l]=true;
    }
}

bool PreskumaneOblasti::isCovered(int x, int y) {
    if (x>=0 && x<n && y>=0 && y<n) {
        return pole[y*n+x];
    } else {
        return false;
    }
}

bool PreskumaneOblasti::isCovered(Poloha *poloha) {
    int k;
    int l;
    
    l =(int) (trunc(poloha->GetX())-x0)/1000 + n/2;
    if ((poloha->GetX()-x0)-(trunc((poloha->GetX()-x0)/1000)*1000) < 0) {
        l--;
    }
    if (l>n-1) l=n-1;
    if (l<0) l=0;
    
    k = (int) (trunc(poloha->GetY())-y0)/1000 + n/2;
    if ((poloha->GetY()-y0)-(trunc((poloha->GetY()-y0)/1000)*1000) < 0) {
        k--;
    }
    if (k>n-1) k=n-1;
    if (k<0) k=0;
    
    return pole[k*n+l];
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

void PreskumaneOblasti::print() {
    for (int j=n-1; j>=0; j--) {
        for (int i=0; i<n; i++) {
            std::cout << pole[j*n + i] << " ";
        }
        std::cout << "\n";
    }
}

PreskumaneOblasti::~PreskumaneOblasti() {
}

