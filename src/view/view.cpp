#include "view.h"
#include "./ui_view.h"

namespace s21 {
View::View(s21::Controller* ctrl, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
    , ctrl_(ctrl)
{
    ui->setupUi(this);
    graphic_ = new Graphic();
    ui->graph_layout->addWidget(graphic_);
    SetEnabledDraw(false);

    connect(this, &View::Draw, graphic_, &Graphic::Draw);
    connect(this, &View::DrawPoints, graphic_, &Graphic::DrawStartingPoints);
    connect(graphic_, &Graphic::SetMinimum, ui->sb_dot_amount, &QSpinBox::setMinimum);
    connect(graphic_, &Graphic::SetMinimum, ui->sb_approx_dot_amount, &QSpinBox::setMinimum);
    connect(ui->pb_clear, &QPushButton::clicked, graphic_, &Graphic::Clear);
    connect(graphic_, &Graphic::SetEnabledDraw, this, &View::SetEnabledDraw);

    connect(ui->tp_algorithm, &QTabWidget::currentChanged, graphic_, &Graphic::Clear);
}

View::~View()
{
    delete ui;
    delete graphic_;
}

void View::SetEnabledDraw(bool is_enabled) {
    for (auto button : ui->pb_drawing_group->buttons()) {
        button->setEnabled(is_enabled);
    }
}

void View::on_pb_load_clicked() {
    QString dataset_path = QFileDialog::getOpenFileName(this, QObject::tr("Open Document"), "/", QObject::tr("Csv File (*.csv)"));

    if (dataset_path.isEmpty()) return;

    ctrl_->LoadData(dataset_path.toStdString());
    ui->pb_clear->click();
    emit DrawPoints(ConvertDateToQdate(ctrl_->GetData()), dataset_path.split("/").back());
}

void View::SetDateRange(int extension)
{
    auto [ min, max ] = ctrl_->GetDateRange();
    QDate min_date = QDate::fromString(QString::fromStdString(min), "yyyy-MM-dd");
    QDate max_date = QDate::fromString(QString::fromStdString(max), "yyyy-MM-dd").addDays(extension);

    ui->date_picker->setDateRange(min_date, max_date);
}

void View::on_pb_interpolate_clicked()
{
    ctrl_->Interpolation();
    SetDateRange();
    emit Draw(ConvertDateToQdate(ctrl_->CalcInterpolPoints((ui->sb_dot_amount->value()))));
}

void View::on_pb_calc_by_date_clicked()
{
    auto date_time = ui->date_picker->dateTime();
    std::string formated_date = date_time.toString("yyyy-MM-dd-hh-mm").toStdString();
    double res = 0.;

    if (ui->tp_algorithm->currentIndex() == 0) {
        res = ctrl_->GetInterpolValueByDateTime(formated_date);
    } else {
        res = ctrl_->GetApproxValueByDateTime(formated_date);
    }

    ui->label_result_calc_by_date->setText(QString::number(res, 'f'));
}

void View::on_pb_approximate_clicked()
{
    static int old_extension = 0;
    int extension = ui->sb_extension->value();
    if (old_extension != extension) {
        ui->pb_clear->click();
    }

    ctrl_->Approximation(ui->sb_polynom_degree->value());

    SetDateRange(extension);
    old_extension = extension;
    emit Draw(ConvertDateToQdate(ctrl_->CalcApproxPoints(ui->sb_approx_dot_amount->value(), extension)), ui->sb_polynom_degree->text());
}

Controller::point_t View::ConvertDateToQdate(const s21::Loader::Data& data) {
    float temp(0);
    Controller::point_t converted_data;
    QDateTime first_date = QDateTime::fromString(QString::fromStdString(data.date_.front()), "yyyy-MM-dd");
    for (int i = 0, size = data.date_.size(); i < size; ++i) {
        QDateTime now = first_date.addSecs(std::modf(data.X_[i], &temp) * 3600. * 24.);
        now = now.addDays(temp);
        converted_data.push_back(std::pair(now, data.Y_[i]));
    }

    return converted_data;
}
}  // namespace s21


