/* 
 * File:   dbConnectorClass.h
 * Author: root
 *
 * Created on Nedeľa, 2015, január 18, 21:04
 */

#ifndef DBCONNECTORCLASS_H
#define	DBCONNECTORCLASS_H

#include "mysql_connection.h"
#include "mysql_driver.h" 
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#define DB_HOST "tcp://localhost:3306"
#define DB_USERNAME "martin"
#define DB_PASSWORD "heslo"
#define DB_DATABASE "diplomovka"

class dbConnectorClass {
public:
    dbConnectorClass();
    virtual ~dbConnectorClass();
    void test();
    bool isConnected(); // vrati ci je pripojeny k DB
    int getNewSpustenieId(); //vytvori a vrati nove ID spustenia
    int getNewPrekazkaId(int idSpustenia); //zisti ake je aktualne najvyssie cislo prekazky
                            //pre dane spustenie a vrati o 1 vacsie
    int savePoloha(); // ulozi polohu robota do DB pre spustenie
    int savePrekazka(); // ulozi prekazku do DB pre spustenie
private:
    bool connected = false;
    
    sql::Driver *driver;
    sql::Connection *con;
    
    int connect();
    int createTables();
};

#endif	/* DBCONNECTORCLASS_H */

