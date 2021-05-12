//
// Created by denis on 18.04.2021.
//

#ifndef LAB_05_CANVASPOLYGON_H
#define LAB_05_CANVASPOLYGON_H

#include "QGraphicsSceneMouseEvent"
#include "QGraphicsView"
#include "MainWindowUI.h"

typedef std::pair<int, int> dot_t;
typedef std::vector<dot_t> line_t;
typedef std::vector<std::vector<QColor>> myPixMap_t;

class CanvasPolygon: public QGraphicsView {

    Q_OBJECT

public:
    //virtual ~CanvasPolygon();

    explicit CanvasPolygon(Ui::MainWindow* ui);
    void DrawLine();
    void mousePressEvent(QMouseEvent *event);

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

signals:
    void pressedMouse(QMouseEvent *event);


public slots:

    void pressedAddLineButton();
    void pressedRemoveLineButton();
    void pressedUpdateRectangleButton();

    void myMousePressEvent(QMouseEvent *event);

private:
    bool isCtrl;
    bool isAddLine;
    bool isUpdateRectangle;


    Ui::MainWindow* m_pUi;
    QPointF currentMouseClick;
    QGraphicsScene* m_pScene;
    QPen* m_pPen{};

    std::vector<line_t> m_vLines;
    line_t currentLine;

    dot_t rectangleStartDot;
    double rectangleWidth;
    double rectangleHeight;


    void ResizeCanvas(int w, int h);
    void DrawLineDDA(dot_t from, dot_t to);
    void drawRectangle();
};


#endif //LAB_05_CANVASPOLYGON_H
