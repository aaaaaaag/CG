//
// Created by denis on 20.03.2021.
//

#ifndef LAB_03_IDRAWCOLORGETTER_H
#define LAB_03_IDRAWCOLORGETTER_H

#include "DrawLine.h"

class IDrawColorGetter
{
public:

    virtual ~IDrawColorGetter() = default;

    virtual DrawColor GetDrawColor() = 0;

};

#endif //LAB_03_IDRAWCOLORGETTER_H
