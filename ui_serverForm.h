/********************************************************************************
** Form generated from reading UI file 'serverForm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERFORM_H
#define UI_SERVERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_serverForm
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *serverForm)
    {
        if (serverForm->objectName().isEmpty())
            serverForm->setObjectName(QString::fromUtf8("serverForm"));
        serverForm->resize(400, 300);
        buttonBox = new QDialogButtonBox(serverForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        retranslateUi(serverForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), serverForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), serverForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(serverForm);
    } // setupUi

    void retranslateUi(QDialog *serverForm)
    {
        serverForm->setWindowTitle(QApplication::translate("serverForm", "serverForm", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class serverForm: public Ui_serverForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERFORM_H
