#ifndef UTILS_H
#define UTILS_H

class QString;

class Utils
{
public:
    Utils();

    static QString cryptByKey(const QString& key, QString target);

    static QString decryptByKey(const QString& key, QString target);
};

#endif // UTILS_H
