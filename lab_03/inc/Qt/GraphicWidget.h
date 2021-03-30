//
// Created by denis on 14.03.2021.
//

#ifndef LAB_03_GRAPHICWIDGET_H
#define LAB_03_GRAPHICWIDGET_H

#include "QGraphicsView"
#include "QPushButton"
#include "IDrawTypeGetter.h"
#include "ICoordsGetter.h"
#include "IDrawColorGetter.h"
#include "ISpectreInformationGetter.h"
#include "DrawColorComboBox.h"

class GraphicWidget: public QGraphicsView {
public:

    GraphicWidget();

    void connectButtonToClearCanvas(QPushButton *button) const;

    void connectButtonToAddLineFunc(QPushButton *button, IDrawTypeGetter *boxDrawType,
                                    IDrawColorGetter *boxDrawColor, IDrawColorGetter* backgroundColor, ICoordsGetter *dataLayout);

    void connectButtonToDrawSpectreFunc(QPushButton *button, IDrawTypeGetter *boxDrawType,
                                        IDrawColorGetter *boxDrawColor, IDrawColorGetter* backgroundColor, ISpectreInformationGetter* dataGetter);

public slots:

    void Clear();

    void AddLine();

    void DrawSpectre();

private:

    QGraphicsScene *mScene;

    ICoordsGetter* m_pDrawDataGetter = nullptr;
    IDrawTypeGetter* m_pDrawTypeGetter = nullptr;
    IDrawColorGetter* m_pDrawColorGetter = nullptr;
    IDrawColorGetter* m_pBackgroundColorGetter = nullptr;


    ISpectreInformationGetter* m_pSpecterDataGetter = nullptr;
};


#endif //LAB_03_GRAPHICWIDGET_H
