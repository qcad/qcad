/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

#ifndef RECMAHELPER_H
#define RECMAHELPER_H

#include "ecmaapi_global.h"

#include <QtScript>
#include <QList>

#include "RVector.h"
#include "RSpline.h"
#include "REntity.h"
#include "RGrid.h"
#include "RLineweight.h"
#include "RGraphicsSceneQt.h"

class RGraphicsScene;
class RGraphicsView;


/**
 * \ingroup ecma
 */
class QCADECMAAPI_EXPORT REcmaHelper {
public:

// tries to convert the given value to all possible inheritance strains 
// if multiple inheritance is used:
template<class T> 
static T* scriptValueTo(QScriptValue v) {
    // try to cast:
    T* ret = qscriptvalue_cast<T*>(v);
    //qDebug() << "scriptValueTo: ret: 1: " << (long int)ret;
    if (ret!=NULL) {
        return ret;
    }

    // try to convert to QObject:
    /*
    ret = qobject_cast<T*>(v.toQObject());
    qDebug() << "scriptValueTo: QObject: " << (long int)v.toQObject();
    if (ret!=NULL) {
        return ret;
    }
    */

    // try to cast prototype
    // TODO: check if this makes sense
    if (ret==NULL && !v.isNull()) {
        QScriptValue prototype = v.prototype();
        ret = qscriptvalue_cast<T*>(prototype);
        //qDebug() << "scriptValueTo: ret: prototype: " << (long int)ret;
    }

    // try to cast prototypes of base classes:
    if (ret==NULL && !v.isNull()) {
        QScriptValue fBaseClasses = v.property("getBaseClasses");
        if (!fBaseClasses.isValid()) {
            return NULL;
        }
        QScriptValue baseClasses = fBaseClasses.call(v);

        // skip first base class (primary base class):
        int i=1;
        while(true) {
            QScriptValue baseClass = baseClasses.property(i);
            if (baseClass.toString().isEmpty()) {
                break;
            }

            //qDebug() << "base class[" << i << "]: " << baseClass.toString();

            ret = qscriptvalue_cast<T*>(v.property(QString("get") + baseClass.toString()).call(v));

            if (ret!=NULL) {
                break;
            }

            i++;
        }
    }

    return ret;
}

// try to convert the given value to a QObject.
/*
template<class T>
static T* scriptValueToQObject(QScriptValue v) {
    // try to convert to QObject:
    T* ret = qobject_cast<T*>(v.toQObject());
    qDebug() << "scriptValueToQObject: toQObject: " << v.toQObject();
    qDebug() << "scriptValueToQObject: ret: 1: " << ret;

    if (ret==NULL && !v.isNull()) {
        QScriptValue prototype = v.prototype();
        ret = qobject_cast<T*>(prototype.toQObject());
        qDebug() << "scriptValueToQObject: ret: 2: " << ret;
    }

    return ret;
}
*/

static QScriptValue throwError(const QString& message, QScriptContext* context);

//static QScriptValue toScriptValue(QScriptEngine* engine, const QMap<QString, QString>& cppValue);

//static bool isRVector(QScriptValue& sv);

template<class T1, class T2>
static QScriptValue pairListToScriptValue(QScriptEngine* engine, const QList<QPair<T1, T2> >& cppValue) {
    QVariantList vl;

    for (int i=0; i<cppValue.size(); ++i) {
        QVariantList vlp;
        QVariant v;
        QPair<T1, T2> item = cppValue.at(i);
//        if (QString(item.first.typeName())=="RLineweight::Lineweight") {
//            v.setValue((int)item.first.value<RLineweight::Lineweight>());
//        }
//        else {
            v.setValue(item.first);
        //}
        vlp.append(v);
        v.setValue(item.second);
        vlp.append(v);

        v.setValue(vlp);
        vl.append(v);
    }

    return qScriptValueFromValue(engine, vl);
}

//template<class T1, class T2>
//static QScriptValue pairToScriptValue(QScriptEngine* engine, const QPair<T1, T2>& cppValue) {
//    QVariantList vl;
//    QVariant v;
//    if (QString(cppValue.first.typeName())=="RLineweight::Lineweight") {
//        v.setValue((int)cppValue.first.value<RLineweight::Lineweight>());
//    }
//    else {
//        v.setValue(cppValue.first);
//    }
//    vl.append(v);
//    v.setValue(cppValue.second);
//    vl.append(v);
//    return qScriptValueFromValue(engine, vl);
//}

static QScriptValue listToScriptValue(QScriptEngine* engine, const QList<QSharedPointer<RShape> >& cppValue);


template<class T>
static QScriptValue listToScriptValue(QScriptEngine* engine, const QList<T>& cppValue) {
    QVariantList vl;
    for (int i = 0; i < cppValue.size(); ++i) {
        QVariant v;
        v.setValue(cppValue.at(i));
        vl.append(v);
    }
    return qScriptValueFromValue(engine, vl);
}

//template<>
//static QScriptValue listToScriptValue<RGraphicsScene*>(QScriptEngine* engine, const QList<RGraphicsScene*>& cppValue);

template<class T>
static QScriptValue setToScriptValue(QScriptEngine* engine, const QSet<T>& cppValue) {
    QVariantList vl;
    typename QSet<T>::const_iterator it;
    for (it=cppValue.begin(); it!=cppValue.end(); it++) {
        QVariant v;
        v.setValue(*it);
        vl.append(v);
    }
    return qScriptValueFromValue(engine, vl);
}

/*
static QScriptValue toScriptValue(QScriptEngine* engine, const QList<double>& cppValue);
static QScriptValue toScriptValue(QScriptEngine* engine, const QList<RVector>& cppValue);
static QScriptValue toScriptValue(QScriptEngine* engine, const QList<RSpline>& cppValue);
static QScriptValue toScriptValue(QScriptEngine* engine, const QList<QKeySequence>& cppValue);
static QScriptValue toScriptValue(QScriptEngine* engine, const QList<RGraphicsScene*>& cppValue);
static QScriptValue toScriptValue(QScriptEngine* engine, const QList<RGraphicsView*>& cppValue);
*/
static QScriptValue toScriptValue(QScriptEngine* engine, RGraphicsView* cppValue);
static QScriptValue toScriptValue(QScriptEngine* engine, RGraphicsScene* cppValue);
static QScriptValue toScriptValue(QScriptEngine* engine, RSnapRestriction* cppValue);
static QScriptValue toScriptValue(QScriptEngine* engine, RShape* cppValue);
static QScriptValue toScriptValue(QScriptEngine* engine, QSharedPointer<RShape>& cppValue);
static QScriptValue toScriptValue(QScriptEngine* engine, QSharedPointer<RObject>& cppValue);
static QScriptValue toScriptValue(QScriptEngine* engine, QSharedPointer<REntity>& cppValue);
static QScriptValue toScriptValue(QScriptEngine* engine, REntity* cppValue);
static QScriptValue toScriptValue(QScriptEngine* engine, QSharedPointer<REntityData>& cppValue);
static QScriptValue toScriptValue(QScriptEngine* engine, RGrid* cppValue);

static QScriptValue toScriptValue(QScriptEngine* engine, const QVariant& cppValue);

template<class T>
static QScriptValue tryCast(QScriptEngine* engine, QSharedPointer<RShape>& cppValue) {
    QSharedPointer<T> shape = cppValue.dynamicCast<T>();
    if (!shape.isNull()) {
        return qScriptValueFromValue(engine, shape);
    }
    else {
        return QScriptValue();
    }
}

template<class T>
static QScriptValue tryCast(QScriptEngine* engine, RShape* cppValue) {
    T* shape = dynamic_cast<T*>(cppValue);
    if (shape!=NULL) {
        return qScriptValueFromValue(engine, shape);
    }
    else {
        return QScriptValue();
    }
}

template<class T>
static QScriptValue tryCast(QScriptEngine* engine, QSharedPointer<RObject>& cppValue) {
    QSharedPointer<T> obj = cppValue.dynamicCast<T>();
    if (!obj.isNull()) {
        return qScriptValueFromValue(engine, obj);
    }
    else {
        return QScriptValue();
    }
}

template<class T>
static QScriptValue tryCast(QScriptEngine* engine, QSharedPointer<REntity>& cppValue) {
    QSharedPointer<T> entity = cppValue.dynamicCast<T>();
    if (!entity.isNull()) {
        return qScriptValueFromValue(engine, entity);
    }
    else {
        return QScriptValue();
    }
}

template<class T>
static QScriptValue tryCast(QScriptEngine* engine, REntity* cppValue) {
    T* entity = dynamic_cast<T*>(cppValue);
    if (entity!=NULL) {
        return qScriptValueFromValue(engine, entity);
    }
    else {
        return QScriptValue();
    }
}

template<class T>
static QScriptValue tryCast(QScriptEngine* engine, QSharedPointer<REntityData>& cppValue) {
    QSharedPointer<T> entity = cppValue.dynamicCast<T>();
    if (!entity.isNull()) {
        return qScriptValueFromValue(engine, entity);
    }
    else {
        return QScriptValue();
    }
}

template<class T>
static QScriptValue tryCast(QScriptEngine* engine, RGrid* cppValue) {
    T* entity = dynamic_cast<T*>(cppValue);
    if (entity!=NULL) {
        return qScriptValueFromValue(engine, entity);
    }
    else {
        return QScriptValue();
    }
}

template<class T>
static QScriptValue tryCast(QScriptEngine* engine, RSnapRestriction* cppValue) {
    T* entity = dynamic_cast<T*>(cppValue);
    if (entity!=NULL) {
        return qScriptValueFromValue(engine, entity);
    }
    else {
        return QScriptValue();
    }
}

static void fromScriptValue(QScriptEngine* engine, QScriptValue scriptValue, QList<QSharedPointer<RShape> >& cppValue);
static QVariant toVariant(const QSharedPointer<RShape>& cppValue);

/*
template<class T>
static void fromScriptValueSP(QScriptEngine* engine, QScriptValue scriptValue, QList<QSharedPointer<T> >& cppValue) {
    QVariantList vl = engine->fromScriptValue<QVariantList>(scriptValue);
    for (int i = 0; i < vl.size(); ++i) {
        qDebug() << "fromScriptValueSP: " << i;
        QSharedPointer<T> v = vl.at(i).value<QSharedPointer<T> >();
        if (!v.isNull()) {
            qDebug() << "fromScriptValueSP: shared pointer";
            cppValue.append(v);
        }
        else {
            qDebug() << "fromScriptValueSP: no shared pointer";
            T* p = vl.at(i).value<T*>();
            if (p!=NULL) {
                qDebug() << "fromScriptValueSP: normal pointer";
                QSharedPointer<T> q(p->clone());
                cppValue.append(q);
            }
        }
    }
}
*/

template<class T> 
static void fromScriptValue(QScriptEngine* engine, QScriptValue scriptValue, QList<T>& cppValue) {
    QVariantList vl = engine->fromScriptValue<QVariantList>(scriptValue);
    for (int i = 0; i < vl.size(); ++i) {
        cppValue.append(vl.at(i).template value<T>());
    }
}

template<class T> 
static void fromScriptValue(QScriptEngine* engine, QScriptValue scriptValue, QSet<T>& cppValue) {
    QVariantList vl = engine->fromScriptValue<QVariantList>(scriptValue);
    for (int i = 0; i < vl.size(); ++i) {
        cppValue.insert(vl.at(i).template value<T>());
    }
}

static void registerFunction(QScriptEngine* engine, QScriptValue* proto,
                             QScriptEngine::FunctionSignature fun,
                             const QString& name);

static void functionStart(const QString& name, QScriptContext *context, QScriptEngine *engine);
static void functionEnd(const QString& name, QScriptContext *context, QScriptEngine *engine);

static void shellFunctionStart(const QString& name, QScriptEngine *engine);
static void shellFunctionEnd(const QString& name, QScriptEngine *engine);

static void printStackTrace(QScriptContext* context);

//static int shellFunctionCounter;
};

template<>
QScriptValue REcmaHelper::listToScriptValue<RGraphicsScene*>(QScriptEngine* engine, const QList<RGraphicsScene*>& cppValue);

template<>
QScriptValue REcmaHelper::listToScriptValue<RGraphicsView*>(QScriptEngine* engine, const QList<RGraphicsView*>& cppValue);

#endif
