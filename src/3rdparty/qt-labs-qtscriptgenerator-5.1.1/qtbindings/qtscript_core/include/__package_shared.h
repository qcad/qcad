
#pragma once

#include <qcoreevent.h>

#include <QtScript/qscriptvalue.h>
#include <QtScript/QScriptEngine>


#include <QFile>


Q_DECLARE_METATYPE(QEvent)

namespace QtMetaTypePrivate {

template <>
inline void *QMetaTypeFunctionHelper<QEvent, true>::Create(const void *t)
{
    if (t)
        return new QEvent(*static_cast<const QEvent*>(t));
    return new QEvent(QEvent::None);
};

template <>
inline void *QMetaTypeFunctionHelper<QEvent, true>::Construct(void *where, const void *t)
{
    if (t)
        return new (where) QEvent(*static_cast<const QEvent*>(t));
    return new (where) QEvent(QEvent::None);
};


}

template <>
inline QEvent qscriptvalue_cast<QEvent>(const QScriptValue &value)
{
    QEvent t(QEvent::None);
    const int id = qMetaTypeId<QEvent>();

    if (qscriptvalue_cast_helper(value, id, &t))
        return t;

    return QEvent(QEvent::None);
}


