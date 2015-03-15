/* 
 * File:   koordSuradClass.h
 * Author: root
 *
 * Created on Nedeľa, 2015, február 8, 15:53
 */

#ifndef KOORDSURADCLASS_H
#define	KOORDSURADCLASS_H

#include <rapidjson/document.h>
#include <cstdio>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <iostream>

class KoordSurad {
public:
    KoordSurad(float x, float y);
    
    const char * toJson();
    static KoordSurad * fromJson(const char *json);
    const char * toString();
    
    float getX();
    void setX(float x);
    float getY();
    void setY(float y);

    virtual ~KoordSurad();
private:
    float x;
    float y;

};

#endif	/* KOORDSURADCLASS_H */

