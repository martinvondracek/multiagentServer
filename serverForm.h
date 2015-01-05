/* 
 * File:   serverForm.h
 * Author: root
 *
 * Created on Pondelok, 2015, január 5, 23:20
 */

#ifndef _SERVERFORM_H
#define	_SERVERFORM_H

#include "ui_serverForm.h"

class serverForm : public QDialog {
    Q_OBJECT
public:
    serverForm();
    virtual ~serverForm();
private:
    Ui::serverForm widget;
};

#endif	/* _SERVERFORM_H */
