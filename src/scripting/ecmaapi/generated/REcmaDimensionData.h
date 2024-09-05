// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMADIMENSIONDATA_H
        #define RECMADIMENSIONDATA_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RDimensionData.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaDimensionData {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue createEcma(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getREntityData(QScriptContext *context,
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
        getType
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getBoundingBox
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        render
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        updateBoundingBox
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        updateTextPositionCenter
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        updateTextPositionSide
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        updateTextData
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        updateShapes
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        updateArrowPos1
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        updateArrowPos2
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        clearStyleOverrides
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getShapes
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPointOnEntity
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isValid
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isSane
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDefinitionPoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDefinitionPoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setText
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getText
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setUpperTolerance
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getUpperTolerance
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setLowerTolerance
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getLowerTolerance
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setTextPosition
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getTextPosition
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setFontName
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getFontName
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimBlockName
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimBlockName
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        hasOverrides
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        hasOverride
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getOverrides
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimXVariant
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimXDouble
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimXInt
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimXBool
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimXColor
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimXVariant
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getVariantOverride
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimXDouble
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDoubleOverride
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimXInt
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getIntOverride
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimXBool
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getBoolOverride
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimXColor
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getColorOverride
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimlfac
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimlfac
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getLinearFactor
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setLinearFactor
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimscale
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimscale
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isArrow1Flipped
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setArrow1Flipped
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isArrow2Flipped
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setArrow2Flipped
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isExtLineFix
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setExtLineFix
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getExtLineFixLength
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setExtLineFixLength
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        adjustExtensionLineFixLength
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        hasSpaceForArrows
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDistanceTo
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        intersectsWith
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getReferencePoints
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        clickReferencePoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        moveReferencePoint
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
        scaleVisualProperties
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        mirror
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimexo
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimexo
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimexe
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimexe
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimasz
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimasz
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimdli
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimdli
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimgap
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimgap
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimtxt
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimtxt
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimlunit
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimlunit
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimjust
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimtad
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimtad
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimtih
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimtih
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimtsz
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimtsz
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimzin
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimzin
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimaunit
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimaunit
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimadec
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimadec
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimdec
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimdec
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimazin
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimazin
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimdsep
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimdsep
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimclrt
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimclrt
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        useArchTick
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimblk
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimblkName
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isDimXScaled
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        hasCustomTextPosition
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setCustomTextPosition
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getLineSpacingStyle
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getLineSpacingFactor
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getTextRotation
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setTextRotation
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getTextData
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        initTextData
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getMeasurement
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getMeasuredValue
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getAutoLabel
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        formatLabel
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        formatAngleLabel
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        update
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimensionBlockReference
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        hasDimensionBlockReference
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        to2D
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RDimensionData* getSelf(const QString& fName, QScriptContext* context)
    ;static RDimensionData* getSelfShell(const QString& fName, QScriptContext* context)
    ;};
    #endif
    