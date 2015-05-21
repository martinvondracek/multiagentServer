/* 
 * File:   dbConnectorClass.h
 * Author: root
 *
 * Created on Nedeľa, 2015, január 18, 21:04
 * 
 * connector to MySQL database
 */

#ifndef DBCONNECTORCLASS_H
#define	DBCONNECTORCLASS_H

#include <mutex>

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "Position.h"
#include "Obstacle.h"
#include "CoveredAreas.h"

#define DB_HOST "tcp://localhost:3306"
#define DB_USERNAME "martin"
#define DB_PASSWORD "heslo"
#define DB_DATABASE "diplomovka"

class DbConnector {
public:
    DbConnector();
    virtual ~DbConnector();
    void test(); // only for delevopment
    bool isConnected(); // returns if is connected to database
    int getNewMappingId(); //returns new ID of mapping
    int updateMappingEnd(int idSpustenia); // updates end time of mapping
    int getNewObstacleId(int idSpustenia); //find out highest id of obstacle
                            //and returns higher
    int savePosition(Position *poloha); // saves position of robot
    int saveObstacle(Obstacle *prekazka); // saves obstacle
    int saveCoveredArea(CoveredArea *bunka); //saves coverage area
    int saveCoveredAreas(CoveredAreas *oblasti); // saves all areas
private:
    bool connected = false;
    std::mutex m;
    
    sql::Driver *driver;
    sql::Connection *con;
    
    int connect(); //connects to database
    int createTables(); //creates necessary table in DB if not existing
};

#endif	/* DBCONNECTORCLASS_H */

