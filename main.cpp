#include "mainwindow.h"
#include <QPushButton>
#include <QApplication>
#include "window.h"
#include <iostream>
#include <string>

#include <fstream>
#include "sudoko.h"
#include <QFile>
#include <QIODevice>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication app (argc, argv);
    Window window;
    window.show();
    return app.exec();
}
