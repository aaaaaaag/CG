//
// Created by denis on 21.03.2021.
//

#include "TimeManager.h"
#include "DrawLine.h"
#include "cmath"

TimeManager::TimeManager(ISpectreInformationGetter *spectreDataGetter): m_pSpectreDataGetter(spectreDataGetter) {
    scene = new QGraphicsScene;
}

void TimeManager::CreateGraph() {
    maxTime = 0;
    this->removeAllSeries();
    if (this->axisX()) this->removeAxis(this->axisX());
    if (this->axisY()) this->removeAxis(this->axisY());
    auto *qtPart = new QBarSet("Qt");
    auto *ddaPart = new QBarSet("ЦДА");
    auto *brezenhemFloatPart = new QBarSet("Брезенхем вещ.");
    auto *brezenhemIntpart = new QBarSet("Брезенхем цел.");
    auto *brezenhemStairsPart = new QBarSet("Брезенхем ступенч.");
    auto *wuuPart = new QBarSet("Ву");

    *qtPart << GetTotalDrawTime(DrawType::Qt);
    //*ddaPart << GetTotalDrawTime(DrawType::DDA);
    //*brezenhemFloatPart << GetTotalDrawTime(DrawType::BrezenhemFloat);
    //*brezenhemIntpart << GetTotalDrawTime(DrawType::BrezenhemInt);
    //*brezenhemStairsPart << GetTotalDrawTime(DrawType::BrezenhemStairs);
    //*wuuPart << GetTotalDrawTime(DrawType::Woo);

    auto series = new QBarSeries;
    series->append(qtPart);
    series->append(ddaPart);
    series->append(brezenhemFloatPart);
    series->append(brezenhemIntpart);
    series->append(brezenhemStairsPart);
    series->append(wuuPart);

    this->addSeries(series);
    this->setTitle("Сравнение способов отрисовки линий по времени");
    this->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Time";
    auto axisX = new QBarCategoryAxis;
    axisX->append(categories);
    this->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QValueAxis();
    axisY->setRange(0,maxTime * 1.1);
    this->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    this->legend()->setVisible(true);
    this->legend()->setAlignment(Qt::AlignRight);

    auto *chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->resize(500, 500);
    chartView->show();


}

void TimeManager::ConnectButton(QPushButton *button) const {
    connect(button, &QPushButton::clicked, this, &TimeManager::CreateGraph);
}

time_t TimeManager::GetDrawTime(DrawType drawType, dot endDot) {
    auto start = clock();
   // DrawLine::drawLine(drawType, DrawColor::Black, dot(0, 0), endDot, scene);
    return clock() - start;
}

time_t TimeManager::GetTotalDrawTime(DrawType drawType) {
    time_t totalTime = 0;
    double degrees, cutLength;
    m_pSpectreDataGetter->GetDegrees(degrees);
    m_pSpectreDataGetter->GetLineLength(cutLength);
    if (degrees == 0) degrees = 30;
    if (cutLength == 0) cutLength = 50;
    for (int i = 0; i < 360; i += degrees)
    {
        double rad = i * M_PI / 180;
        double x = cutLength * cos(rad);
        double y = cutLength * sin(rad);
        totalTime += GetDrawTime(drawType, dot(x, y));
    }
    if (totalTime > maxTime) maxTime = totalTime;
    return totalTime;
}
