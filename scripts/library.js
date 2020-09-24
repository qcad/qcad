/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 * 
 * Function stringToDirectDistanceEntry added 2013 by Robert S.
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

// Version check is disabled for now. This can be used in the future to
// ensure compatibility between scripts and script bindings.
//requiresFramework([3,0,9,0], [3,1,0,0]);

// don't include sprintf.js here to keep library footprint small:
//include("sprintf.js");

if (typeof(global)==="undefined") {
    global = this;
    global.gMainWindow = undefined;
    global.gDocumentInterface = undefined;
}

/**
 * \param file File path argument given on command line (might be absolute or relative).
 * \return Absolute path of given file.
 */
function getAbsolutePathForArg(file) {
    // detect URL (TODO: breaks under win):
//    var url = new QUrl(file);
//    if (url.isValid() && url.scheme().length!==0 && !url.isLocalFile()) {
//        return file;
//    }

    // detect absolute path:
    var fi = new QFileInfo(file);
    if (fi.isAbsolute() || file.startsWith(":")){
        return file;
    }

    // relative path (prepend application dir):
    return RSettings.getLaunchPath() + QDir.separator + file;
}

/**
 * Checks if the QCAD Application Framework is at least of version minVersion
 * and not newer than maxVersion.
 *
 * \param minVersion array in the format [major,minor,revision,build]
 * \param maxVersion array in the format [major,minor,revision,build]
 */
function requiresFramework(minVersion, maxVersion) {
    var frameworkV = getVersionNumber(RSettings.getMajorVersion(), RSettings.getMinorVersion(), RSettings.getRevisionVersion(), RSettings.getBuildVersion());
    var minV = getVersionNumber(minVersion[0], minVersion[1], minVersion[2], minVersion[3]);
    var maxV = getVersionNumber(maxVersion[0], maxVersion[1], maxVersion[2], maxVersion[3]);

    if (frameworkV < minV) {
        qCritical("QCAD Application Framework is too old for script plugin ", includeBasePath);
        debugger;
    }

    if (frameworkV > maxV) {
        qCritical("QCAD Application Framework is too new for script plugin", includeBasePath);
        debugger;
    }
}

function getVersionNumber(major, minor, revision, build) {
    return major*1e9 + minor*1e6 + revision*1e3 + build;
}

/**
 * Check the real type of the given object.
 *
 * Standard ECMAScript typeof returns "string" for a string literal but
 * "object" for a string object constructed with new. Same goes for
 * arrays, etc. This function provides a workaround.
 */
function getTypeOf(v) {
    if (typeof(v)==="object") {
        if (v === null) {
            return "null";
        }
        if (v.constructor == (new String()).constructor) {
            return "string";
        }
        if (v.constructor == (new Array()).constructor) {
            return "array";
        }
        if (v.constructor == (new Date()).constructor) {
            return "date";
        }
        if (v.constructor == (new RegExp()).constructor) {
            return "regex";
        }
        return "object";
    }
    return typeof(v);
}

/**
 * Checks if the given object is of the given type. E.g.
 * isOfType(myObject, QLabel) returns true if myObject is a QLabel. Note
 * that isOfType(myObject, QWidget) returns false even though QLabel is
 * derived from QWidget.
 */
function isOfType(obj, type) {
    return !isNull(obj) && obj.constructor===type;
}

/**
 * Checks if the given object is undefined or null.
 *
 * \return true if the given object is defined and not null.
 * This method also supports shared pointers, i.e. obj.isNull()==true.
 */
function isNull(obj) {
    if (isDeleted(obj)) {
        return true;
    }

    return (obj==null ||
            (typeof(obj.isNull)==="function" && obj.isNull()===true));
}

/**
 * Checks if the given object is a valid number.
 *
 * \return true if the given object is a number and not NaN or +/-Infinity
 * or NULL or undefined.
 */
function isNumber(obj) {
    return (typeof(obj)==="number" && !isNaN(obj) && isFinite(obj));
}

function isNumberGreaterEqualZero(n) {
    return !isNaN(n) && n>=0;
};

function isNumberGreaterZero(n) {
    return !isNaN(n) && n>0;
};

/**
 * Checks if the given object is a string.
 *
 * \return true if the given object is a string
 */
function isString(obj) {
    return (typeof(obj)==="string");
}

/**
 * Checks if the given object is of type RVector.
 *
 * \return true if the given object is an RVector object.
 */
function isVector(obj) {
    return (typeof(obj)==="object" && isOfType(obj, RVector));
}

/**
 * Checks if the given object is a valid vector.
 *
 * \return true if the given object is a valid RVector object.
 */
function isValidVector(obj) {
    return (isVector(obj) && obj.isValid() && isNumber(obj.x) && isNumber(obj.y));
}

/**
 * Checks if the given object is a color.
 *
 * \return true if the given object is an RColor object.
 */
function isColor(obj) {
    return (typeof(obj)==="object" && isOfType(obj, RColor));
}

/**
 * Checks if the given object is a valid color.
 *
 * \return true if the given object is a valid RColor object.
 */
function isValidColor(obj) {
    return (isColor(obj) && obj.isValid());
}

/**
 * Checks if the given object is a valid boolean value.
 *
 * \return true if the given object is a boolean and not NULL or undefined.
 */
function isBoolean(obj) {
    return (typeof(obj)==="boolean");
}

/**
 * Checks if the given object is a valid function.
 *
 * \return true if the given object is a function.
 */
function isFunction(obj) {
    return (typeof(obj)==="function");
}

/**
 * Checks if the given object is a valid QObject.
 *
 * \return true if the given object is a QObject.
 */
function isQObject(obj) {
    return (typeof(obj)==="object" && !isNull(obj.objectName));
}

/**
 * Checks if the given object is a valid QWidget.
 *
 * \return true if the given object is a QWidget.
 */
function isQWidget(obj) {
    return (isQObject(obj) && typeof(obj.show)==="function");
}

/**
 * \return true if the given object is a separator (a frame of type vertical line).
 */
function isSeparator(obj) {
    return isOfType(obj, QFrame) && obj.frameShape==QFrame.VLine;
}

/**
 * Checks if the given object is a layer.
 *
 * \return true if the given object is a layer.
 */
function isLayer(obj) {
    return isOfType(obj, RLayer) || isOfType(obj, RLayerPointer);
}

/**
 * Checks if the given object is a block (RBlock).
 *
 * \return true if the given object is a block.
 */
function isBlock(obj) {
    return isOfType(obj, RBlock) || isOfType(obj, RBlockPointer);
}

/**
 * Checks if the given object is a layout (RLayout).
 *
 * \return true if the given object is a layout.
 */
function isLayout(obj) {
    return isOfType(obj, RLayout) || isOfType(obj, RLayoutPointer);
}

/**
 * Checks if the given object is an RObject.
 *
 * \return true if the given object is an object (derived from RObject).
 */
function isObject(obj) {
    return !isNull(obj) &&
        isFunction(obj.getType) &&
        isNumber(obj.getType());
}

/**
 * Checks if the given object is a graphics entity.
 *
 * \return true if the given object is an entity (derived from REntity).
 */
function isEntity(obj) {
    return !isNull(obj) &&
        isFunction(obj.getType) && 
        isFunction(obj.getData) &&
        isNumber(obj.getType());
}

/**
 * Checks if the given object is a dimension entity of any kind.
 * 
 * \return true if the given object is a dimension entity
 * (RDimensionEntity).
 */
function isDimensionEntity(obj) {
    return isDimAlignedEntity(obj)
        || isDimAngularEntity(obj)
        || isDimArcLengthEntity(obj)
        || isDimDiametricEntity(obj)
        || isDimLinearEntity(obj)
        || isDimOrdinateEntity(obj)
        || isDimRadialEntity(obj)
        || isDimRotatedEntity(obj);
}

/**
 * Checks if the given object is a diametric dimension entity.
 * 
 * \return true if the given object is a diametric dimension entity
 * (RDimDiametricEntity).
 */
function isDimDiametricEntity(obj) {
    return isOfType(obj, RDimDiametricEntity) || isOfType(obj, RDimDiametricEntityPointer);
}

/**
 * Checks if the given object is an aligned dimension entity.
 * 
 * \return true if the given object is an aligned dimension entity
 * (RDimAlignedEntity).
 */
function isDimAlignedEntity(obj) {
    return isOfType(obj, RDimAlignedEntity) || isOfType(obj, RDimAlignedEntityPointer);
}

/**
 * Checks if the given object is a rotated dimension entity.
 * 
 * \return true if the given object is a rotated dimension entity
 * (RDimRotatedEntity).
 */
function isDimRotatedEntity(obj) {
    return isOfType(obj, RDimRotatedEntity) || isOfType(obj, RDimRotatedEntityPointer);
}

/**
 * Checks if the given object is an ordinate dimension entity.
 * 
 * \return true if the given object is an ordinate dimension entity
 * (RDimOrdinateEntity).
 */
function isDimOrdinateEntity(obj) {
    return isOfType(obj, RDimOrdinateEntity) || isOfType(obj, RDimOrdinateEntityPointer);
}

/**
 * Checks if the given object is a radial dimension entity.
 * 
 * \return true if the given object is a radial dimension entity
 * (RDimRadialEntity).
 */
