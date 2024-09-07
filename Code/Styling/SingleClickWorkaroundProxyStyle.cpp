#include "SingleClickWorkaroundProxyStyle.h"

SingleClickWorkaroundProxyStyle::SingleClickWorkaroundProxyStyle() {}

// This class is used to work around an issue where file dialogs close as soon as a file is clicked, even if not conigured that way.
// Issue is present on KDE Plasma 6 / Qt 6, regardless of single click behaviour set in desktop settings.

int SingleClickWorkaroundProxyStyle::styleHint(StyleHint hint, const QStyleOption *option,
              const QWidget *widget, QStyleHintReturn *returnData) const
{
    if (hint == SH_ItemView_ActivateItemOnSingleClick)
        return 0;
    return QProxyStyle::styleHint(hint, option, widget, returnData);
}
