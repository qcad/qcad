#ifndef QTSCRIPTSHELL_QICONENGINE_H
#define QTSCRIPTSHELL_QICONENGINE_H

#include <qiconengine.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QIconEngine : public QIconEngine
{
public:
    QtScriptShell_QIconEngine();
    ~QtScriptShell_QIconEngine();

    QSize  actualSize(const QSize&  size, QIcon::Mode  mode, QIcon::State  state);
    void addFile(const QString&  fileName, const QSize&  size, QIcon::Mode  mode, QIcon::State  state);
    void addPixmap(const QPixmap&  pixmap, QIcon::Mode  mode, QIcon::State  state);
    void paint(QPainter*  painter, const QRect&  rect, QIcon::Mode  mode, QIcon::State  state);
    QPixmap  pixmap(const QSize&  size, QIcon::Mode  mode, QIcon::State  state);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QICONENGINE_H
