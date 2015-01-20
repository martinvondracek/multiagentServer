/* 
 * File:   dbConnectorClass.cpp
 * Author: root
 * 
 * Created on Nedeľa, 2015, január 18, 21:04
 */

#include "dbConnectorClass.h"
#include <stdlib.h>
#include <iostream>
//#include <stdio.h>


#include "mysql_connection.h"
#include "mysql_driver.h" 
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

dbConnectorClass::dbConnectorClass() {
    
}

void dbConnectorClass::test() {
    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        sql::PreparedStatement *pstmt;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://localhost:3306", "martin", "heslo");
        /* Connect to the MySQL test database */
        con->setSchema("diplomovka");
        
        pstmt = con->prepareStatement("INSERT INTO spustenia(timestarted) VALUES(null)");
        //pstmt->setString(1, "CURRENT_TIMESTAMP");
        //pstmt->executeUpdate();
        
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from spustenia");
        while (res->next()) {
            std::cout << res->getString("id") << " : " << res->getString("timestarted") << "\n";
        }
        
        delete pstmt;
        delete res;
        delete stmt;
        delete con;

    } catch (sql::SQLException &e) {
        std::cout << "exception\n";
          std::cout << "# ERR: SQLException in " << __FILE__;
          std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << "\n";
          std::cout << "# ERR: " << e.what() << "\n";
          std::cout << " (MySQL error code: " << e.getErrorCode() << "\n";
          std::cout << ", SQLState: " << e.getSQLState() << " )" << "\n";
    }

}

dbConnectorClass::~dbConnectorClass() {
    std::cout << "destruktor dbConnectorClass\n";
}

