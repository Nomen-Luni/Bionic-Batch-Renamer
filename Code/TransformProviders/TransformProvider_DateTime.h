#ifndef TRANSFORMPROVIDER_DATETIME_H
#define TRANSFORMPROVIDER_DATETIME_H

#include "TransformProvider.h"
#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class TransformProvider_DateTime;
}

class TransformProvider_DateTime : public TransformProvider
{
public:
    explicit TransformProvider_DateTime(QWidget *parent = nullptr);
    ~TransformProvider_DateTime();
    void updateGUIvars();
    QString transform(const QString& inFullUrl, const QString& in, int index, bool& success);

private:
    enum dateSelections
    {
        current,
        date_created,
        date_accessed,
        date_modified,
        date_picture_taken
    };

    enum fromLocations
    {
        from_front,
        from_back
    };

    Ui::TransformProvider_DateTime *ui;

    int atPosition;
    dateSelections dateSelect;
    QString format;
    fromLocations from;
};

#endif // TRANSFORMPROVIDER_DATETIME_H
