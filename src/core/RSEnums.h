#ifndef RSENUMS_H
#define RSENUMS_H

#include "core_global.h"

#include <QEasingCurve>

#if QT_VERSION >= 0x060000
#include <QMetaType>
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


namespace QCADCORE_EXPORT RS {
    static const double PointTolerance = 1.0e-9;
    static const double AngleTolerance = 1.0e-9;

#if QT_VERSION >= 0x060000
    // handled as include to avoid inclusion in Qt 4-5 ECMAScript API:
    #include "RSMetaType.h"
#else
    enum MetaType {
        Bool = QVariant::Bool,
        Char = QVariant::Char,
        Double = QVariant::Double,
        Int = QVariant::Int,
        UnknownType = QVariant::Invalid,
        LongLong = QVariant::LongLong,
        BitArray = QVariant::BitArray,
        Bitmap = QVariant::Bitmap,
        Brush = QVariant::Brush,
        ByteArray = QVariant::ByteArray,
        Color = QVariant::Color,
        Cursor = QVariant::Cursor,
        Date = QVariant::Date,
        DateTime = QVariant::DateTime,
        EasingCurve = QVariant::EasingCurve,
        Font = QVariant::Font,
        Hash = QVariant::Hash,
        Icon = QVariant::Icon,
        Image = QVariant::Image,
        KeySequence = QVariant::KeySequence,
        Line = QVariant::Line,
        LineF = QVariant::LineF,
        List = QVariant::List,
        Locale = QVariant::Locale,
        Map = QVariant::Map,
        Matrix4x4 = QVariant::Matrix4x4,
        Palette = QVariant::Palette,
        Pen = QVariant::Pen,
        Pixmap = QVariant::Pixmap,
        Point = QVariant::Point,
        PointF = QVariant::PointF,
        Polygon = QVariant::Polygon,
        Rect = QVariant::Rect,
        RectF = QVariant::RectF,
        Region = QVariant::Region,
        Size = QVariant::Size,
        SizeF = QVariant::SizeF,
        SizePolicy = QVariant::SizePolicy,
        String = QVariant::String,
        StringList = QVariant::StringList,
        TextFormat = QVariant::TextFormat,
        TextLength = QVariant::TextLength,
        Time = QVariant::Time,
        Transform = QVariant::Transform,
        Url = QVariant::Url,
        Vector2D = QVariant::Vector2D,
        Vector3D = QVariant::Vector3D,
        Vector4D = QVariant::Vector4D,
        Quaternion = QVariant::Quaternion,
        UInt = QVariant::UInt,
        ULongLong = QVariant::ULongLong,
        UserType = QVariant::UserType
    };
#endif

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

        ObjectLinetype,
        ObjectLayer,
        ObjectBlock,
        ObjectLayout,
        ObjectLayerState,
        ObjectView,
        ObjectUcs,
        ObjectDocumentVariable,
        ObjectDimStyle,

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
        EntityWipeout,      /**< Wipeout */
        EntityXRef,         /**< XRef */

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
     * Side used for side of a point relative to an entity
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
        CHAMFERD,  // 10
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
        DIMALTTZ,  // 20
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
        DIMBLK2,  // 30
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
        DIMEXO,  // 40
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
        DIMPOST,  // 50
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
        DIMTDEC,  // 60
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
        DIMTSZ,  // 70
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
        ELEVATION,  // 80
        EXTMAX,
        EXTMIN,
        FACETRES,
        FILLETRAD,
        FILLMODE,
        IMAGEFRAME,
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
        //QCADARCHTICK,
        INVALID = -1,
    };

    enum KnownVariableType {
        VarTypeBool = 1,
        VarTypeInt = 2,
        VarTypeDouble = 3,
        VarTypeColor = 4,
        VarTypeUnknown = -1
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
}

#endif // RSENUMS_H
