#include "view/view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::Controller ctrl;
    s21::View w(&ctrl);
    w.show();
    return a.exec();
}
