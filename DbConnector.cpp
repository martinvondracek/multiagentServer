/* 
 * File:   dbConnectorClass.cpp
 * Author: root
 * 
 * Created on Nedeľa, 2015, január 18, 21:04
 */

#include "DbConnector.h"
#include <stdlib.h>
#include <iostream>
//#include <stdio.h>


DbConnector::DbConnector() {
    connect();
    createTables();
}

bool DbConnector::isConnected() {
    return connected;
}

int DbConnector::connect() {
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

int DbConnector::createTables() {
    sql::PreparedStatement *pstmt;
    
    if (!connected) {
        return -1;
    }
    
    try {
        // vytvorime tabulku spustenia ak neexistuje
        pstmt = con->prepareStatement("CREATE TABLE IF NOT EXISTS `spustenia` (`id` int(11) NOT NULL AUTO_INCREMENT,`timestarted` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,`timeend` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP, PRIMARY KEY (id)) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='uklada id spustenia mapovania' AUTO_INCREMENT=1");
        pstmt->executeUpdate();

        // vytvorime tabulku polohy ak neexistuje
        pstmt = con->prepareStatement("CREATE TABLE IF NOT EXISTS `polohy` (`id` int(11) NOT NULL AUTO_INCREMENT,`id_spustenia` int(11) NOT NULL,`robot` int(11) NOT NULL,`x` float NOT NULL,`y` float NOT NULL,`fi` float NOT NULL, PRIMARY KEY (id)) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='ukladame polohy robota' AUTO_INCREMENT=1");
        pstmt->executeUpdate();

        // vytvorime tabulku prekazky ak neexistuje
        pstmt = con->prepareStatement("CREATE TABLE IF NOT EXISTS `prekazky` (`id` int(11) NOT NULL AUTO_INCREMENT,`id_spustenia` int(11) NOT NULL,`prekazka` int(11) NOT NULL,`robot` int(11) NOT NULL, `x_rob` float NOT NULL, `y_rob` float NOT NULL, `fi_rob` float NOT NULL,  `x_p` float NOT NULL,  `y_p` float NOT NULL,  `naraz_vpravo` tinyint(1) NOT NULL,  `naraz_vlavo` tinyint(1) NOT NULL,  `naraz_vpredu` tinyint(1) NOT NULL, PRIMARY KEY (id)) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='ukladame sem suradnice prekazok' AUTO_INCREMENT=1");
        pstmt->executeUpdate();
        
        // vytvorime tabulku pokrytie ak neexistuje
        pstmt = con->prepareStatement("CREATE TABLE IF NOT EXISTS `pokrytie` (`id` int(11) NOT NULL AUTO_INCREMENT,`id_spustenia` int(11) NOT NULL,`x0` int(11) NOT NULL,`y0` int(11) NOT NULL,`radius` int(11) NOT NULL, `n` int(11) NOT NULL, `rozmer_bunky` int(11) NOT NULL,  `k` int(11) NOT NULL,  `l` int(11) NOT NULL,  `obsadene` tinyint(1) NOT NULL, PRIMARY KEY (id)) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='ukladame sem suradnice prekazok' AUTO_INCREMENT=1");
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

int DbConnector::getNewMappingId() {
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

int DbConnector::getNewObstacleId(int idSpustenia) {
    if (!connected) {
        return -1;
    }
    
    // novu prekazku dostaneme tak ze najdeve navyssie cislo a to zvysime o 1
    sql::Statement *stmt;
    sql::ResultSet *res;
    sql::PreparedStatement *pstmt;
    int newId;
    m.lock();
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
        m.unlock();
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
        m.unlock();
        return -1;
    }
    return newId;
}

int DbConnector::updateMappingEnd(int idSpustenia) {
    if (!connected) {
        return -1;
    }
    
    sql::PreparedStatement *pstmt;
    m.lock();
    try {
        // vytvorime novy riadok
        pstmt = con->prepareStatement("UPDATE spustenia SET timeend=null WHERE id=?");
        pstmt->setInt(1, idSpustenia);
        pstmt->executeQuery();

        delete pstmt;
        m.unlock();
    } catch (sql::SQLException &e) {
        std::cout << "exception\n";
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << "\n";
        std::cout << "# ERR: " << e.what() << "\n";
        std::cout << " (MySQL error code: " << e.getErrorCode() << "\n";
        std::cout << ", SQLState: " << e.getSQLState() << " )" << "\n";
        delete pstmt;
        m.unlock();
        return -1;
    }
    return 0;
}

int DbConnector::savePosition(Position *poloha) {
    //std::cout << "savePoloha\n";
    if (!connected) {
        return -1;
    }
    
    auto t_start = std::chrono::high_resolution_clock::now();
    m.lock();
    sql::PreparedStatement *pstmt;
    try {
        pstmt = con->prepareStatement("INSERT INTO `polohy`(`id_spustenia`, `robot`, `x`, `y`, `fi`) VALUES (?,?,?,?,?)");
        pstmt->setInt(1, poloha->GetId_ofMapping());
        pstmt->setInt(2, poloha->GetRobot());
        pstmt->setDouble(3, poloha->GetX());
        pstmt->setDouble(4, poloha->GetY());
        pstmt->setDouble(5, poloha->GetFi());
        pstmt->executeQuery();
        delete pstmt;
        m.unlock();
    } catch (sql::SQLException &e) {
        std::cout << "exception\n";
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << "\n";
        std::cout << "# ERR: " << e.what() << "\n";
        std::cout << " (MySQL error code: " << e.getErrorCode() << "\n";
        std::cout << ", SQLState: " << e.getSQLState() << " )" << "\n";
        delete pstmt;
        m.unlock();
        return -1;
    }
    auto t_end = std::chrono::high_resolution_clock::now();
    /*std::cout << "savePoloha Wall clock time passed: "
              << std::chrono::duration<double, std::milli>(t_end-t_start).count()
              << " ms\n";*/
    return 0;
}

int DbConnector::saveObstacle(Obstacle *prekazka) {
    //std::cout << "savePrekazka\n";
    if (!connected) {
        return -1;
    }
    
    auto t_start = std::chrono::high_resolution_clock::now();
    m.lock();
    sql::PreparedStatement *pstmt;
    try {
        pstmt = con->prepareStatement("INSERT INTO `prekazky`(`id_spustenia`, `prekazka`, `robot`, `x_rob`, `y_rob`, `fi_rob`, `x_p`, `y_p`, `naraz_vpravo`, `naraz_vlavo`, `naraz_vpredu`) VALUES (?,?,?,?,?,?,?,?,?,?,?)");
        pstmt->setInt(1, prekazka->GetId_mapping());
        pstmt->setInt(2, prekazka->GetIdObstacle());
        pstmt->setInt(3, prekazka->GetRobot());
        pstmt->setDouble(4, prekazka->GetX_rob());
        pstmt->setDouble(5, prekazka->GetY_rob());
        pstmt->setDouble(6, prekazka->GetFi_rob());
        pstmt->setDouble(7, prekazka->GetX_p());
        pstmt->setDouble(8, prekazka->GetY_p());
        pstmt->setBoolean(9, prekazka->IsHit_right());
        pstmt->setBoolean(10, prekazka->IsHit_left());
        pstmt->setBoolean(11, prekazka->IsHit_front());
        pstmt->executeQuery();
        delete pstmt;
        m.unlock();
    } catch (sql::SQLException &e) {
        std::cout << "exception\n";
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << "\n";
        std::cout << "# ERR: " << e.what() << "\n";
        std::cout << " (MySQL error code: " << e.getErrorCode() << "\n";
        std::cout << ", SQLState: " << e.getSQLState() << " )" << "\n";
        delete pstmt;
        m.unlock();
        return -1;
    }
    auto t_end = std::chrono::high_resolution_clock::now();
    /*std::cout << "savePrekazka Wall clock time passed: "
              << std::chrono::duration<double, std::milli>(t_end-t_start).count()
              << " ms\n";*/
    return 0;
}

int DbConnector::saveCoveredArea(CoveredArea *bunka) {
    if (!connected) {
        return -1;
    }
    
    auto t_start = std::chrono::high_resolution_clock::now();
    m.lock();
    sql::PreparedStatement *pstmt;
    try {
        pstmt = con->prepareStatement("INSERT INTO `pokrytie`(`id_spustenia`, `x0`, `y0`, `radius`, `n`, `rozmer_bunky`, `k`, `l`, `obsadene`) VALUES (?,?,?,?,?,?,?,?,?)");
        pstmt->setInt(1, bunka->GetIdMapping());
        pstmt->setInt(2, bunka->GetX0());
        pstmt->setDouble(3, bunka->GetY0());
        pstmt->setDouble(4, bunka->GetRadius());
        pstmt->setDouble(5, bunka->GetN());
        pstmt->setDouble(6, bunka->GetRozmerBunky());
        pstmt->setDouble(7, bunka->GetK());
        pstmt->setDouble(8, bunka->GetL());
        pstmt->setBoolean(9, bunka->IsCovered());
        pstmt->executeQuery();
        delete pstmt;
        m.unlock();
    } catch (sql::SQLException &e) {
        std::cout << "exception\n";
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << "\n";
        std::cout << "# ERR: " << e.what() << "\n";
        std::cout << " (MySQL error code: " << e.getErrorCode() << "\n";
        std::cout << ", SQLState: " << e.getSQLState() << " )" << "\n";
        delete pstmt;
        m.unlock();
        return -1;
    }
    auto t_end = std::chrono::high_resolution_clock::now();
    /*std::cout << "saveOblasti Wall clock time passed: "
              << std::chrono::duration<double, std::milli>(t_end-t_start).count()
              << " ms\n";*/
    return 0;
}

int DbConnector::saveCoveredAreas(CoveredAreas *oblasti) {
    if (!connected) {
        return -1;
    }

    std::list<CoveredArea*> list = oblasti->toList();
    std::list<CoveredArea*>::iterator i;
    for (i = list.begin(); i != list.end(); ++i) {
        saveCoveredArea((*i));
    }
    
    return 0;
}

void DbConnector::test() {
    if (!connected) {
        return;
    }
    
    Position *pol = new Position(0, 2, 1, 1.2, 1.2, 3.14);
    const char * pom = pol->toJson();
    std::cout << pom << "\n";
    Position *pol2 = Position::fromJson(pom);
    std::cout << pol2->GetX() << "\n";
    
    Obstacle *prk = new Obstacle(0, 2, 1, 2, 1.2, 1.2, 3.14, 1.2, 1.2, 1, 0, 1);
    const char * pom2 = prk->toJson();
    Obstacle *prk2 = Obstacle::fromJson(pom2);
    std::cout << prk2->GetId_mapping() << "\n";
}

DbConnector::~DbConnector() {
    std::cout << "destruktor dbConnectorClass\n";
    delete con;
}

