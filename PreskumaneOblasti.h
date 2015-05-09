/* 
 * File:   PreskumaneOblasti.h
 * Author: root
 *
 * Created on Utorok, 2015, marec 24, 23:10
 */

#ifndef PRESKUMANEOBLASTI_H
#define	PRESKUMANEOBLASTI_H

#include <mutex>
#include <list>

#include "Poloha.h"
#include "PreskumanaBunka.h"


class PreskumaneOblasti {
public:
    PreskumaneOblasti(int x, int y, int radius, int idSpustnia);
    
    void addPoloha(Poloha *poloha);
    bool isCovered(int x, int y);
    bool isCovered(Poloha *poloha);
    bool isInTargetArea(int x, int y);
    bool isInTargetArea(Poloha *poloha);
    float getCoverage();
    
    int getRadius();
    int getX();
    int getY();
    int getN();
    
    int convertXtoL(int x);
    int convertYtoK(int y);
    int getStredBunkyX(int x, int y);
    int getStredBunkyY(int x, int y);
    
    void addInaccesibleKoorSur(KoordinacnaSur *sur);
    bool isAccesible(KoordinacnaSur *sur);

    std::list<PreskumanaBunka*> toList();
    void print();
    
    virtual ~PreskumaneOblasti();
private:
    int idSpustnia;
    int x0;
    int y0;
    int radius;
    int rozmerBunky = 1000;
    
    std::list<KoordinacnaSur*> inaccesibleList;
    
    bool *pole;
    int n;
    std::mutex m;
};

#endif	/* PRESKUMANEOBLASTI_H */

