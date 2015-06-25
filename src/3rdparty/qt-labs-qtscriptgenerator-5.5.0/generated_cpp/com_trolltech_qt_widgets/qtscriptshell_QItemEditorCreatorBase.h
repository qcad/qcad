#ifndef QTSCRIPTSHELL_QITEMEDITORCREATORBASE_H
#define QTSCRIPTSHELL_QITEMEDITORCREATORBASE_H

#include <qitemeditorfactory.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QItemEditorCreatorBase : public QItemEditorCreatorBase
{
public:
    QtScriptShell_QItemEditorCreatorBase();
    ~QtScriptShell_QItemEditorCreatorBase();

    QWidget*  createWidget(QWidget*  parent) const;
    QByteArray  valuePropertyName() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QITEMEDITORCREATORBASE_H
