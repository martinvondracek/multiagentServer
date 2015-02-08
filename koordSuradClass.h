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

class koordSuradClass {
public:
    koordSuradClass(float x, float y);
    
    const char * toJson();
    static koordSuradClass * fromJson(const char *json);
    const char * toString();
    
    float getX();
    void setX(float x);
    float getY();
    void setY(float y);

    virtual ~koordSuradClass();
private:
    float x;
    float y;

};

#endif	/* KOORDSURADCLASS_H */

