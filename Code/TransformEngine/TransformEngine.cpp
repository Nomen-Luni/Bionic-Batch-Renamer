#include "TransformEngine.h"
#include "./FileSystemOverlay/FileSystemOverlay.h"
#include <QFileInfo>
#include <QFile>
#include <algorithm>

//Definition of variables declared private static in header
int TransformEngine::numProviders=0;
int TransformEngine::selectedProviderIndex=0;
transformScope TransformEngine::scope;
TransformProvider* TransformEngine::transformProviders[maxTransformProviders];
QStringList TransformEngine::sourceFileNames;
QStringList TransformEngine::targetFileNames;
QStringList TransformEngine::sourceUrls;
//

QStringList* TransformEngine::getSourceFileNamesListPtr()
{
    return &sourceFileNames;
}

QStringList* TransformEngine::getTargetFileNamesListPtr()
{
    return &targetFileNames;
}

bool TransformEngine::addSourceUrls(QStringList urls)
{
    QFileInfo fileInfo;
    foreach (QString url, urls)
    {
        fileInfo.setFile(url);
        if (fileInfo.isWritable()==false) return false;
    }
    sourceUrls.append(urls);
    foreach (QString url, urls)
    {
        fileInfo.setFile(url);
        sourceFileNames.push_back(fileInfo.fileName());
    }
    return true;
}

bool TransformEngine::removeSourceUrl(int index)
{
    sourceUrls.removeAt(index);
    sourceFileNames.removeAt(index);
    return true;
}

void TransformEngine::clearSourceUrls()
{
    sourceUrls.clear();
    sourceFileNames.clear();
    targetFileNames.clear();
}

int TransformEngine::addProvider(TransformProvider* provider)
{
    if (numProviders<maxTransformProviders)
    {
        transformProviders[numProviders]=provider;
        numProviders++;
    }
    return 0;
}

int TransformEngine::selectProvider(int index)
{
    selectedProviderIndex=index;
    return 0;
}

int TransformEngine::selectScope(transformScope scope)
{
    TransformEngine::scope=scope;
    return 0;
}

void TransformEngine::doTransform()
{
    targetFileNames.clear();
    auto provider=transformProviders[selectedProviderIndex];
    provider->transformMulti(sourceUrls, sourceFileNames, targetFileNames, scope);
}

QStringList TransformEngine::createTargetUrls()
{
    QStringList targetUrls;
    QFileInfo fileInfo;
    for (int index=0; index<sourceUrls.length(); index++)
    {
        fileInfo.setFile(sourceUrls[index]);
        QString targetUrl=fileInfo.absolutePath()+"/"+targetFileNames[index];
        targetUrls.append(targetUrl);
    }
    return targetUrls;
}

bool TransformEngine::renameFiles()
{
    bool success;
    QStringList TargetUrls=TransformEngine::createTargetUrls();

    //Test renames virtually before moving any files - identifies name clashes and illegal file names
    FileSystemOverlay fsOverlay;
    for (int index=0; index<sourceUrls.length(); index++)
    {
        success=fsOverlay.RenameFile(sourceUrls[index],TargetUrls[index], true);
        if (success==false) return false;
    }

    for (int index=0; index<sourceUrls.length(); index++)
    {
        QFile sourcefile(sourceUrls[index]);
        if (sourceUrls[index]==TargetUrls[index]) continue; //No change to filename
        success=sourcefile.rename(TargetUrls[index]);
        if (success==false) return false;
    }

    //Update our stored source file names to match the renamed file names
    sourceUrls.clear();
    sourceFileNames.clear();
    foreach (QString targetUrl,TargetUrls)
    {
        sourceUrls.append(targetUrl);
    }
    foreach (QString targetFileName,targetFileNames)
    {
        sourceFileNames.append(targetFileName);
    }

    return true;
}

bool TransformEngine::sortSourceUrls(bool reverseAlphabetical)
{
    QFileInfo fileInfo;

    sourceUrls.sort(Qt::CaseInsensitive);  //Sorts alphabetically
    if (reverseAlphabetical)
    {
        std::reverse(sourceUrls.begin(), sourceUrls.end());
    }

    //Now update the source and target filenames
    sourceFileNames.clear();
    foreach (QString url, sourceUrls)
    {
        fileInfo.setFile(url);
        sourceFileNames.push_back(fileInfo.fileName());
    }
    return true;
}
