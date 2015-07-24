#include "qtscriptshell_QSimpleXmlNodeModel.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractxmlnodemodel.h>
#include <qsourcelocation.h>
#include <qurl.h>
#include <qvector.h>
#include <qxmlname.h>
#include <qxmlnamepool.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QXmlNodeModelIndex)
Q_DECLARE_METATYPE(QVector<QXmlNodeModelIndex>)
Q_DECLARE_METATYPE(QXmlNodeModelIndex::DocumentOrder)
Q_DECLARE_METATYPE(QXmlNodeModelIndex::NodeKind)
Q_DECLARE_METATYPE(QVector<QXmlName>)
Q_DECLARE_METATYPE(QAbstractXmlNodeModel::SimpleAxis)

QtScriptShell_QSimpleXmlNodeModel::QtScriptShell_QSimpleXmlNodeModel(const QXmlNamePool&  namePool)
    : QSimpleXmlNodeModel(namePool) {}

QtScriptShell_QSimpleXmlNodeModel::~QtScriptShell_QSimpleXmlNodeModel() {}

QVector<QXmlNodeModelIndex >  QtScriptShell_QSimpleXmlNodeModel::attributes(const QXmlNodeModelIndex&  element) const
{
    QScriptValue _q_function = __qtscript_self.property("attributes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("attributes") & QScriptValue::QObjectMember)) {
        qFatal("QSimpleXmlNodeModel::attributes() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVector<QXmlNodeModelIndex > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, element)));
    }
}

QUrl  QtScriptShell_QSimpleXmlNodeModel::baseUri(const QXmlNodeModelIndex&  node) const
{
    QScriptValue _q_function = __qtscript_self.property("baseUri");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("baseUri") & QScriptValue::QObjectMember)) {
        return QSimpleXmlNodeModel::baseUri(node);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QUrl >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, node)));
    }
}

QXmlNodeModelIndex::DocumentOrder  QtScriptShell_QSimpleXmlNodeModel::compareOrder(const QXmlNodeModelIndex&  ni1, const QXmlNodeModelIndex&  ni2) const
{
    QScriptValue _q_function = __qtscript_self.property("compareOrder");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("compareOrder") & QScriptValue::QObjectMember)) {
        qFatal("QSimpleXmlNodeModel::compareOrder() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QXmlNodeModelIndex::DocumentOrder >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ni1)
            << qScriptValueFromValue(_q_engine, ni2)));
    }
}

QUrl  QtScriptShell_QSimpleXmlNodeModel::documentUri(const QXmlNodeModelIndex&  ni) const
{
    QScriptValue _q_function = __qtscript_self.property("documentUri");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("documentUri") & QScriptValue::QObjectMember)) {
        qFatal("QSimpleXmlNodeModel::documentUri() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QUrl >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ni)));
    }
}

QXmlNodeModelIndex  QtScriptShell_QSimpleXmlNodeModel::elementById(const QXmlName&  id) const
{
    QScriptValue _q_function = __qtscript_self.property("elementById");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("elementById") & QScriptValue::QObjectMember)) {
        return QSimpleXmlNodeModel::elementById(id);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QXmlNodeModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, id)));
    }
}

QXmlNodeModelIndex::NodeKind  QtScriptShell_QSimpleXmlNodeModel::kind(const QXmlNodeModelIndex&  ni) const
{
    QScriptValue _q_function = __qtscript_self.property("kind");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("kind") & QScriptValue::QObjectMember)) {
        qFatal("QSimpleXmlNodeModel::kind() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QXmlNodeModelIndex::NodeKind >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ni)));
    }
}

QXmlName  QtScriptShell_QSimpleXmlNodeModel::name(const QXmlNodeModelIndex&  ni) const
{
    QScriptValue _q_function = __qtscript_self.property("name");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("name") & QScriptValue::QObjectMember)) {
        qFatal("QSimpleXmlNodeModel::name() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QXmlName >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ni)));
    }
}

QVector<QXmlName >  QtScriptShell_QSimpleXmlNodeModel::namespaceBindings(const QXmlNodeModelIndex&  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("namespaceBindings");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("namespaceBindings") & QScriptValue::QObjectMember)) {
        return QSimpleXmlNodeModel::namespaceBindings(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVector<QXmlName > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

QXmlNodeModelIndex  QtScriptShell_QSimpleXmlNodeModel::nextFromSimpleAxis(QAbstractXmlNodeModel::SimpleAxis  axis, const QXmlNodeModelIndex&  origin) const
{
    QScriptValue _q_function = __qtscript_self.property("nextFromSimpleAxis");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("nextFromSimpleAxis") & QScriptValue::QObjectMember)) {
        qFatal("QSimpleXmlNodeModel::nextFromSimpleAxis() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QXmlNodeModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, axis)
            << qScriptValueFromValue(_q_engine, origin)));
    }
}

QVector<QXmlNodeModelIndex >  QtScriptShell_QSimpleXmlNodeModel::nodesByIdref(const QXmlName&  idref) const
{
    QScriptValue _q_function = __qtscript_self.property("nodesByIdref");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("nodesByIdref") & QScriptValue::QObjectMember)) {
        return QSimpleXmlNodeModel::nodesByIdref(idref);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVector<QXmlNodeModelIndex > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, idref)));
    }
}

QXmlNodeModelIndex  QtScriptShell_QSimpleXmlNodeModel::root(const QXmlNodeModelIndex&  n) const
{
    QScriptValue _q_function = __qtscript_self.property("root");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("root") & QScriptValue::QObjectMember)) {
        qFatal("QSimpleXmlNodeModel::root() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QXmlNodeModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, n)));
    }
}

QString  QtScriptShell_QSimpleXmlNodeModel::stringValue(const QXmlNodeModelIndex&  node) const
{
    QScriptValue _q_function = __qtscript_self.property("stringValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("stringValue") & QScriptValue::QObjectMember)) {
        return QSimpleXmlNodeModel::stringValue(node);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, node)));
    }
}

QVariant  QtScriptShell_QSimpleXmlNodeModel::typedValue(const QXmlNodeModelIndex&  n) const
{
    QScriptValue _q_function = __qtscript_self.property("typedValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("typedValue") & QScriptValue::QObjectMember)) {
        qFatal("QSimpleXmlNodeModel::typedValue() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, n)));
    }
}

