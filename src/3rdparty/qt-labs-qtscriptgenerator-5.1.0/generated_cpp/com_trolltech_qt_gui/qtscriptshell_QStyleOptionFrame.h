#ifndef QTSCRIPTSHELL_QSTYLEOPTIONFRAME_H
#define QTSCRIPTSHELL_QSTYLEOPTIONFRAME_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStyleOptionFrame : public QStyleOptionFrame
{
public:
    QtScriptShell_QStyleOptionFrame();
    QtScriptShell_QStyleOptionFrame(const QStyleOptionFrame&  other);
    QtScriptShell_QStyleOptionFrame(int  version);
    ~QtScriptShell_QStyleOptionFrame();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONFRAME_H
