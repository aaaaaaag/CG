//
// Created by denis on 18.04.2021.
//

#ifndef LAB_05_CANVASPOLYGON_H
#define LAB_05_CANVASPOLYGON_H

#include "QGraphicsSceneMouseEvent"
#include "QGraphicsView"
#include "MainWindowUI.h"
#include "Vector.h"
typedef std::pair<int, int> dot_t;
typedef std::vector<dot_t> line_t;

class CanvasPolygon: public QGraphicsView {

    Q_OBJECT

public:
    //virtual ~CanvasPolygon();

    explicit CanvasPolygon(Ui::MainWindow* ui);
    void DrawLine(dot_t A, dot_t B);
    void mousePressEvent(QMouseEvent *event);

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

signals:
    void pressedMouse(QMouseEvent *event);


public slots:


    void pressedAddLineButton();
    void pressedRemoveLineButton();
    void pressedUpdatePolygonButton();
    void lockPolygon();

    void myMousePressEvent(QMouseEvent *event);

private:

    line_t cutLine(dot_t A, dot_t B);
    int GetDirection();
    std::vector<Vector> GetNormals(int dir);
    bool isCtrl;
    bool isAddLine;
    bool isUpdateShape;
    line_t m_cutLine;

    Ui::MainWindow* m_pUi;
    QPointF currentMouseClick;
    QGraphicsScene* m_pScene;
    QPen* m_pPen{};

    std::vector<line_t> m_vLines;
    line_t currentLine;

    std::vector<dot_t> vPolygonDots;
    std::vector<Vector> vNormals;
    int direction;
    void ResizeCanvas(int w, int h);
    void DrawLineDDA(dot_t from, dot_t to);
};


#endif //LAB_05_CANVASPOLYGON_H
