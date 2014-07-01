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
#include <QKeySequence>

#include "RArcEntity.h"
#include "RAttributeEntity.h"
#include "RAttributeDefinitionEntity.h"
#include "RBlockReferenceEntity.h"
#include "RCircleEntity.h"
#include "RDimAlignedEntity.h"
#include "RDimAngularEntity.h"
#include "RDimDiametricEntity.h"
#include "RDimOrdinateEntity.h"
#include "RDimRadialEntity.h"
#include "RDimRotatedEntity.h"
#include "RDimensionEntity.h"
#include "REllipseEntity.h"
#include "RGraphicsScene.h"
#include "RGraphicsView.h"
#include "RGraphicsViewQt.h"
#include "RHatchEntity.h"
#include "RImageEntity.h"
#include "RLeaderEntity.h"
#include "RLineEntity.h"
#include "RMainWindow.h"
#include "RMetaTypes.h"
#include "ROrthoGrid.h"
#include "RPainterPath.h"
#include "RPointEntity.h"
#include "RPolylineEntity.h"
#include "RRayEntity.h"
#include "RRestrictAngleLength.h"
#include "RRestrictOff.h"
#include "RRestrictOrthogonal.h"
#include "RRestrictHorizontal.h"
#include "RRestrictVertical.h"
#include "RSolidEntity.h"
#include "RSplineEntity.h"
#include "RTextEntity.h"
#include "RTraceEntity.h"
#include "RXLineEntity.h"

#include "REcmaHelper.h"

//int REcmaHelper::shellFunctionCounter = 0;

QScriptValue REcmaHelper::throwError(const QString& message, QScriptContext* context) {
    QScriptContextInfo contextInfo(context);
    return context->throwError(
        QString("%1:%2:%3: %4\n%5")
           .arg(contextInfo.fileName())
           .arg(contextInfo.lineNumber())
           .arg(contextInfo.columnNumber())
           .arg(message)
           .arg(context->backtrace().join("\n")));
}

//bool REcmaHelper::isRVector(QScriptValue& sv) {}

/*
// does not compile in release mode with MSVC 2008:
QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, const QMap<QString, QString>& cppValue) {
    QVariantMap vm;
    QMap<QString, QString>::const_iterator it;
    for (it = cppValue.constBegin(); it!=cppValue.constEnd(); ++it) {
        //QVariant v;
        //v.setValue(cppValue.at(i));
        vm.insert(it.key(), QVariant(it.value()));
    }
    return qScriptValueFromValue(engine, vm);

    // // alterative version (compiles in release mode with MSVC 2008):
    // qDebug() << "REcmaHelper::toScriptValue: QMap<QString, QString>";
    // QMap<QString, QString> vm;
    // QMap<QString, QString>::const_iterator it;
    // for (it = cppValue.constBegin(); it!=cppValue.constEnd(); ++it) {
    //     vm.insert(it.key(), it.value());
    // }
    // return qScriptValueFromValue(engine, vm);
}
*/

