#include "qtscriptshell_QCleanlooksStyle.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qapplication.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qicon.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>
#include <qwindowsstyle.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QStyle::ComplexControl)
Q_DECLARE_METATYPE(QStyleOptionComplex*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QStyle::ControlElement)
Q_DECLARE_METATYPE(QStyleOption*)
Q_DECLARE_METATYPE(QPalette::ColorRole)
Q_DECLARE_METATYPE(QStyle::PrimitiveElement)
Q_DECLARE_METATYPE(QIcon::Mode)
Q_DECLARE_METATYPE(QStyle::SubControl)
Q_DECLARE_METATYPE(QStyle::PixelMetric)
Q_DECLARE_METATYPE(QApplication*)
Q_DECLARE_METATYPE(QStyle::ContentsType)
Q_DECLARE_METATYPE(QStyle::StandardPixmap)
Q_DECLARE_METATYPE(QStyle::StyleHint)
Q_DECLARE_METATYPE(QStyleHintReturn*)
Q_DECLARE_METATYPE(QStyle::SubElement)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QCleanlooksStyle::QtScriptShell_QCleanlooksStyle()
    : QCleanlooksStyle() {}

QtScriptShell_QCleanlooksStyle::~QtScriptShell_QCleanlooksStyle() {}

void QtScriptShell_QCleanlooksStyle::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QCleanlooksStyle::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCleanlooksStyle::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QCleanlooksStyle::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCleanlooksStyle::drawComplexControl(QStyle::ComplexControl  control, const QStyleOptionComplex*  option, QPainter*  painter, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("drawComplexControl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawComplexControl") & QScriptValue::QObjectMember)) {
        QCleanlooksStyle::drawComplexControl(control, option, painter, widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, control)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOptionComplex *>(option))
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget)));
    }
}

void QtScriptShell_QCleanlooksStyle::drawControl(QStyle::ControlElement  ce, const QStyleOption*  option, QPainter*  painter, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("drawControl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawControl") & QScriptValue::QObjectMember)) {
        QCleanlooksStyle::drawControl(ce, option, painter, widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ce)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(option))
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget)));
    }
}

void QtScriptShell_QCleanlooksStyle::drawItemPixmap(QPainter*  painter, const QRect&  rect, int  alignment, const QPixmap&  pixmap) const
{
    QScriptValue _q_function = __qtscript_self.property("drawItemPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawItemPixmap") & QScriptValue::QObjectMember)) {
        QCleanlooksStyle::drawItemPixmap(painter, rect, alignment, pixmap);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, alignment)
            << qScriptValueFromValue(_q_engine, pixmap));
    }
}

void QtScriptShell_QCleanlooksStyle::drawItemText(QPainter*  painter, const QRect&  rect, int  flags, const QPalette&  pal, bool  enabled, const QString&  text, QPalette::ColorRole  textRole) const
{
    QScriptValue _q_function = __qtscript_self.property("drawItemText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawItemText") & QScriptValue::QObjectMember)) {
        QCleanlooksStyle::drawItemText(painter, rect, flags, pal, enabled, text, textRole);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, flags)
            << qScriptValueFromValue(_q_engine, pal)
            << qScriptValueFromValue(_q_engine, enabled)
            << qScriptValueFromValue(_q_engine, text)
            << qScriptValueFromValue(_q_engine, textRole));
    }
}

void QtScriptShell_QCleanlooksStyle::drawPrimitive(QStyle::PrimitiveElement  elem, const QStyleOption*  option, QPainter*  painter, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("drawPrimitive");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawPrimitive") & QScriptValue::QObjectMember)) {
        QCleanlooksStyle::drawPrimitive(elem, option, painter, widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, elem)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(option))
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget)));
    }
}

bool  QtScriptShell_QCleanlooksStyle::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QCleanlooksStyle::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QCleanlooksStyle::eventFilter(QObject*  o, QEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QCleanlooksStyle::eventFilter(o, e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, o)
            << qScriptValueFromValue(_q_engine, e)));
    }
}

QPixmap  QtScriptShell_QCleanlooksStyle::generatedIconPixmap(QIcon::Mode  iconMode, const QPixmap&  pixmap, const QStyleOption*  opt) const
{
    QScriptValue _q_function = __qtscript_self.property("generatedIconPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("generatedIconPixmap") & QScriptValue::QObjectMember)) {
        return QCleanlooksStyle::generatedIconPixmap(iconMode, pixmap, opt);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QPixmap >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, iconMode)
            << qScriptValueFromValue(_q_engine, pixmap)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(opt))));
    }
}

QStyle::SubControl  QtScriptShell_QCleanlooksStyle::hitTestComplexControl(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, const QPoint&  pt, const QWidget*  w) const
{
    QScriptValue _q_function = __qtscript_self.property("hitTestComplexControl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hitTestComplexControl") & QScriptValue::QObjectMember)) {
        return QCleanlooksStyle::hitTestComplexControl(cc, opt, pt, w);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QStyle::SubControl >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cc)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOptionComplex *>(opt))
            << qScriptValueFromValue(_q_engine, pt)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(w))));
    }
}

