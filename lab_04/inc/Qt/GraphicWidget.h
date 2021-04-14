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
#include "ICircleInformationGetter.h"
#include "IEllipseInformationGetter.h"
#include "ICircleSpectreInformationGetter.h"
#include "IEllipseSpectreInformationGetter.h"

class GraphicWidget: public QGraphicsView {
public:

    GraphicWidget();

    void connectButtonToClearCanvas(QPushButton *button) const;

    void connectButtonToAddCircleFunc(QPushButton *button, IDrawTypeGetter *boxDrawType,
                                      IDrawColorGetter *boxDrawColor, IDrawColorGetter* backgroundColor, ICircleInformationGetter *dataLayout);

    void connectButtonToAddEllipseFunc(QPushButton *button, IDrawTypeGetter *boxDrawType,
                                      IDrawColorGetter *boxDrawColor, IDrawColorGetter* backgroundColor, IEllipseInformationGetter *dataLayout);

    void connectButtonToCircleSpectre(QPushButton *button, IDrawTypeGetter *boxDrawType,
                                      IDrawColorGetter *boxDrawColor, IDrawColorGetter* backgroundColor, ICircleSpectreInformationGetter* dataGetter);

    void connectButtonToEllipseSpectre(QPushButton *button, IDrawTypeGetter *boxDrawType,
                                      IDrawColorGetter *boxDrawColor, IDrawColorGetter* backgroundColor, IEllipseSpectreInformationGetter* dataGetter);
public slots:

    void Clear();

    void addCircle();

    void addEllipse();

    void drawCircleSpectre();

    void drawEllipseSpectre();

private:

    QGraphicsScene *mScene;

    ICircleInformationGetter* m_pCircleDataGetter = nullptr;
    IEllipseInformationGetter* m_pEllipseDataGetter = nullptr;
    ICircleSpectreInformationGetter* m_pCircleSpectreDataGetter = nullptr;
    IEllipseSpectreInformationGetter* m_pEllipseSpectreDataGetter = nullptr;

    ICoordsGetter* m_pDrawDataGetter = nullptr;
    IDrawTypeGetter* m_pDrawTypeGetter = nullptr;
    IDrawColorGetter* m_pDrawColorGetter = nullptr;
    IDrawColorGetter* m_pBackgroundColorGetter = nullptr;


    ISpectreInformationGetter* m_pSpecterDataGetter = nullptr;
};


#endif //LAB_03_GRAPHICWIDGET_H
