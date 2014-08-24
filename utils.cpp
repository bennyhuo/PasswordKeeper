#include "utils.h"
#include <QtCore>

Utils::Utils()
{
}

QString Utils::cryptByKey(const QString &key, QString target)
{
    QByteArray kb,tb;
    kb.append(key);
    tb.append(target);

    qDebug() << tb;
    for(int i = 0;i<tb.size();i++){
        int j = i % kb.size();
        tb[i] = tb.at(i)+kb.at(j);
    }
    tb = tb.toBase64();
    qDebug() << tb;

//    target.clear();
//    target.append(tb);
    QString ret;
    ret.append(tb);
    return ret;
}

QString Utils::decryptByKey(const QString &key, QString target)
{
    QByteArray kb,tb;
    kb.append(key);
    tb.append(target);

    qDebug() << tb;
    tb= QByteArray::fromBase64(tb);
    for(int i = 0;i<tb.size();i++){
        int j = i % kb.size();
        tb[i] = tb.at(i)-kb.at(j);
    }
    qDebug() << tb;

    QString ret;
    ret.append(tb);
    return ret;
}


