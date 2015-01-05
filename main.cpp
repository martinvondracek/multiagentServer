/*
 * File:   main.cpp
 * Author: root
 *
 * Created on Pondelok, 2015, január 5, 23:18
 */

#include <QApplication>

#include "serverForm.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    // create and show your widgets here
    serverForm frm;
    frm.show();

    return app.exec();
}
