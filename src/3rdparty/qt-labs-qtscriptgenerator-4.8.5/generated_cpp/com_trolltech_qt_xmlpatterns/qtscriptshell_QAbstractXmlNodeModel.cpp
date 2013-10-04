#include "qtscriptshell_QAbstractXmlNodeModel.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractxmlnodemodel.h>
#include <qsourcelocation.h>
#include <qurl.h>
#include <qvector.h>
#include <qxmlname.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QXmlNodeModelIndex)
Q_DECLARE_METATYPE(QVector<QXmlNodeModelIndex>)
Q_DECLARE_METATYPE(QXmlNodeModelIndex::DocumentOrder)
Q_DECLARE_METATYPE(QXmlNodeModelIndex::NodeKind)
Q_DECLARE_METATYPE(QVector<QXmlName>)
Q_DECLARE_METATYPE(QAbstractXmlNodeModel::SimpleAxis)

QtScriptShell_QAbstractXmlNodeModel::~QtScriptShell_QAbstractXmlNodeModel() {}

QVector<QXmlNodeModelIndex >  QtScriptShell_QAbstractXmlNodeModel::attributes(const QXmlNodeModelIndex&  element) const
{
    QScriptValue _q_function = __qtscript_self.property("attributes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("attributes") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlNodeModel::attributes() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVector<QXmlNodeModelIndex > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, element)));
    }
}

QUrl  QtScriptShell_QAbstractXmlNodeModel::baseUri(const QXmlNodeModelIndex&  ni) const
{
    QScriptValue _q_function = __qtscript_self.property("baseUri");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("baseUri") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlNodeModel::baseUri() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QUrl >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ni)));
    }
}

QXmlNodeModelIndex::DocumentOrder  QtScriptShell_QAbstractXmlNodeModel::compareOrder(const QXmlNodeModelIndex&  ni1, const QXmlNodeModelIndex&  ni2) const
{
    QScriptValue _q_function = __qtscript_self.property("compareOrder");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("compareOrder") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlNodeModel::compareOrder() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QXmlNodeModelIndex::DocumentOrder >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ni1)
            << qScriptValueFromValue(_q_engine, ni2)));
    }
}

QUrl  QtScriptShell_QAbstractXmlNodeModel::documentUri(const QXmlNodeModelIndex&  ni) const
{
    QScriptValue _q_function = __qtscript_self.property("documentUri");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("documentUri") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlNodeModel::documentUri() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QUrl >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ni)));
    }
}

QXmlNodeModelIndex  QtScriptShell_QAbstractXmlNodeModel::elementById(const QXmlName&  NCName) const
{
    QScriptValue _q_function = __qtscript_self.property("elementById");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("elementById") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlNodeModel::elementById() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QXmlNodeModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, NCName)));
    }
}

QXmlNodeModelIndex::NodeKind  QtScriptShell_QAbstractXmlNodeModel::kind(const QXmlNodeModelIndex&  ni) const
{
    QScriptValue _q_function = __qtscript_self.property("kind");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("kind") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlNodeModel::kind() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QXmlNodeModelIndex::NodeKind >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ni)));
    }
}

QXmlName  QtScriptShell_QAbstractXmlNodeModel::name(const QXmlNodeModelIndex&  ni) const
{
    QScriptValue _q_function = __qtscript_self.property("name");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("name") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlNodeModel::name() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QXmlName >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ni)));
    }
}

QVector<QXmlName >  QtScriptShell_QAbstractXmlNodeModel::namespaceBindings(const QXmlNodeModelIndex&  n) const
{
    QScriptValue _q_function = __qtscript_self.property("namespaceBindings");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("namespaceBindings") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlNodeModel::namespaceBindings() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVector<QXmlName > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, n)));
    }
}

QXmlNodeModelIndex  QtScriptShell_QAbstractXmlNodeModel::nextFromSimpleAxis(QAbstractXmlNodeModel::SimpleAxis  axis, const QXmlNodeModelIndex&  origin) const
{
    QScriptValue _q_function = __qtscript_self.property("nextFromSimpleAxis");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("nextFromSimpleAxis") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlNodeModel::nextFromSimpleAxis() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QXmlNodeModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, axis)
            << qScriptValueFromValue(_q_engine, origin)));
    }
}

QVector<QXmlNodeModelIndex >  QtScriptShell_QAbstractXmlNodeModel::nodesByIdref(const QXmlName&  NCName) const
{
    QScriptValue _q_function = __qtscript_self.property("nodesByIdref");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("nodesByIdref") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlNodeModel::nodesByIdref() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVector<QXmlNodeModelIndex > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, NCName)));
    }
}

QXmlNodeModelIndex  QtScriptShell_QAbstractXmlNodeModel::root(const QXmlNodeModelIndex&  n) const
{
    QScriptValue _q_function = __qtscript_self.property("root");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("root") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlNodeModel::root() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QXmlNodeModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, n)));
    }
}

QString  QtScriptShell_QAbstractXmlNodeModel::stringValue(const QXmlNodeModelIndex&  n) const
{
    QScriptValue _q_function = __qtscript_self.property("stringValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("stringValue") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlNodeModel::stringValue() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, n)));
    }
}

QVariant  QtScriptShell_QAbstractXmlNodeModel::typedValue(const QXmlNodeModelIndex&  n) const
{
    QScriptValue _q_function = __qtscript_self.property("typedValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("typedValue") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlNodeModel::typedValue() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, n)));
    }
}

