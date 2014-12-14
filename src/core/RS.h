/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

#ifndef RS_H
#define RS_H

#include "core_global.h"

#include <QPair>
#include <QString>
#include <QStringList>
#include <QVariant>

class RVector;
class RPropertyAttributes;

/**
 * Some useful macros for OS detection.
 */
#if defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
#  define ROS_WINDOWS
#  define ROS_WIN32
#  define ROS_WIN64
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define ROS_WINDOWS
#  define ROS_WIN32
#else
#  define ROS_POSIX
#endif

/**
 * Class namespace for various global enums.
 *
 * Most enums fit in a class, but some are truly global, others
 * cannot be declared in a class because this would result in
 * problems with include files that depend on each other (note that
 * there is no way to forward-declare nested classes or enums).
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RS {
public:

    /**
     * Message type for debugging and displaying user messages.
     */
    enum MessageType {
       Print,
       Debug,
       Warning,
       Critical,
       Command
    };

    /**
     * Entity types used for property handling / filtering.
     */
    enum EntityType {
        EntityAll,          /**< All entities (for filters) */
        EntityUnknown,      /**< Unknown */
        EntityAttribute,    /**< Block attribute */
        EntityAttributeDefinition,     /**< Block attribute definition */
        EntityBlockRef,     /**< Block reference */
        EntityBlockRefAttr, /**< Block reference with attributes */
        EntityPoint,        /**< Point */
        EntityLine,         /**< Line */
        EntityXLine,        /**< XLine */
        EntityRay,          /**< Ray */
        EntityPolyline,     /**< Polyline */
        EntityArc,          /**< Arc */
        EntityCircle,       /**< Circle */
        EntityEllipse,      /**< Ellipse */
        EntitySolid,        /**< Solid */
        Entity3dFace,       /**< 3d Face */
        EntityTextBased,    /**< Any text based entity (text, attribute def, attribute) */
        EntityText,         /**< Text */
        EntityTrace,        /**< Trace */
        EntityDimension,    /**< Any Dimension */
        EntityDimLinear,    /**< Any linear dimension */
        EntityDimAligned,   /**< Linear aligned Dimension */
        EntityDimRotated,   /**< Linear rotated Dimension */
        EntityDimRadial,    /**< Radial Dimension */
        EntityDimDiametric, /**< Diametric Dimension */
        EntityDimAngular,   /**< Angular Dimension */
        EntityDimOrdinate,  /**< Ordinate Dimension */
        EntityHatch,        /**< Hatch */
        EntityImage,        /**< Image */
        EntityLeader,       /**< Leader */
        EntitySpline,       /**< Spline */
        EntityViewport,     /**< Viewport */
        EntityUser          /**< User defined entity. Use this to identify
                                 entities that are added in a separate library
                                 and resort to C++ RTTI for RTTI. */
    };

    /**
     * Sets the current rendering hint for exports.
     *
     * \see RExporter::setProjectionRenderingHint
     */
    enum ProjectionRenderingHint {
        RenderTop,
        RenderSide,
        RenderFront,
        RenderThreeD
    };

    /**
     * Side used for side of a point relativ to an entity
     * (right hand or left hand side)
     */
    enum Side {
        RightHand, LeftHand, NoSide, BothSides
    };

    /**
     * Entity ending. Used for returning which end of an entity is ment.
     */
    enum Ending {
        EndingStart,    /**< Start point. */
        EndingEnd,      /**< End point. */
        EndingNone      /**< Neither. */
    };

    /**
     * Vertical alignments.
     */
    enum VAlign {
        VAlignTop,      /**< Top. */
        VAlignMiddle,   /**< Middle */
        VAlignBase,     /**< Base line */
        VAlignBottom    /**< Bottom */
    };

    /**
     * Horizontal alignments.
     */
    enum HAlign {
        HAlignLeft,      /**< Left */
        HAlignCenter,    /**< Centered */
        HAlignRight,     /**< Right */
        HAlignAlign,     /**< Aligned */
        HAlignMid,       /**< Middle (?) */
        HAlignFit        /**< Fit */
    };

    /**
     * Text drawing direction.
     */
    enum TextDrawingDirection {
        LeftToRight = 1,     /**< Left to right */
        TopToBottom = 3,     /**< Top to bottom */
        ByStyle = 5          /**< Inherited from associated text style */
    };

    /**
     * Line spacing style for texts.
     */
    enum TextLineSpacingStyle {
        AtLeast = 1,        /**< Taller characters will override */
        Exact = 2           /**< Taller characters will not override */
    };

    /**
     * End used to specify from which end of a shape to measure a distance.
     */
    enum From {
        FromStart = 0x1,
        FromEnd = 0x2,
        FromAny = 0x3,         /**< Start or end **/
        AlongPolyline = 0x4
    };

    /**
     * Projection type for isometric projections.
     */
    enum IsoProjectionType {
        IsoTop,        //!< Top projection (x/y)
        IsoBottom,     //!< Bottom projection (x/y)
        IsoLeft,       //!< Front left projection (x/z)
        IsoLeftBack,   //!< Back left projection (x/z)
        IsoRight,      //!< Front right projection (y/z)
        IsoRightBack   //!< Back right projection (y/z)
    };

    /**
     * Enum of supported units (values correspond to DXF spec).
     */
    enum Unit {
        None = 0,         /**< No unit (unit from parent) */
        Inch = 1,         /**< Inch */
        Foot = 2,         /**< Foot: 12 Inches */
        Mile = 3,         /**< Mile: 1760 Yards = 1609 m */
        Millimeter = 4,   /**< Millimeter: 0.001m */
        Centimeter = 5,   /**< Centimeter: 0.01m */
        Meter = 6,        /**< Meter */
        Kilometer = 7,    /**< Kilometer: 1000m */
        Microinch = 8,    /**< Microinch: 0.000001 */
        Mil = 9,          /**< Mil = 0.001 Inch*/
        Yard = 10,        /**< Yard: 3 Feet */
        Angstrom = 11,    /**< Angstrom: 10^-10m  */
        Nanometer = 12,   /**< Nanometer: 10^-9m  */
        Micron = 13,      /**< Micron: 10^-6m  */
        Decimeter = 14,   /**< Decimeter: 0.1m */
        Decameter = 15,   /**< Decameter: 10m */
        Hectometer = 16,  /**< Hectometer: 100m */
        Gigameter = 17,   /**< Gigameter: 1000000m */
        Astro = 18,       /**< Astro: 149.6 x 10^9m */
        Lightyear = 19,   /**< Lightyear: 9460731798 x 10^6m */
        Parsec = 20,      /**< Parsec: 30857 x 10^12 */
        //Plu = 21          /**< PLU: Plotter units used in HP/GL. 40plu = 1mm. not supported by open design*/
        MaxUnit = Parsec
    };

    /**
     * Angle format for printing angles.
     */
    enum AngleFormat {
        /** Degrees with decimal point (e.g. 24.5<degree symbol>) */
        DegreesDecimal = 0,
        /** Degrees, Minutes and Seconds (e.g. 24<degree symbol>30'5'') */
        DegreesMinutesSeconds = 1,
        /** Gradians with decimal point (e.g. 390.5)*/
        Gradians = 2,
        /** Radians with decimal point (e.g. 1.57)*/
        Radians = 3,
        /** Surveyor's units */
        Surveyors = 4
    };

    /**
     * Format for length values.
     */
    enum LinearFormat {
        /** Scientific (e.g. 2.5E+05) */
        Scientific = 1,
        /** Decimal (e.g. 9.5)*/
        Decimal = 2,
        /** Engineering (e.g. 7' 11.5")*/
        Engineering = 3,
        /** Architectural stacked (e.g. 7'-9 1/8")*/
        ArchitecturalStacked = 4,
        /** Fractional stacked (e.g. 7 9 1/8) */
        FractionalStacked = 5,
        /** Architectural (e.g. ?)*/
        Architectural = 6,
        /** Fractional (e.g. ?)*/
        Fractional = 7,
        /** Not supported */
        WindowsDesktop = 8
    };

    /**
     * Angle Units.
     */
    enum AngleUnit {
        Deg,               /**< Degrees */
        Rad,               /**< Radians */
        Gra                /**< Gradians */
    };

    /**
     * Well established document variables.
     */
    enum KnownVariable {
        ANGBASE,
        ANGDIR,
        ATTMODE,
        AUNITS,
        AUPREC,
        CECOLOR,
        CELTSCALE,
        CHAMFERA,
        CHAMFERB,
        CHAMFERC,
        CHAMFERD,
        CMLJUST,
        CMLSCALE,
        /** Decimal places in angular dimensions */
        DIMADEC,
        DIMALT,
        DIMALTD,
        DIMALTF,
        DIMALTRND,
        DIMALTTD,
        DIMALTTZ,
        DIMALTU,
        DIMALTZ,
        DIMAPOST,
        DIMASZ,
        DIMATFIT,
        /** Formatting of angular dimensions */
        DIMAUNIT,
        /** Controls display of leading / trailing zeros for angular dimensions */
        DIMAZIN,
        DIMBLK,
        DIMBLK1,
        DIMBLK2,
        DIMCEN,
        DIMCLRD,
        DIMCLRE,
        DIMCLRT,
        /** Decimal places in linear dimensions */
        DIMDEC,
        DIMDLE,
        DIMDLI,
        DIMDSEP,
        DIMEXE,
        DIMEXO,
        DIMFRAC,
        /** Distance between dimension text and dimension lines, negative for box */
        DIMGAP,
        /** Vertical position of dimension label */
        DIMJUST,
        DIMLDRBLK,
        DIMLFAC,
        DIMLIM,
        /** Formatting of linear dimensions */
        DIMLUNIT,
        DIMLWD,
        DIMLWE,
        DIMPOST,
        DIMRND,
        DIMSAH,
        DIMSCALE,
        DIMSD1,
        DIMSD2,
        DIMSE1,
        DIMSE2,
        DIMSOXD,
        /** Vertical position of dimension label */
        DIMTAD,
        DIMTDEC,
        DIMTFAC,
        DIMTIH,
        DIMTIX,
        DIMTM,
        DIMTOFL,
        DIMTOH,
        DIMTOL,
        DIMTOLJ,
        DIMTP,
        /** Archtick size or 0 for arrows */
        DIMTSZ,
        DIMTVP,
        DIMTXSTY,
        /** Dimension text size */
        DIMTXT,
        DIMTZIN,
        DIMUPT,
        /** Controls display of leading / trailing zeros for linear dimensions */
        DIMZIN,
        DISPSILH,
        DWGCODEPAGE,
        DRAWORDERCTL,
        ELEVATION,
        EXTMAX,
        EXTMIN,
        FACETRES,
        FILLETRAD,
        FILLMODE,
        INSBASE,
        INSUNITS,
        ISOLINES,
        LIMCHECK,
        LIMMAX,
        LIMMIN,
        LTSCALE,
        LUNITS,
        LUPREC,
        MAXACTVP,
        MIRRTEXT,
        ORTHOMODE,
        /* Point display mode */
        PDMODE,
        /* Point display size */
        PDSIZE,
        PELEVATION,
        PELLIPSE,
        PEXTMAX,
        PEXTMIN,
        PINSBASE,
        PLIMCHECK,
        PLIMMAX,
        PLIMMIN,
        PLINEGEN,
        PLINEWID,
        PROXYGRAPHICS,
        PSLTSCALE,
        PUCSNAME,
        PUCSORG,
        PUCSXDIR,
        PUCSYDIR,
        QTEXTMODE,
        REGENMODE,
        SHADEDGE,
        SHADEDIF,
        SKETCHINC,
        SKPOLY,
        SPLFRAME,
        SPLINESEGS,
        SPLINETYPE,
        SURFTAB1,
        SURFTAB2,
        SURFTYPE,
        SURFU,
        SURFV,
        TEXTQLTY,
        TEXTSIZE,
        TEXTSTYLE,
        THICKNESS,
        TILEMODE,
        TRACEWID,
        TREEDEPTH,
        UCSNAME,
        UCSORG,
        UCSXDIR,
        UCSYDIR,
        UNITMODE,
        USERI1,
        USERI2,
        USERI3,
        USERI4,
        USERI5,
        USERR1,
        USERR2,
        USERR3,
        USERR4,
        USERR5,
        USRTIMER,
        VISRETAIN,
        WORLDVIEW,
        MaxKnownVariable = WORLDVIEW,
        INVALID = -1
    };

    enum BooleanOperation {
        Intersection,
        Union,
        Difference,
        Xor
    };

    enum FillType {
        EvenOdd,
        NonZero,
        Positive,
        Negative
    };

    enum Orientation {
        Any,
        CW,
        CCW
    };

