#include "QtCsv.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QtCsv csv;
    csv.open("../QtCsv/TestFile.csv");
    csv.readAll();
    csv.close();

    return a.exec();
}
