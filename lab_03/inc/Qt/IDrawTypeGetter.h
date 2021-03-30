//
// Created by denis on 14.03.2021.
//

#ifndef LAB_03_IDRAWTYPEGETTER_H
#define LAB_03_IDRAWTYPEGETTER_H

#include <DrawLine.h>


class IDrawTypeGetter
{
public:
    virtual ~IDrawTypeGetter() = default;

    virtual DrawType GetSelectedMode() = 0;

};

#endif //LAB_03_IDRAWTYPEGETTER_H
