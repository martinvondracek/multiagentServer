/*
 * File:   main.cpp
 * Author: root
 *
 * Created on Pondelok, 2015, január 5, 23:18
 */

#include <QApplication>

#include "serverForm.h"
#include "PreskumaneOblasti.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    // create and show your widgets here
    serverForm frm;
    frm.show();

    return app.exec();
    
    
//    PreskumaneOblasti *oblasti = new PreskumaneOblasti(0, 0, 2001, 1);
//    oblasti->addPoloha(new Poloha(0, 1, 1, 
//            -5000, 5000,
//            0));
//    oblasti->print();
}
