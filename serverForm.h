/* 
 * File:   serverForm.h
 * Author: root
 *
 * Created on Pondelok, 2015, január 5, 23:20
 */

#ifndef _SERVERFORM_H
#define	_SERVERFORM_H

#include "ui_serverForm.h"
#include "socketClass.h"
#include "dbConnectorClass.h"

struct komunikacia_shm {
    socketClass * socketUtil; //objekt pre komunikáciu cez socket
    dbConnectorClass *dbUtil;
    int spustenieId;
};

class serverForm : public QDialog {
    Q_OBJECT
public:
    serverForm();
    virtual ~serverForm();
public slots:
    void startServerClicked(); //spusti server
    void startMappingClicked(); //spusti mapovanie
    void stopMappingClicked(); //zastavi mapovanie
private:
    Ui::serverForm widget;
    bool serverStarted = false; //ci je spusteny server
    bool mappingNow = false; //ci je spustene mapovanie
    socketClass * socketUtil; //objekt pre komunikáciu cez socket
    dbConnectorClass *dbUtil;
    int spustenieId;
    komunikacia_shm *shm; //
};

#endif	/* _SERVERFORM_H */
