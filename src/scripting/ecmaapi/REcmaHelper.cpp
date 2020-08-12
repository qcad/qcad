/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
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
#include "RDimAngular2LEntity.h"
#include "RDimAngular3PEntity.h"
#include "RDimArcLengthEntity.h"
#include "RDimDiametricEntity.h"
#include "RDimOrdinateEntity.h"
#include "RDimRadialEntity.h"
#include "RDimRotatedEntity.h"
#include "RDimensionEntity.h"
#include "REllipseEntity.h"
#include "RFaceEntity.h"
#include "RGraphicsScene.h"
#include "RGraphicsSceneQt.h"
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
#include "RToleranceEntity.h"
#include "RTraceEntity.h"
#include "RViewportEntity.h"
#include "RXLineEntity.h"

#include "REcmaHelper.h"

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
    v = tryCast<RDocumentVariables>(engine, cppValue);
    if (v.isValid()) return v;
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

    if (cppValue.isNull()) {
        return qScriptValueFromValue(engine, cppValue);
    }

    switch (cppValue->getType()) {
    case RS::EntityLine:
        v = tryCast<RLineEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityRay:
        v = tryCast<RRayEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityXLine:
        v = tryCast<RXLineEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityArc:
        v = tryCast<RArcEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityCircle:
        v = tryCast<RCircleEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityText:
        v = tryCast<RTextEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityAttribute:
        v = tryCast<RAttributeEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityAttributeDefinition:
        v = tryCast<RAttributeDefinitionEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityBlockRef:
        v = tryCast<RBlockReferenceEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimAligned:
        v = tryCast<RDimAlignedEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimAngular2L:
        v = tryCast<RDimAngular2LEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimAngular3P:
        v = tryCast<RDimAngular3PEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimArcLength:
        v = tryCast<RDimArcLengthEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimDiametric:
        v = tryCast<RDimDiametricEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimOrdinate:
        v = tryCast<RDimOrdinateEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimRadial:
        v = tryCast<RDimRadialEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimRotated:
        v = tryCast<RDimRotatedEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityEllipse:
        v = tryCast<REllipseEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityFace:
        v = tryCast<RFaceEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityHatch:
        v = tryCast<RHatchEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityImage:
        v = tryCast<RImageEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityLeader:
        v = tryCast<RLeaderEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityPoint:
        v = tryCast<RPointEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityPolyline:
        v = tryCast<RPolylineEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntitySolid:
        v = tryCast<RSolidEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityTrace:
        v = tryCast<RTraceEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityViewport:
        v = tryCast<RViewportEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntitySpline:
        v = tryCast<RSplineEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityTolerance:
        v = tryCast<RToleranceEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    }

    return qScriptValueFromValue(engine, cppValue);
}

