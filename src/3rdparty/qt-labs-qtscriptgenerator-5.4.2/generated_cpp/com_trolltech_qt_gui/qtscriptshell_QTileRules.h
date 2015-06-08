#ifndef QTSCRIPTSHELL_QTILERULES_H
#define QTSCRIPTSHELL_QTILERULES_H

#include <qdrawutil.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTileRules : public QTileRules
{
public:
    QtScriptShell_QTileRules(Qt::TileRule  horizontalRule, Qt::TileRule  verticalRule);
    QtScriptShell_QTileRules(Qt::TileRule  rule = Qt::StretchTile);
    ~QtScriptShell_QTileRules();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTILERULES_H
