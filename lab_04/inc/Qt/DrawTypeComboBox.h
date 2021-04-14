//
// Created by denis on 14.03.2021.
//

#ifndef LAB_03_DRAWTYPECOMBOBOX_H
#define LAB_03_DRAWTYPECOMBOBOX_H

#include "QComboBox"
#include "DrawLine.h"
#include "IDrawTypeGetter.h"

class DrawTypeComboBox: public QComboBox, public IDrawTypeGetter {
public:

    DrawTypeComboBox();

    DrawType GetSelectedMode() override;

};


#endif //LAB_03_DRAWTYPECOMBOBOX_H
