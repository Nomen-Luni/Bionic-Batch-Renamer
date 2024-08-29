#ifndef TRANSFORMPROVIDER_SEARCHREPLACE_H
#define TRANSFORMPROVIDER_SEARCHREPLACE_H

#include "TransformProvider.h"
#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class TransformProvider_SearchReplace;
}

class TransformProvider_SearchReplace : public TransformProvider
{
public:
    explicit TransformProvider_SearchReplace(QWidget *parent = nullptr);
    ~TransformProvider_SearchReplace();
    void updateGUIvars();
    QString transform(const QString& inFullUrl, const QString& in, int index, bool& success);

private:
    Ui::TransformProvider_SearchReplace *ui;

    bool caseSensitiveSearch;
    bool regularExpression;
    QString replaceWith;
    QString searchFor;
};

#endif // TRANSFORMPROVIDER_SEARCHREPLACE_H
