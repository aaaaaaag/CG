//
// Created by denis on 13.04.2021.
//

#ifndef LAB_04_ELLIPSEPARTUI_H
#define LAB_04_ELLIPSEPARTUI_H

#include "QGridLayout"
#include "IEllipseInformationGetter.h"
#include "EditLineUpdated.h"

class EllipsePartUI: public QGridLayout, public IEllipseInformationGetter {
public:

    EllipsePartUI();

    bool GetCenter(dot &res) override;

    bool GetXAxisLen(double &res) override;

    bool GetYAxisLen(double &res) override;

private:

    IConverter* xCenter;
    IConverter* yCenter;
    IConverter* xAxis;
    IConverter* yAxis;

};


#endif //LAB_04_ELLIPSEPARTUI_H
