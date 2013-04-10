#ifndef QTSCRIPTSHELL_QXMLINPUTSOURCE_H
#define QTSCRIPTSHELL_QXMLINPUTSOURCE_H

#include <qxml.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QXmlInputSource : public QXmlInputSource
{
public:
    QtScriptShell_QXmlInputSource();
    QtScriptShell_QXmlInputSource(QIODevice*  dev);
    ~QtScriptShell_QXmlInputSource();

    QString  data() const;
    void fetchData();
    QString  fromRawData(const QByteArray&  data, bool  beginning = false);
    QChar  next();
    void reset();
    void setData(const QByteArray&  dat);
    void setData(const QString&  dat);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QXMLINPUTSOURCE_H
