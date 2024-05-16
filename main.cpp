#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
#include <vector>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    mainwindow m;
    m.show();

    return a.exec();
}
