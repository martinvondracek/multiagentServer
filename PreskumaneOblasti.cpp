/* 
 * File:   PreskumaneOblasti.cpp
 * Author: root
 * 
 * Created on Utorok, 2015, marec 24, 23:10
 */

#include "CoveredAreas.h"

CoveredAreas::CoveredAreas(int x, int y, int radius, int idSpustnia) {
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

void CoveredAreas::addPosition(Position *poloha) {
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

bool CoveredAreas::isCovered(int x, int y) {
    m.lock();
    if ((x>=0 && x<n) && (y>=0 && y<n)) {
        m.unlock();
        return pole[y*n+x];
    } else {
        std::cout << "zla suradnica v isCovered\n";
        m.unlock();
        return false;
    }
}

bool CoveredAreas::isCovered(Position *poloha) {
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

bool CoveredAreas::isInTargetArea(int x, int y) {
    if ((x>=0 && x<n) && (y>=0 && y<n)) {
        return true;
    } else {
        std::cout << "zla suradnica v isInTargetArea\n";
        return false;
    }
}

bool CoveredAreas::isInTargetArea(Position *poloha) {
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
    
    if (k>=0 && k<n && l>=0 && l<=n) {
        return true;
    } else {
        return false;
    }
}

float CoveredAreas::getCoverage() {
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

int CoveredAreas::getRadius() {
    return radius;
}

int CoveredAreas::getX() {
    return x0;
}

int CoveredAreas::getY() {
    return y0;
}


int CoveredAreas::getN() {
    return n;
}

int CoveredAreas::convertXtoL(int x) {
    int l = n/2;
    int pomX = x;
    
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
    
    if (l>n-1) l=n-1;
    if (l<0) l=0;
    
    return l;
}

int CoveredAreas::convertYtoK(int y) {
    int k = n/2;
    int pomY = y;
    
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
    
    return k;
}

int CoveredAreas::getStredBunkyX(int x, int y) {
    if (x < 0) {
        x = 0;
    }
    if (x >= n-1) {
        x = n -1;
    }
    
    // zistime x suradnicu stredu 0tej bunky
    int stred0 = (-1) * (n/2) * 1000 + 500;
    
    // vratime stred ntej bunky
    return stred0 + x*1000;
}

int CoveredAreas::getStredBunkyY(int x, int y) {
    if (y < 0) {
        y = 0;
    }
    if (y >= n-1) {
        y = n -1;
    }
    
    // zistime x suradnicu stredu 0tej bunky
    int stred0 = (-1) * (n/2) * 1000 + 500;
    
    // vratime stred ntej bunky
    return stred0 + y*1000;
}

void CoveredAreas::print() {
    m.lock();
    for (int j=n-1; j>=0; j--) {
        for (int i=0; i<n; i++) {
            std::cout << pole[j*n + i] << " ";
        }
        std::cout << "\n";
    }
    m.unlock();
}

void CoveredAreas::addInaccesibleKoorSur(CoordinationPosition *sur) {
    m.lock();
    inaccesibleList.push_back(sur);
    m.unlock();
}

bool CoveredAreas::isAccesible(CoordinationPosition *sur) {
    std::list<CoordinationPosition*>::iterator i;
    for (i = inaccesibleList.begin(); i != inaccesibleList.end(); ++i) {
        if ((*i)->equals(sur)) {
            return false;
        }
    }
    return true;
}

std::list<CoveredArea*> CoveredAreas::toList() {
    m.lock();
    std::list<CoveredArea*> list;
    for (int j=n-1; j>=0; j--) {
        for (int i=0; i<n; i++) {
            list.push_back(new CoveredArea(0, idSpustnia, x0, y0, radius, n, rozmerBunky, i, j, pole[j*n + i]));
        }
    }
    m.unlock();
    return list;
}

CoveredAreas::~CoveredAreas() {
    m.lock();
    m.unlock();
}

