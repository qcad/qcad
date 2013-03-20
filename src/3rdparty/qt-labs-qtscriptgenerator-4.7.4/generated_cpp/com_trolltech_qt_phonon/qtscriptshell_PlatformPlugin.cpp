#include "qtscriptshell_PlatformPlugin.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <abstractmediastream.h>
#include <objectdescription.h>
#include <qbytearray.h>
#include <qicon.h>
#include <qlist.h>
#include <qobject.h>
#include <qpair.h>
#include <qstringlist.h>
#include <qurl.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(Phonon::AbstractMediaStream*)
template <> \
struct QMetaTypeId< QPair<QByteArray,QString> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QPair<QByteArray,QString> >("QPair<QByteArray,QString>"); \
        return metatype_id; \
    } \
};
template <> \
struct QMetaTypeId< QList<QPair<QByteArray,QString> > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QList<QPair<QByteArray,QString> > >("QList<QPair<QByteArray,QString> >"); \
        return metatype_id; \
    } \
};
Q_DECLARE_METATYPE(char*)
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

QtScriptShell_PlatformPlugin::QtScriptShell_PlatformPlugin()
    : Phonon::PlatformPlugin() {}

QtScriptShell_PlatformPlugin::~QtScriptShell_PlatformPlugin() {}

QString  QtScriptShell_PlatformPlugin::applicationName() const
{
    QScriptValue _q_function = __qtscript_self.property("applicationName");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("applicationName") & QScriptValue::QObjectMember)) {
        qFatal("PlatformPlugin::applicationName() is abstract!");
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

QObject*  QtScriptShell_PlatformPlugin::createBackend()
{
    QScriptValue _q_function = __qtscript_self.property("createBackend");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createBackend") & QScriptValue::QObjectMember)) {
        qFatal("PlatformPlugin::createBackend() is abstract!");
    } else {
        return qscriptvalue_cast<QObject* >(_q_function.call(__qtscript_self));
    }
}

QObject*  QtScriptShell_PlatformPlugin::createBackend(const QString&  library, const QString&  version)
{
    QScriptValue _q_function = __qtscript_self.property("createBackend");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createBackend") & QScriptValue::QObjectMember)) {
        qFatal("PlatformPlugin::createBackend() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QObject* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, library)
            << qScriptValueFromValue(_q_engine, version)));
    }
}

Phonon::AbstractMediaStream*  QtScriptShell_PlatformPlugin::createMediaStream(const QUrl&  url, QObject*  parent)
{
    QScriptValue _q_function = __qtscript_self.property("createMediaStream");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createMediaStream") & QScriptValue::QObjectMember)) {
        qFatal("PlatformPlugin::createMediaStream() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<Phonon::AbstractMediaStream* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, url)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

QList<QPair<QByteArray , QString >  >  QtScriptShell_PlatformPlugin::deviceAccessListFor(const Phonon::AudioOutputDevice&  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("deviceAccessListFor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("deviceAccessListFor") & QScriptValue::QObjectMember)) {
        return Phonon::PlatformPlugin::deviceAccessListFor(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QList<QPair<QByteArray , QString >  > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

QIcon  QtScriptShell_PlatformPlugin::icon(const QString&  name) const
{
    QScriptValue _q_function = __qtscript_self.property("icon");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("icon") & QScriptValue::QObjectMember)) {
        qFatal("PlatformPlugin::icon() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QIcon >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

bool  QtScriptShell_PlatformPlugin::isMimeTypeAvailable(const QString&  mimeType) const
{
    QScriptValue _q_function = __qtscript_self.property("isMimeTypeAvailable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isMimeTypeAvailable") & QScriptValue::QObjectMember)) {
        qFatal("PlatformPlugin::isMimeTypeAvailable() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, mimeType)));
    }
}

qreal  QtScriptShell_PlatformPlugin::loadVolume(const QString&  outputName) const
{
    QScriptValue _q_function = __qtscript_self.property("loadVolume");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("loadVolume") & QScriptValue::QObjectMember)) {
        qFatal("PlatformPlugin::loadVolume() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<qreal >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, outputName)));
    }
}

void QtScriptShell_PlatformPlugin::notification(const char*  notificationName, const QString&  text, const QStringList&  actions, QObject*  receiver, const char*  actionSlot) const
{
    QScriptValue _q_function = __qtscript_self.property("notification");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("notification") & QScriptValue::QObjectMember)) {
        qFatal("PlatformPlugin::notification() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<char *>(notificationName))
            << qScriptValueFromValue(_q_engine, text)
            << qScriptValueFromValue(_q_engine, actions)
            << qScriptValueFromValue(_q_engine, receiver)
            << qScriptValueFromValue(_q_engine, const_cast<char *>(actionSlot)));
    }
}

QList<int >  QtScriptShell_PlatformPlugin::objectDescriptionIndexes(Phonon::ObjectDescriptionType  type) const
{
    QScriptValue _q_function = __qtscript_self.property("objectDescriptionIndexes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("objectDescriptionIndexes") & QScriptValue::QObjectMember)) {
        qFatal("PlatformPlugin::objectDescriptionIndexes() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QList<int > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, type)));
    }
}

QHash<QByteArray , QVariant >  QtScriptShell_PlatformPlugin::objectDescriptionProperties(Phonon::ObjectDescriptionType  type, int  index) const
{
    QScriptValue _q_function = __qtscript_self.property("objectDescriptionProperties");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("objectDescriptionProperties") & QScriptValue::QObjectMember)) {
        qFatal("PlatformPlugin::objectDescriptionProperties() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QHash<QByteArray , QVariant > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, type)
            << qScriptValueFromValue(_q_engine, index)));
    }
}

void QtScriptShell_PlatformPlugin::saveVolume(const QString&  outputName, qreal  volume)
{
    QScriptValue _q_function = __qtscript_self.property("saveVolume");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("saveVolume") & QScriptValue::QObjectMember)) {
        qFatal("PlatformPlugin::saveVolume() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, outputName)
            << qScriptValueFromValue(_q_engine, volume));
    }
}

