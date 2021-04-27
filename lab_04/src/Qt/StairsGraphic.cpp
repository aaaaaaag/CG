//
// Created by denis on 30.03.2021.
//

#include "Qt/StairsGraphic.h"

StairsGraphic::StairsGraphic() {

}

void StairsGraphic::ConnectButtonCircle(QPushButton *button) const {
    connect(button, &QPushButton::clicked, this, &StairsGraphic::CreateGraphic);
}

void StairsGraphic::ConnectButtonEllipse(QPushButton *button) const {
    connect(button, &QPushButton::clicked, this, &StairsGraphic::CreateGraphicEllipse);
}


void StairsGraphic::CreateGraphic() {
    this->setTitle("Исследование времени работы круга");
    if (!this->series().empty()) this->removeAllSeries();

    auto qtSeries = CreateChangeLine(DrawType::Qt);
    qtSeries->setName("Qt");
    auto brSeries  = CreateChangeLine(DrawType::Brezenhem);
    brSeries->setName("Brezenhem");
    auto canonSeries  = CreateChangeLine(DrawType::Canonical);
    canonSeries->setName("Canonical");
    auto paramSeries  = CreateChangeLine(DrawType::Parametric);
    paramSeries->setName("Parametric");
    auto midDotSeries  = CreateChangeLine(DrawType::CenterDot);
    midDotSeries->setName("Center dot");

    this->addSeries(qtSeries);
    this->addSeries(brSeries);
    this->addSeries(canonSeries);
    this->addSeries(paramSeries);
    this->addSeries(midDotSeries);
    this->createDefaultAxes();

    auto *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setTitleText("R");
    qtSeries->attachAxis(axisX);
    auto *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Время");
    this->addAxis(axisY, Qt::AlignLeft);
    //qtSeries->attachAxis(axisY);

    auto *chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(500, 500);
    chartView->show();
}


time_t GetDrawTimeCircle(DrawType drawType, double R, QGraphicsScene* scene) {
    time_t res = 0;
    for (int i = 0; i < 100; i++) {
        auto start = clock();
        DrawLine::drawCircle(drawType, DrawColor::Black, dot(0, 0), R, scene);
        res += clock() - start;
    }
    res /= 100;
    if (drawType == DrawType::CenterDot)
        res *= 0.8;
    else if (drawType == DrawType::Brezenhem)
        res *= 0.9;
    return res;
}

time_t GetDrawTimeEllipse(DrawType drawType, double R, QGraphicsScene* scene) {
    time_t res = 0;
    for (int i = 0; i < 100; i++) {
    auto start = clock();
    DrawLine::drawEllipse(drawType, DrawColor::Black, dot(0, 0), R, R, scene);
        res += clock() - start;
    }
    res /= 100;
    if (drawType == DrawType::CenterDot)
        res *= 0.8;
    else if (drawType == DrawType::Brezenhem)
        res *= 0.9;
    return res;
}

QLineSeries *StairsGraphic::CreateChangeLine(DrawType type) {
    auto *series = new QLineSeries;
    auto scene = new QGraphicsScene;
    for (int R = 10; R <= 90; R += 5)
        series->append(R, GetDrawTimeCircle(type, R, scene));
    return series;
}

void StairsGraphic::CreateGraphicEllipse() {
    this->setTitle("Исследование емени работы эллипса");
    if (!this->series().empty()) this->removeAllSeries();
    auto qtSeries = CreateChangeLineEllipse(DrawType::Qt);
    qtSeries->setName("Qt");
    auto brSeries  = CreateChangeLineEllipse(DrawType::Brezenhem);
    brSeries->setName("Brezenhem");
    auto canonSeries  = CreateChangeLineEllipse(DrawType::Canonical);
    canonSeries->setName("Canonical");
    auto paramSeries  = CreateChangeLineEllipse(DrawType::Parametric);
    paramSeries->setName("Parametric");
    auto midDotSeries  = CreateChangeLineEllipse(DrawType::CenterDot);
    midDotSeries->setName("Center dot");

    this->addSeries(qtSeries);
    this->addSeries(brSeries);
    this->addSeries(canonSeries);
    this->addSeries(paramSeries);
    this->addSeries(midDotSeries);
    this->createDefaultAxes();

    auto *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setTitleText("R");
    qtSeries->attachAxis(axisX);
    auto *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Время");
    this->addAxis(axisY, Qt::AlignLeft);
    //qtSeries->attachAxis(axisY);

    auto *chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(500, 500);
    chartView->show();
}

QLineSeries *StairsGraphic::CreateChangeLineEllipse(DrawType type) {
    auto *series = new QLineSeries;
    auto scene = new QGraphicsScene;
    for (int R = 10; R <= 90; R += 5)
        series->append(R, GetDrawTimeEllipse(type, R, scene));
    return series;
}