/*
QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, const QList<double>& cppValue) {
    QVariantList vl;
    for (int i = 0; i < cppValue.size(); ++i) {
        QVariant v;
        v.setValue(cppValue.at(i));
        vl.append(v);
    }
    return qScriptValueFromValue(engine, vl);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, const QList<RVector>& cppValue) {
    QVariantList vl;
    for (int i = 0; i < cppValue.size(); ++i) {
        QVariant v;
        v.setValue(cppValue.at(i));
        vl.append(v);
    }
    return qScriptValueFromValue(engine, vl);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, const QList<RSpline>& cppValue) {
    QVariantList vl;
    for (int i = 0; i < cppValue.size(); ++i) {
        QVariant v;
        v.setValue(cppValue.at(i));
        vl.append(v);
    }
    return qScriptValueFromValue(engine, vl);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, const QList<QKeySequence>& cppValue) {
    QVariantList vl;
    for (int i = 0; i < cppValue.size(); ++i) {
        QVariant v;
        v.setValue(cppValue.at(i));
        vl.append(v);
    }
    return qScriptValueFromValue(engine, vl);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, const QList<RGraphicsScene*>& cppValue) {
    QVariantList vl;
    for (int i = 0; i < cppValue.size(); ++i) {
        QVariant v;
        v.setValue(cppValue.at(i));
        vl.append(v);
    }
    return qScriptValueFromValue(engine, vl);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, const QList<RGraphicsView*>& cppValue) {
    QVariantList vl;
    for (int i = 0; i < cppValue.size(); ++i) {
        QVariant v;
        v.setValue(cppValue.at(i));
        vl.append(v);
    }
    return qScriptValueFromValue(engine, vl);
}
*/

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, RGraphicsView* cppValue) {
    RGraphicsViewQt* v = dynamic_cast<RGraphicsViewQt*>(cppValue);
    if (v!=NULL) {
        return qScriptValueFromValue(engine, v);
    }

    return qScriptValueFromValue(engine, cppValue);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, RGraphicsScene* cppValue) {
    RGraphicsSceneQt* v = dynamic_cast<RGraphicsSceneQt*>(cppValue);
    if (v!=NULL) {
        return qScriptValueFromValue(engine, v);
    }

    return qScriptValueFromValue(engine, cppValue);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, RSnapRestriction* cppValue) {
    QScriptValue v;

    v = tryCast<RRestrictOff>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RRestrictAngleLength>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RRestrictHorizontal>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RRestrictVertical>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RRestrictOrthogonal>(engine, cppValue);
    if (v.isValid()) return v;

    return qScriptValueFromValue(engine, cppValue);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, QSharedPointer<RShape>& cppValue) {
    QScriptValue v;

    v = tryCast<RPoint>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RLine>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RRay>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RXLine>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RArc>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RCircle>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<REllipse>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RSpline>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RPolyline>(engine, cppValue);
    if (v.isValid()) return v;

    return qScriptValueFromValue(engine, cppValue);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, RShape* cppValue) {
    QScriptValue v;

    v = tryCast<RPoint>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RLine>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RRay>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RXLine>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RArc>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RCircle>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<REllipse>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RSpline>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RPolyline>(engine, cppValue);
    if (v.isValid()) return v;

    return qScriptValueFromValue(engine, cppValue);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, QSharedPointer<RObject>& cppValue) {

    QSharedPointer<REntity> entity = cppValue.dynamicCast<REntity>();
    if (!entity.isNull()) {
        return toScriptValue(engine, entity);
    }

    QScriptValue v;
    v = tryCast<RLayer>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RBlock>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RLinetype>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RUcs>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RView>(engine, cppValue);
    if (v.isValid()) return v;

    return qScriptValueFromValue(engine, cppValue);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, QSharedPointer<REntity>& cppValue) {
    QScriptValue v;

    v = tryCast<RLineEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RRayEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RXLineEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RArcEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RCircleEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RTextEntity>(engine, cppValue);
    if (v.isValid()) return v;

    v = tryCast<RAttributeEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RAttributeDefinitionEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RBlockReferenceEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimAlignedEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimAngularEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimDiametricEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimOrdinateEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimRadialEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimRotatedEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<REllipseEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RHatchEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RImageEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RLeaderEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RPointEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RPolylineEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RSolidEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RTraceEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RSplineEntity>(engine, cppValue);
    if (v.isValid()) return v;

    return qScriptValueFromValue(engine, cppValue);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, REntity* cppValue) {
    QScriptValue v;

    v = tryCast<RAttributeEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RAttributeDefinitionEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RArcEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RBlockReferenceEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RCircleEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimAlignedEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimAngularEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimDiametricEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimOrdinateEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimRadialEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimRotatedEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<REllipseEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RHatchEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RImageEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RLeaderEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RLineEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RRayEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RXLineEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RPointEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RPolylineEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RSolidEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RTraceEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RSplineEntity>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RTextEntity>(engine, cppValue);
    if (v.isValid()) return v;

    return qScriptValueFromValue(engine, cppValue);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, QSharedPointer<REntityData>& cppValue) {
    QScriptValue v;

    v = tryCast<RAttributeData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RAttributeDefinitionData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RArcData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RBlockReferenceData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RCircleData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimAlignedData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimAngularData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimDiametricData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimOrdinateData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimRadialData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimRotatedData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<REllipseData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RHatchData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RImageData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RLeaderData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RLineData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RRayData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RXLineData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RPointData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RPolylineData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RSolidData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RTraceData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RSplineData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RTextData>(engine, cppValue);
    if (v.isValid()) return v;

    return qScriptValueFromValue(engine, cppValue);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, RGrid* cppValue) {
    QScriptValue v;

    v = tryCast<ROrthoGrid>(engine, cppValue);
    if (v.isValid()) return v;

    return qScriptValueFromValue(engine, cppValue);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, const QVariant& cppValue) {
    //qDebug() << "REcmaHelper::toScriptValue: variant: type: " << cppValue.type();
    //qDebug() << "REcmaHelper::toScriptValue: variant: type: " << cppValue.typeName();

    if (cppValue.canConvert<QList<double> >()) {
        //qDebug() << "REcmaHelper::toScriptValue: variant: can convert to double list";
        QList<double> res = cppValue.value<QList<double> >();
        return listToScriptValue(engine, res);
    }

    switch (cppValue.type()) {
    case QVariant::Double: {
            double res = cppValue.toDouble();
            return qScriptValueFromValue(engine, res);
        }
    case QVariant::LongLong:
    case QVariant::ULongLong:
    case QVariant::UInt:
    case QVariant::Int: {
            int res = cppValue.toInt();
            return qScriptValueFromValue(engine, res);
        }
    case QVariant::String: {
            QString res = cppValue.toString();
            return qScriptValueFromValue(engine, res);
        }
    default:
        return qScriptValueFromValue(engine, cppValue);
        break;
    }

    //if (cppValue.type()==QVariant::List) {
    //    qDebug() << "REcmaHelper::toScriptValue: list";
    //    QVariantList res = cppValue.toList();
    //    return qScriptValueFromValue(engine, res);
        //return listToScriptValue(engine, res);
    //}
}

