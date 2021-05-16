#include "transformengine.h"
#include "./FileSystemOverlay/filesystemoverlay.h"
#include <QFileInfo>
#include <QFile>
#include <algorithm>

//Definition of variables declared private static in header
int TransformEngine::numProviders=0;
int TransformEngine::selectedProviderIndex=0;
transformScope TransformEngine::scope;
TransformProvider* TransformEngine::transformProviders[MaxTransformProviders];
QStringList TransformEngine::SourceFileNames;
QStringList TransformEngine::TargetFileNames;
QStringList TransformEngine::SourceUrls;
//

QStringList* TransformEngine::GetSourceFileNamesListPtr()
{
    return &SourceFileNames;
}

QStringList* TransformEngine::GetTargetFileNamesListPtr()
{
    return &TargetFileNames;
}

bool TransformEngine::AddSourceUrls(QStringList urls)
{
    QFileInfo fileInfo;
    foreach (QString url, urls)
    {
        fileInfo.setFile(url);
        if (fileInfo.isWritable()==false) return false;
    }
    SourceUrls.append(urls);
    foreach (QString url, urls)
    {
        fileInfo.setFile(url);
        SourceFileNames.push_back(fileInfo.fileName());
    }
    return true;
}

bool TransformEngine::RemoveSourceUrl(int index)
{
    SourceUrls.removeAt(index);
    SourceFileNames.removeAt(index);
    return true;
}

void TransformEngine::ClearSourceUrls()
{
    SourceUrls.clear();
    SourceFileNames.clear();
    TargetFileNames.clear();
}

int TransformEngine::AddProvider(TransformProvider* provider)
{
    if (numProviders<MaxTransformProviders)
    {
        transformProviders[numProviders]=provider;
        numProviders++;
    }
    return 0;
}

int TransformEngine::SelectProvider(int index)
{
    selectedProviderIndex=index;
    return 0;
}

int TransformEngine::SelectScope(transformScope scope)
{
    TransformEngine::scope=scope;
    return 0;
}

void TransformEngine::DoTransform()
{
    TargetFileNames.clear();
    auto provider=transformProviders[selectedProviderIndex];
    provider->transformMulti(SourceUrls, SourceFileNames, TargetFileNames, scope);
}

QStringList TransformEngine::CreateTargetUrls()
{
    QStringList targetUrls;
    QFileInfo fileInfo;
    for (int index=0; index<SourceUrls.length(); index++)
    {
        fileInfo.setFile(SourceUrls[index]);
        QString targetUrl=fileInfo.absolutePath()+"/"+TargetFileNames[index];
        targetUrls.append(targetUrl);
    }
    return targetUrls;
}

bool TransformEngine::RenameFiles()
{
    bool success;
    QStringList TargetUrls=TransformEngine::CreateTargetUrls();

    //Test renames virtually before moving any files - identifies name clashes and illegal file names
    FileSystemOverlay fsOverlay;
    for (int index=0; index<SourceUrls.length(); index++)
    {
        success=fsOverlay.RenameFile(SourceUrls[index],TargetUrls[index]);
        if (success==false) return false;
    }

    for (int index=0; index<SourceUrls.length(); index++)
    {
        QFile sourcefile(SourceUrls[index]);
        success=sourcefile.rename(TargetUrls[index]);
        if (success==false) return false;
    }

    //Update our stored source file names to match the renamed file names
    SourceUrls.clear();
    SourceFileNames.clear();
    foreach (QString targetUrl,TargetUrls)
    {
        SourceUrls.append(targetUrl);
    }
    foreach (QString targetFileName,TargetFileNames)
    {
        SourceFileNames.append(targetFileName);
    }

    return true;
}

bool TransformEngine::SortSourceUrls(bool reverseAlphabetical)
{
    QFileInfo fileInfo;

    SourceUrls.sort(Qt::CaseInsensitive);  //Sorts alphabetically
    if (reverseAlphabetical)
    {
        std::reverse(SourceUrls.begin(), SourceUrls.end());
    }

    //Now update the source and target filenames
    SourceFileNames.clear();
    foreach (QString url, SourceUrls)
    {
        fileInfo.setFile(url);
        SourceFileNames.push_back(fileInfo.fileName());
    }
    return true;
}
