//
// Created by denis on 13.04.2021.
//

#ifndef LAB_04_IELLIPSESPECTREINFORMATIONGETTER_H
#define LAB_04_IELLIPSESPECTREINFORMATIONGETTER_H

class IEllipseSpectreInformationGetter
{
public:

    virtual ~IEllipseSpectreInformationGetter() = default;

    virtual bool GetAxisStep(double& res) = 0;

    virtual bool GetEllipseNumb(double& res) = 0;
};

#endif //LAB_04_IELLIPSESPECTREINFORMATIONGETTER_H
