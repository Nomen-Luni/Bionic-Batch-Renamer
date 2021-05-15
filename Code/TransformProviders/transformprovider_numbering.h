#ifndef TRANSFORMPROVIDER_NUMBERING_H
#define TRANSFORMPROVIDER_NUMBERING_H

#include "transformprovider.h"
#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class TransformProvider_numbering;
}

class TransformProvider_numbering : public TransformProvider
{
public:
    explicit TransformProvider_numbering(QWidget *parent = nullptr);
    ~TransformProvider_numbering();
    void UpdateGUIvars();
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

    Ui::TransformProvider_numbering *ui;

    //QString startWith;
    spacerTypes spacerType;
    padCharacterTypes padCharacterType;
    int padWidth;

    int startNumber;
    locationTypes location;
};

#endif // TRANSFORMPROVIDER_NUMBERING_H
