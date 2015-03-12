#include "qtscriptshell_QPrinter.h"

#include <QtScript/QScriptEngine>
#include <QPrinterInfo>
#include <QVariant>
#include <qlist.h>
#include <qpaintengine.h>
#include <qprintengine.h>
#include <qprinter.h>
#include <qrect.h>
#include <qsize.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QPrinter::QtScriptShell_QPrinter(QPrinter::PrinterMode  mode)
    : QPrinter(mode) {}

QtScriptShell_QPrinter::QtScriptShell_QPrinter(const QPrinterInfo&  printer, QPrinter::PrinterMode  mode)
    : QPrinter(printer, mode) {}

QtScriptShell_QPrinter::~QtScriptShell_QPrinter() {}

