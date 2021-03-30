//
// Created by denis on 14.03.2021.
//

#ifndef LAB_03_EDITLINEUPDATED_H
#define LAB_03_EDITLINEUPDATED_H

#include "QLineEdit"
#include "IConverter.h"

class EditLineUpdated: public QLineEdit, public IConverter {
public:

    bool toDouble(double& res) override;

};


#endif //LAB_03_EDITLINEUPDATED_H
