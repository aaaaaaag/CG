//
// Created by denis on 30.03.2021.
//

#include "StairsGraphic.h"

StairsGraphic::StairsGraphic() {

}

void StairsGraphic::ConnectButton(QPushButton *button) const {
    connect(button, &QPushButton::clicked, this, &StairsGraphic::CreateGraphic);
}

void StairsGraphic::CreateGraphic() {
    this->setTitle("Исследование ступенчатости");

    auto qtSeries  = CreateChangeLine(DrawType::DDA);
    qtSeries->setName("DDA");
    auto brFloatSeries  = CreateChangeLine(DrawType::BrezenhemFloat);
    brFloatSeries->setName("Brez. float");
    auto brIntSeries  = CreateChangeLine(DrawType::BrezenhemInt);
    brIntSeries->setName("Brez. int");


    this->addSeries(qtSeries);
    this->addSeries(brIntSeries);
    this->addSeries(brFloatSeries);
    this->createDefaultAxes();

//    auto *axisX = new QDateTimeAxis;
//    axisX->setTickCount(10);
//    axisX->setFormat("MMM yyyy");
//    axisX->setTitleText("Угол");
//    series->attachAxis(axisX);
//    auto *axisY = new QValueAxis;
//    axisY->setLabelFormat("%i");
//    axisY->setTitleText("Количество ступенек");
//    this->addAxis(axisY, Qt::AlignLeft);
//    series->attachAxis(axisY);
//
    auto *chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(500, 500);
    chartView->show();
}

QLineSeries *StairsGraphic::CreateChangeLine(DrawType type) {
    auto *series = new QLineSeries;
    auto scene = new QGraphicsScene;
    for (int i = 0; i < 90; i += 5)
    {
        double rad = i * M_PI / 180;
        double x = 50 * cos(rad);
        double y = 50 * sin(rad);
        auto stairs = DrawLine::drawLine(type, DrawColor::Black, dot(0, 0), dot(x, y), scene);
        series->append(i, stairs);
    }
    return series;
}
