/********************************************************************************
** Form generated from reading UI file 'designerAIfbBP.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DESIGNERAIFBBP_H
#define DESIGNERAIFBBP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayoutMain;
    QVBoxLayout *verticalLayout_10;
    QLabel *helpInfo_9;
    QPushButton *buttonDeleteLastAction_9;
    QComboBox *comboBoxColor_9;
    QComboBox *comboBoxDelay_9;
    QPushButton *buttonLockFigure_9;
    QPushButton *buttonClearCanvas_9;
    QPushButton *buttonTimeCmp_9;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1243, 890);
        MainWindow->setMinimumSize(QSize(0, 35));
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayoutMain = new QHBoxLayout();
        horizontalLayoutMain->setObjectName(QStringLiteral("horizontalLayoutMain"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setSizeConstraint(QLayout::SetMinimumSize);
        helpInfo_9 = new QLabel(centralwidget);
        helpInfo_9->setObjectName(QStringLiteral("helpInfo_9"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(helpInfo_9->sizePolicy().hasHeightForWidth());
        helpInfo_9->setSizePolicy(sizePolicy);
        helpInfo_9->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_10->addWidget(helpInfo_9);

        buttonDeleteLastAction_9 = new QPushButton(centralwidget);
        buttonDeleteLastAction_9->setObjectName(QStringLiteral("buttonDeleteLastAction_9"));
        buttonDeleteLastAction_9->setMinimumSize(QSize(0, 40));

        verticalLayout_10->addWidget(buttonDeleteLastAction_9);

        comboBoxColor_9 = new QComboBox(centralwidget);
        comboBoxColor_9->setObjectName(QStringLiteral("comboBoxColor_9"));
        comboBoxColor_9->setMinimumSize(QSize(0, 40));

        verticalLayout_10->addWidget(comboBoxColor_9);

        comboBoxDelay_9 = new QComboBox(centralwidget);
        comboBoxDelay_9->setObjectName(QStringLiteral("comboBoxDelay_9"));
        comboBoxDelay_9->setMinimumSize(QSize(0, 40));

        verticalLayout_10->addWidget(comboBoxDelay_9);

        buttonLockFigure_9 = new QPushButton(centralwidget);
        buttonLockFigure_9->setObjectName(QStringLiteral("buttonLockFigure_9"));
        buttonLockFigure_9->setMinimumSize(QSize(0, 40));

        verticalLayout_10->addWidget(buttonLockFigure_9);

        buttonClearCanvas_9 = new QPushButton(centralwidget);
        buttonClearCanvas_9->setObjectName(QStringLiteral("buttonClearCanvas_9"));
        buttonClearCanvas_9->setMinimumSize(QSize(0, 40));

        verticalLayout_10->addWidget(buttonClearCanvas_9);

        buttonTimeCmp_9 = new QPushButton(centralwidget);
        buttonTimeCmp_9->setObjectName(QStringLiteral("buttonTimeCmp_9"));
        buttonTimeCmp_9->setMinimumSize(QSize(0, 40));

        verticalLayout_10->addWidget(buttonTimeCmp_9);


        horizontalLayoutMain->addLayout(verticalLayout_10);


        gridLayout->addLayout(horizontalLayoutMain, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1243, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        helpInfo_9->setText(QApplication::translate("MainWindow", "<html><head/><body><p>\320\224\320\273\321\217 \320\276\321\202\321\200\320\270\321\201\320\276\320\262\320\272\320\270 \320\262\320\265\321\200\321\202\320\270\320\272\320\260\320\273\321\214\320\275\321\213\321\205 \320\270 </p><p>\320\263\320\276\321\200\320\270\320\267\320\276\320\275\321\202\320\260\320\273\321\214\320\275\321\213\321\205 \320\273\320\270\320\275\320\270\320\271 \320\267\320\260\320\266\320\274\320\270\321\202\320\265 ctrl</p><p> \320\270 \321\201\321\202\320\260\320\262\321\214\321\202\320\265 \320\274\321\213\321\210\320\272\320\276\320\271 \321\202\320\276\321\207\320\272\320\270</p></body></html>", nullptr));
        buttonDeleteLastAction_9->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\277\320\276\321\201\320\273\320\265\320\264\320\275\321\216\321\216 \321\202\320\276\321\207\320\272\321\203", nullptr));
        buttonLockFigure_9->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\274\320\272\320\275\321\203\321\202\321\214 \320\270 \320\267\320\260\320\272\321\200\320\260\321\201\320\270\321\202\321\214", nullptr));
        buttonClearCanvas_9->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\276\321\202 \320\262\321\201\320\265\320\263\320\276", nullptr));
        buttonTimeCmp_9->setText(QApplication::translate("MainWindow", "\320\241\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\265 \320\262\321\200\320\265\320\274\320\265\320\275\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DESIGNERAIFBBP_H
