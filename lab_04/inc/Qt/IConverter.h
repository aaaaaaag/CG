//
// Created by denis on 15.03.2021.
//

#ifndef LAB_03_ICONVERTER_H
#define LAB_03_ICONVERTER_H

class IConverter
{
public:

    virtual ~IConverter() = default;

    virtual bool toDouble(double& res) = 0;

};

#endif //LAB_03_ICONVERTER_H
