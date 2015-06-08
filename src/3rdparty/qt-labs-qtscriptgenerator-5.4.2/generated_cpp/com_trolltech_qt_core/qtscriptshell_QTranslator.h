#ifndef QTSCRIPTSHELL_QTRANSLATOR_H
#define QTSCRIPTSHELL_QTRANSLATOR_H

#include <qtranslator.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTranslator : public QTranslator
{
public:
    QtScriptShell_QTranslator(QObject*  parent = 0);
    ~QtScriptShell_QTranslator();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  isEmpty() const;
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTRANSLATOR_H
