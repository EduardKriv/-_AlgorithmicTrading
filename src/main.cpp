#include "view/view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    alg::Controller ctrl;
    alg::View w(&ctrl);
    w.show();
    return a.exec();
}