function isDimRadialEntity(obj) {
    return isOfType(obj, RDimRadialEntity) || isOfType(obj, RDimRadialEntityPointer);
}

/**
 * Checks if the given object is an angular dimension entity.
 * 
 * \return true if the given object is an angular dimension entity
 * (RDimAngular2LEntity or RDimAngular3PEntity).
 */
function isDimAngularEntity(obj) {
    return isDimAngular2LEntity(obj) || isDimAngular3PEntity(obj);
}

/**
 * Checks if the given object is an angular dimension from 2 lines entity.
 *
 * \return true if the given object is an angular dimension entity
 * (RDimAngular2LEntity).
 */
function isDimAngular2LEntity(obj) {
    return isOfType(obj, RDimAngular2LEntity) || isOfType(obj, RDimAngular2LEntityPointer);
}

/**
 * Checks if the given object is an angular dimension from 3 points entity.
 *
 * \return true if the given object is an angular dimension entity
 * (RDimAngular3PEntity).
 */
function isDimAngular3PEntity(obj) {
    return isOfType(obj, RDimAngular3PEntity) || isOfType(obj, RDimAngular3PEntityPointer);
}

/**
 * Checks if the given object is an arc length dimension entity.
 *
 * \return true if the given object is an arc length dimension entity
 * (RDimArcLengthEntity).
 */
function isDimArcLengthEntity(obj) {
    return isOfType(obj, RDimArcLengthEntity) || isOfType(obj, RDimArcLengthEntityPointer);
}

/**
 * Checks if the given object is a linear dimension entity.
 * 
 * \return true if the given object is a linear dimension entity
 * (RDimLinearEntity).
 */
function isDimLinearEntity(obj) {
    return isOfType(obj, RDimLinearEntity) || isOfType(obj, RDimLinearEntityPointer);
}

/**
 * Checks if the given object is a hatch entity.
 *
 * \return true if the given object is an arc entity (RHatchEntity).
 */
function isHatchEntity(obj) {
    return isOfType(obj, RHatchEntity) || isOfType(obj, RHatchEntityPointer);
}

/**
 * Checks if the given object is an arc entity.
 *
 * \return true if the given object is an arc entity (RArcEntity).
 */
function isArcEntity(obj) {
    return isOfType(obj, RArcEntity) || isOfType(obj, RArcEntityPointer);
}

/**
 * Checks if the given object is a circle entity.
 *
 * \return true if the given object is a line entity (RCircleEntity).
 */
function isCircleEntity(obj) {
    return isOfType(obj, RCircleEntity) || isOfType(obj, RCircleEntityPointer);
}

/**
 * Checks if the given object is an ellipse entity.
 *
 * \return true if the given object is an ellipse entity (REllipseEntity).
 */
function isEllipseEntity(obj) {
    return isOfType(obj, REllipseEntity) || isOfType(obj, REllipseEntityPointer);
}

/**
 * Checks if the given object is an ellipse entity and represents a full ellipse.
 *
 * \return true if the given object is an ellipse entity (REllipseEntity).
 */
function isFullEllipseEntity(obj) {
    return isEllipseEntity(obj) && obj.isFullEllipse();
}

/**
 * Checks if the given object is a line entity.
 *
 * \return true if the given object is a line entity (RLineEntity).
 */
function isLineEntity(obj) {
    return isOfType(obj, RLineEntity) || isOfType(obj, RLineEntityPointer);
}

/**
 * Checks if the given object is a line, xline or ray entity.
 *
 * \return true if the given object is a line based entity (RLineEntity, RXLineEntity, RRayEntity).
 */
function isLineBasedEntity(obj) {
    return isLineEntity(obj) || isXLineEntity(obj) || isRayEntity(obj);
}

/**
 * Checks if the given object is an xline entity.
 *
 * \return true if the given object is an xline entity (RXLineEntity).
 */
function isXLineEntity(obj) {
    return isOfType(obj, RXLineEntity) || isOfType(obj, RXLineEntityPointer);
}

/**
 * Checks if the given object is a ray entity.
 *
 * \return true if the given object is a ray entity (RRayEntity).
 */
function isRayEntity(obj) {
    return isOfType(obj, RRayEntity) || isOfType(obj, RRayEntityPointer);
}

/**
 * Checks if the given object is a point entity.
 *
 * \return true if the given object is a point entity (RPointEntity).
 */
function isPointEntity(obj) {
    return isOfType(obj, RPointEntity) || isOfType(obj, RPointEntityPointer);
}

/**
 * Checks if the given object is an image entity.
 *
 * \return true if the given object is an image entity (RImageEntity).
 */
function isImageEntity(obj) {
    return isOfType(obj, RImageEntity) || isOfType(obj, RImageEntityPointer);
}

/**
 * \return true if the given object is a polyline entity (RPolylineEntity).
 */
function isPolylineEntity(obj) {
    return isOfType(obj, RPolylineEntity) || isOfType(obj, RPolylineEntityPointer);
}

/**
 * \return true if the given object is a geometrically closed polyline entity.
 */
function isClosedPolylineEntity(obj, tolerance) {
    if (isNull(tolerance)) {
        return isPolylineEntity(obj) && obj.isGeometricallyClosed();
    }
    else {
        return isPolylineEntity(obj) && obj.isGeometricallyClosed(tolerance);
    }
}

/**
 * Checks if the given object is a solid entity.
 *
 * \return true if the given object is a solid entity (RSolidEntity).
 */
function isSolidEntity(obj) {
    return isOfType(obj, RSolidEntity) || isOfType(obj, RSolidEntityPointer);
}

/**
 * Checks if the given object is a trace entity.
 *
 * \return true if the given object is a trace entity (RTraceEntity).
 */
function isTraceEntity(obj) {
    return isOfType(obj, RTraceEntity) || isOfType(obj, RTraceEntityPointer);
}

/**
 * Checks if the given object is a face entity.
 *
 * \return true if the given object is a face entity (RFaceEntity).
 */
function isFaceEntity(obj) {
    return isOfType(obj, RFaceEntity) || isOfType(obj, RFaceEntityPointer);
}

/**
 * Checks if the given object is a viewport entity.
 *
 * \return true if the given object is a viewport entity (RViewportEntity).
 */
function isViewportEntity(obj) {
    return isOfType(obj, RViewportEntity) || isOfType(obj, RViewportEntityPointer);
}

/**
 * Checks if the given object is a spline entity.
 *
 * \return true if the given object is a spline entity (RSplineEntity).
 */
function isSplineEntity(obj) {
    return isOfType(obj, RSplineEntity) || isOfType(obj, RSplineEntityPointer);
}

/**
 * Checks if the given object is a spline entity with fit points.
 *
 * \return true if the given object is a spline entity (RSplineEntity) with fit points.
 */
function isSplineEntityWithFitPoints(obj) {
    return isSplineEntity(obj) && obj.hasFitPoints();
}

function isClosedSplineEntity(obj, tolerance) {
    if (isNull(tolerance)) {
        return isSplineEntity(obj) && obj.isGeometricallyClosed();
    }
    else {
        return isSplineEntity(obj) && obj.isGeometricallyClosed(tolerance);
    }
}

/**
 * Checks if the given object is a text, attribute or attribute definition entity.
 *
 * \return true if the given object is a text based entity (RTextBasedEntity).
 */
function isTextBasedEntity(obj) {
    return isTextEntity(obj) || isAttributeDefinitionEntity(obj) || isAttributeEntity(obj);
}

/**
 * Checks if the given object is a text entity.
 *
 * \return true if the given object is a text entity (RTextEntity).
 */
function isTextEntity(obj) {
    return isOfType(obj, RTextEntity) || isOfType(obj, RTextEntityPointer);
}

/**
 * Checks if the given object is a simple text entity.
 *
 * \return true if the given object is a text entity (RTextEntity) and simple.
 */
function isSimpleTextEntity(obj) {
    return isTextEntity(obj) && obj.isSimple();
}

/**
 * Checks if the given object is a block reference entity.
 *
 * \return true if the given object is a block reference entity (RBlockReferenceEntity).
 */
function isBlockReferenceEntity(obj) {
    return isOfType(obj, RBlockReferenceEntity) || isOfType(obj, RBlockReferenceEntityPointer);
}

/**
 * Checks if the given object is an attribute definition entity.
 *
 * \return true if the given object is an attribute definition entity (RAttributeDefinitionEntity).
 */
function isAttributeDefinitionEntity(obj) {
    return isOfType(obj, RAttributeDefinitionEntity) || isOfType(obj, RAttributeDefinitionEntityPointer);
}

/**
 * Checks if the given object is an attribute entity.
 *
 * \return true if the given object is an attribute entity (RAttributeEntity).
 */
function isAttributeEntity(obj) {
    return isOfType(obj, RAttributeEntity) || isOfType(obj, RAttributeEntityPointer);
}

/**
 * Checks if the given object is a leader entity.
 * 
 * \return true if the given object is a leader entity
 * (RLeaderEntity).
 */
function isLeaderEntity(obj) {
    return isOfType(obj, RLeaderEntity) || isOfType(obj, RLeaderEntityPointer);
}

/**
 * Checks if the given object is a tolerance entity.
 *
 * \return true if the given object is a tolerance entity (RToleranceEntity).
 */
