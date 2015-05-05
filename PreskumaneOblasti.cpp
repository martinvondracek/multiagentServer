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
    m.lock();
    
    int k = n/2;
    int l = n/2;
    int pomY = poloha->GetY();
    int pomX = poloha->GetX();
    
    if (pomX > 0) {
        pomX -= 999;
        while (pomX > 0) {
            l++;
            pomX -= 1000;
        }
    } else if (pomX < 0) {
        pomX -= 1;
        while (pomX < 0) {
            l--;
            pomX += 1000;
        }
    }
    
    if (pomY > 0) {
        pomY -= 999;
        while (pomY > 0) {
            k++;
            pomY -= 1000;
        }
    } else if (pomY < 0) {
        pomY -= 1;
        while (pomY < 0) {
            k--;
            pomY += 1000;
        }
    }
    
    if (k>n-1) k=n-1;
    if (k<0) k=0;
    
    if (l>n-1) l=n-1;
    if (l<0) l=0;
    
    if (k>=0 && k<n && l>=0 && l<n) {
        pole[k*n+l]=true;
    }
    
    m.unlock();
}

bool PreskumaneOblasti::isCovered(int x, int y) {
    m.lock();
    if (x>=0 && x<n && y>=0 && y<n) {
        m.unlock();
        return pole[y*n+x];
    } else {
        m.unlock();
        return false;
    }
}

bool PreskumaneOblasti::isCovered(Poloha *poloha) {
    m.lock();
    int k = n/2;
    int l = n/2;
    int pomY = poloha->GetY();
    int pomX = poloha->GetX();
    
    if (pomX > 0) {
        pomX -= 999;
        while (pomX > 0) {
            l++;
            pomX -= 1000;
        }
    } else if (pomX < 0) {
        pomX -= 1;
        while (pomX < 0) {
            l--;
            pomX += 1000;
        }
    }
    
    if (pomY > 0) {
        pomY -= 999;
        while (pomY > 0) {
            k++;
            pomY -= 1000;
        }
    } else if (pomY < 0) {
        pomY -= 1;
        while (pomY < 0) {
            k--;
            pomY += 1000;
        }
    }
    
    if (k>n-1) k=n-1;
    if (k<0) k=0;
    
    if (l>n-1) l=n-1;
    if (l<0) l=0;
    
    m.unlock();
    return pole[k*n+l];
}

bool PreskumaneOblasti::isInTargetArea(int x, int y) {
    if (x>0 && x<n && y>0 && y<=n) {
        return true;
    } else {
        return false;
    }
}

bool PreskumaneOblasti::isInTargetArea(Poloha *poloha) {
    int k = n/2;
    int l = n/2;
    int pomY = poloha->GetY();
    int pomX = poloha->GetX();
    
    if (pomX > 0) {
        pomX -= 999;
        while (pomX > 0) {
            l++;
            pomX -= 1000;
        }
    } else if (pomX < 0) {
        pomX -= 1;
        while (pomX < 0) {
            l--;
            pomX += 1000;
        }
    }
    
    if (pomY > 0) {
        pomY -= 999;
        while (pomY > 0) {
            k++;
            pomY -= 1000;
        }
    } else if (pomY < 0) {
        pomY -= 1;
        while (pomY < 0) {
            k--;
            pomY += 1000;
        }
    }
    
    if (k>0 && k<n && l>0 && l<=n) {
        return true;
    } else {
        return false;
    }
}

float PreskumaneOblasti::getCoverage() {
    m.lock();
    int i;
    int count = 0;
    
    for(i=0; i<(n*n); i++) {
        if (pole[i]) {
            count++;
        }
    }
    
    m.unlock();
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
    m.lock();
    for (int j=n-1; j>=0; j--) {
        for (int i=0; i<n; i++) {
            std::cout << pole[j*n + i] << " ";
        }
        std::cout << "\n";
    }
    m.unlock();
}

std::list<PreskumanaBunka*> PreskumaneOblasti::toList() {
    m.lock();
    std::list<PreskumanaBunka*> list;
    for (int j=n-1; j>=0; j--) {
        for (int i=0; i<n; i++) {
            list.push_back(new PreskumanaBunka(0, idSpustnia, x0, y0, radius, n, rozmerBunky, i, j, pole[j*n + i]));
        }
    }
    m.unlock();
    return list;
}

PreskumaneOblasti::~PreskumaneOblasti() {
    m.lock();
    m.unlock();
}

