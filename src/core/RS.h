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

#ifndef RS_H
#define RS_H

#include "core_global.h"

#include <QEasingCurve>
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

#define REASING_LINEAR QEasingCurve::Linear
#define REASING_INQUAD QEasingCurve::InQuad
#define REASING_OUTQUAD QEasingCurve::OutQuad
#define REASING_INOUTQUAD QEasingCurve::InOutQuad
#define REASING_OUTINQUAD QEasingCurve::OutInQuad
#define REASING_INCUBIC QEasingCurve::InCubic
#define REASING_OUTCUBIC QEasingCurve::OutCubic
#define REASING_INOUTCUBIC QEasingCurve::InOutCubic
#define REASING_OUTINCUBIC QEasingCurve::OutInCubic
#define REASING_INQUART QEasingCurve::InQuart
#define REASING_OUTQUART QEasingCurve::OutQuart
#define REASING_INOUTQUART QEasingCurve::InOutQuart
#define REASING_OUTINQUART QEasingCurve::OutInQuart
#define REASING_INQUINT QEasingCurve::InQuint
#define REASING_OUTQUINT QEasingCurve::OutQuint
#define REASING_INOUTQUINT QEasingCurve::InOutQuint
#define REASING_OUTINQUINT QEasingCurve::OutInQuint
#define REASING_INSINE QEasingCurve::InSine
#define REASING_OUTSINE QEasingCurve::OutSine
#define REASING_INOUTSINE QEasingCurve::InOutSine
#define REASING_OUTINSINE QEasingCurve::OutInSine
#define REASING_INEXPO QEasingCurve::InExpo
#define REASING_OUTEXPO QEasingCurve::OutExpo
#define REASING_INOUTEXPO QEasingCurve::InOutExpo
#define REASING_OUTINEXPO QEasingCurve::OutInExpo
#define REASING_INCIRC QEasingCurve::InCirc
#define REASING_OUTCIRC QEasingCurve::OutCirc
#define REASING_INOUTCIRC QEasingCurve::InOutCirc
#define REASING_OUTINCIRC QEasingCurve::OutInCirc
#define REASING_INELASTIC QEasingCurve::InElastic
#define REASING_OUTELASTIC QEasingCurve::OutElastic
#define REASING_INOUTELASTIC QEasingCurve::InOutElastic
#define REASING_OUTINELASTIC QEasingCurve::OutInElastic
#define REASING_INBACK QEasingCurve::InBack
#define REASING_OUTBACK QEasingCurve::OutBack
#define REASING_INOUTBACK QEasingCurve::InOutBack
#define REASING_OUTINBACK QEasingCurve::OutInBack
#define REASING_INBOUNCE QEasingCurve::InBounce
#define REASING_OUTBOUNCE QEasingCurve::OutBounce
#define REASING_INOUTBOUNCE QEasingCurve::InOutBounce
#define REASING_OUTINBOUNCE QEasingCurve::OutInBounce
//#define REASING_INCURVE QEasingCurve::InCurve
//#define REASING_OUTCURVE QEasingCurve::OutCurve
//#define REASING_SINECURVE QEasingCurve::SineCurve
//#define REASING_COSINECURVE QEasingCurve::CosineCurve
//#define REASING_BEZIERSPLINE QEasingCurve::BezierSpline
//#define REASING_TCBSPLINE QEasingCurve::TCBSpline

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
     * \todo QCAD 4: rename to objectType
     */
    enum EntityType {
        ObjectAll,
        ObjectUnknown,      /**< Unknown object */

        ObjectBlock,
        ObjectLayer,
        ObjectLayerState,
        ObjectLinetype,
        ObjectView,
        ObjectLayout,
        ObjectUcs,
        ObjectDocumentVariable,

        EntityAll,          /**< All entities (for filters) */
        EntityUnknown,      /**< Unknown entity */
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
        EntityFace,         /**< Face */
        EntityDimension,    /**< Any Dimension */
        EntityDimLinear,    /**< Any linear dimension */
        EntityDimAligned,   /**< Linear aligned Dimension */
        EntityDimRotated,   /**< Linear rotated Dimension */
        EntityDimRadial,    /**< Radial Dimension */
        EntityDimDiametric, /**< Diametric Dimension */
        EntityDimAngular,   /**< Angular Dimension */
        EntityDimAngular2L, /**< Angular Dimension from 2 lines */
        EntityDimAngular3P, /**< Angular Dimension from 3 points */
        EntityDimArcLength, /**< Arc Length Dimension */
        EntityDimOrdinate,  /**< Ordinate Dimension */
        EntityHatch,        /**< Hatch */
        EntityImage,        /**< Image */
        EntityLeader,       /**< Leader */
        EntitySpline,       /**< Spline */
        EntityViewport,     /**< Viewport */
        EntityTolerance,    /**< Tolerance */
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
     * Orthogonal mode, used for snap restrictions.
     */
    enum OrthoMode {
        OrthoVertical,
        OrthoHorizonal,
        Orthogonal
    };

    /**
     * Side used for side of a point relativ to an entity
     * (right hand or left hand side)
     */
    enum Side {
        NoSide = 0,
        LeftHand = 1,
        RightHand = 2,
        BothSides = 3
    };

    /**
     * Entity ending. Used for returning which end of an entity is meant.
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
        FromAny = FromStart|FromEnd,         /**< Start or end **/
        AlongPolyline = 0x4
    };

    /**
     * Projection type for isometric projections.
     */
    enum IsoProjectionType {
        NoProjection =  0x00000000,      //!< No projection (2d x/y)
        Top =           0x00000001,      //!< Top projection (x/y)
        Bottom =        0x00000002,      //!< Bottom projection (x/y)
        Left =          0x00000004,      //!< Front left projection (x/z)
        LeftBack =      0x00000008,      //!< Back left projection (x/z)
        Right =         0x00000010,      //!< Front right projection (y/z)
        RightBack =     0x00000020,      //!< Back right projection (y/z)

        Isometric =     0x00010000,      //!< Isometric
        IsometricTrue = 0x00020000,      //!< Isometric
        Planometric =   0x00040000,      //!< Planometric
        Dimetric =      0x00080000,      //!< Dimetric

        Cabinet =       0x00100000,      //!< Cabinet
        Cabinet30 =     0x00200000,      //!< Cabinet30
        Cavalier =      0x00400000,      //!< Cavalier

        User1 =         0x01000000,      //!< User defined 1
        User2 =         0x02000000,      //!< User defined 2
        User3 =         0x04000000,      //!< User defined 3
        User4 =         0x08000000,      //!< User defined 4

        // backwards compatibility:
        IsoTop = Top | Isometric,
        IsoBottom = Bottom | Isometric,
        IsoLeft = Left | Isometric,
        IsoLeftBack = LeftBack | Isometric,
        IsoRight = Right | Isometric,
        IsoRightBack = RightBack | Isometric
    };

    /**
     * Enum of supported measurement systems.
     */
    enum Measurement {
        UnknownMeasurement = -1,
        Imperial = 0,         /**< Imperial */
        Metric = 1,            /**< Metric */
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
        CLAYER,
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
        /** Decimal separator in dimensions */
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
        MEASUREMENT,
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
        UnknownOrientation = -1,
        Any = 0,
        CW = 1,
        CCW = 2
    };

    enum JoinType {
        JoinBevel,
        JoinRound,
        JoinMiter
    };

    enum EndType {
        EndClosedPolygon,
        EndClosedLine,
        EndOpenButt,
        EndOpenSquare,
        EndOpenRound,
        EndOpenSingle
    };

    enum Easing {
        Linear = REASING_LINEAR,
        InQuad = REASING_INQUAD,
        OutQuad = REASING_OUTQUAD,
        InOutQuad = REASING_INOUTQUAD,
        OutInQuad = REASING_OUTINQUAD,
        InCubic = REASING_INCUBIC,
        OutCubic = REASING_OUTCUBIC,
        InOutCubic = REASING_INOUTCUBIC,
        OutInCubic = REASING_OUTINCUBIC,
        InQuart = REASING_INQUART,
        OutQuart = REASING_OUTQUART,
        InOutQuart = REASING_INOUTQUART,
        OutInQuart = REASING_OUTINQUART,
        InQuint = REASING_INQUINT,
        OutQuint = REASING_OUTQUINT,
        InOutQuint = REASING_INOUTQUINT,
        OutInQuint = REASING_OUTINQUINT,
        InSine = REASING_INSINE,
        OutSine = REASING_OUTSINE,
        InOutSine = REASING_INOUTSINE,
        OutInSine = REASING_OUTINSINE,
        InExpo = REASING_INEXPO,
        OutExpo = REASING_OUTEXPO,
        InOutExpo = REASING_INOUTEXPO,
        OutInExpo = REASING_OUTINEXPO,
        InCirc = REASING_INCIRC,
        OutCirc = REASING_OUTCIRC,
        InOutCirc = REASING_INOUTCIRC,
        OutInCirc = REASING_OUTINCIRC,
        InElastic = REASING_INELASTIC,
        OutElastic = REASING_OUTELASTIC,
        InOutElastic = REASING_INOUTELASTIC,
        OutInElastic = REASING_OUTINELASTIC,
        InBack = REASING_INBACK,
        OutBack = REASING_OUTBACK,
        InOutBack = REASING_INOUTBACK,
        OutInBack = REASING_OUTINBACK,
        InBounce = REASING_INBOUNCE,
        OutBounce = REASING_OUTBOUNCE,
        InOutBounce = REASING_INOUTBOUNCE,
        OutInBounce = REASING_OUTINBOUNCE,
        //InCurve = REASING_INCURVE,
        //OutCurve = REASING_OUTCURVE,
        //SineCurve = REASING_SINECURVE,
        //CosineCurve = REASING_COSINECURVE,
        //BezierSpline = REASING_BEZIERSPLINE,
        //TCBSpline = REASING_TCBSPLINE
    };

