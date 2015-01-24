/* 
 * File:   polohaClass.h
 * Author: root
 *
 * Created on Sobota, 2015, január 24, 10:45
 */

#ifndef POLOHACLASS_H
#define	POLOHACLASS_H

class polohaClass {
public:
    polohaClass(int id, int id_spustenia, int robot, float x, float y, float fi);
    virtual ~polohaClass();
    
    float GetFi();
    void SetFi(float fi);
    int GetId();
    void SetId(int id);
    int GetId_spustenia();
    void SetId_spustenia(int id_spustenia);
    int GetRobot();
    void SetRobot(int robot);
    float GetX();
    void SetX(float x);
    float GetY();
    void SetY(float y);
private:
    int id;
    int id_spustenia;
    int robot;
    float x;
    float y;
    float fi;
};

#endif	/* POLOHACLASS_H */

