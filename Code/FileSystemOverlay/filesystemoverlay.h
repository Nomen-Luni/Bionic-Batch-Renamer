#ifndef FILESYSTEMOVERLAY_H
#define FILESYSTEMOVERLAY_H
#include <QMap>
#include <QString>

class FileSystemOverlay
{
public:
    FileSystemOverlay();
    bool RenameFile(QString fromPath, QString toPath, bool allowIdenticalFromTo);
    bool FileExists(QString path);
private:
    QMap<QString,QString> overlayFiles;
};

#endif // FILESYSTEMOVERLAY_H
