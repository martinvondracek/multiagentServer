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
    std::list<agent_in_shm>::iterator i;
    for (i = agentsList->begin(); i != agentsList->end(); ++i) {
        int x = x_0 + radius * sin(krok * PI / 180) * (-1);
        int y = y_0 + radius * cos(krok * PI / 180);
        i->koordinacnaSuradnica = new KoordinacnaSur(x, y);
    }
    
    // todo teraz ich vymeníme tak, aby sme minimalizovali dráhy k nim
    
}

void NavigaciaUtil::updateKoorSuradnice(PreskumaneOblasti *oblasti, std::list<agent_in_shm> *agentsList) {
    // TODO implementovat
}

NavigaciaUtil::~NavigaciaUtil() {
}

