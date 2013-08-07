#include "qtscriptshell_QUndoCommand.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qundostack.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(const QUndoCommand*)

QtScriptShell_QUndoCommand::QtScriptShell_QUndoCommand(QUndoCommand*  parent)
    : QUndoCommand(parent) {}

QtScriptShell_QUndoCommand::QtScriptShell_QUndoCommand(const QString&  text, QUndoCommand*  parent)
    : QUndoCommand(text, parent) {}

QtScriptShell_QUndoCommand::~QtScriptShell_QUndoCommand() {}

int  QtScriptShell_QUndoCommand::id() const
{
    QScriptValue _q_function = __qtscript_self.property("id");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("id") & QScriptValue::QObjectMember)) {
        return QUndoCommand::id();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QUndoCommand::mergeWith(const QUndoCommand*  other)
{
    QScriptValue _q_function = __qtscript_self.property("mergeWith");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mergeWith") & QScriptValue::QObjectMember)) {
        return QUndoCommand::mergeWith(other);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<const QUndoCommand *>(other))));
    }
}

void QtScriptShell_QUndoCommand::redo()
{
    QScriptValue _q_function = __qtscript_self.property("redo");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("redo") & QScriptValue::QObjectMember)) {
        QUndoCommand::redo();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QUndoCommand::undo()
{
    QScriptValue _q_function = __qtscript_self.property("undo");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("undo") & QScriptValue::QObjectMember)) {
        QUndoCommand::undo();
    } else {
        _q_function.call(__qtscript_self);
    }
}