public:
    static bool compare(const QVariant& v1, const QVariant& v2);
    static bool compare(const QPair<QVariant, RPropertyAttributes>& p1,
                        const QPair<QVariant, RPropertyAttributes>& p2);
    static int getCpuCores();

    static QString getHostId();
    static QString getSystemId();
    static QString getWindowManagerId();

    static QStringList getDirectoryList(const QString& subDirectory);
    static QStringList getFileList(const QString& subDirectory,
                                   const QString& fileExtension);
    static QStringList getFontList();
    static QStringList getPatternList(bool metric);
    static QStringList getLinetypeList(bool metric);

    template<class T>
    static bool mapContainsCaseInsensitive(const QMap<QString, T>& map, const QString& key) {
        return QStringList(map.keys()).contains(key, Qt::CaseInsensitive);
    }

    template<class T>
    static T mapValueCaseInsensitive(const QMap<QString, T>& map, const QString& key) {
        QMapIterator<QString, T> it(map);
        while (it.hasNext()) {
            it.next();
            if (QString::compare(it.key(), key, Qt::CaseInsensitive)==0) {
                return it.value();
            }
        }

        return T();
    }

    static const double PointTolerance;
    static const double AngleTolerance;
};

Q_DECLARE_METATYPE(RS*)
Q_DECLARE_METATYPE(RS::AngleFormat)
Q_DECLARE_METATYPE(RS::AngleFormat*)
Q_DECLARE_METATYPE(RS::AngleUnit)
Q_DECLARE_METATYPE(RS::EntityType)
Q_DECLARE_METATYPE(RS::EntityType*)
Q_DECLARE_METATYPE(RS::From)
Q_DECLARE_METATYPE(RS::From*)
Q_DECLARE_METATYPE(RS::HAlign)
Q_DECLARE_METATYPE(RS::HAlign*)
Q_DECLARE_METATYPE(RS::IsoProjectionType)
Q_DECLARE_METATYPE(RS::IsoProjectionType*)
Q_DECLARE_METATYPE(RS::KnownVariable)
Q_DECLARE_METATYPE(RS::KnownVariable*)
Q_DECLARE_METATYPE(RS::LinearFormat)
Q_DECLARE_METATYPE(RS::LinearFormat*)
Q_DECLARE_METATYPE(RS::MessageType)
Q_DECLARE_METATYPE(RS::ProjectionRenderingHint)
Q_DECLARE_METATYPE(RS::Side)
Q_DECLARE_METATYPE(RS::Ending)
Q_DECLARE_METATYPE(RS::TextDrawingDirection)
Q_DECLARE_METATYPE(RS::TextDrawingDirection*)
Q_DECLARE_METATYPE(RS::TextLineSpacingStyle)
Q_DECLARE_METATYPE(RS::TextLineSpacingStyle*)
Q_DECLARE_METATYPE(RS::Unit)
Q_DECLARE_METATYPE(RS::VAlign)
Q_DECLARE_METATYPE(RS::VAlign*)
Q_DECLARE_METATYPE(RS::BooleanOperation)
Q_DECLARE_METATYPE(RS::FillType)
Q_DECLARE_METATYPE(RS::Orientation)
Q_DECLARE_METATYPE(QList<RS::EntityType>)

#endif