void REcmaHelper::registerFunction(QScriptEngine* engine, QScriptValue* proto,
    QScriptEngine::FunctionSignature fun, const QString& name) {

    QScriptValue f = engine->newFunction(fun);
    f.setData(QScriptValue(engine, uint(0xBABE0000)));
    proto->setProperty(name, f,  QScriptValue::SkipInEnumeration);
}

void REcmaHelper::fromScriptValue(QScriptEngine* engine, QScriptValue scriptValue, QList<QSharedPointer<RShape> >& cppValue) {
    QVariantList variantList = engine->fromScriptValue<QVariantList>(scriptValue);
    for (int i = 0; i < variantList.size(); ++i) {
        QVariant v = variantList.at(i);
        QSharedPointer<RShape> pShape = v.value<QSharedPointer<RShape> >();
        if (!pShape.isNull()) {
            cppValue.append(pShape);
        }
        else {
            RShape* shape = v.value<RShape*>();
            if (shape!=NULL) {
                QSharedPointer<RShape> pShape(shape->clone());
                cppValue.append(pShape);
            }

            else if (v.canConvert<RArc>()) {
                RArc obj = v.value<RArc>();
                QSharedPointer<RArc> p(obj.clone());
                cppValue.append(p);
            }

            else if (v.canConvert<RCircle>()) {
                RCircle obj = v.value<RCircle>();
                QSharedPointer<RCircle> p(obj.clone());
                cppValue.append(p);
            }

            else if (v.canConvert<RLine>()) {
                RLine obj = v.value<RLine>();
                QSharedPointer<RLine> p(obj.clone());
                cppValue.append(p);
            }

            else if (v.canConvert<RRay>()) {
                RRay obj = v.value<RRay>();
                QSharedPointer<RRay> p(obj.clone());
                cppValue.append(p);
            }

            else if (v.canConvert<RXLine>()) {
                RXLine obj = v.value<RXLine>();
                QSharedPointer<RXLine> p(obj.clone());
                cppValue.append(p);
            }

            else if (v.canConvert<RPoint>()) {
                RPoint obj = v.value<RPoint>();
                QSharedPointer<RPoint> p(obj.clone());
                cppValue.append(p);
            }

            else if (v.canConvert<RPolyline>()) {
                RPolyline obj = v.value<RPolyline>();
                QSharedPointer<RPolyline> p(obj.clone());
                cppValue.append(p);
            }

            else if (v.canConvert<RSpline>()) {
                RSpline obj = v.value<RSpline>();
                QSharedPointer<RSpline> p(obj.clone());
                cppValue.append(p);
            }

            else if (v.canConvert<RTextLabel>()) {
                RTextLabel obj = v.value<RTextLabel>();
                QSharedPointer<RTextLabel> p(obj.clone());
                cppValue.append(p);
            }

            else if (v.canConvert<RTriangle>()) {
                RTriangle obj = v.value<RTriangle>();
                QSharedPointer<RTriangle> p(obj.clone());
                cppValue.append(p);
            }
        }
    }
}