function isToleranceEntity(obj) {
    return isOfType(obj, RToleranceEntity) || isOfType(obj, RToleranceEntityPointer);
}

/**
 * Checks if the given object is an entity of the given type.
 */
function isEntityType(obj, type) {
    if (!isEntity(obj)) {
        return false;
    }

    if (obj.getType()===type) {
        return true;
    }

    if (type===RS.EntityTextBased) {
        if (isTextBasedEntity(obj)) {
            return true;
        }
    }
    if (type===RS.EntityDimension) {
        if (isDimensionEntity(obj)) {
            return true;
        }
    }

    return false;
}

/**
 * Checks if the given object is a shape.
 *
 * \return true if the given object is a shape (derived from RShape).
 */
function isShape(obj) {
    return !isNull(obj) &&
        isFunction(obj.getBoundingBox) &&
        isFunction(obj.getClosestPointOnShape);
}

/**
 * Checks if the given object is a directed shape.
 *
 * \return true if the given object is a directed shape.
 */
function isDirectedShape(obj) {
    return isShape(obj) && obj.isDirected();
}

/**
 * Checks if the given object is an arc shape.
 *
 * \return true if the given object is an arc shape (RArc).
 */
function isArcShape(obj) {
    return isOfType(obj, RArc) || isOfType(obj, RArcPointer);
}

/**
 * Checks if the given object is a circle shape.
 *
 * \return true if the given object is a circle shape (RCircle).
 */
function isCircleShape(obj) {
    return isOfType(obj, RCircle) || isOfType(obj, RCirclePointer);
}

/**
 * Checks if the given object is an ellipse shape.
 *
 * \return true if the given object is an ellipse shape (REllipse).
 */
function isEllipseShape(obj) {
    return isOfType(obj, REllipse) || isOfType(obj, REllipsePointer);
}

/**
 * Checks if the given object is a full ellipse shape.
 *
 * \return true if the given object is a full ellipse shape (REllipse).
 */
function isFullEllipseShape(obj) {
    return isEllipseShape(obj) && obj.isFullEllipse();
}

/**
 * Checks if the given object is an ellipse arc shape.
 *
 * \return true if the given object is an ellipse arc shape (REllipse).
 */
function isEllipseArcShape(obj) {
    return isEllipseShape(obj) && !obj.isFullEllipse();
}

/**
 * Checks if the given object is a line based shape.
 *
 * \return true if the given object is a line based shape (RLine, RXline, RRay).
 */
function isLineBasedShape(obj) {
    return isLineShape(obj) || isXLineShape(obj) || isRayShape(obj);
}

/**
 * Checks if the given object is a line shape.
 *
 * \return true if the given object is a line shape (RLine).
 */
function isLineShape(obj) {
    return isOfType(obj, RLine) || isOfType(obj, RLinePointer);
}

/**
 * Checks if the given object is an xline shape.
 *
 * \return true if the given object is an xline shape (RXLine).
 */
function isXLineShape(obj) {
    return isOfType(obj, RXLine) || isOfType(obj, RXLinePointer);
}

/**
 * Checks if the given object is a ray shape.
 *
 * \return true if the given object is a ray shape (RRay).
 */
function isRayShape(obj) {
    return isOfType(obj, RRay) || isOfType(obj, RRayPointer);
}

/**
 * Checks if the given object is a point shape.
 *
 * \return true if the given object is a point shape (RPoint).
 */
function isPointShape(obj) {
    return isOfType(obj, RPoint) || isOfType(obj, RPointPointer);
}

/**
 * Checks if the given object is a polyline shape.
 *
 * \return true if the given object is a polyline shape (RPolyline).
 */
function isPolylineShape(obj) {
    return isOfType(obj, RPolyline) || isOfType(obj, RPolylinePointer);
}

/**
 * \return true if the given object is a geometrically closed polyline shape.
 */
function isClosedPolylineShape(obj) {
    return isPolylineShape(obj) && obj.isGeometricallyClosed();
}

/**
 * Checks if the given object is a spline shape.
 *
 * \return true if the given object is a spline shape (RSpline).
 */
function isSplineShape(obj) {
    return isOfType(obj, RSpline) || isOfType(obj, RSplinePointer);
}

/**
 * Checks if the given object is a closed spline shape.
 *
 * \return true if the given object is a closed spline shape (RSpline).
 */
function isClosedSplineShape(obj, tolerance) {
    if (isNull(tolerance)) {
        return isSplineShape(obj) && obj.isGeometricallyClosed();
    }
    else {
        return isSplineShape(obj) && obj.isGeometricallyClosed(tolerance);
    }
}

/**
 * Checks if the given object is a triangle shape.
 *
 * \return true if the given object is a triangle shape (RTriangle).
 */
function isTriangleShape(obj) {
    return isOfType(obj, RTriangle) || isOfType(obj, RTrianglePointer);
}


/**
 * Converts the given entity type enum to a human readable,
 * translated string.
 *
 * \return A translated string for the given entity type.
 *
 * \param type Entity type (RS::EntityType)
 * \param plural True to return plural, false (default) to return singular.
 */
function entityTypeToString(type, plural) {
    if (isNull(plural)) {
        plural = false;
    }

    switch (type) {
    case RS.ObjectAll:
        return plural ? qsTr("Objects") : qsTr("Object");
    case RS.ObjectUnknown:
        return plural ? qsTr("Unknown Objects") : qsTr("Unknown Object");
    case RS.ObjectBlock:
        return plural ? qsTr("Blocks") : qsTr("Block");
    case RS.ObjectLayer:
        return plural ? qsTr("Layers") : qsTr("Layer");
    case RS.ObjectLayout:
        return plural ? qsTr("Layouts") : qsTr("Layout");
    case RS.ObjectLinetype:
        return plural ? qsTr("Linetypes") : qsTr("Linetype");
    case RS.ObjectView:
        return plural ? qsTr("Views") : qsTr("View");

    case RS.EntityAll:
        return plural ? qsTr("Entities") : qsTr("Entity");
    case RS.Entity3dFace:
        return plural ? qsTr("3dFaces") : qsTr("3dFace");
    case RS.EntityBlockRef:
        return plural ? qsTr("Block References") : qsTr("Block Reference");
    case RS.EntityBlockRefAttr:
        return plural ? qsTr("Block References and Attributes") : qsTr("Block Reference and Attributes");
    case RS.EntityArc:
        return plural ? qsTr("Arcs") : qsTr("Arc");
    case RS.EntityAttribute:
        return plural ? qsTr("Attributes") : qsTr("Attribute");
    case RS.EntityAttributeDefinition:
        return plural ? qsTr("Attribute Definitions") : qsTr("Attribute Definition");
    case RS.EntityCircle:
        return plural ? qsTr("Circles") : qsTr("Circle");
    case RS.EntityDimension:
        return plural ? qsTr("Dimensions") : qsTr("Dimension");
    case RS.EntityDimAligned:
        return plural ? qsTr("Aligned Dimensions") : qsTr("Aligned Dimension");
    case RS.EntityDimAngular:
        return plural ? qsTr("Angular Dimensions") : qsTr("Angular Dimension");
    case RS.EntityDimAngular2L:
        return plural ? qsTr("Angular Dimensions (2 Line)") : qsTr("Angular Dimension (2 Line)");
    case RS.EntityDimAngular3P:
        return plural ? qsTr("Angular Dimensions (3 Point)") : qsTr("Angular Dimension (3 Point)");
    case RS.EntityDimArcLength:
        return plural ? qsTr("Arc Dimension") : qsTr("Arc Dimension");
    case RS.EntityDimDiametric:
        return plural ? qsTr("Diametric Dimensions") : qsTr("Diametric Dimension");
    case RS.EntityDimOrdinate:
        return plural ? qsTr("Ordinate Dimensions") : qsTr("Ordinate Dimension");
    case RS.EntityDimRotated:
        return plural ? qsTr("Rotated Dimensions") : qsTr("Rotated Dimension");
    case RS.EntityDimRadial:
        return plural ? qsTr("Radial Dimensions") : qsTr("Radial Dimension");
    case RS.EntityEllipse:
        return plural ? qsTr("Ellipses") : qsTr("Ellipse");
    case RS.EntityHatch:
        return plural ? qsTr("Hatches") : qsTr("Hatch");
    case RS.EntityImage:
        return plural ? qsTr("Images") : qsTr("Image");
    case RS.EntityLeader:
        return plural ? qsTr("Leaders") : qsTr("Leader");
    case RS.EntityTolerance:
        return plural ? qsTr("Tolerances") : qsTr("Tolerance");
    case RS.EntityLine:
        return plural ? qsTr("Lines") : qsTr("Line");
    case RS.EntityXLine:
        return plural ? qsTr("Infinite Lines") : qsTr("Infinite Line");
    case RS.EntityRay:
        return plural ? qsTr("Rays") : qsTr("Ray");
    case RS.EntityPoint:
        return plural ? qsTr("Points") : qsTr("Point");
    case RS.EntityPolyline:
        return plural ? qsTr("Polylines") : qsTr("Polyline");
    case RS.EntitySolid:
        return plural ? qsTr("Solids") : qsTr("Solid");
    case RS.EntityTrace:
        return plural ? qsTr("Traces") : qsTr("Trace");
    case RS.EntityFace:
        return plural ? qsTr("Faces") : qsTr("Face");
    case RS.EntitySpline:
        return plural ? qsTr("Splines") : qsTr("Spline");
    case RS.EntityTextBased:
        return plural ? qsTr("Text based") : qsTr("Text based");
    case RS.EntityText:
        return plural ? qsTr("Texts") : qsTr("Text");
    case RS.EntityViewport:
        return plural ? qsTr("Viewports") : qsTr("Viewport");
    case RS.EntityUnknown:
    default:
        return plural ? qsTr("Unknown Entities") : qsTr("Unknown Entity");
    }
}

