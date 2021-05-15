#ifndef TRANSFORMPROVIDER_SEARCHREPLACE_H
#define TRANSFORMPROVIDER_SEARCHREPLACE_H

#include "transformprovider.h"
#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class TransformProvider_searchReplace;
}

class TransformProvider_searchReplace : public TransformProvider
{
public:
    explicit TransformProvider_searchReplace(QWidget *parent = nullptr);
    ~TransformProvider_searchReplace();
    void UpdateGUIvars();
    QString transform(const QString& inFullUrl, const QString& in, int index, bool& success);

private:
    Ui::TransformProvider_searchReplace *ui;

    bool caseSensitiveSearch;
    bool regularExpression;
    QString replaceWith;
    QString searchFor;
};

#endif // TRANSFORMPROVIDER_SEARCHREPLACE_H
