#ifndef QTSCRIPTSHELL_QINPUTCONTEXT_H
#define QTSCRIPTSHELL_QINPUTCONTEXT_H

#include <qinputcontext.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QInputContext : public QInputContext
{
public:
    QtScriptShell_QInputContext(QObject*  parent = 0);
    ~QtScriptShell_QInputContext();

    QList<QAction* >  actions();
    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  filterEvent(const QEvent*  event);
    QFont  font() const;
    QString  identifierName();
    bool  isComposing() const;
    QString  language();
    void mouseHandler(int  x, QMouseEvent*  event);
    void reset();
    void timerEvent(QTimerEvent*  arg__1);
    void update();
    void widgetDestroyed(QWidget*  w);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QINPUTCONTEXT_H
