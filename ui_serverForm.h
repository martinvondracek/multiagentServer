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
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serverForm
{
public:
    QPushButton *koniecButton;
    QLabel *infoLabel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *ipLabel;
    QLineEdit *portEdit;
    QLineEdit *maxAgentEdit;
    QLabel *agentCountLabel;
    QPushButton *startServerButton;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QPushButton *startMappingButton;
    QPushButton *stopMappingButton;

    void setupUi(QDialog *serverForm)
    {
        if (serverForm->objectName().isEmpty())
            serverForm->setObjectName(QString::fromUtf8("serverForm"));
        serverForm->resize(444, 392);
        koniecButton = new QPushButton(serverForm);
        koniecButton->setObjectName(QString::fromUtf8("koniecButton"));
        koniecButton->setGeometry(QRect(290, 350, 141, 31));
        QFont font;
        font.setPointSize(12);
        koniecButton->setFont(font);
        infoLabel = new QLabel(serverForm);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));
        infoLabel->setGeometry(QRect(10, 10, 421, 22));
        QFont font1;
        font1.setPointSize(13);
        infoLabel->setFont(font1);
        infoLabel->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(serverForm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 60, 201, 121));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        verticalLayout->addWidget(label_5);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        verticalLayout->addWidget(label_3);

        layoutWidget1 = new QWidget(serverForm);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(230, 60, 191, 161));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        ipLabel = new QLabel(layoutWidget1);
        ipLabel->setObjectName(QString::fromUtf8("ipLabel"));
        ipLabel->setFont(font1);
        ipLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(ipLabel);

        portEdit = new QLineEdit(layoutWidget1);
        portEdit->setObjectName(QString::fromUtf8("portEdit"));

        verticalLayout_2->addWidget(portEdit);

        maxAgentEdit = new QLineEdit(layoutWidget1);
        maxAgentEdit->setObjectName(QString::fromUtf8("maxAgentEdit"));

        verticalLayout_2->addWidget(maxAgentEdit);

        agentCountLabel = new QLabel(layoutWidget1);
        agentCountLabel->setObjectName(QString::fromUtf8("agentCountLabel"));
        QFont font2;
        font2.setPointSize(14);
        agentCountLabel->setFont(font2);

        verticalLayout_2->addWidget(agentCountLabel);

        startServerButton = new QPushButton(layoutWidget1);
        startServerButton->setObjectName(QString::fromUtf8("startServerButton"));
        startServerButton->setFont(font);

        verticalLayout_2->addWidget(startServerButton);

        layoutWidget2 = new QWidget(serverForm);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(40, 270, 361, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        startMappingButton = new QPushButton(layoutWidget2);
        startMappingButton->setObjectName(QString::fromUtf8("startMappingButton"));
        startMappingButton->setFont(font);

        horizontalLayout->addWidget(startMappingButton);

        stopMappingButton = new QPushButton(layoutWidget2);
        stopMappingButton->setObjectName(QString::fromUtf8("stopMappingButton"));
        stopMappingButton->setFont(font);

        horizontalLayout->addWidget(stopMappingButton);

        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        koniecButton->raise();
        infoLabel->raise();

        retranslateUi(serverForm);
        QObject::connect(koniecButton, SIGNAL(clicked()), serverForm, SLOT(close()));

        QMetaObject::connectSlotsByName(serverForm);
    } // setupUi

    void retranslateUi(QDialog *serverForm)
    {
        serverForm->setWindowTitle(QApplication::translate("serverForm", "serverForm", 0, QApplication::UnicodeUTF8));
        koniecButton->setText(QApplication::translate("serverForm", "Koniec", 0, QApplication::UnicodeUTF8));
        infoLabel->setText(QApplication::translate("serverForm", "Info", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("serverForm", "IP adresa", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("serverForm", "Port:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("serverForm", "Max. agentov:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("serverForm", "Pripojen\303\275ch agentov:", 0, QApplication::UnicodeUTF8));
        ipLabel->setText(QApplication::translate("serverForm", "000.000.000.000", 0, QApplication::UnicodeUTF8));
        agentCountLabel->setText(QApplication::translate("serverForm", "0", 0, QApplication::UnicodeUTF8));
        startServerButton->setText(QApplication::translate("serverForm", "Spusti\305\245 server", 0, QApplication::UnicodeUTF8));
        startMappingButton->setText(QApplication::translate("serverForm", "Spusti\305\245 mapovanie", 0, QApplication::UnicodeUTF8));
        stopMappingButton->setText(QApplication::translate("serverForm", "Zastavi\305\245 mapovanie", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class serverForm: public Ui_serverForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERFORM_H
