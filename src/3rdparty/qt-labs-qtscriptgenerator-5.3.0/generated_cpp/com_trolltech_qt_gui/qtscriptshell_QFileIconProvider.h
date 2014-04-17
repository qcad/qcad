#ifndef QTSCRIPTSHELL_QFILEICONPROVIDER_H
#define QTSCRIPTSHELL_QFILEICONPROVIDER_H

#include <qfileiconprovider.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QFileIconProvider : public QFileIconProvider
{
public:
    QtScriptShell_QFileIconProvider();
    ~QtScriptShell_QFileIconProvider();

    QIcon  icon(QFileIconProvider::IconType  type) const;
    QIcon  icon(const QFileInfo&  info) const;
    QString  type(const QFileInfo&  info) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFILEICONPROVIDER_H
