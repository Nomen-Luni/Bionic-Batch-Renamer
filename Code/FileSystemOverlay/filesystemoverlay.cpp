#include "filesystemoverlay.h"
//#include <boost/filesystem.hpp>
#include <QFile>

FileSystemOverlay::FileSystemOverlay()
{

}

bool FileSystemOverlay::RenameFile(QString fromPath, QString toPath)
{
    if (FileExists(fromPath)==false) return false; //Source file doesn't exist ERROR
    if (FileExists(toPath)) return false; //File already exists at destination ERROR

    overlayFiles.insert(toPath,fromPath);
    overlayFiles.insert(fromPath,"");   //This either creates a new overlay or replaces the existing one
    return true;
}

bool FileSystemOverlay::FileExists(QString path)
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
