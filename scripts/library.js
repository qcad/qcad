/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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

include("sprintf.js");

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
    // detect URL:
    var url = new QUrl(file);
    if (url.isValid() && url.scheme().length!==0 && !url.isLocalFile()) {
        return file;
    }

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
//    if (obj!=null && obj.constructor===RLineEntity) {
//        bt();
//    }
//    if (isDeleted(obj)) {
//        return true;
//    }

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
    return (typeof(obj)==="object" && obj.toString().startsWith("RVector"));
}

/**
 * Checks if the given object is a valid vector.
 *
 * \return true if the given object is a valid RVector object.
 */
function isValidVector(obj) {
    return (isVector(obj) && obj.isValid());
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
 * Checks if the given object is a graphics entity.
 *
 * \return true if the given object is an entity (derived from REntity).
 */
function isEntity(obj) {
    return !isNull(obj) &&
        isFunction(obj.getType) && 
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
 * (RDimAngularEntity).
 */
function isDimAngularEntity(obj) {
    return isOfType(obj, RDimAngularEntity) || isOfType(obj, RDimAngularEntityPointer);
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
 * Checks if the given object is a polyline entity.
 *
 * \return true if the given object is a spline entity (RPolylineEntity).
 */
function isPolylineEntity(obj) {
    return isOfType(obj, RPolylineEntity) || isOfType(obj, RPolylineEntityPointer);
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
 * \return true if the given object is a directed shape (derived from RShape and RDirected).
 */
function isDirectedShape(obj) {
    return isShape(obj) &&
            isFunction(obj.getStartPoint) &&
            isFunction(obj.getEndPoint) &&
            isFunction(obj.reverse);
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
 * Checks if the given object is a spline shape.
 *
 * \return true if the given object is a spline shape (RSpline).
 */
function isSplineShape(obj) {
    return isOfType(obj, RSpline) || isOfType(obj, RSplinePointer);
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
    case RS.EntityAll:
        return plural ? qsTr("Entity") : qsTr("Entities");
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

function getEntityTypeProperties(type) {
    switch (type) {
    case RS.EntityAll:
        return REntity.getStaticPropertyTypeIds();
    case RS.EntityBlockReferenceEntity:
        return RBlockReferenceEntity.getStaticPropertyTypeIds();
    case RS.EntityArc:
        return RArcEntity.getStaticPropertyTypeIds();
    case RS.EntityAttribute:
        return RAttributeEntity.getStaticPropertyTypeIds();
    case RS.EntityAttributeDefinition:
        return RAttributeDefinitionEntity.getStaticPropertyTypeIds();
    case RS.EntityCircle:
        return RCircleEntity.getStaticPropertyTypeIds();
    case RS.EntityDimension:
        return RDimensionEntity.getStaticPropertyTypeIds();
    case RS.EntityDimAligned:
        return RDimAlignedEntity.getStaticPropertyTypeIds();
    case RS.EntityDimAngular:
        return RDimAngularEntity.getStaticPropertyTypeIds();
    case RS.EntityDimDiametric:
        return RDimDiametricEntity.getStaticPropertyTypeIds();
    case RS.EntityDimOrdinate:
        return RDimOrdinateEntity.getStaticPropertyTypeIds();
    case RS.EntityDimRotated:
        return RDimRotatedEntity.getStaticPropertyTypeIds();
    case RS.EntityDimRadial:
        return RDimRadialEntity.getStaticPropertyTypeIds();
    case RS.EntityEllipse:
        return REllipseEntity.getStaticPropertyTypeIds();
    case RS.EntityHatch:
        return RHatchEntity.getStaticPropertyTypeIds();
    case RS.EntityImage:
        return RImageEntity.getStaticPropertyTypeIds();
    case RS.EntityLeader:
        return RLeaderEntity.getStaticPropertyTypeIds();
    case RS.EntityLine:
        return RLineEntity.getStaticPropertyTypeIds();
    case RS.EntityPoint:
        return RPointEntity.getStaticPropertyTypeIds();
    case RS.EntityPolyline:
        return RPolylineEntity.getStaticPropertyTypeIds();
    case RS.EntitySolid:
        return RSolidEntity.getStaticPropertyTypeIds();
    case RS.EntityTrace:
        return RTraceEntity.getStaticPropertyTypeIds();
    case RS.EntityViewport:
        return RViewportEntity.getStaticPropertyTypeIds();
    case RS.EntityRay:
        return RRayEntity.getStaticPropertyTypeIds();
    case RS.EntityXLine:
        return RXLineEntity.getStaticPropertyTypeIds();
    case RS.EntitySpline:
        return RSplineEntity.getStaticPropertyTypeIds();
    case RS.EntityTextBased:
        return RTextBasedEntity.getStaticPropertyTypeIds();
    case RS.EntityText:
        return RTextEntity.getStaticPropertyTypeIds();
    case RS.EntityUnknown:
    default:
        return [];
    }
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
 * \return Array of child widgets.
 */
function getWidgets(widget, ca) {
    if (isNull(widget) || isDeleted(widget)) {
        return undefined;
    }

    if (isNull(ca)) {
        ca = new Object();
    }
    var children = widget.children();
    for (var i = 0; i < children.length; ++i) {
        var child = children[i];
        if (isDeleted(child)) {
            continue;
        }
        if (!isNull(child.objectName) && child.objectName !== "") {
            ca[child.objectName] = child;
        }
        if (!isNull(child.children) && child.children().length !== 0) {
            getWidgets(child, ca);
        }
    }

    return ca;
}

/**
 * Sleeps for the given milliseconds.
 * \param msec the time to sleep
 */
function sleep(msec) {
    var date = new Date();
    var curDate = null;
    var c = 0;
    do {
        curDate = new Date();
        ++c;
    } while (curDate - date < msec);
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

/**
 * \return A new array which contains every unique item of this array only once.
 */
Array.prototype.unique = function() {
    var a = [], i, l = this.length;
    for (i = 0; i < l; i++) {
        if (a.indexOf(this[i], 0) < 0) {
            a.push(this[i]);
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
 * Remove the given value from the array.
 * \param val The value to remove.
 */
Array.prototype.remove = function(val) {
    for (var i=0; i<this.length; i++) {
        if (this[i] == val) {
            this.splice(i, 1);
            break;
        }
    }
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

/**
 * Destructively finds the intersection of
 * two arrays.
 *
 * \param a first array, must already be sorted
 * \param b second array, must already be sorted
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
}

/**
 * Escapes a string for use as literlal match in regular expression.
 */
RegExp.escape = function(s) {
    return s.replace(/[\-\[\]{}()*+?.,\\\^$|#\s]/g, "\\$&");
}

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

/**
 * Formats the given coordinate (RVector) into a locale aware string.
 */
function coordinateToString(coordinate, decimals, relative, polar) {
    var first;
    var second;
    var sep;
    if (polar) {
        sep = RSettings.getStringValue("Input/PolarCoordinateSeparator", "<");
        first = coordinate.getMagnitude();
        second = coordinate.getAngle() / (2 * Math.PI) * 360;
    }
    else {
        sep = RSettings.getStringValue("Input/CartesianCoordinateSeparator", ",");
        first = coordinate.x;
        second = coordinate.y;
    }

    var prefix;
    if (relative) {
        prefix = RSettings.getStringValue(
                    "Input/RelativeCoordinatePrefix",
                    String.fromCharCode(64)  // @ (doxygen can't cope with an @ here)
        );
    }
    else {
        prefix = "";
    }

    return prefix +
            numberToString(first, decimals) +
            sep +
            numberToString(second, decimals);
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
    var decimalPoint =
        RSettings.getStringValue("Input/DecimalPoint", ".");
    var cartCoordSep =
        RSettings.getStringValue("Input/CartesianCoordinateSeparator", ",");
    var polCoordSep =
        RSettings.getStringValue("Input/PolarCoordinateSeparator", "<");
    var relCoordPre =
        RSettings.getStringValue(
            "Input/RelativeCoordinatePrefix",
            String.fromCharCode(64) // @ (doxygen can't cope with an @ here)
        );

    if (str.count(cartCoordSep)!==1 && str.count(polCoordSep)!==1) {
        // not a coordinate (not an error):
        return undefined;
    }

    var relative = false;
    if (str[0]===relCoordPre) {
        relative = true;
        str = str.substring(1);
    }

    var sl;
    var polar = false;
    if (str.count(cartCoordSep)===1) {
        sl = str.split(cartCoordSep);
        polar = false;
    }
    else {
        sl = str.split(polCoordSep);
        polar = true;
    }

    if (sl.length!==2) {
        // invalid coordinate:
        return RVector.invalid;
    }

    // 'fix' decimal point:
    if (decimalPoint!=='.') {
        sl[0] = sl[0].replace(decimalPoint, '.');
        sl[1] = sl[1].replace(decimalPoint, '.');
    }

    // evaluate x/y or radius/angle pair:
    var a0 = RMath.eval(sl[0]);
    var a1 = RMath.eval(sl[1]);

    if (isNaN(a0) || isNaN(a1)) {
        // invalid coordinate:
        return RVector.invalid;
    }

    var pos;
    if (polar) {
        // polar coordinate:
        pos = RVector.createPolar(a0,RMath.deg2rad(a1));
    }
    else {
        // Cartesian coordinate:
        pos = new RVector(a0,a1);
    }

    // relative coordinate:
    if (relative) {
        pos = relativeZero.operator_add(pos);
    }

    return pos;
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
    if (isPointShape(shape)) {
        return new RPointEntity(document, new RPointData(shape.getPosition()));
    }
    else if (isLineShape(shape)) {
        return new RLineEntity(document, new RLineData(shape));
    }
    else if (isRayShape(shape)) {
        return new RRayEntity(document, new RRayData(shape));
    }
    else if (isXLineShape(shape)) {
        return new RXLineEntity(document, new RXLineData(shape));
    }
    else if (isArcShape(shape)) {
        return new RArcEntity(document, new RArcData(shape));
    }
    else if (isCircleShape(shape)) {
        return new RCircleEntity(document, new RCircleData(shape));
    }
    else if (isEllipseShape(shape)) {
        return new REllipseEntity(document, new REllipseData(shape));
    }
    else if (isPolylineShape(shape)) {
        return new RPolylineEntity(document, new RPolylineData(shape));
    }
    else if (isSplineShape(shape)) {
        return new RSplineEntity(document, new RSplineData(shape));
    }
    else if (isTriangleShape(shape)) {
        return new RSolidEntity(document, new RSolidData(shape));
    }

    qWarning("shapeToEntity: unknown shape: ", shape);
    return undefined;
}

function getClosestSimpleShape(entity, pos) {
    return entity.getClosestSimpleShape(pos);
}

function trimStartPoint(shape, p) {
    shape.trimStartPoint(p);
    if (isXLineShape(shape)) {
        return xLineToRay(shape);
    }
    else {
        return shape;
    }
}

function trimEndPoint(shape, p) {
    shape.trimEndPoint(p);
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
 */
function modifyEntity(op, entity, shape) {
    if ((isXLineEntity(entity) && (isRayShape(shape) || isLineShape(shape))) ||
        (isRayEntity(entity) && (isXLineShape(shape) || isLineShape(shape))) ||
        (isLineEntity(entity) && (isXLineShape(shape) || isRayShape(shape)))) {

        var e = shapeToEntity(entity.getDocument(), shape);
        e.copyAttributesFrom(entity);
        op.deleteObject(entity);
        op.addObject(e, false);
        return;
    }

    entity.setShape(shape);

    op.addObject(entity, false);
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
    if (RSettings.isQt(5)) {
        QGuiApplication.restoreOverrideCursor();
    }
    else {
        QApplication.restoreOverrideCursor();
    }
}

function addActionsToWidgets() {
    var actions = RGuiAction.getActions();
    var widgetTypes = ["Menu", "ToolBar", "Panel"];
    for (var c=0; c<actions.length; ++c) {
        var a = actions[c];
        if (a.icon.isNull() && !a.isIconDisabled()) {
            a.setIcon("scripts/Empty.svg");
        }
        var className = a.getScriptClass();
        var wns = a.getWidgetNames();

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
                    }
                }
            }
            var w = RMainWindowQt.getMainWindow().findChild(wn);
            if (!isNull(w)) {

                // workaround for QTBUG-38256 (action not triggered for letter based shortcuts in sub menus)
                if (RSettings.isQt(5)) {
                    if (isOfType(w.parentWidget(), QMenu)) {
                        new QShortcut(a.shortcut, a.parentWidget(), 0, 0,  Qt.WindowShortcut).activated.connect(a, "trigger");

                        // avoid 'Ambiguous shortcut overload' when tool buttons visible:
                        var sc = a.shortcut.toString();
                        if (sc.length>0) {
                            a.setShortcutText(" (" + sc + ")");
                        }
                        a.setDefaultShortcuts([]);
                    }
                }

                if (visibility) {
                    RGuiAction.addToWidget(a, w);
                }
                else {
                    // action not visible in this widget:
                    RGuiAction.removeFromWidget(a, w);
                }
            }
            else {
                qWarning("RGuiAction::init: Cannot add action to widget: ", wn);
            }
        }
    }
}

// fix QPlainTextEdit API for Qt 5:
if (!isFunction(QPlainTextEdit.prototype.toPlainText)) {
    QPlainTextEdit.prototype.toPlainText = function() {
        return this.plainText;
    }
}
