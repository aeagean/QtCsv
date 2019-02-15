#ifndef QTCSV_H
#define QTCSV_H

#include <QFile>
#include <QString>
#include <QVariantMap>

class QtCsv
{
public:
    QtCsv();
    virtual ~QtCsv();

    bool open(const QString &fileName);
    QList<QVariantMap> readAll();
    bool write(const QList<QVariantMap> &maps);
    void close();

private:
    QStringList splitCSVLine(const QString &lineStr);

private:
    QFile *m_file;
};

#endif // QTCSV_H
