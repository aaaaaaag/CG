//
// Created by denis on 13.04.2021.
//

#ifndef LAB_04_ELLIPSESPECTREPARTUI_H
#define LAB_04_ELLIPSESPECTREPARTUI_H

#include "IEllipseSpectreInformationGetter.h"
#include "QGridLayout"
#include "IConverter.h"
class EllipseSpectrePartUI: public IEllipseSpectreInformationGetter, public QGridLayout {
public:

    EllipseSpectrePartUI();

    bool GetAxisStep(double &res) override;

    bool GetEllipseNumb(double &res) override;

private:

    IConverter* m_pAxisStep;
    IConverter* m_pEllipseNumb;

};


#endif //LAB_04_ELLIPSESPECTREPARTUI_H