QRect  QtScriptShell_QCleanlooksStyle::itemPixmapRect(const QRect&  r, int  flags, const QPixmap&  pixmap) const
{
    QScriptValue _q_function = __qtscript_self.property("itemPixmapRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemPixmapRect") & QScriptValue::QObjectMember)) {
        return QCleanlooksStyle::itemPixmapRect(r, flags, pixmap);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, r)
            << qScriptValueFromValue(_q_engine, flags)
            << qScriptValueFromValue(_q_engine, pixmap)));
    }
}

int  QtScriptShell_QCleanlooksStyle::pixelMetric(QStyle::PixelMetric  metric, const QStyleOption*  option, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("pixelMetric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("pixelMetric") & QScriptValue::QObjectMember)) {
        return QCleanlooksStyle::pixelMetric(metric, option, widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, metric)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(option))
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
    }
}

void QtScriptShell_QCleanlooksStyle::polish(QApplication*  app)
{
    QScriptValue _q_function = __qtscript_self.property("polish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("polish") & QScriptValue::QObjectMember)) {
        QCleanlooksStyle::polish(app);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, app));
    }
}

void QtScriptShell_QCleanlooksStyle::polish(QPalette&  pal)
{
    QScriptValue _q_function = __qtscript_self.property("polish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("polish") & QScriptValue::QObjectMember)) {
        QCleanlooksStyle::polish(pal);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, pal));
    }
}

void QtScriptShell_QCleanlooksStyle::polish(QWidget*  widget)
{
    QScriptValue _q_function = __qtscript_self.property("polish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("polish") & QScriptValue::QObjectMember)) {
        QCleanlooksStyle::polish(widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, widget));
    }
}

QSize  QtScriptShell_QCleanlooksStyle::sizeFromContents(QStyle::ContentsType  type, const QStyleOption*  option, const QSize&  size, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeFromContents");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeFromContents") & QScriptValue::QObjectMember)) {
        return QCleanlooksStyle::sizeFromContents(type, option, size, widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, type)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(option))
            << qScriptValueFromValue(_q_engine, size)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
    }
}

QPalette  QtScriptShell_QCleanlooksStyle::standardPalette() const
{
    QScriptValue _q_function = __qtscript_self.property("standardPalette");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("standardPalette") & QScriptValue::QObjectMember)) {
        return QCleanlooksStyle::standardPalette();
    } else {
        return qscriptvalue_cast<QPalette >(_q_function.call(__qtscript_self));
    }
}

QPixmap  QtScriptShell_QCleanlooksStyle::standardPixmap(QStyle::StandardPixmap  standardPixmap, const QStyleOption*  opt, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("standardPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("standardPixmap") & QScriptValue::QObjectMember)) {
        qFatal("QCleanlooksStyle::standardPixmap() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QPixmap >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, standardPixmap)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
    }
}

int  QtScriptShell_QCleanlooksStyle::styleHint(QStyle::StyleHint  hint, const QStyleOption*  option, const QWidget*  widget, QStyleHintReturn*  returnData) const
{
    QScriptValue _q_function = __qtscript_self.property("styleHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("styleHint") & QScriptValue::QObjectMember)) {
        return QCleanlooksStyle::styleHint(hint, option, widget, returnData);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, hint)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(option))
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))
            << qScriptValueFromValue(_q_engine, returnData)));
    }
}

QRect  QtScriptShell_QCleanlooksStyle::subControlRect(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, QStyle::SubControl  sc, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("subControlRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("subControlRect") & QScriptValue::QObjectMember)) {
        return QCleanlooksStyle::subControlRect(cc, opt, sc, widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cc)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOptionComplex *>(opt))
            << qScriptValueFromValue(_q_engine, sc)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
    }
}

QRect  QtScriptShell_QCleanlooksStyle::subElementRect(QStyle::SubElement  r, const QStyleOption*  opt, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("subElementRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("subElementRect") & QScriptValue::QObjectMember)) {
        return QCleanlooksStyle::subElementRect(r, opt, widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, r)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
    }
}

void QtScriptShell_QCleanlooksStyle::timerEvent(QTimerEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QCleanlooksStyle::timerEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QCleanlooksStyle::unpolish(QApplication*  app)
{
    QScriptValue _q_function = __qtscript_self.property("unpolish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unpolish") & QScriptValue::QObjectMember)) {
        QCleanlooksStyle::unpolish(app);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, app));
    }
}

void QtScriptShell_QCleanlooksStyle::unpolish(QWidget*  widget)
{
    QScriptValue _q_function = __qtscript_self.property("unpolish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unpolish") & QScriptValue::QObjectMember)) {
        QCleanlooksStyle::unpolish(widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, widget));
    }
}

