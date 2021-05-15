#ifndef TRANSFORMPROVIDER_INSERTOVERWRITE_H
#define TRANSFORMPROVIDER_INSERTOVERWRITE_H

#include "transformprovider.h"
#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class TransformProvider_insertOverwrite;
}

class TransformProvider_insertOverwrite : public TransformProvider
{
public:
    explicit TransformProvider_insertOverwrite(QWidget *parent = nullptr);
    ~TransformProvider_insertOverwrite();
    void UpdateGUIvars();
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

    Ui::TransformProvider_insertOverwrite *ui;

    fromLocations from;
    modes mode;
    int position;
    QString text;
};

#endif // TRANSFORMPROVIDER_INSERTOVERWRITE_H
