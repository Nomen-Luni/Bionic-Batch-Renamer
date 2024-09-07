#ifndef FILEOPERATION_H
#define FILEOPERATION_H
#include <QString>
#include <QStringList>
#include <QSet>

class FileOperation
{
public:
    FileOperation();
    static QString urlsUnique(QStringList urlsList);
    static QString urlsUnique(QSet<QString>* uniqueUrlsSet, QStringList urlsList);
    static QString urlsWriteable(QStringList urls);
    static QString findNonClashingRenameOrder(QStringList sourceUrlsList, QStringList targetUrlsList);
    static QString renameFiles();
    static QString renameFiles(QStringList sourceUrlsList, QStringList targetUrlsList);
private:
    static QString renameFilesNoClashes(QStringList sourceUrlsList, QStringList targetUrlsList);
};

#endif // FILEOPERATION_H
