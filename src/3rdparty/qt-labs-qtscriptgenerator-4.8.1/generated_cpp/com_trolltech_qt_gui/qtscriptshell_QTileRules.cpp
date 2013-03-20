#include "qtscriptshell_QTileRules.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QTileRules::QtScriptShell_QTileRules(Qt::TileRule  horizontalRule, Qt::TileRule  verticalRule)
    : QTileRules(horizontalRule, verticalRule) {}

QtScriptShell_QTileRules::QtScriptShell_QTileRules(Qt::TileRule  rule)
    : QTileRules(rule) {}

QtScriptShell_QTileRules::~QtScriptShell_QTileRules() {}

