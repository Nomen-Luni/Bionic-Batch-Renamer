#ifndef TRANSFORMENGINE_H
#define TRANSFORMENGINE_H

#include <QStringList>
#include "TransformProviders/enum_transformScope.h"
#include "TransformProviders/TransformProvider.h"

class TransformEngine
{
public:
    static QStringList* getSourceFileNamesListPtr();
    static QStringList* getTargetFileNamesListPtr();
    static bool addSourceUrls(QStringList urls);
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
    static QStringList sourceFileNames;
    static QStringList targetFileNames;
    static QStringList sourceUrls;
};

#endif // TRANSFORMENGINE_H
