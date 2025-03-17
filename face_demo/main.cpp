#include "facedialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FaceDialog w;
    w.setModal(true);
    w.exec();

    return a.exec();
}
