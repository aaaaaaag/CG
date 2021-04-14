//
// Created by denis on 21.03.2021.
//

#ifndef LAB_03_TIMEMANAGER_H
#define LAB_03_TIMEMANAGER_H

#include "QtCharts/QtCharts"
#include "Qt/ISpectreInformationGetter.h"
#include "QPushButton"
#include <ctime>
#include "DrawLine.h"

using namespace QtCharts;

class TimeManager: public QChart{
public:

    explicit TimeManager(ISpectreInformationGetter* spectreDataGetter);

    void ConnectButton(QPushButton* button) const;

private slots:

    void CreateGraph();

private:

    time_t GetDrawTime(DrawType drawType, dot endDot);

    time_t GetTotalDrawTime(DrawType drawType);

    ISpectreInformationGetter* m_pSpectreDataGetter;
    QGraphicsScene *scene;

    time_t maxTime = 0;
};


#endif //LAB_03_TIMEMANAGER_H
