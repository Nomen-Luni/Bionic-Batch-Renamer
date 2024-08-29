#ifndef TRANSFORMPROVIDER_REMOVECHARS_H
#define TRANSFORMPROVIDER_REMOVECHARS_H

#include "TransformProvider.h"
#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class TransformProvider_RemoveChars;
}

class TransformProvider_RemoveChars : public TransformProvider
{
public:
    explicit TransformProvider_RemoveChars(QWidget *parent = nullptr);
    ~TransformProvider_RemoveChars();
    void updateGUIvars();
    QString transform(const QString& inFullUrl, const QString& in, int index, bool& success);

private:
    enum fromToLocations
    {
        fromto_front,
        fromto_back
    };

    Ui::TransformProvider_RemoveChars *ui;

    int fromChars;
    int toChars;
    fromToLocations from;
    fromToLocations to;
    //QPalette paletteSpinboxError;
    //QPalette paletteSpinboxDefault;
};

#endif // TRANSFORMPROVIDER_REMOVECHARS_H
