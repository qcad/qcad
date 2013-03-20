#ifndef QTSCRIPTSHELL_QSTYLEOPTIONVIEWITEMV4_H
#define QTSCRIPTSHELL_QSTYLEOPTIONVIEWITEMV4_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionViewItemV4 : public QStyleOptionViewItemV4
{
public:
    QtScriptShell_QStyleOptionViewItemV4();
    QtScriptShell_QStyleOptionViewItemV4(const QStyleOptionViewItem&  other);
    QtScriptShell_QStyleOptionViewItemV4(const QStyleOptionViewItemV4&  other);
    QtScriptShell_QStyleOptionViewItemV4(int  version);
    ~QtScriptShell_QStyleOptionViewItemV4();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONVIEWITEMV4_H
