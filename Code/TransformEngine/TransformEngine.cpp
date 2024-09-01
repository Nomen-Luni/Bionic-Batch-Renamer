#include "TransformEngine.h"
#include "./FileSystemOverlay/FileSystemOverlay.h"
#include "./FileOperation/FileOperation.h"
#include <QFileInfo>
#include <QFile>
#include <algorithm>

//Definition of variables declared private static in header
int TransformEngine::numProviders=0;
int TransformEngine::selectedProviderIndex=0;
transformScope TransformEngine::scope;
TransformProvider* TransformEngine::transformProviders[maxTransformProviders];
QStringList TransformEngine::sourceFileNamesList;
QStringList TransformEngine::targetFileNamesList;
QStringList TransformEngine::sourceUrlsList;
//

QStringList TransformEngine::getSourceFileNamesList()
{
    return sourceFileNamesList;
}

QStringList TransformEngine::getTargetFileNamesList()
{
    return targetFileNamesList;
}

QString TransformEngine::addSourceUrls(QStringList urls)
{
    QFileInfo fileInfo;
    QString errorStr=FileOperation::urlsUnique(urls);
    if (errorStr!="")
        return QObject::tr("Selected URLs not added:\nSelected URLs contained duplicates.");

    errorStr=FileOperation::urlsWriteable(urls);
    if (errorStr!="")
        return QObject::tr("Selected URLs not added:\nEnsure user has write access to all selected files and directories.");

    QList<QString> combinedUrlsList(sourceUrlsList);
    combinedUrlsList.append(urls);

    errorStr=FileOperation::urlsUnique(combinedUrlsList);
    if (errorStr!="")
        return QObject::tr("Selected URLs not added:\nCannot re-add urls that have previously been added.");

    sourceUrlsList.append(urls);
    foreach (QString url, urls)
    {
        fileInfo.setFile(url);
        sourceFileNamesList.push_back(fileInfo.fileName());
    }
    return "";
}

bool TransformEngine::removeSourceUrl(int index)
{
    sourceUrlsList.removeAt(index);
    sourceFileNamesList.removeAt(index);
    return true;
}

void TransformEngine::clearSourceUrls()
{
    sourceUrlsList.clear();
    sourceFileNamesList.clear();
    targetFileNamesList.clear();
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
    targetFileNamesList.clear();
    auto provider=transformProviders[selectedProviderIndex];
    provider->transformMulti(sourceUrlsList, sourceFileNamesList, targetFileNamesList, scope);
}

QStringList TransformEngine::createTargetUrls()
{
    QStringList targetUrls;
    QFileInfo fileInfo;
    for (int index=0; index<sourceUrlsList.length(); index++)
    {
        fileInfo.setFile(sourceUrlsList[index]);
        QString targetUrl=fileInfo.absolutePath()+"/"+targetFileNamesList[index];
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
    for (int index=0; index<sourceUrlsList.length(); index++)
    {
        success=fsOverlay.renameFile(sourceUrlsList[index],TargetUrls[index], true);
        if (success==false) return false;
    }

    for (int index=0; index<sourceUrlsList.length(); index++)
    {
        QFile sourcefile(sourceUrlsList[index]);
        if (sourceUrlsList[index]==TargetUrls[index]) continue; //No change to filename
        success=sourcefile.rename(TargetUrls[index]);
        if (success==false) return false;
    }

    //Update our stored source file names to match the renamed file names
    sourceUrlsList.clear();
    sourceFileNamesList.clear();
    foreach (QString targetUrl,TargetUrls)
    {
        sourceUrlsList.append(targetUrl);
    }
    foreach (QString targetFileName,targetFileNamesList)
    {
        sourceFileNamesList.append(targetFileName);
    }

    return true;
}

bool TransformEngine::sortSourceUrls(bool reverseAlphabetical)
{
    QFileInfo fileInfo;

    sourceUrlsList.sort(Qt::CaseInsensitive);  //Sorts alphabetically
    if (reverseAlphabetical)
    {
        std::reverse(sourceUrlsList.begin(), sourceUrlsList.end());
    }

    //Now update the source and target filenames
    sourceFileNamesList.clear();
    foreach (QString url, sourceUrlsList)
    {
        fileInfo.setFile(url);
        sourceFileNamesList.push_back(fileInfo.fileName());
    }
    return true;
}
