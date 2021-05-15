#ifndef TRANSFORMPROVIDER_REMOVECHARS_H
#define TRANSFORMPROVIDER_REMOVECHARS_H

#include "transformprovider.h"
#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class TransformProvider_removeChars;
}

class TransformProvider_removeChars : public TransformProvider
{
public:
    explicit TransformProvider_removeChars(QWidget *parent = nullptr);
    ~TransformProvider_removeChars();
    void UpdateGUIvars();
    QString transform(const QString& inFullUrl, const QString& in, int index, bool& success);

private:
    enum fromToLocations
    {
        fromto_front,
        fromto_back
    };

    Ui::TransformProvider_removeChars *ui;

    int fromChars;
    int toChars;
    fromToLocations from;
    fromToLocations to;
    //QPalette paletteSpinboxError;
    //QPalette paletteSpinboxDefault;
};

#endif // TRANSFORMPROVIDER_REMOVECHARS_H
