/* 
 * File:   dbConnectorClass.h
 * Author: root
 *
 * Created on Nedeľa, 2015, január 18, 21:04
 */

#ifndef DBCONNECTORCLASS_H
#define	DBCONNECTORCLASS_H

#define DB_HOST localhost
#define DB_USERNAME martin
#define DB_PASSWORD heslo
#define DB_DATABASE diplomovka

class dbConnectorClass {
public:
    dbConnectorClass();
    virtual ~dbConnectorClass();
    void test();
private:
    int connected = 0;
};

#endif	/* DBCONNECTORCLASS_H */

