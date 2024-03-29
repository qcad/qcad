// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMAGRAPHICSSCENE_H
        #define RECMAGRAPHICSSCENE_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RGraphicsScene.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaGraphicsScene {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue createEcma(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getRExporter(QScriptContext *context,
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
        getDocumentInterface
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getGraphicsViews
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        clear
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        exportDocumentSettings
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        regenerate
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        updateSelectionStatus
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        regenerateViews
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        repaintViews
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setCursor
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handleTerminateEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handleKeyPressEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handleKeyReleaseEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handleMouseMoveEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handleMousePressEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handleMouseReleaseEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handleMouseDoubleClickEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handleWheelEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handleTabletEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handleSwipeGestureEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handlePanGestureEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handlePinchGestureEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        registerView
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        unregisterView
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        beginPreview
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        endPreview
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        clearPreview
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isPreviewEmpty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addToPreview
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addPathToPreview
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        beginNoColorMode
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        endNoColorMode
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getNoColorMode
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getHighlightedReferencePoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        highlightEntity
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        highlightReferencePoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        selectReferencePoints
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        exportCurrentEntity
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        unexportEntity
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        countReferencePoints
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        hasSelectedReferencePoints
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        dump
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RGraphicsScene* getSelf(const QString& fName, QScriptContext* context)
    ;static RGraphicsScene* getSelfShell(const QString& fName, QScriptContext* context)
    ;};
    #endif
    