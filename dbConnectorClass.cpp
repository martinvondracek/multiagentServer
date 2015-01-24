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


dbConnectorClass::dbConnectorClass() {
    connect();
    createTables();
}

bool dbConnectorClass::isConnected() {
    return connected;
}

int dbConnectorClass::getNewSpustenieId() {
    if (!connected) {
        return -1;
    }
    
    sql::Statement *stmt;
    sql::ResultSet *res;
    sql::PreparedStatement *pstmt;
    int newId;
    try {
        stmt = con->createStatement();
        // vytvorime novy riadok
        pstmt = con->prepareStatement("INSERT INTO spustenia(timestarted) VALUES(null)");
        pstmt->executeQuery();
        // nove id je to najvacsie
        pstmt = con->prepareStatement("SELECT max(id) from spustenia");
        res = pstmt->executeQuery();
        while (res->next()) {
            newId = atoi(res->getString("max(id)").c_str());
        }

        delete res;
        delete stmt;
        delete pstmt;
    } catch (sql::SQLException &e) {
        std::cout << "exception\n";
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << "\n";
        std::cout << "# ERR: " << e.what() << "\n";
        std::cout << " (MySQL error code: " << e.getErrorCode() << "\n";
        std::cout << ", SQLState: " << e.getSQLState() << " )" << "\n";
        delete res;
        delete stmt;
        delete pstmt;
        return -1;
    }
    return newId;
}

int dbConnectorClass::getNewPrekazkaId(int idSpustenia) {
    if (!connected) {
        return -1;
    }
    
    // novu prekazku dostaneme tak ze najdeve navyssie cislo a to zvysime o 1
    sql::Statement *stmt;
    sql::ResultSet *res;
    sql::PreparedStatement *pstmt;
    int newId;
    try {
        stmt = con->createStatement();
        pstmt = con->prepareStatement("SELECT max(prekazka) from prekazky where id_spustenia=?");
        pstmt->setInt(1, idSpustenia);
        res = pstmt->executeQuery();
        while (res->next()) {
            newId = atoi(res->getString("max(prekazka)").c_str());
            newId += 1;
        }

        delete res;
        delete stmt;
        delete pstmt;
    } catch (sql::SQLException &e) {
        std::cout << "exception\n";
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << "\n";
        std::cout << "# ERR: " << e.what() << "\n";
        std::cout << " (MySQL error code: " << e.getErrorCode() << "\n";
        std::cout << ", SQLState: " << e.getSQLState() << " )" << "\n";
        delete res;
        delete stmt;
        delete pstmt;
        return -1;
    }
    return newId;
}

int dbConnectorClass::savePoloha() {
    if (!connected) {
        return -1;
    }
    // TODO implementovat
    
    return -1;
}

int dbConnectorClass::savePrekazka() {
    if (!connected) {
        return -1;
    }
    // TODO implementovat
    
    return -1;
}

int dbConnectorClass::connect() {
    try {
        driver = get_driver_instance();
        con = driver->connect(DB_HOST, DB_USERNAME, DB_PASSWORD);
        con->setSchema(DB_DATABASE);
        connected = true;
        return 0;
    } catch (sql::SQLException &e) {
        std::cout << "exception\n";
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << "\n";
        std::cout << "# ERR: " << e.what() << "\n";
        std::cout << " (MySQL error code: " << e.getErrorCode() << "\n";
        std::cout << ", SQLState: " << e.getSQLState() << " )" << "\n";
        connected = false;
        return -1;
    }
}

int dbConnectorClass::createTables() {
    sql::PreparedStatement *pstmt;
    
    if (!connected) {
        return -1;
    }
    
    try {
        // vytvorime tabulku spustenia ak neexistuje
        pstmt = con->prepareStatement("CREATE TABLE IF NOT EXISTS `spustenia` (`id` int(11) NOT NULL AUTO_INCREMENT,`timestarted` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP, PRIMARY KEY (id)) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='uklada id spustenia mapovania' AUTO_INCREMENT=1");
        pstmt->executeUpdate();

        // vytvorime tabulku polohy ak neexistuje
        pstmt = con->prepareStatement("CREATE TABLE IF NOT EXISTS `polohy` (`id` int(11) NOT NULL AUTO_INCREMENT,`id_spustenia` int(11) NOT NULL,`robot` int(11) NOT NULL,`x` float NOT NULL,`y` float NOT NULL,`fi` float NOT NULL, PRIMARY KEY (id)) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='ukladame polohy robota' AUTO_INCREMENT=1");
        pstmt->executeUpdate();

        // vytvorime tabulku prekazky ak neexistuje
        pstmt = con->prepareStatement("CREATE TABLE IF NOT EXISTS `prekazky` (`id` int(11) NOT NULL AUTO_INCREMENT,`id_spustenia` int(11) NOT NULL,`prekazka` int(11) NOT NULL, `x_rob` float NOT NULL, `y_rob` float NOT NULL, `fi_rob` float NOT NULL,  `x_p` float NOT NULL,  `y_p` float NOT NULL,  `naraz_vpravo` tinyint(1) NOT NULL,  `naraz_vlavo` tinyint(1) NOT NULL,  `naraz_vpredu` tinyint(1) NOT NULL, PRIMARY KEY (id)) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='ukladame sem suradnice prekazok' AUTO_INCREMENT=1");
        pstmt->executeUpdate();

        delete pstmt;
        return 0;
    } catch (sql::SQLException &e) {
        std::cout << "exception\n";
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << "\n";
        std::cout << "# ERR: " << e.what() << "\n";
        std::cout << " (MySQL error code: " << e.getErrorCode() << "\n";
        std::cout << ", SQLState: " << e.getSQLState() << " )" << "\n";
        delete pstmt;
        return -1;
    }
}

void dbConnectorClass::test() {
    if (!connected) {
        return;
    }
    return;
    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        sql::PreparedStatement *pstmt;

        driver = get_driver_instance();
        con = driver->connect("tcp://localhost:3306", "martin", "heslo");
        con->setSchema("diplomovka");
        
        pstmt = con->prepareStatement("INSERT INTO spustenia(timestarted) VALUES(null)");
        // INSERT INTO `polohy`(`id_spustenia`, `robot`, `x`, `y`, `fi`) VALUES (18,1,0,1,0);
        // INSERT INTO `prekazky`(`id_spustenia`, `prekazka`, `x_rob`, `y_rob`, `fi_rob`, `x_p`, `y_p`, `naraz_vpravo`, `naraz_vlavo`, `naraz_vpredu`) VALUES (18,1,0,1,0,1.3,0,0,0,1)
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
    delete con;
}

