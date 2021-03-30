//
// Created by denis on 20.03.2021.
//

#ifndef LAB_03_ISPECTREINFORMATIONGETTER_H
#define LAB_03_ISPECTREINFORMATIONGETTER_H

class ISpectreInformationGetter
{
public:

    virtual bool GetDegrees(double& res) = 0;

    virtual bool GetLineLength(double& res) = 0;

};


#endif //LAB_03_ISPECTREINFORMATIONGETTER_H
