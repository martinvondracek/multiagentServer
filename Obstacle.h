/* 
 * File:   prekazkaClass.h
 * Author: root
 *
 * Created on Sobota, 2015, január 24, 10:45
 * 
 * for storing obstacles found by agent
 */

#ifndef PREKAZKACLASS_H
#define	PREKAZKACLASS_H

#include <rapidjson/document.h>
#include <cstdio>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <iostream>

class Obstacle {
public:
    Obstacle(int id, int id_spustenia, int prekazka, int robot, float x_rob,
            float y_rob, float fi_rob, float x_p, float y_p, bool naraz_vpravo,
            bool naraz_vlavo, bool naraz_vpredu);
    virtual ~Obstacle();
    
    const char * toJson();
    static Obstacle * fromJson(const char *json);
    const char * toString();
    
    float getDistance(Obstacle *p2); // return distance from other obstacle
    
    float GetFi_rob();
    void SetFi_rob(float fi_rob);
    int GetId();
    void SetId(int id);
    int GetId_mapping();
    void SetId_mapping(int id_spustenia);
    bool IsHit_left();
    void SetHit_left(bool naraz_vlavo);
    bool IsHit_right();
    void SetHit_right(bool naraz_vpravo);
    bool IsHit_front();
    void SetHit_front(bool naraz_vpredu);
    int GetIdObstacle();
    void SetIdObstacle(int prekazka);
    int GetRobot();
    void SetRobot(int robot);
    float GetX_p();
    void SetX_p(float x_p);
    float GetX_rob();
    void SetX_rob(float x_rob);
    float GetY_p();
    void SetY_p(float y_p);
    float GetY_rob();
    void SetY_rob(float y_rob);
private:
    int id;
    int id_spustenia;
    int prekazka;
    int robot;
    float x_rob;
    float y_rob;
    float fi_rob;
    float x_p;
    float y_p;
    bool naraz_vpravo;
    bool naraz_vlavo;
    bool naraz_vpredu;
};

#endif	/* PREKAZKACLASS_H */