QScriptValue REcmaHelper::toScriptValue(QScriptEngine* engine, REntity* cppValue) {
    QScriptValue v;

    if (cppValue==NULL) {
        return qScriptValueFromValue(engine, cppValue);
    }

    switch (cppValue->getType()) {
    case RS::EntityAttribute:
        v = tryCast<RAttributeEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityAttributeDefinition:
        v = tryCast<RAttributeDefinitionEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityArc:
        v = tryCast<RArcEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityBlockRef:
        v = tryCast<RBlockReferenceEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityCircle:
        v = tryCast<RCircleEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimAligned:
        v = tryCast<RDimAlignedEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimAngular2L:
        v = tryCast<RDimAngular2LEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimAngular3P:
        v = tryCast<RDimAngular3PEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimDiametric:
        v = tryCast<RDimDiametricEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimOrdinate:
        v = tryCast<RDimOrdinateEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimRadial:
        v = tryCast<RDimRadialEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityDimRotated:
        v = tryCast<RDimRotatedEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityEllipse:
        v = tryCast<REllipseEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityFace:
        v = tryCast<RFaceEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityHatch:
        v = tryCast<RHatchEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityImage:
        v = tryCast<RImageEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityLeader:
        v = tryCast<RLeaderEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityLine:
        v = tryCast<RLineEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityRay:
        v = tryCast<RRayEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityXLine:
        v = tryCast<RXLineEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityPoint:
        v = tryCast<RPointEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityPolyline:
        v = tryCast<RPolylineEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntitySolid:
        v = tryCast<RSolidEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityTrace:
        v = tryCast<RTraceEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityViewport:
        v = tryCast<RViewportEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntitySpline:
        v = tryCast<RSplineEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityText:
        v = tryCast<RTextEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    case RS::EntityTolerance:
        v = tryCast<RToleranceEntity>(engine, cppValue);
        if (v.isValid()) return v;
        break;
    }

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
    v = tryCast<RDimAngular2LData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimAngular3PData>(engine, cppValue);
    if (v.isValid()) return v;
    v = tryCast<RDimArcLengthData>(engine, cppValue);
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
    v = tryCast<RFaceData>(engine, cppValue);
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
    v = tryCast<RViewportData>(engine, cppValue);
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
    if (cppValue.canConvert<QList<double> >()) {
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
}

void REcmaHelper::registerFunction(QScriptEngine* engine, QScriptValue* proto,
    QScriptEngine::FunctionSignature fun, const QString& name) {

    QScriptValue f = engine->newFunction(fun);
    f.setData(QScriptValue(engine, uint(0xBABE0000)));

    // skip in enumeration - otherwise segfault under windows/msvc:
    proto->setProperty(name, f,  QScriptValue::ReadOnly | QScriptValue::Undeletable /*| QScriptValue::SkipInEnumeration*/);
}

void REcmaHelper::fromScriptValue(QScriptEngine* engine, QScriptValue scriptValue, QList<QSharedPointer<RShape> >& cppValue) {
    QVariantList variantList = engine->fromScriptValue<QVariantList>(scriptValue);
    for (int i = 0; i < variantList.size(); ++i) {
        QVariant v = variantList.at(i);
        //qDebug() << "type: " << v.typeName();

        QSharedPointer<RShape> pShape = v.value<QSharedPointer<RShape> >();
        if (!pShape.isNull()) {
            cppValue.append(pShape);
            continue;
        }

        QSharedPointer<RShape> pLine = v.value<QSharedPointer<RLine> >();
        if (!pLine.isNull()) {
            cppValue.append(pLine);
            continue;
        }

        QSharedPointer<RShape> pArc = v.value<QSharedPointer<RArc> >();
        if (!pArc.isNull()) {
            cppValue.append(pArc);
            continue;
        }

        // TODO: add more shared pointer types...

        RShape* shape = v.value<RShape*>();
        if (shape!=NULL) {
            QSharedPointer<RShape> pShape(shape->clone());
            cppValue.append(pShape);
            continue;
        }

        if (v.canConvert<RArc>()) {
            RArc obj = v.value<RArc>();
            QSharedPointer<RArc> p(obj.clone());
            cppValue.append(p);
            continue;
        }

        if (v.canConvert<RCircle>()) {
            RCircle obj = v.value<RCircle>();
            QSharedPointer<RCircle> p(obj.clone());
            cppValue.append(p);
            continue;
        }

        if (v.canConvert<RLine>()) {
            RLine obj = v.value<RLine>();
            QSharedPointer<RLine> p(obj.clone());
            cppValue.append(p);
            continue;
        }

        if (v.canConvert<RRay>()) {
            RRay obj = v.value<RRay>();
            QSharedPointer<RRay> p(obj.clone());
            cppValue.append(p);
            continue;
        }

        if (v.canConvert<RXLine>()) {
            RXLine obj = v.value<RXLine>();
            QSharedPointer<RXLine> p(obj.clone());
            cppValue.append(p);
            continue;
        }

        if (v.canConvert<RPoint>()) {
            RPoint obj = v.value<RPoint>();
            QSharedPointer<RPoint> p(obj.clone());
            cppValue.append(p);
            continue;
        }

        if (v.canConvert<RPolyline>()) {
            RPolyline obj = v.value<RPolyline>();
            QSharedPointer<RPolyline> p(obj.clone());
            cppValue.append(p);
            continue;
        }

        if (v.canConvert<RSpline>()) {
            RSpline obj = v.value<RSpline>();
            QSharedPointer<RSpline> p(obj.clone());
            cppValue.append(p);
            continue;
        }

        if (v.canConvert<RTextLabel>()) {
            RTextLabel obj = v.value<RTextLabel>();
            QSharedPointer<RTextLabel> p(obj.clone());
            cppValue.append(p);
            continue;
        }

        if (v.canConvert<RTriangle>()) {
            RTriangle obj = v.value<RTriangle>();
            QSharedPointer<RTriangle> p(obj.clone());
            cppValue.append(p);
            continue;
        }
    }
}

void REcmaHelper::fromScriptValue(QScriptEngine* engine, QScriptValue scriptValue, QList<RS::EntityType>& cppValue) {
    QVariantList vl = engine->fromScriptValue<QVariantList>(scriptValue);
    for (int i = 0; i < vl.size(); ++i) {
        cppValue.append((RS::EntityType)vl.at(i).toInt());
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

QScriptValue REcmaHelper::listToScriptValue(QScriptEngine* engine, const QList<QChar>& cppValue) {
    QVariantList vl;
    for (int i = 0; i < cppValue.size(); ++i) {
        QVariant v(QString(cppValue.at(i)));
        vl.append(v);
    }
    return qScriptValueFromValue(engine, vl);
}

QVariant REcmaHelper::toVariant(const QSharedPointer<RShape>& cppValue) {
    QVariant v;

    if (cppValue.isNull()) {
        v.setValue(QSharedPointer<RShape>());
        return v;
    }

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

void REcmaHelper::printStackTrace(QScriptContext* context) {
    QScriptContext* c = context;
    while (c!=NULL) {
        qDebug() << c->toString();
        c = c->parentContext();
    }
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
