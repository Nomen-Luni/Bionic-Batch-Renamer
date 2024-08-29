#ifndef TRANSFORMPROVIDER_INSERTOVERWRITE_H
#define TRANSFORMPROVIDER_INSERTOVERWRITE_H

#include "TransformProvider.h"
#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class TransformProvider_InsertOverwrite;
}

class TransformProvider_InsertOverwrite : public TransformProvider
{
public:
    explicit TransformProvider_InsertOverwrite(QWidget *parent = nullptr);
    ~TransformProvider_InsertOverwrite();
    void updateGUIvars();
    QString transform(const QString& inFullUrl, const QString& in, int index, bool& success);

private:
    enum fromLocations
    {
        from_front,
        from_back
    };
    enum modes
    {
        insert,
        overwrite
    };

    Ui::TransformProvider_InsertOverwrite *ui;

    fromLocations from;
    modes mode;
    int position;
    QString text;
};

#endif // TRANSFORMPROVIDER_INSERTOVERWRITE_H
