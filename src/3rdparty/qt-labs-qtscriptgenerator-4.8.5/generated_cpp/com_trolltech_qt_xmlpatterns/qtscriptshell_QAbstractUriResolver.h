#ifndef QTSCRIPTSHELL_QABSTRACTURIRESOLVER_H
#define QTSCRIPTSHELL_QABSTRACTURIRESOLVER_H

#include <qabstracturiresolver.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAbstractUriResolver : public QAbstractUriResolver
{
public:
    QtScriptShell_QAbstractUriResolver(QObject*  parent = 0);
    ~QtScriptShell_QAbstractUriResolver();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QUrl  resolve(const QUrl&  relative, const QUrl&  baseURI) const;
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QABSTRACTURIRESOLVER_H
