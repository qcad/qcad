#ifndef QTSCRIPTSHELL_QSTYLEOPTIONFOCUSRECT_H
#define QTSCRIPTSHELL_QSTYLEOPTIONFOCUSRECT_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionFocusRect : public QStyleOptionFocusRect
{
public:
    QtScriptShell_QStyleOptionFocusRect();
    QtScriptShell_QStyleOptionFocusRect(const QStyleOptionFocusRect&  other);
    QtScriptShell_QStyleOptionFocusRect(int  version);
    ~QtScriptShell_QStyleOptionFocusRect();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONFOCUSRECT_H
