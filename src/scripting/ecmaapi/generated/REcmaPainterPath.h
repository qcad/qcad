// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is copyable.
        
        #ifndef RECMAPAINTERPATH_H
        #define RECMAPAINTERPATH_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RPainterPath.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaPainterPath {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue createEcma(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getQPainterPath(QScriptContext *context,
            QScriptEngine *engine)
        ;

    // returns class name:
    static  QScriptValue getClassName(QScriptContext *context, QScriptEngine *engine) 
        ;

    // returns all base classes (in case of multiple inheritance):
    static  QScriptValue getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        ;

    // properties:
    

    // public methods:
    static  QScriptValue
        setPath
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getShapes
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getCurrentPosition
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isAtPosition
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        moveTo
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        moveToOrNop
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        lineTo
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        quadTo
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        cubicTo
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        closeSubpath
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        containsPoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addPolyline
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addPath
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        appendPath
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addLine
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addArc
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addSpline
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addRect
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addBox
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getBoundingBox
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getStartPoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getEndPoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isValid
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setValid
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isSane
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getZLevel
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setZLevel
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPen
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setPen
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getBrush
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setBrush
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setMode
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getMode
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setHighlighted
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isHighlighted
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setSelected
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isSelected
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setFixedPenColor
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isFixedPenColor
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setFixedBrushColor
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isFixedBrushColor
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setAutoRegen
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getAutoRegen
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setAlwaysRegen
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getAlwaysRegen
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setInheritPen
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getInheritPen
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setPixelUnit
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPixelUnit
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setNoClipping
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getNoClipping
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setNoColorMode
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getNoColorMode
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setSimplePointDisplay
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getSimplePointDisplay
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setPolylineGen
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPolylineGen
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setNoPattern
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getNoPattern
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setScreenBasedLinetype
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getScreenBasedLinetype
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setWipeout
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getWipeout
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setFrameless
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getFrameless
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setPixelWidth
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPixelWidth
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setFeatureSize
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getFeatureSize
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setPixelSizeHint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPixelSizeHint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDistanceTo
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addPoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        hasPoints
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setPoints
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPoints
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        transform
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        move
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        rotate
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        scale
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getElementCount
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getXAt
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getYAt
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getTypeAt
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isEmpty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addShape
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addOriginalShape
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        hasOriginalShapes
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        countOriginalShapes
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getOriginalShape
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        rotateList
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        translateList
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        scaleList
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getMinList
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getMaxList
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue copy
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RPainterPath* getSelf(const QString& fName, QScriptContext* context)
    ;static RPainterPath* getSelfShell(const QString& fName, QScriptContext* context)
    ;static  QScriptValue toScriptValueEnumMode(QScriptEngine* engine, const RPainterPath::Mode& value)
    ;static  void fromScriptValueEnumMode(const QScriptValue& value, RPainterPath::Mode& out)
    ;};
    #endif
    