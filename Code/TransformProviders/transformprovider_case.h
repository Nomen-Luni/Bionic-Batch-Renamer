#ifndef TRANSFORMPROVIDER_CASE_H
#define TRANSFORMPROVIDER_CASE_H

#include "transformprovider.h"
#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class TransformProvider_case;
}

class TransformProvider_case : public TransformProvider
{
public:
    explicit TransformProvider_case(QWidget *parent = nullptr);
    ~TransformProvider_case();
    void UpdateGUIvars();
    QString transform(const QString& inFullUrl, const QString& in, int index, bool& success);

private:
    enum modes
    {
        lower_case,
        upper_case,
        title_case,
        first_letter_uppercase
    };

    Ui::TransformProvider_case *ui;
    modes mode;
    static QString toTitleCase(const QString& string);
    static QString capitaliseFirstLetter(const QString& string);
};

#endif // TRANSFORMPROVIDER_CASE_H
