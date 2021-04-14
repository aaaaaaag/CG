//
// Created by denis on 20.03.2021.
//

#ifndef LAB_03_DRAWCOLORCOMBOBOX_H
#define LAB_03_DRAWCOLORCOMBOBOX_H

#include "IDrawColorGetter.h"
#include "QComboBox"
#include "map"
#include "string"

class DrawColorComboBox: public IDrawColorGetter, public QComboBox{
public:

    DrawColorComboBox();

    DrawColor GetDrawColor() override;
private:

    void SetBaseColors();

    void connectColor(const std::string& stringColor, DrawColor typeColor);

    std::map<std::string, DrawColor> m_colors;
};


#endif //LAB_03_DRAWCOLORCOMBOBOX_H
