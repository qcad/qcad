#ifndef QTSCRIPTSHELL_QSTYLEOPTIONVIEWITEM_H
#define QTSCRIPTSHELL_QSTYLEOPTIONVIEWITEM_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionViewItem : public QStyleOptionViewItem
{
public:
    QtScriptShell_QStyleOptionViewItem();
    QtScriptShell_QStyleOptionViewItem(const QStyleOptionViewItem&  other);
    QtScriptShell_QStyleOptionViewItem(int  version);
    ~QtScriptShell_QStyleOptionViewItem();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONVIEWITEM_H
