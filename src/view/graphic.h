#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QDateTime>
#include <QDateTimeAxis>
#include <QMainWindow>
#include <QMouseEvent>
#include <QScatterSeries>
#include <QWheelEvent>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

class Graphic : public QChartView {
  Q_OBJECT

 public:
  using point_t = std::vector<std::pair<QDateTime, long double>>;

  explicit Graphic(QWidget *parent = nullptr);
  ~Graphic();

 public slots:
  void Draw(const Graphic::point_t &, const QString & = "");
  void DrawStartingPoints(const Graphic::point_t &, QString &);
  void Clear();

 private:
  QDateTimeAxis *axis_x_;
  QValueAxis *axis_y_;
  QChart *chart_;

  short graph_count_;

  void wheelEvent(QWheelEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

 signals:
  void SetMinimum(int);
  void SetEnabledDraw(bool);
};
#endif  // GRAPHIC_H
