#include "QtCsv.h"

#include <QDebug>
#include <QTextCodec>

QtCsv::QtCsv()
{
    m_file = NULL;
}

QtCsv::~QtCsv()
{
    if (m_file)
        delete m_file;
}

bool QtCsv::open(const QString &fileName)
{
    m_file = new QFile(fileName);
    if (!m_file->open(QIODevice::ReadWrite)) {
        qDebug()<<"[error] "<<QString("Open %1 file failed!").arg(fileName);
        return false;
    }
    else {
        return true;
    }
}

bool QtCsv::readAll(QList<QVariantMap> &results)
{
    if (m_file == NULL)
        return false;

    bool isFirstLine = true;
    QStringList titles;

    while (!m_file->atEnd()) {
        QByteArray line = m_file->readLine();
        QStringList contents = QString(line.toStdString().data()).split(',', QString::SkipEmptyParts);

        if (isFirstLine) {
            isFirstLine = false;
            titles = contents;
        }

        QVariantMap item;
        for (int i = 0; i < contents.count(); i++) {
            if (i >= titles.count())
                continue;
            item[titles[i]] = contents.at(i);
        }

        results.append(item);
    }

    return true;
}

bool QtCsv::write(const QList<QVariantMap> &maps)
{
    if (m_file == NULL)
        return false;

    /* 将内容写入到文件 */
//    QTextCodec *codec = QTextCodec::codecForName("GB18030");
//    if (codec == NULL) {
//        qDebug()<<"[Error] Can't find GB18030 codec.";
//        return false;
//    }

//    QByteArray encodedString = codec->fromUnicode(QString::fromUtf8("名称,型号,一级类别,二级类别,价格,性能特点,产品描述,代表厂家,\n"));
//    filelength += encodedString.size();
//    m_file->write(encodedString);

    QString content;
    QString titles;
    for (int i = 0; i < maps.size(); i++) {
        const QVariantMap &item = maps[i];

        QMapIterator<QString, QVariant> iter(item);
        while (iter.hasNext()) {
            iter.next();

            if (i == 0) {
                titles.append(QString("%1,").arg(iter.key()));
                if (i < maps.size() -1 )
                    titles.append(QString("\n"));
            }
            else {
                content.append(QString("%1,").arg(iter.value().toString()));
                if (i < maps.size() -1 )
                    content.append(QString("\n"));
            }
        }

        if (i == 0)
            m_file->write(titles.toStdString().c_str(), titles.size());

        m_file->write(content.toStdString().c_str(), content.size());
    }

    return true;
}

void QtCsv::close()
{
    m_file->close();
}
