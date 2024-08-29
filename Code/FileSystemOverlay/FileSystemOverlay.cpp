#include "FileSystemOverlay.h"
#include <QFile>

FileSystemOverlay::FileSystemOverlay()
{

}

bool FileSystemOverlay::renameFile(QString fromPath, QString toPath, bool allowIdenticalFromTo)
{
    if (fileExists(fromPath)==false) return false; //Source file doesn't exist ERROR
    if ((allowIdenticalFromTo) & (toPath==fromPath)) return true; //New name is same as old and that is allowed
    if (fileExists(toPath)) return false; //File already exists at destination ERROR

    overlayFiles.insert(toPath,fromPath);
    overlayFiles.insert(fromPath,"");   //This either creates a new overlay or replaces the existing one
    return true;
}

bool FileSystemOverlay::fileExists(QString path)
{
    //Check overlays first
    if (overlayFiles.contains(path))
    {
        if (overlayFiles.value(path)=="") return false; //File was deleted in overlay
        return true;    //Overlay path string is not empty, therefore a file was moved to this path
    }
    //No corresponding overlay, check real filesystem
    QFile file(path);
    return file.exists();
}
