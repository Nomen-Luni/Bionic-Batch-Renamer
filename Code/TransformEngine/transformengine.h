#ifndef TRANSFORMENGINE_H
#define TRANSFORMENGINE_H

#include <QStringList>
#include "enum_transformScope.h"
#include "TransformProviders/transformprovider.h"

class TransformEngine
{
public:
    static QStringList* GetSourceFileNamesListPtr();
    static QStringList* GetTargetFileNamesListPtr();
    static bool AddSourceUrls(QStringList urls);
    static bool RemoveSourceUrl(int index);
    static void ClearSourceUrls();
    static int AddProvider(TransformProvider* provider);
    static int SelectProvider(int index);
    static int SelectScope(transformScope txScope);
    static void DoTransform();
    static bool RenameFiles();
    static QStringList CreateTargetUrls();

private:
    TransformEngine() {}    //Static/singleton- not instanced
    static const int MaxTransformProviders = 50;
    static int numProviders;
    static int selectedProviderIndex;
    static transformScope scope;
    static TransformProvider* transformProviders[MaxTransformProviders];
    static QStringList SourceFileNames;
    static QStringList TargetFileNames;
    static QStringList SourceUrls;
};

#endif // TRANSFORMENGINE_H
