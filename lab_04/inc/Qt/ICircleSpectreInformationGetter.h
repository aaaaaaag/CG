//
// Created by denis on 13.04.2021.
//

#ifndef LAB_04_ICIRCLESPECTREINFORMATIONGETTER_H
#define LAB_04_ICIRCLESPECTREINFORMATIONGETTER_H


class ICircleSpectreInformationGetter
{
public:

    virtual ~ICircleSpectreInformationGetter() = default;

    virtual bool GetStartRadius(double& res) = 0;

    virtual bool GetEndRadius(double& res) = 0;

    virtual bool GetRadiusStep(double& step) = 0;

    virtual bool GetCircleNumb(double& res) = 0;

};

#endif //LAB_04_ICIRCLESPECTREINFORMATIONGETTER_H
