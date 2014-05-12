#ifndef QTSCRIPTSHELL_QSTYLEOPTIONGRAPHICSITEM_H
#define QTSCRIPTSHELL_QSTYLEOPTIONGRAPHICSITEM_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStyleOptionGraphicsItem : public QStyleOptionGraphicsItem
{
public:
    QtScriptShell_QStyleOptionGraphicsItem();
    QtScriptShell_QStyleOptionGraphicsItem(const QStyleOptionGraphicsItem&  other);
    QtScriptShell_QStyleOptionGraphicsItem(int  version);
    ~QtScriptShell_QStyleOptionGraphicsItem();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONGRAPHICSITEM_H
