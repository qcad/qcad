#include "qtscriptshell_QPlainTextDocumentLayout.h"

#include <QtScript/QScriptEngine>
#include <QAbstractTextDocumentLayout>
#include <QVariant>
#include <qpainter.h>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>
#include <qtextdocument.h>
#include <qtextobject.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QPlainTextDocumentLayout::QtScriptShell_QPlainTextDocumentLayout(QTextDocument*  document)
    : QPlainTextDocumentLayout(document) {}

QtScriptShell_QPlainTextDocumentLayout::~QtScriptShell_QPlainTextDocumentLayout() {}

