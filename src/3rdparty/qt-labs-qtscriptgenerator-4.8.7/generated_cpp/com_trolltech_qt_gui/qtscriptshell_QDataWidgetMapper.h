#ifndef QTSCRIPTSHELL_QDATAWIDGETMAPPER_H
#define QTSCRIPTSHELL_QDATAWIDGETMAPPER_H

#include <qdatawidgetmapper.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QDataWidgetMapper : public QDataWidgetMapper
{
public:
    QtScriptShell_QDataWidgetMapper(QObject*  parent = 0);
    ~QtScriptShell_QDataWidgetMapper();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void setCurrentIndex(int  index);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QDATAWIDGETMAPPER_H
