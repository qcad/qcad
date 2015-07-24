#ifndef QTSCRIPTSHELL_QSTYLEOPTIONCOMPLEX_H
#define QTSCRIPTSHELL_QSTYLEOPTIONCOMPLEX_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStyleOptionComplex : public QStyleOptionComplex
{
public:
    QtScriptShell_QStyleOptionComplex(const QStyleOptionComplex&  other);
    QtScriptShell_QStyleOptionComplex(int  version = QStyleOptionComplex::Version, int  type = SO_Complex);
    ~QtScriptShell_QStyleOptionComplex();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONCOMPLEX_H
