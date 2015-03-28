/* 
 * File:   PreskumaneOblasti.h
 * Author: root
 *
 * Created on Utorok, 2015, marec 24, 23:10
 */

#ifndef PRESKUMANEOBLASTI_H
#define	PRESKUMANEOBLASTI_H

#include "Poloha.h"


class PreskumaneOblasti {
public:
    PreskumaneOblasti(int x, int y, int radius, int idSpustnia);
    
    void addPoloha(Poloha *poloha);
    bool isCovered(int x, int y);
    bool isCovered(Poloha *poloha);
    float getCoverage();
    
    int getRadius();
    int getX();
    int getY();

    void print();
    
    virtual ~PreskumaneOblasti();
private:
    int idSpustnia;
    int x0;
    int y0;
    int radius;
    
    bool *pole;
    int n;
};

#endif	/* PRESKUMANEOBLASTI_H */

