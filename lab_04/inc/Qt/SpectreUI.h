//
// Created by denis on 20.03.2021.
//

#ifndef LAB_03_SPECTREUI_H
#define LAB_03_SPECTREUI_H

#include "QGridLayout"
#include "ISpectreInformationGetter.h"
#include "IConverter.h"

class SpectreUI: public QGridLayout, public ISpectreInformationGetter{
public:

    SpectreUI();

    bool GetDegrees(double& res) override;

    bool GetLineLength(double& res) override;

private:

    IConverter *m_pDegreesLine;
    IConverter *m_pCutLength;

};


#endif //LAB_03_SPECTREUI_H
