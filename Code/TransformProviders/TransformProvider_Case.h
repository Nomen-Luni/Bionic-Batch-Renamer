#ifndef TRANSFORMPROVIDER_CASE_H
#define TRANSFORMPROVIDER_CASE_H

#include "TransformProvider.h"
#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class TransformProvider_Case;
}

class TransformProvider_Case : public TransformProvider
{
public:
    explicit TransformProvider_Case(QWidget *parent = nullptr);
    ~TransformProvider_Case();
    void updateGUIvars();
    QString transform(const QString& inFullUrl, const QString& in, int index, bool& success);

private:
    enum modes
    {
        lower_case,
        upper_case,
        title_case,
        first_letter_uppercase
    };

    Ui::TransformProvider_Case *ui;
    modes mode;
    static QString toTitleCase(const QString& string);
    static QString capitaliseFirstLetter(const QString& string);
};

#endif // TRANSFORMPROVIDER_CASE_H
