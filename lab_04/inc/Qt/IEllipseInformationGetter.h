//
// Created by denis on 13.04.2021.
//

#ifndef LAB_04_IELLIPSEINFORMATIONGETTER_H
#define LAB_04_IELLIPSEINFORMATIONGETTER_H

#include "DrawLine.h"

class IEllipseInformationGetter
{
public:

    virtual ~IEllipseInformationGetter() = default;

    virtual bool GetCenter(dot& res) = 0;

    virtual bool GetXAxisLen(double& res) = 0;

    virtual bool GetYAxisLen(double& res) = 0;

};


#endif //LAB_04_IELLIPSEINFORMATIONGETTER_H
