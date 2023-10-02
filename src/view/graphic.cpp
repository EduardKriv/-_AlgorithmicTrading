#include "graphic.h"

Graphic::Graphic(QWidget *parent)
    : QChartView(parent)
    , axis_x_ { nullptr }
    , axis_y_ { nullptr }
    , chart_ { new QChart() }
    , graph_count_(0)
{
    setOptimizationFlags(DontAdjustForAntialiasing | DontSavePainterState);
    chart_->setAnimationOptions(QChart::NoAnimation);
    chart_->setTheme(QChart::ChartThemeDark);
    setRenderHint(QPainter::Antialiasing);

    chart_->createDefaultAxes();
    setChart(chart_);
}

Graphic::~Graphic() {
    chart_->removeAllSeries();
}

void Graphic::wheelEvent(QWheelEvent *event) {
    qreal factor = event->angleDelta().y() > 0 ? 0.5 : 2.25;
    chart_->zoom(factor);
    update();
}

void Graphic::mouseMoveEvent(QMouseEvent *event) {
    static QPointF mouse_press_pos;

    if (event->buttons() & Qt::LeftButton) {
        QPointF diff = QPointF(event->position() - mouse_press_pos);
        chart_->scroll(qreal(-diff.x()), qreal(diff.y()));
        update();
    }

    mouse_press_pos = QPointF(event->position());
}

void Graphic::DrawStartingPoints(const point_t& data, QString& filename) {
    chart()->deleteLater(); 

    QScatterSeries *series = new QScatterSeries();
    series->setPointsVisible(true);
    series->setMarkerSize(5);

    for (size_t i = 0, size = data.size(); i < size; ++i) {
       auto [ date, value ] = data[i];
       series->append(date.toMSecsSinceEpoch(), value);
    }

    axis_x_ = new QDateTimeAxis();
    axis_y_ = new QValueAxis();

    chart_ = new QChart();
    chart_->legend()->setColor(Qt::white);
    chart_->addSeries(series);

    chart_->addAxis(axis_x_, Qt::AlignBottom);
    chart_->addAxis(axis_y_, Qt::AlignLeft);

    series->attachAxis(axis_x_);
    series->attachAxis(axis_y_);

    chart_->setTitle(filename);
    setChart(chart_);

    chart_->setAnimationOptions(QChart::NoAnimation);
    chart_->setTheme(QChart::ChartThemeDark);

    setRenderHint(QPainter::Antialiasing);

    emit SetMinimum(data.size());
    emit SetEnabledDraw(true);
}

void Graphic::Draw(const point_t& data, const QString& graph_name) {
    QLineSeries *lines = new QLineSeries();
    lines->setPointsVisible(true);
    lines->setMarkerSize(2);
    lines->setName(graph_name);

    for (size_t i = 0, size = data.size(); i < size; ++i) {
        auto [ date, value ] =  data[i];
        lines->append(date.toMSecsSinceEpoch(), value);
    }

    chart_->addSeries(lines);

    lines->attachAxis(axis_x_);
    lines->attachAxis(axis_y_);

    graph_count_++;

    if (graph_count_ == 5) {
        emit SetEnabledDraw(false);
    }
}

void Graphic::Clear()
{ 
    if (graph_count_)
        emit SetEnabledDraw(true);

    auto series = chart_->series();
    for (; graph_count_; --graph_count_) {
        series[graph_count_]->deleteLater();
    }
}
