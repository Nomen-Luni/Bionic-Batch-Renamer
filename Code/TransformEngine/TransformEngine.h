#ifndef TRANSFORMENGINE_H
#define TRANSFORMENGINE_H

#include <QStringList>
#include "TransformProviders/enum_transformScope.h"
#include "TransformProviders/TransformProvider.h"

class TransformEngine
{
public:
    static QStringList getSourceFileNamesList();
    static QStringList getTargetFileNamesList();
    static QString addSourceUrls(QStringList urls);
    static bool removeSourceUrl(int index);
    static void clearSourceUrls();
    static int addProvider(TransformProvider* provider);
    static int selectProvider(int index);
    static int selectScope(transformScope txScope);
    static void doTransform();
    static bool renameFiles();
    static QStringList createTargetUrls();
    static bool sortSourceUrls(bool reverseAlphabetical);

private:
    TransformEngine() {}    //Static/singleton- not instanced
    static const int maxTransformProviders = 50;
    static int numProviders;
    static int selectedProviderIndex;
    static transformScope scope;
    static TransformProvider* transformProviders[maxTransformProviders];
    static QStringList sourceFileNamesList;
    static QStringList targetFileNamesList;
    static QStringList sourceUrlsList;
};

#endif // TRANSFORMENGINE_H
