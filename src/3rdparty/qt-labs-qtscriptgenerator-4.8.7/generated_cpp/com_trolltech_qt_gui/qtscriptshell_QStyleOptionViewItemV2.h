#ifndef QTSCRIPTSHELL_QSTYLEOPTIONVIEWITEMV2_H
#define QTSCRIPTSHELL_QSTYLEOPTIONVIEWITEMV2_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionViewItemV2 : public QStyleOptionViewItemV2
{
public:
    QtScriptShell_QStyleOptionViewItemV2();
    QtScriptShell_QStyleOptionViewItemV2(const QStyleOptionViewItem&  other);
    QtScriptShell_QStyleOptionViewItemV2(const QStyleOptionViewItemV2&  other);
    QtScriptShell_QStyleOptionViewItemV2(int  version);
    ~QtScriptShell_QStyleOptionViewItemV2();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONVIEWITEMV2_H
