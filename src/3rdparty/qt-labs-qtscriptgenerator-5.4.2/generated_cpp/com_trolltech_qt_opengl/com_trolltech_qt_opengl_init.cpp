#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QGLFramebufferObjectFormat_class(QScriptEngine *engine);
QScriptValue qtscript_create_QGLContext_class(QScriptEngine *engine);
QScriptValue qtscript_create_QGLColormap_class(QScriptEngine *engine);
QScriptValue qtscript_create_QGLShader_class(QScriptEngine *engine);
QScriptValue qtscript_create_QGLPixelBuffer_class(QScriptEngine *engine);
QScriptValue qtscript_create_QGLFramebufferObject_class(QScriptEngine *engine);
QScriptValue qtscript_create_QGLShaderProgram_class(QScriptEngine *engine);
QScriptValue qtscript_create_QGLWidget_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_opengl_class_names[] = {
    "QGLFramebufferObjectFormat"
    , "QGLContext"
    , "QGLColormap"
    , "QGLShader"
    , "QGLPixelBuffer"
    , "QGLFramebufferObject"
    , "QGLShaderProgram"
    , "QGLWidget"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_opengl_class_functions[] = {
    qtscript_create_QGLFramebufferObjectFormat_class
    , qtscript_create_QGLContext_class
    , qtscript_create_QGLColormap_class
    , qtscript_create_QGLShader_class
    , qtscript_create_QGLPixelBuffer_class
    , qtscript_create_QGLFramebufferObject_class
    , qtscript_create_QGLShaderProgram_class
    , qtscript_create_QGLWidget_class
};

void qtscript_initialize_com_trolltech_qt_opengl_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 8; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_opengl_class_names[i],
            qtscript_com_trolltech_qt_opengl_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
