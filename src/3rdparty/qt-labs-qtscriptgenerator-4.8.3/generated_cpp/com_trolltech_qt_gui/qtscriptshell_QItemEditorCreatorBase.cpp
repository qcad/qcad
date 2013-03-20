#include "qtscriptshell_QItemEditorCreatorBase.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QItemEditorCreatorBase::QtScriptShell_QItemEditorCreatorBase()
    : QItemEditorCreatorBase() {}

QtScriptShell_QItemEditorCreatorBase::~QtScriptShell_QItemEditorCreatorBase() {}

QWidget*  QtScriptShell_QItemEditorCreatorBase::createWidget(QWidget*  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("createWidget");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createWidget") & QScriptValue::QObjectMember)) {
        qFatal("QItemEditorCreatorBase::createWidget() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QWidget* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

QByteArray  QtScriptShell_QItemEditorCreatorBase::valuePropertyName() const
{
    QScriptValue _q_function = __qtscript_self.property("valuePropertyName");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("valuePropertyName") & QScriptValue::QObjectMember)) {
        qFatal("QItemEditorCreatorBase::valuePropertyName() is abstract!");
    } else {
        return qscriptvalue_cast<QByteArray >(_q_function.call(__qtscript_self));
    }
}