function translateFilterStrings(filterStrings) {
    for (var i=0; i<filterStrings.length; i++) {
        filterStrings[i] = filterStrings[i].replace("All CAD Files", qsTr("All CAD Files"));
        filterStrings[i] = filterStrings[i].replace("DXF Files", qsTr("DXF Files"));
        filterStrings[i] = filterStrings[i].replace("SVG Files", qsTr("SVG Files"));
        filterStrings[i] = filterStrings[i].replace("DXF Drawing", qsTr("DXF Drawing"));
        filterStrings[i] = filterStrings[i].replace("DWG Drawing", qsTr("DWG Drawing"));
        filterStrings[i] = filterStrings[i].replace("PDF File", qsTr("PDF File"));
        filterStrings[i] = filterStrings[i].replace("PDF/A-1B File", qsTr("PDF/A-1B File"));
    }
    return filterStrings;
}

/**
 * Checks the type of the given object.
 *
 * \return true if the given object is a combo box.
 */
function isComboBox(obj) {
    return !isNull(obj) &&
            (
             isOfType(obj, QComboBox) ||
             isOfType(obj, RColorCombo) ||
             isOfType(obj, RLineweightCombo) ||
             isOfType(obj, RLinetypeCombo)
            );
}

/**
 * Gets an object from its object path.
 * Object paths are separated by <tt>::</tt>.
 * \param path the object path
 * \param widget the widget [optional, used for the recursive call], obsolete
 * \return Object or undefined
 */
function objectFromPath(path) {
    var child = getMainWindow();
    var children = path.split("::");
    for (var i = 1; i < children.length; ++i) {
        if (typeof(child)==="undefined") {
            return undefined;
        }
        child = child.findChild(children[i]);
    }
    return child;
}

/**
 * Gets the widget path for the given widget.
 * The widgets in the path are separated with <tt>::</tt>,
 * e.g. <tt>MainWindow::LayerListDock::LayerWidget::btAdd</tt>  
 * \param widget the widget
 * \return the widget path
 */
function getWidgetPath(widget) {
    var pw = widget.parentWidget();
    var str = widget.objectName !== "" ? widget.objectName : widget.toString();
    if (isNull(pw)) {
        return str;
    }
    return getWidgetPath(pw) + "::" + str;
}

/**
 * Gets all child widgets and stores them in an array.
 *
 * All child widgets are retrieved (recursively).
 * 
 * Use of this function as shown in the example below
 * (formWidget is the parent widget). 
 * <tt>
 * var widgets = getWidgets(formWidget);
 * widgets["FindText"].text = text;
 * </tt>
 * 
 * \param widget the parent widget
 * \param ca the initial array which holds some child widgets for
 *        recursive calls
 * \param allowDuplicates True to collect widgets with same name under
 * a different key ("MyField", "MyField_1", "MyField_2").
 * \return Array of child widgets.
 */
function getWidgets(widget, ca, allowDuplicates) {
    if (isNull(widget) || isDeleted(widget)) {
        return undefined;
    }
    if (isNull(allowDuplicates)) {
        allowDuplicates = false;
    }

    if (isNull(ca)) {
        ca = {};
    }
    var children = widget.children();
    for (var i = 0; i < children.length; ++i) {
        var child = children[i];
        if (isDeleted(child)) {
            continue;
        }
        if (!isNull(child.objectName) && child.objectName !== "") {
            if (isNull(ca[child.objectName]) || allowDuplicates===false) {
                // new child or overwrite child:
                ca[child.objectName] = child;
            }
            else {
                // find alternative key for child:
                for (var k=1; k<10000; k++) {
                    if (isNull(ca[child.objectName + "_" + k])) {
                        ca[child.objectName + "_" + k] = child;
                        break;
                    }
                }
            }
        }

        if (!isNull(child.children) && child.children().length !== 0) {
            getWidgets(child, ca, allowDuplicates);
        }
    }

    return ca;
}

/**
 * Converts radiant to degrees.
 * \param val the value in radiant
 * \return the value in degrees
 */
function rad2deg(val) {
    return val * (180 / Math.PI);
}

/**
 * Converts degrees to radiant.
 * \param val the value in degrees
 * \return the value in radiant
 */
function deg2rad(val) {
    return val * (Math.PI / 180);
}

function roundDouble(num, dec) {
    return Math.round(num*Math.pow(10, dec)) / Math.pow(10, dec);
}

function roundVector(v, dec) {
    var x = roundDouble(v.x, dec);
    var y = roundDouble(v.y, dec);
    return new RVector(x, y);
}

/**
 * Copies a directory recursively.
 * Existing files are not overridden.
 * \param sourceDirPath The source directory.
 * \param destDirPath The destination directory.
 * \return true, if the directory was deleted successfully
 */
function copyDirectory(sourceDirPath, destDirPath) {
    var sourceDir = new QDir(sourceDirPath);
    if (!sourceDir.exists()) {
        return false;
    }
    
    var destDir = new QDir(destDirPath);
    if (!destDir.exists()) {
        destDir.mkdir(destDirPath);
    }
    
    var i;
    var files;
    var srcName;
    var destName;
    var filterFlags = new QDir.Filters(QDir.Files);
    var sortFlags = new QDir.SortFlags(QDir.NoSort);
    files = sourceDir.entryList(filterFlags, sortFlags);
    for(i = 0; i< files.length; i++) {
        srcName = sourceDirPath + QDir.separator + files[i];
        destName = destDirPath + QDir.separator + files[i];
        if (!QFile.copy(srcName, destName)) {
            qWarning("library.js:", "copyDirectory(): Warning: File exists:", destName);
        }
    }

    var flags = new QDir.Filters(QDir.AllDirs, QDir.NoDotAndDotDot);
    files = sourceDir.entryList(flags);
    for(i = 0; i< files.length; i++) {
        srcName = sourceDirPath + QDir.separator + files[i];
        destName = destDirPath + QDir.separator + files[i];
        copyDirectory(srcName, destName);
    }
    return true;
}

/**
 * Removes a directory recursively.
 * \param dirPath The directory to remove.
 * \return true, if no errors occurs
 */
function removeDirectory(dirPath) {
    var dir = new QDir(dirPath);
    var hasErr = false;
    if (dir.exists()) {
        var flags = new QDir.Filters(QDir.NoDotAndDotDot, 
                QDir.Dirs, QDir.Files, QDir.Hidden);
        var entries = dir.entryInfoList(flags);
        for (var i = 0; i <  entries.length; i++) {
            var entryInfo = entries[i];
            var path = entryInfo.absoluteFilePath();
            if (entryInfo.isDir()) {
                hasErr = removeDirectory(path);
            } else {
                var file = new QFile(path);
                if (!file.remove()) {
                    hasErr = true;
                }
            }
            if (hasErr) {
                break;
            }
        }
        if (!dir.rmdir(dir.absolutePath())) {
            hasErr = true;
        }
    }
    return hasErr;
}

/**
 * Finds a file recursively.
 * \param dirPath The directory to search.
 * \param fileName File name.
 * \return Path of the file or undefined.
 */
function findFile(dirPath, fileName, ignoreDirs) {
    if (isNull(ignoreDirs)) {
        ignoreDirs = [];
    }

    var res = [];

    var dir = new QDir(dirPath);
    if (!dir.exists()) {
        return res;
    }

    var i;
    var files;
    var name;
    var filterFlags = new QDir.Filters(QDir.Files);
    var sortFlags = new QDir.SortFlags(QDir.NoSort);
    files = dir.entryList([fileName], filterFlags, sortFlags);
    for (i=0; i<files.length; i++) {
        res = res.concat(dirPath + QDir.separator + files[i]);
    }

    var flags = new QDir.Filters(QDir.AllDirs, QDir.NoDotAndDotDot);
    files = dir.entryList(flags);
    for (i = 0; i< files.length; i++) {
        var nextDir = dirPath + QDir.separator + files[i];
        if (ignoreDirs.indexOf(files[i])==-1) {
            res = res.concat(findFile(nextDir, fileName, ignoreDirs));
        }
    }

    return res;
}

/**
 * Clones the given object (deep copy).
 */
function deepCopy(obj) {
    if (Object.prototype.toString.call(obj) === '[object Array]') {
        var out = [], i = 0, len = obj.length;
        for ( ; i < len; i++ ) {
            out[i] = arguments.callee(obj[i]);
        }
        return out;
    }
    if (typeof obj === 'object') {
        var out = {}, i;
        for ( i in obj ) {
            out[i] = arguments.callee(obj[i]);
        }
        return out;
    }
    return obj;
}

