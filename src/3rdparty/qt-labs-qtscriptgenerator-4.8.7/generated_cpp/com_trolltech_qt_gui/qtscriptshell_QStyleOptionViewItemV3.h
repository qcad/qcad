#ifndef QTSCRIPTSHELL_QSTYLEOPTIONVIEWITEMV3_H
#define QTSCRIPTSHELL_QSTYLEOPTIONVIEWITEMV3_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionViewItemV3 : public QStyleOptionViewItemV3
{
public:
    QtScriptShell_QStyleOptionViewItemV3();
    QtScriptShell_QStyleOptionViewItemV3(const QStyleOptionViewItem&  other);
    QtScriptShell_QStyleOptionViewItemV3(const QStyleOptionViewItemV3&  other);
    QtScriptShell_QStyleOptionViewItemV3(int  version);
    ~QtScriptShell_QStyleOptionViewItemV3();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONVIEWITEMV3_H
