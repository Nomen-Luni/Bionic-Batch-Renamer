#ifndef FILESYSTEMOVERLAY_H
#define FILESYSTEMOVERLAY_H
#include <QMap>
#include <QString>

class FileSystemOverlay
{
public:
    FileSystemOverlay();
    bool renameFile(QString fromPath, QString toPath, bool allowIdenticalFromTo);
    bool fileExists(QString path);
private:
    QMap<QString,QString> overlayFiles;
};

#endif // FILESYSTEMOVERLAY_H
