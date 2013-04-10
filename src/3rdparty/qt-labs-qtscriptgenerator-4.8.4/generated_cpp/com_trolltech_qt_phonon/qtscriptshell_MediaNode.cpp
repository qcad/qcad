#include "qtscriptshell_MediaNode.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <path.h>
#include <qlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_MediaNode::~QtScriptShell_MediaNode() {}

