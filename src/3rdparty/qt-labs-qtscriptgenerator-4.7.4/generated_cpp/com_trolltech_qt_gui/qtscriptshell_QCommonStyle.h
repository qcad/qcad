#ifndef QTSCRIPTSHELL_QCOMMONSTYLE_H
#define QTSCRIPTSHELL_QCOMMONSTYLE_H

#include <qcommonstyle.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QCommonStyle : public QCommonStyle
{
public:
    QtScriptShell_QCommonStyle();
    ~QtScriptShell_QCommonStyle();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    void drawComplexControl(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, QPainter*  p, const QWidget*  w = 0) const;
    void drawControl(QStyle::ControlElement  element, const QStyleOption*  opt, QPainter*  p, const QWidget*  w = 0) const;
    void drawItemPixmap(QPainter*  painter, const QRect&  rect, int  alignment, const QPixmap&  pixmap) const;
    void drawItemText(QPainter*  painter, const QRect&  rect, int  flags, const QPalette&  pal, bool  enabled, const QString&  text, QPalette::ColorRole  textRole) const;
    void drawPrimitive(QStyle::PrimitiveElement  pe, const QStyleOption*  opt, QPainter*  p, const QWidget*  w = 0) const;
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QPixmap  generatedIconPixmap(QIcon::Mode  iconMode, const QPixmap&  pixmap, const QStyleOption*  opt) const;
    QStyle::SubControl  hitTestComplexControl(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, const QPoint&  pt, const QWidget*  w = 0) const;
    QRect  itemPixmapRect(const QRect&  r, int  flags, const QPixmap&  pixmap) const;
    int  pixelMetric(QStyle::PixelMetric  m, const QStyleOption*  opt = 0, const QWidget*  widget = 0) const;
    void polish(QApplication*  app);
    void polish(QPalette&  arg__1);
    void polish(QWidget*  widget);
    QSize  sizeFromContents(QStyle::ContentsType  ct, const QStyleOption*  opt, const QSize&  contentsSize, const QWidget*  widget = 0) const;
    QPalette  standardPalette() const;
    QPixmap  standardPixmap(QStyle::StandardPixmap  standardPixmap, const QStyleOption*  opt, const QWidget*  widget) const;
    int  styleHint(QStyle::StyleHint  sh, const QStyleOption*  opt = 0, const QWidget*  w = 0, QStyleHintReturn*  shret = 0) const;
    QRect  subControlRect(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, QStyle::SubControl  sc, const QWidget*  w = 0) const;
    QRect  subElementRect(QStyle::SubElement  r, const QStyleOption*  opt, const QWidget*  widget = 0) const;
    void timerEvent(QTimerEvent*  arg__1);
    void unpolish(QApplication*  application);
    void unpolish(QWidget*  widget);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QCOMMONSTYLE_H
