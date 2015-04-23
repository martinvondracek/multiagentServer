/* 
 * File:   NavigaciaUtil.cpp
 * Author: root
 * 
 * Created on April 13, 2015, 9:03 PM
 */

#include "NavigaciaUtil.h"

NavigaciaUtil::NavigaciaUtil() {
}

void NavigaciaUtil::initializeKoorSuradnice(PreskumaneOblasti *oblasti, std::list<agent_in_shm> *agentsList){
    // todo vypocitame prvotne koor suradnice tak, ze
    // ich rozmiestnime rovnomerne na kruznici polomeru cieloveho radiusu
    
    int radius = oblasti->getRadius();
    int x_0 = oblasti->getX();
    int y_0 = oblasti->getY();
    int agentCount = agentsList->size();
    int krok = 360 / agentCount;
    
    // najskôr priradíme body postupne agentom
    int j = 0;
    std::list<agent_in_shm>::iterator i;
    
    while (j<agentCount) {
        int x = x_0 + radius * sin(j * krok * PI / 180) * (-1);
        int y = y_0 + radius * cos(j * krok * PI / 180);
        KoordinacnaSur *koor = new KoordinacnaSur(x, y);
        
        for (i = agentsList->begin(); i != agentsList->end(); ++i) {
            if (!i->koordinacnaSuradnica->isValid()) {
                i->koordinacnaSuradnica = koor;
                break;
            } else {
                if (i->aktPoloha->getVzdialenost(i->koordinacnaSuradnica) >
                        i->aktPoloha->getVzdialenost(koor)) {
                    
                    KoordinacnaSur *pom = i->koordinacnaSuradnica;
                    i->koordinacnaSuradnica = koor;
                    koor = pom;
                }
            }
        }
        j++;
    }
    
    // najskôr priradíme body postupne agentom
    /*int j = 0;
    std::list<agent_in_shm>::iterator i;
    for (i = agentsList->begin(); i!=agentsList->end(); ++i,j++) {
        int x = x_0 + radius * sin(j * krok * PI / 180) * (-1);
        int y = y_0 + radius * cos(j * krok * PI / 180);
        KoordinacnaSur *koor = new KoordinacnaSur(x, y);
        i->koordinacnaSuradnica = koor;
    }*/
    
}

void NavigaciaUtil::updateKoorSuradnice(PreskumaneOblasti *oblasti, std::list<agent_in_shm> *agentsList) {
    std::list<agent_in_shm>::iterator i;
    for (i = agentsList->begin(); i!=agentsList->end(); ++i) {
        // todo implementovat
        if (! i->koordinacnaSuradnica->isValid()) {
            
        }
    }
}

NavigaciaUtil::~NavigaciaUtil() {
}

