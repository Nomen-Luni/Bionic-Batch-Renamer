#ifndef TRANSFORMPROVIDER_NUMBERING_H
#define TRANSFORMPROVIDER_NUMBERING_H

#include "TransformProvider.h"
#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class TransformProvider_Numbering;
}

class TransformProvider_Numbering : public TransformProvider
{
public:
    explicit TransformProvider_Numbering(QWidget *parent = nullptr);
    ~TransformProvider_Numbering();
    void updateGUIvars();
    QString transform(const QString& inFullUrl, const QString& in, int index, bool& success);

private:
    enum locationTypes
    {
        at_start,
        at_end
    };

    enum spacerTypes
    {
        none,
        space,
        period,
        hyphen,
        underscore
    };

    enum padCharacterTypes
    {
        nopad,
        zeros,
        spaces
    };

    Ui::TransformProvider_Numbering *ui;

    //QString startWith;
    spacerTypes spacerType;
    padCharacterTypes padCharacterType;
    int padWidth;

    int startNumber;
    locationTypes location;
};

#endif // TRANSFORMPROVIDER_NUMBERING_H
