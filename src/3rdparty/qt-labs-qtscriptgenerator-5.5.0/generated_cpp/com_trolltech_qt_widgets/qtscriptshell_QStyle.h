#ifndef QTSCRIPTSHELL_QSTYLE_H
#define QTSCRIPTSHELL_QSTYLE_H

#include <qstyle.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStyle : public QStyle
{
public:
    QtScriptShell_QStyle();
    ~QtScriptShell_QStyle();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    void drawComplexControl(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, QPainter*  p, const QWidget*  widget = 0) const;
    void drawControl(QStyle::ControlElement  element, const QStyleOption*  opt, QPainter*  p, const QWidget*  w = 0) const;
    void drawItemPixmap(QPainter*  painter, const QRect&  rect, int  alignment, const QPixmap&  pixmap) const;
    void drawItemText(QPainter*  painter, const QRect&  rect, int  flags, const QPalette&  pal, bool  enabled, const QString&  text, QPalette::ColorRole  textRole = QPalette::NoRole) const;
    void drawPrimitive(QStyle::PrimitiveElement  pe, const QStyleOption*  opt, QPainter*  p, const QWidget*  w = 0) const;
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QPixmap  generatedIconPixmap(QIcon::Mode  iconMode, const QPixmap&  pixmap, const QStyleOption*  opt) const;
    QStyle::SubControl  hitTestComplexControl(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, const QPoint&  pt, const QWidget*  widget = 0) const;
    QRect  itemPixmapRect(const QRect&  r, int  flags, const QPixmap&  pixmap) const;
    int  layoutSpacing(QSizePolicy::ControlType  control1, QSizePolicy::ControlType  control2, Qt::Orientation  orientation, const QStyleOption*  option = 0, const QWidget*  widget = 0) const;
    int  pixelMetric(QStyle::PixelMetric  metric, const QStyleOption*  option = 0, const QWidget*  widget = 0) const;
    void polish(QApplication*  arg__1);
    void polish(QPalette&  arg__1);
    void polish(QWidget*  arg__1);
    QSize  sizeFromContents(QStyle::ContentsType  ct, const QStyleOption*  opt, const QSize&  contentsSize, const QWidget*  w = 0) const;
    QIcon  standardIcon(QStyle::StandardPixmap  standardIcon, const QStyleOption*  option = 0, const QWidget*  widget = 0) const;
    QPalette  standardPalette() const;
    QPixmap  standardPixmap(QStyle::StandardPixmap  standardPixmap, const QStyleOption*  opt = 0, const QWidget*  widget = 0) const;
    int  styleHint(QStyle::StyleHint  stylehint, const QStyleOption*  opt = 0, const QWidget*  widget = 0, QStyleHintReturn*  returnData = 0) const;
    QRect  subControlRect(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, QStyle::SubControl  sc, const QWidget*  widget = 0) const;
    QRect  subElementRect(QStyle::SubElement  subElement, const QStyleOption*  option, const QWidget*  widget = 0) const;
    void timerEvent(QTimerEvent*  arg__1);
    void unpolish(QApplication*  arg__1);
    void unpolish(QWidget*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLE_H
