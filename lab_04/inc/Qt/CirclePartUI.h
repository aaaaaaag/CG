//
// Created by denis on 08.04.2021.
//

#ifndef LAB_04_CIRCLEPARTUI_H
#define LAB_04_CIRCLEPARTUI_H

#include "QGridLayout"
#include "ICircleInformationGetter.h"
#include "EditLineUpdated.h"

class CirclePartUI: public QGridLayout, public ICircleInformationGetter {
public:

    CirclePartUI();

    bool GetCenter(dot& res) override;

    bool GetRadius(double& res) override;

private:

    IConverter *m_pXCenter;
    IConverter *m_pYCenter;
    IConverter *m_pRadius;

};


#endif //LAB_04_CIRCLEPARTUI_H
