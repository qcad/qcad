#ifndef QTSCRIPTSHELL_QSTYLEOPTIONRUBBERBAND_H
#define QTSCRIPTSHELL_QSTYLEOPTIONRUBBERBAND_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStyleOptionRubberBand : public QStyleOptionRubberBand
{
public:
    QtScriptShell_QStyleOptionRubberBand();
    QtScriptShell_QStyleOptionRubberBand(const QStyleOptionRubberBand&  other);
    QtScriptShell_QStyleOptionRubberBand(int  version);
    ~QtScriptShell_QStyleOptionRubberBand();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONRUBBERBAND_H
