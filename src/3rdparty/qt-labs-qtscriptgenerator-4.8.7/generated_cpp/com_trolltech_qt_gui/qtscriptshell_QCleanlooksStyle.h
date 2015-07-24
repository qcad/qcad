#ifndef QTSCRIPTSHELL_QCLEANLOOKSSTYLE_H
#define QTSCRIPTSHELL_QCLEANLOOKSSTYLE_H

#include <qcleanlooksstyle.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QCleanlooksStyle : public QCleanlooksStyle
{
public:
    QtScriptShell_QCleanlooksStyle();
    ~QtScriptShell_QCleanlooksStyle();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    void drawComplexControl(QStyle::ComplexControl  control, const QStyleOptionComplex*  option, QPainter*  painter, const QWidget*  widget) const;
    void drawControl(QStyle::ControlElement  ce, const QStyleOption*  option, QPainter*  painter, const QWidget*  widget) const;
    void drawItemPixmap(QPainter*  painter, const QRect&  rect, int  alignment, const QPixmap&  pixmap) const;
    void drawItemText(QPainter*  painter, const QRect&  rect, int  flags, const QPalette&  pal, bool  enabled, const QString&  text, QPalette::ColorRole  textRole = QPalette::NoRole) const;
    void drawPrimitive(QStyle::PrimitiveElement  elem, const QStyleOption*  option, QPainter*  painter, const QWidget*  widget = 0) const;
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  o, QEvent*  e);
    QPixmap  generatedIconPixmap(QIcon::Mode  iconMode, const QPixmap&  pixmap, const QStyleOption*  opt) const;
    QStyle::SubControl  hitTestComplexControl(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, const QPoint&  pt, const QWidget*  w = 0) const;
    QRect  itemPixmapRect(const QRect&  r, int  flags, const QPixmap&  pixmap) const;
    int  pixelMetric(QStyle::PixelMetric  metric, const QStyleOption*  option = 0, const QWidget*  widget = 0) const;
    void polish(QApplication*  app);
    void polish(QPalette&  pal);
    void polish(QWidget*  widget);
    QSize  sizeFromContents(QStyle::ContentsType  type, const QStyleOption*  option, const QSize&  size, const QWidget*  widget) const;
    QPalette  standardPalette() const;
    QPixmap  standardPixmap(QStyle::StandardPixmap  standardPixmap, const QStyleOption*  opt, const QWidget*  widget) const;
    int  styleHint(QStyle::StyleHint  hint, const QStyleOption*  option = 0, const QWidget*  widget = 0, QStyleHintReturn*  returnData = 0) const;
    QRect  subControlRect(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, QStyle::SubControl  sc, const QWidget*  widget) const;
    QRect  subElementRect(QStyle::SubElement  r, const QStyleOption*  opt, const QWidget*  widget = 0) const;
    void timerEvent(QTimerEvent*  event);
    void unpolish(QApplication*  app);
    void unpolish(QWidget*  widget);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QCLEANLOOKSSTYLE_H
