#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QUiLoader_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_uitools_class_names[] = {
    "QUiLoader"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_uitools_class_functions[] = {
    qtscript_create_QUiLoader_class
};

void qtscript_initialize_com_trolltech_qt_uitools_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 1; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_uitools_class_names[i],
            qtscript_com_trolltech_qt_uitools_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
