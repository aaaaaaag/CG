//
// Created by denis on 13.04.2021.
//

#ifndef LAB_04_CIRCLESPECTREPARTUI_H
#define LAB_04_CIRCLESPECTREPARTUI_H

#include "ICircleSpectreInformationGetter.h"
#include "QGridLayout"
#include "IConverter.h"

class CircleSpectrePartUI: public ICircleSpectreInformationGetter, public QGridLayout {
public:

    CircleSpectrePartUI();

    bool GetStartRadius(double &res) override;

    bool GetEndRadius(double &res) override;

    bool GetRadiusStep(double &step) override;

    bool GetCircleNumb(double &res) override;

private:

    IConverter *m_pStartRadius;
    IConverter *m_pEndRadius;
    IConverter *m_pRadiusStep;
    IConverter *m_pCircleNumb;
};


#endif //LAB_04_CIRCLESPECTREPARTUI_H
