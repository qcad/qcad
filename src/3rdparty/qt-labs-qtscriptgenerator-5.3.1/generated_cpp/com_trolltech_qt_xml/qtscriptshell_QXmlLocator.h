#ifndef QTSCRIPTSHELL_QXMLLOCATOR_H
#define QTSCRIPTSHELL_QXMLLOCATOR_H

#include <qxml.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QXmlLocator : public QXmlLocator
{
public:
    QtScriptShell_QXmlLocator();
    ~QtScriptShell_QXmlLocator();

    int  columnNumber() const;
    int  lineNumber() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QXMLLOCATOR_H
