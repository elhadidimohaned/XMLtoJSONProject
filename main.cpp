#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    QFile stylesheetfile("./Adaptic.qss");
//    stylesheetfile.open(QFile::ReadOnly);
//    QString stylesheet = QLatin1String(stylesheetfile.readAll());
//    a.setStyleSheet(stylesheet);

    QFile file("C://Users//mohan//Documents//XMLtoJson2//Adaptic.qss");
    file.open(QFile::ReadOnly);

    QString styleSheet { QLatin1String(file.readAll()) };

        //setup stylesheet
    a.setStyleSheet(styleSheet);


    w.show();
    return a.exec();
}
