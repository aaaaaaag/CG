//
// Created by denis on 08.04.2021.
//

#ifndef LAB_04_ICIRCLEINFORMATIONGETTER_H
#define LAB_04_ICIRCLEINFORMATIONGETTER_H

#include "DrawLine.h"
class ICircleInformationGetter
{
public:

    virtual ~ICircleInformationGetter() = default;

    virtual bool GetCenter(dot& res) = 0;

    virtual bool GetRadius(double& res) = 0;

};

#endif //LAB_04_ICIRCLEINFORMATIONGETTER_H
