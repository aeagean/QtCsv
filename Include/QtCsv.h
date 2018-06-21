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
    bool readAll(QList<QVariantMap> &results);
    bool write(const QList<QVariantMap> &maps);
    void close();

private:
    QFile *m_file;
};

#endif // QTCSV_H
