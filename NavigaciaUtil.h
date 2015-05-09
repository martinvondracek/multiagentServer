/* 
 * File:   NavigaciaUtil.h
 * Author: root
 *
 * Created on April 13, 2015, 9:03 PM
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
    static void updateKoorSuradnice(PreskumaneOblasti *oblasti, std::list<agent_in_shm> *agentsList);
    static bool isKoorSuradniceAssigned(KoordinacnaSur *sur, std::list<agent_in_shm> *agentsList);
    
    virtual ~NavigaciaUtil();
private:

};

#endif	/* NAVIGACIAUTIL_H */

