#ifndef QTSCRIPTSHELL_QSHORTCUT_H
#define QTSCRIPTSHELL_QSHORTCUT_H

#include <qshortcut.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QShortcut : public QShortcut
{
public:
    QtScriptShell_QShortcut(QWidget*  parent);
    QtScriptShell_QShortcut(const QKeySequence&  key, QWidget*  parent, const char*  member = 0, const char*  ambiguousMember = 0, Qt::ShortcutContext  context = Qt::WindowShortcut);
    ~QtScriptShell_QShortcut();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSHORTCUT_H
