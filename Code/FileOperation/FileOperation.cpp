#include "FileOperation.h"
#include <QFileInfo>

FileOperation::FileOperation() {}

// Checks all urls in <urls> are unique.
QString FileOperation::urlsUnique(QStringList urls)
{
    QSet<QString> uniqueUrls;
    foreach (QString url, urls)
    {
        if (uniqueUrls.contains(url)) return url;
        uniqueUrls.insert(url);
    }
    return "";
}

/*
// Checks the urls in <urls>, when combined with the urls in <existingUniqueUrls>, are all unique.
static QString urlsUnique(QSet<QString> existingUniqueUrls,  QStringList urls)
{

    foreach (QString url, urls)
    {
        if (existingUniqueUrls.contains(url)) return url;
        existingUniqueUrls.insert(url);
    }
    return "";
}
*/

QString FileOperation::urlsWriteable(QStringList urls)
{
    QFileInfo fileInfo;
    foreach (QString url, urls)
    {
        fileInfo.setFile(url);
        if (fileInfo.isWritable()==false) return url;
    }
    return "";
}