function hasOwnPropertyCI(obj, prop) {
   return Object.keys(obj)
           .filter(function (v) {
               return v.toLowerCase() === prop.toLowerCase();
           }).length > 0;
}

function getOwnPropertyCI(obj, prop) {
    var ret = Object.keys(obj)
            .filter(function (v) {
                return v.toLowerCase() === prop.toLowerCase();
            });
    if (ret.length>0) {
        return obj[ret[0]];
    }
    return undefined;
}

/**
 * \return A new array which contains every unique item of this array only once.
 */
Array.prototype.unique = function(method) {
    var a = [], i, l = this.length;
    for (i = 0; i < l; i++) {
        if (isNull(method)) {
            if (a.indexOf(this[i], 0) < 0) {
                a.push(this[i]);
            }
        }
        else {
            if (!a.contains(this[i], method)) {
                a.push(this[i]);
            }
        }
    }
    return a;
};

/**
 * \return True if this array contains the given value or object 'obj'.
 * \param method Name of method to call from obj to compare it to anther object.
 * Opptional,  defaults to == operator for the comparison.
 */
Array.prototype.contains = function(obj, method) {
    for (var i = 0; i < this.length; i++) {
        // method is a function(a,b):
        if (isFunction(method)) {
            if (method(this[i], obj)) {
                return true;
            }
        }
        else if (isFunction(this[i][method])) {
            // method is the name of a member method that compares
            // two objects, eg. "equals":
            if (this[i][method](obj)) {
                return true;
            }
        }
        else {
            if (this[i] == obj) {
                return true;
            }
        }
    }
    return false;
};

/**
 * \return True if this array contains the given string (case insensitive).
 */
Array.prototype.containsIgnoreCase = function(obj) {
    return this.contains(obj, function(a,b) { return a.toUpperCase()===b.toUpperCase(); });
};

/**
 * \return Array with all elements of this array that are not also
 * in the given array (subtract).
 */
Array.prototype.difference = function(a) {
    return this.filter(function(i) { return !(a.indexOf(i) > -1); } );
};

/**
 * \return True if this array is identical with the given array in
 * length and contents.
 */
Array.prototype.isEqual = function(b) {
    if (this.length!==b.length) {
        return false;
    }

    for (var i=0; i<this.length; i++) {
        if (this[i]!==b[i]) {
            return false;
        }
    }

    return true;
};

/**
 * \return True if the length of this array is zero.
 */
Array.prototype.isEmpty = function() {
    return (this.length == 0);
};

/**
 * Empties the array (sets its length to 0).
 */
Array.prototype.clear = function() {
    this.length = 0;
};

/**
 * Remove the first match of the given value from the array.
 * \param val The value to remove.
 */
Array.prototype.remove = function(val, compareFunction) {
    for (var i=0; i<this.length; i++) {
        var match = false;
        if (!isNull(compareFunction)) {
            match = compareFunction(this[i], val);
        }
        else {
            match = (this[i] == val);
        }

        if (match) {
            this.splice(i, 1);
            break;
        }
    }
};

/**
 * Removes all matches of the given value from the array.
 * \param The value(s) to remove.
 */
Array.prototype.removeAll = function() {
    var what, a = arguments, l = a.length, ax;
    while (l && this.length) {
        what = a[--l];
        while ((ax = this.indexOf(what)) !== -1) {
            this.splice(ax, 1);
        }
    }
    return this;
};

/**
 * Remove the first case insensitive match of the given string value from the array.
 * \param val The value to remove.
 */
Array.prototype.removeIgnoreCase = function(val) {
    this.remove(val, function(a,b) { return a.toUpperCase()===b.toUpperCase(); });
};

/**
 * Remove the given parameter from an array (by default 'undefined').
 * 
 * test = new Array("","One","Two","", "Three","","Four").clean("");
 *
 * test2 = [1,2,,3,,3,,,,,,4,,4,,5,,6,,,,];
 * test2.clean(undefined);
 *
 * \param deleteValue
 * \return {Array}
 */
Array.prototype.clean = function(deleteValue) {
    for (var i = 0; i < this.length; i++) {
        if (this[i] == deleteValue) {         
            this.splice(i, 1);
            i--;
        }
    }
    return this;
};

/**
 * Clones (copies) the array.
 * 
 * \returns the cloned array
 */
Array.prototype.clone = function() {
    return this.slice(0);
};

/**
 * Sorts this array with numerical items (ascending)
 */
Array.prototype.sortNumerical = function() {
    Array.prototype.sort.call(this, function(a,b) { return a - b });
}

Array.alphaNumericalSorter = function(a, b) {
    return RS.compareAlphanumerical(a, b);
};

/**
 * Sorts this array with string items (case insensitive)
 */
//Array.prototype.sortCaseInsensitive = function() {
//    Array.prototype.sort.call(this, function (a, b) {
//        return a.toLowerCase().localeCompare(b.toLowerCase());
//    });
//};

/* Finds the intersection of two sorted arrays.
 *
 * \param a first array, must already be sorted
 * \param b second array, must already be sorted
 *
 * Items must be sorted NUMERICALLY (sortNumerical) if arrays contain numbers or
 * ALPHABETICALLY (sort) if arrays contain strings.
 *
 * Should have O(n) operations, where n is
 * n = MIN(a.length(), b.length())
 */
Array.intersectSafe = function(a, b) {
    var ai=0;
    var bi=0;
    var result = [];

    while (ai < a.length && bi < b.length) {
        if (a[ai] < b[bi]) {
            ai++;
        }
        else if (a[ai] > b[bi]) {
            bi++;
        }
        else {
            result.push(a[ai]);
            ai++;
            bi++;
        }
    }

    return result;
};

/**
 * Destructively finds the intersection of
 * two arrays.
 *
 * \param a first array, must already be sorted
 * \param b second array, must already be sorted
 *
 * Items must be sorted NUMERICALLY (sortNumerical) if arrays contain numbers or
 * ALPHABETICALLY (sort) if arrays contain strings.
 *
 * State of input arrays is undefined when
 * the function returns.
 */
Array.intersect = function(a, b) {
  var result = [];
  while (a.length > 0 && b.length > 0 ) {
     if (a[0] < b[0]) {
        a.shift();
     }
     else if (a[0] > b[0]) {
        b.shift();
     }
     else {
       result.push(a.shift());
       b.shift();
     }
  }

  return result;
};

/**
 * Escapes a string for use as literlal match in regular expression.
 */
