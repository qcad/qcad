#include "qtscriptshell_QItemEditorFactory.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qitemeditorfactory.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QVariant::Type)

QtScriptShell_QItemEditorFactory::QtScriptShell_QItemEditorFactory()
    : QItemEditorFactory() {}

QtScriptShell_QItemEditorFactory::~QtScriptShell_QItemEditorFactory() {}

QWidget*  QtScriptShell_QItemEditorFactory::createEditor(QVariant::Type  type, QWidget*  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("createEditor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createEditor") & QScriptValue::QObjectMember)) {
        return QItemEditorFactory::createEditor(type, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QWidget* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, type)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

QByteArray  QtScriptShell_QItemEditorFactory::valuePropertyName(QVariant::Type  type) const
{
    QScriptValue _q_function = __qtscript_self.property("valuePropertyName");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("valuePropertyName") & QScriptValue::QObjectMember)) {
        return QItemEditorFactory::valuePropertyName(type);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QByteArray >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, type)));
    }
}

