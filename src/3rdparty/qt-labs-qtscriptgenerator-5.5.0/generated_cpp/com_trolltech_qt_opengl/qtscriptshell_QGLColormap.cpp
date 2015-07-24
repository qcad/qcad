#include "qtscriptshell_QGLColormap.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcolor.h>
#include <qglcolormap.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QGLColormap::QtScriptShell_QGLColormap()
    : QGLColormap() {}

QtScriptShell_QGLColormap::QtScriptShell_QGLColormap(const QGLColormap&  arg__1)
    : QGLColormap(arg__1) {}

QtScriptShell_QGLColormap::~QtScriptShell_QGLColormap() {}

