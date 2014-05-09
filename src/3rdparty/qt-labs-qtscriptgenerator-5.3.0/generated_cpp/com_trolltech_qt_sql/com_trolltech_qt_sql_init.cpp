#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QSqlDriverCreatorBase_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSqlRecord_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSqlField_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSqlQuery_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSqlDatabase_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSqlRelation_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSqlResult_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSqlError_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSql_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSqlIndex_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSqlDriver_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSqlQueryModel_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSqlTableModel_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSqlRelationalTableModel_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_sql_class_names[] = {
    "QSqlDriverCreatorBase"
    , "QSqlRecord"
    , "QSqlField"
    , "QSqlQuery"
    , "QSqlDatabase"
    , "QSqlRelation"
    , "QSqlResult"
    , "QSqlError"
    , "QSql"
    , "QSqlIndex"
    , "QSqlDriver"
    , "QSqlQueryModel"
    , "QSqlTableModel"
    , "QSqlRelationalTableModel"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_sql_class_functions[] = {
    qtscript_create_QSqlDriverCreatorBase_class
    , qtscript_create_QSqlRecord_class
    , qtscript_create_QSqlField_class
    , qtscript_create_QSqlQuery_class
    , qtscript_create_QSqlDatabase_class
    , qtscript_create_QSqlRelation_class
    , qtscript_create_QSqlResult_class
    , qtscript_create_QSqlError_class
    , qtscript_create_QSql_class
    , qtscript_create_QSqlIndex_class
    , qtscript_create_QSqlDriver_class
    , qtscript_create_QSqlQueryModel_class
    , qtscript_create_QSqlTableModel_class
    , qtscript_create_QSqlRelationalTableModel_class
};

void qtscript_initialize_com_trolltech_qt_sql_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 14; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_sql_class_names[i],
            qtscript_com_trolltech_qt_sql_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
