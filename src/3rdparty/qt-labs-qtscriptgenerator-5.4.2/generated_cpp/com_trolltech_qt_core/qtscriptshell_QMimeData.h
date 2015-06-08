#ifndef QTSCRIPTSHELL_QMIMEDATA_H
#define QTSCRIPTSHELL_QMIMEDATA_H

#include <qmimedata.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QMimeData : public QMimeData
{
public:
    QtScriptShell_QMimeData();
    ~QtScriptShell_QMimeData();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QStringList  formats() const;
    bool  hasFormat(const QString&  mimetype) const;
    QVariant  retrieveData(const QString&  mimetype, QVariant::Type  preferredType) const;
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QMIMEDATA_H
