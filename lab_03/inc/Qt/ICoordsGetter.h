//
// Created by denis on 14.03.2021.
//

#ifndef LAB_03_ICOORDSGETTER_H
#define LAB_03_ICOORDSGETTER_H

#include "DrawLine.h"

class ICoordsGetter
{
public:

    virtual ~ICoordsGetter() = default;

    virtual bool GetStartCoord(dot &res) = 0;

    virtual bool GetEndCoord(dot& res) = 0;

};

#endif //LAB_03_ICOORDSGETTER_H