QScriptValue REcmaHelper::listToScriptValue(QScriptEngine* engine, const QList<QSharedPointer<RShape> >& cppValue) {
    QVariantList vl;
    for (int i = 0; i < cppValue.size(); ++i) {
        QVariant v = toVariant(cppValue.at(i));
        vl.append(v);
    }
    return qScriptValueFromValue(engine, vl);
}

QVariant REcmaHelper::toVariant(const QSharedPointer<RShape>& cppValue) {
    QVariant v;

    {
        QSharedPointer<RPoint> shape = cppValue.dynamicCast<RPoint>();
        if (!shape.isNull()) {
            v.setValue(shape);
            return v;
        }
    }
    {
        QSharedPointer<RLine> shape = cppValue.dynamicCast<RLine>();
        if (!shape.isNull()) {
            v.setValue(shape);
            return v;
        }
    }
    {
        QSharedPointer<RRay> shape = cppValue.dynamicCast<RRay>();
        if (!shape.isNull()) {
            v.setValue(shape);
            return v;
        }
    }
    {
        QSharedPointer<RXLine> shape = cppValue.dynamicCast<RXLine>();
        if (!shape.isNull()) {
            v.setValue(shape);
            return v;
        }
    }
    {
        QSharedPointer<RArc> shape = cppValue.dynamicCast<RArc>();
        if (!shape.isNull()) {
            v.setValue(shape);
            return v;
        }
    }
    {
        QSharedPointer<RCircle> shape = cppValue.dynamicCast<RCircle>();
        if (!shape.isNull()) {
            v.setValue(shape);
            return v;
        }
    }
    {
        QSharedPointer<REllipse> shape = cppValue.dynamicCast<REllipse>();
        if (!shape.isNull()) {
            v.setValue(shape);
            return v;
        }
    }
    {
        QSharedPointer<RSpline> shape = cppValue.dynamicCast<RSpline>();
        if (!shape.isNull()) {
            v.setValue(shape);
            return v;
        }
    }
    {
        QSharedPointer<RPolyline> shape = cppValue.dynamicCast<RPolyline>();
        if (!shape.isNull()) {
            v.setValue(shape);
            return v;
        }
    }
    {
        QSharedPointer<RTriangle> shape = cppValue.dynamicCast<RTriangle>();
        if (!shape.isNull()) {
            v.setValue(shape);
            return v;
        }
    }

    Q_ASSERT_X(false, "REcmaHelper::toVariant", "Unknown shape");

    return v;
}

void REcmaHelper::functionStart(const QString& name, QScriptContext* context, QScriptEngine* engine) {
    //qDebug() << "REcmaHelper::functionStart: " << name;
}

void REcmaHelper::functionEnd(const QString& name, QScriptContext* context, QScriptEngine* engine) {
    //qDebug() << "REcmaHelper::functionEnd: " << name;
}

void REcmaHelper::shellFunctionStart(const QString& name, QScriptEngine* engine) {
    //qDebug() << "REcmaHelper::shellFunctionStart: " << name;
}

void REcmaHelper::shellFunctionEnd(const QString& name, QScriptEngine* engine) {
    //qDebug() << "REcmaHelper::shellFunctionEnd: " << name;
}


template<>
QScriptValue REcmaHelper::listToScriptValue<RGraphicsScene*>(QScriptEngine* engine, const QList<RGraphicsScene*>& cppValue) {
    QVariantList vl;
    for (int i = 0; i < cppValue.size(); ++i) {
        QVariant v;
        RGraphicsSceneQt* sq = dynamic_cast<RGraphicsSceneQt*>(cppValue.at(i));
        if (sq!=NULL) {
            v.setValue(sq);
        }
        else {
            v.setValue(cppValue.at(i));
        }
        vl.append(v);
    }
    return qScriptValueFromValue(engine, vl);
}

template<>
QScriptValue REcmaHelper::listToScriptValue<RGraphicsView*>(QScriptEngine* engine, const QList<RGraphicsView*>& cppValue) {
    QVariantList vl;
    for (int i = 0; i < cppValue.size(); ++i) {
        QVariant v;
        RGraphicsViewQt* sq = dynamic_cast<RGraphicsViewQt*>(cppValue.at(i));
        if (sq!=NULL) {
            v.setValue(sq);
        }
        else {
            v.setValue(cppValue.at(i));
        }
        vl.append(v);
    }
    return qScriptValueFromValue(engine, vl);
}
