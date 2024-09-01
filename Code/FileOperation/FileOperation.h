#ifndef FILEOPERATION_H
#define FILEOPERATION_H
#include <QString>
#include <QStringList>
#include <QSet>

class FileOperation
{
public:
    FileOperation();
    static QString urlsUnique(QStringList urls);
    static QString urlsWriteable(QStringList urls);
private:
};

#endif // FILEOPERATION_H