public:
    static bool compare(const QVariant& v1, const QVariant& v2, bool noTolerance = false);
    static bool compare(const QPair<QVariant, RPropertyAttributes>& p1,
                        const QPair<QVariant, RPropertyAttributes>& p2,
                        bool noTolerance = false);
    static int getCpuCores();
    static int getIdealThreadCount();
    static QString getBuildCpuArchitecture();

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

    static QStringList sortAlphanumerical(const QStringList& list);
    static QStringList compareChunkify(const QString& s);
    static int compareAlphanumerical(const QString& s1, const QString& s2);
    static bool lessThanAlphanumerical(const QString& s1, const QString& s2);

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
Q_DECLARE_METATYPE(RS::OrthoMode)
Q_DECLARE_METATYPE(RS::OrthoMode*)
Q_DECLARE_METATYPE(RS::KnownVariable)
Q_DECLARE_METATYPE(RS::KnownVariable*)
Q_DECLARE_METATYPE(RS::LinearFormat)
Q_DECLARE_METATYPE(RS::LinearFormat*)
Q_DECLARE_METATYPE(RS::MessageType)
Q_DECLARE_METATYPE(RS::ProjectionRenderingHint)
Q_DECLARE_METATYPE(RS::Side)
Q_DECLARE_METATYPE(RS::Ending)
Q_DECLARE_METATYPE(RS::Ending*)
Q_DECLARE_METATYPE(RS::TextDrawingDirection)
Q_DECLARE_METATYPE(RS::TextDrawingDirection*)
Q_DECLARE_METATYPE(RS::TextLineSpacingStyle)
Q_DECLARE_METATYPE(RS::TextLineSpacingStyle*)
Q_DECLARE_METATYPE(RS::Unit)
Q_DECLARE_METATYPE(RS::Measurement)
Q_DECLARE_METATYPE(RS::Measurement*)
Q_DECLARE_METATYPE(RS::VAlign)
Q_DECLARE_METATYPE(RS::VAlign*)
Q_DECLARE_METATYPE(RS::BooleanOperation)
Q_DECLARE_METATYPE(RS::FillType)
Q_DECLARE_METATYPE(RS::Orientation)
Q_DECLARE_METATYPE(RS::JoinType)
Q_DECLARE_METATYPE(RS::EndType)
Q_DECLARE_METATYPE(RS::Easing)
Q_DECLARE_METATYPE(RS::Easing*)
Q_DECLARE_METATYPE(QList<RS::EntityType>)

#endif
