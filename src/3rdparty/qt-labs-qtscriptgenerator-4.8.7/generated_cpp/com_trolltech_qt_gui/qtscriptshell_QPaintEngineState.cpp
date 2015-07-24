#include "qtscriptshell_QPaintEngineState.h"

#include <QtScript/QScriptEngine>
#include <QPainterPath>
#include <QVariant>
#include <qbrush.h>
#include <qfont.h>
#include <qmatrix.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpen.h>
#include <qpoint.h>
#include <qregion.h>
#include <qtransform.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QPaintEngineState::QtScriptShell_QPaintEngineState()
    : QPaintEngineState() {}

QtScriptShell_QPaintEngineState::~QtScriptShell_QPaintEngineState() {}

