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


    void LockAndFill();
    void DeleteLastDot();
    void Clear();
    void myMousePressEvent(QMouseEvent *event);

private:

    bool isCtrl;

    Ui::MainWindow* m_pUi;
    std::vector<QPointF> m_vPolygonDots;
    QPointF currentMouseClick;
    QGraphicsScene* m_pScene;
    QPen* m_pPen{};

    bool isMouseInFigure();
    void ResizeCanvas(int w, int h);
    void CreatePixColorMap(int w, int h);
    std::vector<std::vector<QColor>> m_vPixColorMap;
    std::vector<std::vector<QColor>> m_vPixColorMapOld;
    void DrawLineDDA(dot_t from, dot_t to);
    std::vector<line_t> m_vLines;

    std::vector<dot_t> m_vStack;

    void Fill();

    bool isTrav;

    double minX;
    double maxX;
    double centerX;

};


#endif //LAB_05_CANVASPOLYGON_H
