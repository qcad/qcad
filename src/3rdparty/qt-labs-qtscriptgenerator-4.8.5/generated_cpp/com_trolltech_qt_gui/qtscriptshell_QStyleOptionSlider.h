#ifndef QTSCRIPTSHELL_QSTYLEOPTIONSLIDER_H
#define QTSCRIPTSHELL_QSTYLEOPTIONSLIDER_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionSlider : public QStyleOptionSlider
{
public:
    QtScriptShell_QStyleOptionSlider();
    QtScriptShell_QStyleOptionSlider(const QStyleOptionSlider&  other);
    QtScriptShell_QStyleOptionSlider(int  version);
    ~QtScriptShell_QStyleOptionSlider();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONSLIDER_H
