#include "qtscriptshell_QSslConfiguration.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qlist.h>
#include <qsslcertificate.h>
#include <qsslcipher.h>
#include <qsslconfiguration.h>
#include <qsslkey.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QSslConfiguration::QtScriptShell_QSslConfiguration()
    : QSslConfiguration() {}

QtScriptShell_QSslConfiguration::QtScriptShell_QSslConfiguration(const QSslConfiguration&  other)
    : QSslConfiguration(other) {}

QtScriptShell_QSslConfiguration::~QtScriptShell_QSslConfiguration() {}

