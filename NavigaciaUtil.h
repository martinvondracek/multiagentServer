/* 
 * File:   NavigaciaUtil.h
 * Author: root
 *
 * Created on April 13, 2015, 9:03 PM
 * 
 * utility for navigation - coordinating movement of agents
 */

#ifndef NAVIGACIAUTIL_H
#define	NAVIGACIAUTIL_H

#include "PreskumaneOblasti.h"
#include "KoordinacnaSur.h"
#include "Server.h"
#define PI 3.14159265


class NavigaciaUtil {
public:
    NavigaciaUtil();
    
    static void initializeKoorSuradnice(PreskumaneOblasti *oblasti, std::list<agent_in_shm> *agentsList);
    // initializes coordination positions for every agent - every agent is assigned one position on target radius
    static void updateKoorSuradnice(PreskumaneOblasti *oblasti, std::list<agent_in_shm> *agentsList);
    // updates every agent with invalid or inaccesible coordination position
    // agent is assigned new nearest position
    static bool isKoorSuradniceAssigned(KoordinacnaSur *sur, std::list<agent_in_shm> *agentsList);
    // if coordination position is assigned to any other agent
    
    virtual ~NavigaciaUtil();
private:

};

#endif	/* NAVIGACIAUTIL_H */