RegExp.escape = function(s) {
    return s.replace(/[\-\[\]{}()*+?.,\\\^$|#\s]/g, "\\$&");
};

/**
 * Checks the type of the given object.
 *
 * \return true if the given object is an array.
 */
function isArray(obj) {
    return getTypeOf(obj)==="array";
    //return obj && !(obj.propertyIsEnumerable('length'))
    //    && typeof obj === 'object' && typeof(obj.length) === 'number';
}

/**
 * \class String
 * \brief ECMAScript Script class.
 */

/**
 * Capitalize words in a text string.
 * \return New string with capitalized words.
 */
String.prototype.capitalize = function(){
    return this.replace( /(^|\s)([a-z])/g , function(m, p1, p2){
        return p1 + p2.toUpperCase();
    });
};

/**
 * Trims white space.
 * \return New string with removed whitespace at start and end of this string.
 */
String.prototype.trim = function() {
    return this.replace(/^\s+|\s+$/g, '');
};

/**
 * Shortens a string.
 * \return New string shortened to the given number of pixels using ellipsis (...).
 */
String.prototype.elidedText = function(font, pixel) {
    var fm = new QFontMetrics(font);
    var t = fm.elidedText(this, Qt.ElideMiddle, pixel);
    fm.destroy();
    // replace HORIZONTAL ELLIPSIS (not every GUI font has those):
    t = t.replace(/\u2026/g, '...');
    return t;
};

/**
 * Returns true if this string starts with \c str.
 */
String.prototype.startsWith = function(str) {
    return (this.indexOf(str) === 0);
};

/**
 * Returns true if this string ends with \c str.
 */
String.prototype.endsWith = function(str) {
    return this.indexOf(str, this.length - str.length) !== -1;
};

/**
 * Returns true if this string is empty.
 */
String.prototype.isEmpty = function() {
    return (this == "");
};

/**
 * Returns true if this string contains \c str.
 */
String.prototype.contains = function(str) {
    return this.indexOf(str)!==-1;
};

/**
 * Returns true if this string contains \c str. Case insensitive.
 */
String.prototype.containsIgnoreCase = function(str) {
    return this.toLowerCase().indexOf(str.toLowerCase())!==-1;
};


/**
 * Returns the number of occurrences of \c ch in this string.
 */
String.prototype.count = function(ch) {
    return this.split(ch).length - 1;
};

/**
 * Returns a substring that contains the \c num leftmost characters of this string.
 */
String.prototype.left = function(num) {
    if (num>this.length) {
        return this;
    }
    return this.substr(0,num);
};

/**
 * Returns a substring that contains the \c num rightmost characters of this string.
 */
String.prototype.right = function(num) {
    if (num>this.length) {
        return this;
    }
    return this.substr(this.length-num, num);
};

/**
 * Returns a string that contains \c n characters of this string, 
 * starting at the specified \c position index.
 */
String.prototype.mid = function(position, n) {
    return this.substr(position, n);
};

/**
 * Returns true if this string equals "true".
 */
String.prototype.toBoolean = function() {
    return (/^true$/i).test(this);
};

/**
 * Converts this string into a float value if possible. If not, returns NaN.
 */
String.prototype.toFloat = function() {
    return parseFloat(this);
};

/**
 * Converts this string into an int value if possible. If not, returns NaN.
 */
String.prototype.toInt = function() {
    return parseInt(this, 10);
};

/**
 * Wraps a string after the given number of characters.
 * 
 * Example:
 * "long string".wordWrap(80, true, "\n")
 * Wraps after 80 characters, break words, too, uses a "\n" character
 * for new lines.
 * 
 * @param m the number of characters to wrap after 
 * @param c true: break words, false: don't break words 
 * @param b line break character, usually "\n"
 * @returns the wrapped text
 */
String.prototype.wordWrap = function(m, c, b){
    if(isNull(m)){
        m = 80;
    }
    if(isNull(c)){
        c = false;
    }
    if(isNull(b)){
        b = "\n";
    }
    
    var i, j, s, r = this.split("\n");
    if(m > 0) for(i in r){
        for(s = r[i], r[i] = ""; s.length > m;
            j = c ? m : (j = s.substr(0, m).match(/\S*$/)).input.length - j[0].length
            || m,
            r[i] += s.substr(0, j) + ((s = s.substr(j)).length ? b : "")
        );
        r[i] += s;
    }
    return r.join("\n");
};

String.prototype.regexIndexOf = function(regex, startpos) {
    var indexOf = this.substring(startpos || 0).search(regex);
    return (indexOf >= 0) ? (indexOf + (startpos || 0)) : indexOf;
}

String.prototype.regexLastIndexOf = function(regex, startpos) {
    regex = (regex.global) ? regex : new RegExp(regex.source, "g" + (regex.ignoreCase ? "i" : "") + (regex.multiLine ? "m" : ""));
    if(typeof (startpos) == "undefined") {
        startpos = this.length;
    } else if(startpos < 0) {
        startpos = 0;
    }
    var stringToWorkWith = this.substring(0, startpos + 1);
    var lastIndexOf = -1;
    var nextStop = 0;
    while((result = regex.exec(stringToWorkWith)) != null) {
        lastIndexOf = result.index;
        regex.lastIndex = ++nextStop;
    }
    return lastIndexOf;
}

/**
 * Modulo which works also for negative numbers (workaround for
 * ECMAScript modulo bug).
 */
Number.prototype.mod = function(n) {
    return ((this%n)+n)%n;
};

Math.sign = Math.sign || function(x) {
  x = +x; // convert to a number
  if (x === 0 || isNaN(x)) {
    return Number(x);
  }
  return x > 0 ? 1 : -1;
};

/**
 * Formats the given number into a locale aware string.
 */
function numberToString(num, decimals) {
    //var ret = "%1".arg(num, 0, 'f', decimals);
    var formatString = "%." + decimals + "f";
    var ret = sprintf(formatString, num);
    var decimalPoint = RSettings.getStringValue("Input/DecimalPoint", ".");
    if (decimalPoint!==".") {
        ret = ret.replace(".", decimalPoint);
    }
    return ret;
}

function angleToString(num, decimals) {
    var formatString = "%." + decimals + "f";
    var ret = sprintf(formatString, num);
    var decimalPoint = RSettings.getStringValue("Input/DecimalPoint", ".");
    if (decimalPoint!==".") {
        ret = ret.replace(".", decimalPoint);
    }
    return ret;
}

/**
 * Formats the given coordinate (RVector) into a locale aware string.
 */
function coordinateToString(coordinate, decimals, relative, polar, doc) {
    if (isNull(decimals)) {
        decimals = 3;
    }
    if (isNull(relative)) {
        relative = false;
    }
    if (isNull(polar)) {
        polar = false;
    }

    var first;
    var second;
    var sep;
    if (polar) {
        sep = RSettings.getPolarCoordinateSeparator();
        if (!isNull(doc)) {
            first = doc.formatLinear(coordinate.getMagnitude());
            second = doc.formatAngle(coordinate.getAngle());
        }
        else {
            first = numberToString(coordinate.getMagnitude(), decimals);
            second = angleToString(coordinate.getAngle() / (2 * Math.PI) * 360, decimals);
        }
    }
    else {
        sep = RSettings.getCartesianCoordinateSeparator();
        if (!isNull(doc)) {
            first = doc.formatLinear(coordinate.x);
            second = doc.formatLinear(coordinate.y);
        }
        else {
            first = numberToString(coordinate.x, decimals);
            second = numberToString(coordinate.y, decimals);
        }
    }

    var prefix;
    if (relative) {
        prefix = RSettings.getRelativeCoordinatePrefix();
    }
    else {
        prefix = "";
    }

    return prefix + first + sep + second;
}

/**
 * Parses the given string as coordinate.
 *
 * \param relativeZero RVector position of relative zero point.
 * \param str String to parse (e.g. "34,15.6" or "@10,30" or "50<60", ...)
 *
 * \return undefined if the string is not a coordinate, an invalid RVector
 *      if str is an invalid coordinate or the RVector result.
 */
function stringToCoordinate(relativeZero, str) {
    return RMath.parseCoordinate(str, relativeZero);
}

/**
 * Parses the given string as direct distance entry.
 *
 * \author Robert S
 *
 * \param relativeZero RVector position of relative zero point.
 * \param cursorPosition RVector position of cursor.
 * \param str String to parse (e.g. "34" or "15.123", ...)
 *
 * \return Invalid RVector if str is an invalid dde or
 *         return the dde point.
 */
function stringToDirectDistanceEntry(relativeZero, cursorPosition, str) {
    var cartCoordSep =
        RSettings.getStringValue("Input/CartesianCoordinateSeparator", ',');
    var polCoordSep =
        RSettings.getStringValue("Input/PolarCoordinateSeparator", '<');
    if (str.contains(cartCoordSep) || str.contains(polCoordSep)) {
        return undefined;
    }

    var value = RMath.eval(str);
    if (isNumber(value)) {
        var point1 = relativeZero;
        if (!isValidVector(point1)) {       // if this is the first action
            point1 = new RVector(0.0, 0.0); // of a new drawing relativezero
        }                                   // is not valid
        var point2 = cursorPosition;
        if (point1.equalsFuzzy(point2)) {
            // cursor at same pos as relative zero:
            return RVector.invalid;
        }

        var angle = point1.getAngleTo(point2);
        var v = new RVector();
        v.setPolar(value, angle);
        var point = point1.operator_add(v);
        return point;
     } else {
        // not a direct distance entry (not an error):
        return undefined;
     }
}

/**
 * Creates and returns a new entity based on the given shape.
 */
function shapeToEntity(document, shape) {
    var s = shape;
    if (isFunction(s.data)) {
        s = s.data();
    }

    if (isPointShape(s)) {
        return new RPointEntity(document, new RPointData(s.getPosition()));
    }
    else if (isLineShape(s)) {
        return new RLineEntity(document, new RLineData(s));
    }
    else if (isRayShape(s)) {
        return new RRayEntity(document, new RRayData(s));
    }
    else if (isXLineShape(s)) {
        return new RXLineEntity(document, new RXLineData(s));
    }
    else if (isArcShape(s)) {
        return new RArcEntity(document, new RArcData(s));
    }
    else if (isCircleShape(s)) {
        return new RCircleEntity(document, new RCircleData(s));
    }
    else if (isEllipseShape(s)) {
        return new REllipseEntity(document, new REllipseData(s));
    }
    else if (isPolylineShape(s)) {
        return new RPolylineEntity(document, new RPolylineData(s));
    }
    else if (isSplineShape(s)) {
        return new RSplineEntity(document, new RSplineData(s));
    }
    else if (isTriangleShape(s)) {
        return new RSolidEntity(document, new RSolidData(s));
    }

    qWarning("shapeToEntity: unknown shape: ", s);
    return undefined;
}

function getClosestSimpleShape(entity, pos) {
    return entity.getClosestSimpleShape(pos);
}

function trimStartPoint(shape, trimPoint, clickPoint) {
    shape.trimStartPoint(trimPoint, clickPoint);
    if (isXLineShape(shape)) {
        return xLineToRay(shape);
    }
    else {
        return shape;
    }
}

function trimEndPoint(shape, trimPoint, clickPoint) {
    shape.trimEndPoint(trimPoint, clickPoint);
    if (isXLineShape(shape)) {
        return xLineToRay(shape);
    }
    else if (isRayShape(shape)) {
        return rayToLine(shape);
    }
    else {
        return shape;
    }
}

function xLineToRay(xline) {
    return new RRay(xline.getBasePoint(), xline.getDirectionVector());
};

function rayToLine(ray) {
    return new RLine(ray.getBasePoint(), ray.getSecondPoint());
};

/**
 * Modify the given entity to represent the given shape.
 *
 * Possible conversions:
 * Line -> XLine, Ray
 * XLine -> Line, Ray
 * Ray -> XLine, Line
 * Circle -> Arc
 */
function modifyEntity(op, entity, shape) {
    if ((isXLineEntity(entity) && (isRayShape(shape) || isLineShape(shape))) ||
        (isRayEntity(entity) && (isXLineShape(shape) || isLineShape(shape))) ||
        (isLineEntity(entity) && (isXLineShape(shape) || isRayShape(shape))) ||
        (isCircleEntity(entity) && isArcShape(shape))) {

        var e = shapeToEntity(entity.getDocument(), shape);
//        if (isFunction(entity.data)) {
//            e.copyAttributesFrom(entity.data());
//            op.deleteObject(entity.data());
//        }
//        else {
            e.copyAttributesFrom(entity);
            op.deleteObject(entity);
//        }

        op.addObject(e, false);
        return true;
    }

    if (isFunction(entity.setShape)) {
        entity.setShape(shape);
        op.addObject(entity, false);
        return true;
    }

    return false;
};


/**
 * Insert CAD fonts at the top into the given font combo box.
 */
function initFontComboBox(comboBox) {
    if (RSettings.getBoolValue("Text/UseReducedFontList", false)===true) {
        var list = RSettings.getValue("Text/ReducedFontList", []);
        if (list.length!==0) {
            comboBox.clear();
            comboBox.addItems(list);
        }
    }
    else {
        var fontList = RFontList.getNames();
        for (var i=fontList.length-1; i>=0; --i) {
            // ignore shape definition files:
            if (fontList[i]==="ltypeshp" || fontList[i]==="qcadshp") {
                continue;
            }

            comboBox.insertItem(0, new QIcon(), fontList[i]);
        }
    }

    if (RSettings.getBoolValue("Text/ShowFontPreview", true)===false) {
        // disables the font preview which is known to be slow
        // on some Linux installations:
        var view = comboBox.view();
        view.setItemDelegate(new QItemDelegate(comboBox));
    }
}

function activateFont(fontComboBox, fontName) {
    var index = fontComboBox.findText(fontName, Qt.MatchFixedString);
    fontComboBox.setCurrentIndex(index);
}

function setMainWindow(w) {
    global.gMainWindow = w;
}

function getMainWindow() {
    if (!isNull(global.gMainWindow)) {
        return global.gMainWindow;
    }

    return RMainWindowQt.getMainWindow();
}

function getCurrentDateTime(format) {
    return new QDateTime(QDateTime.currentDateTime()).toString(format);
}

function mergeProperties(obj1,obj2) {
    var obj3 = {};
    var attrname;
    for (attrname in obj1) { obj3[attrname] = obj1[attrname]; }
    for (attrname in obj2) { obj3[attrname] = obj2[attrname]; }
    return obj3;
}

/**
 * Fixes the given symbol table name (e.g. block or layer name).
 *
 * \param name Suggested name, for example coming from a file base name.
 * \return Fixed name or undefined if the name cannot be fixed
 * (i.e. contains invalid characters).
 */
function fixSymbolTableName(name) {
    // trim white space at begining and end to avoid invalid block name:
    name = name.trim();

    // max length:
    if (name.length>255) {
        name = name.left(255);
    }

    // invalid block name characters:
    var rx = new RegExp("^[^<>/\\\\\":;\?\*|,=`]*$");
    if (!rx.test(name)) {
        return undefined;
    }

    return name;
}

function getClipboard() {
    if (RSettings.isQt(5)) {
        return QGuiApplication.clipboard()
    }
    else {
        return QApplication.clipboard();
    }
}


function stripDirtyFlag(title) {
    return title.replace("[*] ", "");
}

function addDirtyFlag(title) {
    return "[*] " + title;
}

function hasPlugin(name) {
    // TODO: refactor:
    if (name==="PROTOOLS") {
        if (new QFileInfo("scripts/Pro").exists()) {
            // PROTOOLS available not as plugins but as scripts folder:
            return true;
        }
    }

    return RPluginLoader.hasPlugin(name);
}

/**
 * Enable / disable easy drag and drop for the given entity.
 * Entities tagged for easy drag and drop can be moved by dragging
 * them while a block reference is selected.
 */
function setInBlockEasyDragAndDrop(entity, v) {
    return entity.setCustomProperty("QCAD", "InBlockEasyDragAndDrop", v ? "1" : "0");
}

function getInBlockEasyDragAndDrop(entity) {
    return entity.getCustomProperty("QCAD", "InBlockEasyDragAndDrop", "0")==="1";
}

/**
 * Enable / disable in block text editing for the given entity.
 */
function setInBlockTextEdit(entity, v) {
    return entity.setCustomProperty("QCAD", "InBlockTextEdit", v ? "1" : "0");
}

function getInBlockTextEdit(entity) {
    return entity.getCustomProperty("QCAD", "InBlockTextEdit", "0")==="1";
}

function setOverrideWaitCursor() {
    if (!RSettings.isGuiEnabled()) {
        return;
    }
    setOverrideCursor(new QCursor(Qt.WaitCursor));
}

function setOverrideCursor(cursor) {
    if (!RSettings.isGuiEnabled()) {
        return;
    }

    if (RSettings.isQt(5)) {
        QGuiApplication.setOverrideCursor(cursor);
    }
    else {
        QApplication.setOverrideCursor(cursor);
    }
}

function restoreOverrideCursor() {
    if (!RSettings.isGuiEnabled()) {
        return;
    }

    if (RSettings.isQt(5)) {
        QGuiApplication.restoreOverrideCursor();
    }
    else {
        QApplication.restoreOverrideCursor();
    }
}

function initUserShortcuts() {
    var keys = RSettings.getAllKeys("Shortcuts");

    var i, key, action;

    for (i=0; i<keys.length; i++) {
        key = keys[i];
        action = RGuiAction.getByScriptFile(key);
        if (isNull(action)) {
            continue;
        }

        var match = action.getScriptFile().contains("OpenFile");

        var scStringList = RSettings.getValue("Shortcuts/" + key);

        if (match) qDebug("scStringList", scStringList);

        // explicitely no shortcuts:
        if (isNull(scStringList)) {
            if (match) qDebug("explicitely no shortcuts");
            action.setShortcuts([]);
            continue;
        }

        if (match) qDebug("setting shortcuts to ", scStringList);

        //action.setShortcutsFromStrings(scStringList);
        //action.setShortcuts(scStringList);

        var scList = [];
        for (var k=0; k<scStringList.length; k++) {
            var sc = new QKeySequence(scStringList[k]);
            scList.push(sc);
        }
        action.setShortcuts(scList);
    }

    keys = RSettings.getAllKeys("Commands");

    for (i=0; i<keys.length; i++) {
        key = keys[i];
        action = RGuiAction.getByScriptFile(key);
        if (isNull(action)) {
            continue;
        }
        var cmStringList = RSettings.getValue("Commands/" + key);

        // explicitely no commands:
        if (isNull(cmStringList)) {
            action.setCommands([]);
            continue;
        }

        action.setCommands(cmStringList);
    }
}

function addActionsToWidgets() {
    initUserShortcuts();

    var appWin = RMainWindowQt.getMainWindow();

    // delete previous shortcut delegates:
    // part of workaround for QTBUG-38256, QTBUG-57990:
    if ((RSettings.getQtVersion()<0x050500 && RSettings.getQtVersion()>=0x050000) ||
        (RSettings.getQtVersion()===0x050800 && RS.getSystemId()==="linux")) {

        var scObjs = appWin.property("DelegatedShortcutsObjs");
        if (!isNull(scObjs)) {
            for (var si=0; si<scObjs.length; si++) {
                if (isNull(scObjs[si])) {
                    continue;
                }
                scObjs[si].destroy();
            }
        }
        appWin.setProperty("DelegatedShortcutsObjs", []);
    }

    var actions = RGuiAction.getActions();
    var widgetTypes = ["Menu", "ToolBar", "MatrixPanel", "Panel"];
    for (var c=0; c<actions.length; ++c) {
        var a = actions[c];
        if (a.icon.isNull() && !a.isIconDisabled()) {
            a.setIcon(autoPath("scripts/Empty.svg"));
        }
        var className = a.getScriptClass();
        var wns = a.getWidgetNames();
        var addedToWidget = false;

        for (var k=0; k<wns.length; k++) {
            var wn = wns[k];
            if (wn.length===0) {
                continue;
            }

            var visibility = true;
            if (wn[0]==="!") {
                visibility = false;
                wn = wn.substring(1);
            }

            // check tool visibility based on user preferences:
            if (className.length!==0) {
                var key;

                for (var j=0; j<widgetTypes.length; j++) {
                    var widgetType = widgetTypes[j];
                    var keyPostfix = widgetType;
                    if (keyPostfix==="Panel") {
                        keyPostfix = "CadToolBar";
                    }

                    if (wn.endsWith(widgetType)) {
                        key = className + "/VisibleIn" + keyPostfix;
                        visibility = RSettings.getBoolValue(key, visibility);
                        RSettings.setValue(key, visibility, false);
                        break;
                    }
                }
            }
            var w = appWin.findChild(wn);
            if (!isNull(w)) {

                // workaround for QTBUG-38256 (action not triggered for letter based shortcuts in SUB menus):
                // workaround for QTBUG-57990 (action not triggered for letter based shortcuts in ALL menus):
                if ((RSettings.getQtVersion()<0x050500 && RSettings.getQtVersion()>=0x050000) ||
                    (RSettings.getQtVersion()===0x050800 && RS.getSystemId()==="linux")) {

                    if (k===0) {
                        var shortcuts = a.shortcuts();

                        var scObjs = appWin.property("DelegatedShortcutsObjs");
                        if (isNull(scObjs)) {
                            scObjs=[];
                        }
                        for (var si=0; si<shortcuts.length; si++) {
                            var scObj = new QShortcut(shortcuts[si], a.parentWidget(), 0, 0, Qt.WindowShortcut)
                            scObj.activated.connect(a, "trigger");
                            scObjs.push(scObj);
                        }
                        appWin.setProperty("DelegatedShortcutsObjs", scObjs);

                        var sc = a.shortcut.toString();
                        if (sc.length>0) {
                            if (RS.getSystemId()==="linux") {
                                a.setShortcutText("[" + sc + "]");
                            }
                            else {
                                a.setShortcutText(" " + sc);
                            }
                        }
                        a.setProperty("DelegatedShortcuts", shortcuts);
                        a.setDefaultShortcuts([]);
                    }
                }

                if (visibility) {
                    RGuiAction.addToWidget(a, w);
                    addedToWidget = true;

                    if (isFunction(w.widgetForAction)) {
                        // if action was added to tool bar: set object name of tool button:
                        var tb = w.widgetForAction(a);
                        if (!isNull(tb)) {
                            tb.objectName = "ToolButton" + a.objectName.replace(/Action$/, "");
                        }
                    }
                }
                else {
                    // action not visible in this widget:
                    RGuiAction.removeFromWidget(a, w);
                }
            }
        }

        if (!addedToWidget) {
            // always add action to main window to make sure keycodes
            // are active even if action is invisible:
            RGuiAction.addToWidget(a, appWin);
        }
    }
}

/**
 * \return Array of QUrl objects with all URLs extracted from
 * the mime data (usually from drag and drop).
 */
function getUrlsFromMimeData(mimeData) {
    var urls = [];

    if (mimeData.hasFormat("text/uri-list")) {
        urls = mimeData.urls();
    }

    else if (mimeData.hasFormat("text/plain")) {
        var text = mimeData.text();
        var url = new QUrl(text);
        if (!url.isValid()) {
            return [];
        }
        if (!isUrl(url)) {
            return [];
        }
        urls = [url];
    }

    return urls;
}

/**
 * \return True if the urlString is a URL that can be loaded.
 */
function isUrl(urlString) {
    var url = new QUrl(urlString);
    var scheme = url.scheme();
    return scheme==="file" || scheme==="http" || scheme==="https" || scheme==="ftp";
}

function getDontUseNativeDialog() {
    // don't use KDE file dialog (workaround for file type filter bug):
    return RS.getWindowManagerId()==="kde" || RSettings.getBoolValue("SaveAs/UseSystemFileDialog", true)===false;
};

function autoPath(path) {
    if (new QFileInfo(path).exists()) {
        return path;
    }
    else {
        return ":" + path;
    }
}

function exists(path) {
    return new QFileInfo(autoPath(path)).exists();
}

function neutralPath(path) {
    if (path.startsWith(":/")) {
        return path.substring(2);
    }
    if (path.startsWith(":")) {
        return path.substring(1);
    }
    return path;
}

/**
 * \return Mapped icon path for the given icon for the current theme or
 * mapped icon path for a dark theme (-inverse) or the same path or undefined if no such
 * icon can be found.
 */
function autoIconPath(path) {
    // set theme specific icon:
    var themePath = RSettings.getThemePath();
    var themeIconFile = undefined;
    if (themePath.length>0) {
        var fi = new QFileInfo(path);
        var iconFileName = fi.fileName();
        themeIconFile = themePath + "/icons/" + iconFileName;
        if (!new QFileInfo(themeIconFile).exists()) {
            // no SVG found, look up PNG:
            var iconBaseName = fi.baseName();
            themeIconFile = themePath + "/icons/" + iconBaseName + ".png";
            if (!new QFileInfo(themeIconFile).exists()) {
                // no PNG found, use default icon:
                themeIconFile = undefined;
            }
        }
    }

    if (!isNull(themeIconFile)) {
        // got icon from theme:
        return themeIconFile;
    }

    // no theme icon, try dark mode icon:
    var darkModeIconFile = undefined;
    if (RSettings.hasDarkGuiBackground()) {
        darkModeIconFile = path.replace(/\.svg$/, "-inverse.svg");
        darkModeIconFile = darkModeIconFile.replace(/\.png$/, "-inverse.png");
        if (!new QFileInfo(darkModeIconFile).exists()) {
            darkModeIconFile = undefined;
        }
    }

    if (!isNull(darkModeIconFile)) {
        // got dark mode icon:
        return darkModeIconFile;
    }

    if (!new QFileInfo(path).exists()) {
        // given icon does not exist (for icons based on object names, e.g. in options toolbar):
        return undefined;
    }

    return path;
}

function applyTheme() {
    var theme = RSettings.getValue("Theme/ThemeName", undefined);
    if (!isNull(theme)) {
        var path = "themes/" + theme + "/";

        qApp.styleSheet = "";

        // load stylesheet.css, stylesheet_[win|macos|linux].css:
        var found = false;
        var systemId = RS.getSystemId();
        if (systemId==="osx") systemId = "macos";

        var postfixes = ["", "_" + systemId];
        for (var i=0; i<postfixes.length; i++) {
            var postfix = postfixes[i];
            var fn = path + "stylesheet" + postfix + ".css";
            qDebug("trying to load theme stylesheet: ", fn);

            if (new QFileInfo(fn).exists()) {
                var css = readTextFile(fn);
                if (css.contains("RequiresPlugin:true")) {
                    // only load theme if plugin loaded:
                    var pluginId = theme.toUpperCase() + "STYLE";
                    if (!RPluginLoader.hasPlugin(pluginId)) {
                        qWarning("Theme not loaded: ", theme);
                        qWarning("Theme plugin not found:", pluginId);
                        return;
                    }
                }

                css = css.replace(/url\(/g, "url(" + path);
                qApp.styleSheet = qApp.styleSheet + "\n" + css;
                found = true;
            }
        }

        if (!found) {
            if (theme!=="Default") {
                qWarning("Cannot open theme: ", theme);
            }
        }
    }
}

function readTextFile(fileName) {
    var file = new QFile(fileName);
    var flags = new QIODevice.OpenMode(QIODevice.ReadOnly | QIODevice.Text);
    if (file.open(flags)) {
        var textStream = new QTextStream(file);
        textStream.setCodec("UTF-8");
        var contents = textStream.readAll();
        file.close();
        return contents;
    }

    return undefined;
}

function writeTextFile(fileName, str) {
    var file = new QFile(fileName);
    var flags = new QIODevice.OpenMode(QIODevice.WriteOnly | QIODevice.Text);
    if (file.open(flags)) {
        var textStream = new QTextStream(file);
        textStream.setCodec("UTF-8");
        textStream.writeString(str);
    }
    file.close();
}

function getKeyboardModifiers(event) {
    if (!isNull(event)) {
        if (isFunction(event.getModifiers)) {
            return event.getModifiers();
        }
        else {
            return event.modifiers();
        }
    }

    if (RSettings.isQt(5)) {
        return QGuiApplication.queryKeyboardModifiers();
    }
    else {
        return QApplication.queryKeyboardModifiers();
    }
}

function isShiftPressed(event) {
    return (getKeyboardModifiers(event) & Qt.ShiftModifier) > 0 ||
           (getKeyboardModifiers() & Qt.ShiftModifier) > 0;
}

function isAltPressed(event) {
    return (getKeyboardModifiers(event) & Qt.AltModifier) > 0 ||
           (getKeyboardModifiers() & Qt.AltModifier) > 0;
}

function isControlPressed(event) {
    return (getKeyboardModifiers(event) & Qt.ControlModifier) > 0 ||
           (getKeyboardModifiers() & Qt.ControlModifier) > 0;
}

function createSpatialIndex() {
    if (!isNull(global.SpatialIndexClass)) {
        // use class defined as global variable "SpatialIndexClass":
        // allows plugins to override the default spatial index class:
        return new global[global.SpatialIndexClass]();
    }
    //return new RSpatialIndexSimple();
    return new RSpatialIndexNavel();
}

// Qt 4 API workaround:
function qsTranslate2(context, sourceText, disambiguation, n) {
    if (RSettings.isQt(4)) {
        if (isNull(disambiguation)) {
            return qsTranslate(context, sourceText);
        }
        if (isNull(n)) {
            return qsTranslate(context, sourceText, disambiguation);
        }
        return qsTranslate(context, sourceText, disambiguation, "UnicodeUTF8", n);
    }
    return qsTranslate(context, sourceText, disambiguation, n);
}

// fix QPlainTextEdit API for Qt 5:
if (!isFunction(QPlainTextEdit.prototype.toPlainText)) {
    QPlainTextEdit.prototype.toPlainText = function() {
        return this.plainText;
    }
}

// add QUrl.isLocalFile to API for Qt 4.7:
if (!isFunction(QUrl.prototype.isLocalFile)) {
    QUrl.prototype.isLocalFile = function() {
        return this.scheme().toLowerCase()==="file";
    }
}
