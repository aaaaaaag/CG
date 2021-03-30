//
// Created by denis on 20.03.2021.
//

#include "Qt/DrawColorComboBox.h"

DrawColorComboBox::DrawColorComboBox() {
    SetBaseColors();
    for (const auto& color: m_colors)
        addItem(QString(color.first.data()));
}

DrawColor DrawColorComboBox::GetDrawColor() {
    auto selectedName = this->currentText().toStdString();
    return m_colors.at(selectedName);
}

void DrawColorComboBox::connectColor(const std::string& stringColor, DrawColor typeColor) {
    m_colors.emplace(stringColor, typeColor);
}

void DrawColorComboBox::SetBaseColors() {
    connectColor("Black", DrawColor::Black);
    connectColor("White", DrawColor::White);
    connectColor("Red", DrawColor::Red);
    connectColor("Green", DrawColor::Green);
    connectColor("Blue", DrawColor::Blue);
    connectColor("Yellow", DrawColor::Yellow);
}


