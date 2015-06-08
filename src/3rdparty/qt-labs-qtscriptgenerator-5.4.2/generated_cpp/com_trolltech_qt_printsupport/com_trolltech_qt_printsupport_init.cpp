#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QPrinter_class(QScriptEngine *engine);
QScriptValue qtscript_create_QPrintEngine_class(QScriptEngine *engine);
QScriptValue qtscript_create_QPrintPreviewWidget_class(QScriptEngine *engine);
QScriptValue qtscript_create_QPrintPreviewDialog_class(QScriptEngine *engine);
QScriptValue qtscript_create_QAbstractPrintDialog_class(QScriptEngine *engine);
QScriptValue qtscript_create_QPageSetupDialog_class(QScriptEngine *engine);
QScriptValue qtscript_create_QPrintDialog_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_printsupport_class_names[] = {
    "QPrinter"
    , "QPrintEngine"
    , "QPrintPreviewWidget"
    , "QPrintPreviewDialog"
    , "QAbstractPrintDialog"
    , "QPageSetupDialog"
    , "QPrintDialog"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_printsupport_class_functions[] = {
    qtscript_create_QPrinter_class
    , qtscript_create_QPrintEngine_class
    , qtscript_create_QPrintPreviewWidget_class
    , qtscript_create_QPrintPreviewDialog_class
    , qtscript_create_QAbstractPrintDialog_class
    , qtscript_create_QPageSetupDialog_class
    , qtscript_create_QPrintDialog_class
};

void qtscript_initialize_com_trolltech_qt_printsupport_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 7; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_printsupport_class_names[i],
            qtscript_com_trolltech_qt_printsupport_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
