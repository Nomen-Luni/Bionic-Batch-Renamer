#ifndef SINGLECLICKWORKAROUNDPROXYSTYLE_H
#define SINGLECLICKWORKAROUNDPROXYSTYLE_H

#include <QProxyStyle>

class SingleClickWorkaroundProxyStyle: public QProxyStyle
{
public:
    SingleClickWorkaroundProxyStyle();
    int styleHint(StyleHint hint, const QStyleOption *option = nullptr, const QWidget *widget = nullptr, QStyleHintReturn *returnData = nullptr) const override;
};

#endif // SINGLECLICKWORKAROUNDPROXYSTYLE_H
