#ifndef TRANSFORMPROVIDER_H
#define TRANSFORMPROVIDER_H

#include <QWidget>
#include "enum_transformScope.h"

namespace Ui {
class TransformProvider;
}

class TransformProvider : public QWidget
{
    Q_OBJECT

public:
    explicit TransformProvider(QWidget* parent = nullptr):QWidget(parent){}
    QString displayName;
    bool transformMulti(const QStringList& inFullUrls, const QStringList& in, QStringList& out, transformScope txScope);
private:
    virtual QString transform(const QString& inFullUrl, const QString& in, int index, bool& success) = 0;
    virtual void updateGUIvars() = 0;
    bool splitFileName(const QString& fullFileName, QString& filename, QString& extension, bool greedyExtension=false);
};

#endif // TRANSFORMPROVIDER_H
