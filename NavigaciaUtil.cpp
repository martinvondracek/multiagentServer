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
    
    int radius = oblasti->getRadius() * 2 / 3;
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
                std::cout << koor->toString() << "\n";
                break;
            } else {
                if (i->aktPoloha->getVzdialenost(i->koordinacnaSuradnica) >
                        i->aktPoloha->getVzdialenost(koor)) {
                    
                    KoordinacnaSur *pom = i->koordinacnaSuradnica;
                    i->koordinacnaSuradnica = koor;
                    std::cout << koor->toString() << "\n";
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
        std::cout << "update koor sur agenta " << i->id << "\n";
        //std::cout << i->koordinacnaSuradnica->toString() << "\n";
        if (! i->koordinacnaSuradnica->isValid() && oblasti->getCoverage()<100) {
            // ak uz neni validna (tobot tam bol) tak pridelíme mu dalsiu najblizsiu npreskumanu suradnicu
            // budeme brat radiusy po 1 metre a zistime polohu pre viacer uhov na tomto radiuse
            // bod musi byt v cielovej oblasti a nesmie byt pokryty
            /*std::cout << "tu 1\n";
            int x_r = i->aktPoloha->GetX();
            int y_r = i->aktPoloha->GetY();
            
            int pocetSur = 8;
            int uhol;
            int krok;
            int radius = 1000;
            bool wantNext = false;
            
            while (radius <= oblasti->getRadius() && wantNext==false) {
                krok = 360 / pocetSur;
                uhol = 0;
                while (uhol < 360  && wantNext==false) {
                    int x = x_r + radius * sin(uhol * PI / 180) * (-1);
                    int y = y_r + radius * cos(uhol * PI / 180);
                    
                    if (oblasti->isInTargetArea(x, y) && !oblasti->isCovered(x, y)) {
                        KoordinacnaSur *koor = new KoordinacnaSur(x, y);
                        std::cout << koor->toString() << "\n";
                        i->koordinacnaSuradnica = koor;
                        wantNext = true;
                    }
                    
                    uhol += krok;
                }
                
                pocetSur *=2;
                radius += 1000;
            }*/
            
            int x_r = i->aktPoloha->GetX();
            int y_r = i->aktPoloha->GetY();
            int fi_r = i->aktPoloha->GetFi();
            int x_b = oblasti->convertXtoL(x_r);
            int y_b = oblasti->convertYtoK(y_r);
            
            KoordinacnaSur *koor = KoordinacnaSur::newInvalid();
            if (! oblasti->isCovered(x_b, y_b)) {
                i->koordinacnaSuradnica = new KoordinacnaSur(oblasti->getStredBunkyX(x_b, y_b), oblasti->getStredBunkyY(x_b, y_b));
                std::cout << i->koordinacnaSuradnica->toString() << "\n";
            } else {
                bool brk = false;
                for (int m=1; m<oblasti->getN(); m++) {
                    if (brk) break;
                    
                    // dame sa vlavo dole
                    int x_p = x_b - m;
                    int y_p = y_b - m;
                    if (oblasti->isInTargetArea(x_p, y_p) && !oblasti->isCovered(x_p, y_p)) {
                        KoordinacnaSur *koor = new KoordinacnaSur(oblasti->getStredBunkyX(x_p, y_p), oblasti->getStredBunkyY(x_p, y_p));
                        i->koordinacnaSuradnica = new KoordinacnaSur(oblasti->getStredBunkyX(x_p, y_p), oblasti->getStredBunkyY(x_p, y_p));
                        std::cout << i->koordinacnaSuradnica->toString() << "\n";
                        brk = true;
                        break;
                    }
                    
                    // presunieme sa doprava
                    for (int a=1; a<=2*m; a++) {
                        if (brk) break;
                        
                        x_p++;
                        if (oblasti->isInTargetArea(x_p, y_p) && !oblasti->isCovered(x_p, y_p)) {
                            i->koordinacnaSuradnica = new KoordinacnaSur(oblasti->getStredBunkyX(x_p, y_p), oblasti->getStredBunkyY(x_p, y_p));
                            std::cout << i->koordinacnaSuradnica->toString() << "\n";
                            brk = true;
                            break;
                        }
                    }
                    
                    // presunieme sa hore
                    for (int a=1; a<=2*m; a++) {
                        if (brk) break;
                        
                        y_p++;
                        if (oblasti->isInTargetArea(x_p, y_p) && !oblasti->isCovered(x_p, y_p)) {
                            i->koordinacnaSuradnica = new KoordinacnaSur(oblasti->getStredBunkyX(x_p, y_p), oblasti->getStredBunkyY(x_p, y_p));
                            std::cout << i->koordinacnaSuradnica->toString() << "\n";
                            brk = true;
                            break;
                        }
                    }
                    
                    // presunieme sa dolava
                    for (int a=1; a<=2*m; a++) {
                        if (brk) break;
                        
                        x_p--;
                        if (oblasti->isInTargetArea(x_p, y_p) && !oblasti->isCovered(x_p, y_p)) {
                            i->koordinacnaSuradnica = new KoordinacnaSur(oblasti->getStredBunkyX(x_p, y_p), oblasti->getStredBunkyY(x_p, y_p));
                            std::cout << i->koordinacnaSuradnica->toString() << "\n";
                            brk = true;
                            break;
                        }
                    }
                    
                    // presunieme sa dole
                    for (int a=1; a<2*m; a++) {
                        if (brk) break;
                        
                        y_p--;
                        if (oblasti->isInTargetArea(x_p, y_p) && !oblasti->isCovered(x_p, y_p)) {
                            i->koordinacnaSuradnica = new KoordinacnaSur(oblasti->getStredBunkyX(x_p, y_p), oblasti->getStredBunkyY(x_p, y_p));
                            std::cout << i->koordinacnaSuradnica->toString() << "\n";
                            brk = true;
                            break;
                        }
                    }
                }
            }
            
        }
    }
}

NavigaciaUtil::~NavigaciaUtil() {
}

