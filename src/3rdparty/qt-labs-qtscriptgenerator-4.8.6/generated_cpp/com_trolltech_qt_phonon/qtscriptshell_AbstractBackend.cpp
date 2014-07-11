#include "qtscriptshell_AbstractBackend.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(Phonon::BackendInterface::Class)
Q_DECLARE_METATYPE(QSet<QObject*>)
Q_DECLARE_METATYPE(Phonon::ObjectDescriptionType)
Q_DECLARE_METATYPE(QList<int>)
template <> \
struct QMetaTypeId< QHash<QByteArray,QVariant> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QHash<QByteArray,QVariant> >("QHash<QByteArray,QVariant>"); \
        return metatype_id; \
    } \
};

QtScriptShell_AbstractBackend::QtScriptShell_AbstractBackend()
    : Phonon::BackendInterface() {}

QtScriptShell_AbstractBackend::~QtScriptShell_AbstractBackend() {}

QStringList  QtScriptShell_AbstractBackend::availableMimeTypes() const
{
    QScriptValue _q_function = __qtscript_self.property("availableMimeTypes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("availableMimeTypes") & QScriptValue::QObjectMember)) {
        qFatal("AbstractBackend::availableMimeTypes() is abstract!");
    } else {
        return qscriptvalue_cast<QStringList >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_AbstractBackend::connectNodes(QObject*  arg__1, QObject*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("connectNodes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("connectNodes") & QScriptValue::QObjectMember)) {
        qFatal("AbstractBackend::connectNodes() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

QObject*  QtScriptShell_AbstractBackend::createObject(Phonon::BackendInterface::Class  c, QObject*  parent, const QList<QVariant >&  args)
{
    QScriptValue _q_function = __qtscript_self.property("createObject");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createObject") & QScriptValue::QObjectMember)) {
        qFatal("AbstractBackend::createObject() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QObject* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, c)
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, args)));
    }
}

bool  QtScriptShell_AbstractBackend::disconnectNodes(QObject*  arg__1, QObject*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("disconnectNodes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("disconnectNodes") & QScriptValue::QObjectMember)) {
        qFatal("AbstractBackend::disconnectNodes() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

bool  QtScriptShell_AbstractBackend::endConnectionChange(QSet<QObject* >  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("endConnectionChange");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endConnectionChange") & QScriptValue::QObjectMember)) {
        qFatal("AbstractBackend::endConnectionChange() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

QList<int >  QtScriptShell_AbstractBackend::objectDescriptionIndexes(Phonon::ObjectDescriptionType  type) const
{
    QScriptValue _q_function = __qtscript_self.property("objectDescriptionIndexes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("objectDescriptionIndexes") & QScriptValue::QObjectMember)) {
        qFatal("AbstractBackend::objectDescriptionIndexes() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QList<int > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, type)));
    }
}

QHash<QByteArray , QVariant >  QtScriptShell_AbstractBackend::objectDescriptionProperties(Phonon::ObjectDescriptionType  type, int  index) const
{
    QScriptValue _q_function = __qtscript_self.property("objectDescriptionProperties");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("objectDescriptionProperties") & QScriptValue::QObjectMember)) {
        qFatal("AbstractBackend::objectDescriptionProperties() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QHash<QByteArray , QVariant > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, type)
            << qScriptValueFromValue(_q_engine, index)));
    }
}

bool  QtScriptShell_AbstractBackend::startConnectionChange(QSet<QObject* >  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("startConnectionChange");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startConnectionChange") & QScriptValue::QObjectMember)) {
        qFatal("AbstractBackend::startConnectionChange() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

