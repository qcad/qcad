#include "qtscriptshell_QPlastiqueStyle.h"

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
#include <qplastiquestyle.h>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

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

QtScriptShell_QPlastiqueStyle::QtScriptShell_QPlastiqueStyle()
    : QPlastiqueStyle() {}

QtScriptShell_QPlastiqueStyle::~QtScriptShell_QPlastiqueStyle() {}

void QtScriptShell_QPlastiqueStyle::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QPlastiqueStyle::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QPlastiqueStyle::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QPlastiqueStyle::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QPlastiqueStyle::drawComplexControl(QStyle::ComplexControl  control, const QStyleOptionComplex*  option, QPainter*  painter, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("drawComplexControl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawComplexControl") & QScriptValue::QObjectMember)) {
        QPlastiqueStyle::drawComplexControl(control, option, painter, widget);
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

void QtScriptShell_QPlastiqueStyle::drawControl(QStyle::ControlElement  element, const QStyleOption*  option, QPainter*  painter, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("drawControl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawControl") & QScriptValue::QObjectMember)) {
        QPlastiqueStyle::drawControl(element, option, painter, widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, element)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(option))
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget)));
    }
}

void QtScriptShell_QPlastiqueStyle::drawItemPixmap(QPainter*  painter, const QRect&  rect, int  alignment, const QPixmap&  pixmap) const
{
    QScriptValue _q_function = __qtscript_self.property("drawItemPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawItemPixmap") & QScriptValue::QObjectMember)) {
        QPlastiqueStyle::drawItemPixmap(painter, rect, alignment, pixmap);
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

void QtScriptShell_QPlastiqueStyle::drawItemText(QPainter*  painter, const QRect&  rect, int  flags, const QPalette&  pal, bool  enabled, const QString&  text, QPalette::ColorRole  textRole) const
{
    QScriptValue _q_function = __qtscript_self.property("drawItemText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawItemText") & QScriptValue::QObjectMember)) {
        QPlastiqueStyle::drawItemText(painter, rect, flags, pal, enabled, text, textRole);
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

void QtScriptShell_QPlastiqueStyle::drawPrimitive(QStyle::PrimitiveElement  element, const QStyleOption*  option, QPainter*  painter, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("drawPrimitive");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawPrimitive") & QScriptValue::QObjectMember)) {
        QPlastiqueStyle::drawPrimitive(element, option, painter, widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, element)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(option))
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget)));
    }
}

bool  QtScriptShell_QPlastiqueStyle::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QPlastiqueStyle::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QPlastiqueStyle::eventFilter(QObject*  watched, QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QPlastiqueStyle::eventFilter(watched, event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, watched)
            << qScriptValueFromValue(_q_engine, event)));
    }
}

QPixmap  QtScriptShell_QPlastiqueStyle::generatedIconPixmap(QIcon::Mode  iconMode, const QPixmap&  pixmap, const QStyleOption*  opt) const
{
    QScriptValue _q_function = __qtscript_self.property("generatedIconPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("generatedIconPixmap") & QScriptValue::QObjectMember)) {
        return QPlastiqueStyle::generatedIconPixmap(iconMode, pixmap, opt);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QPixmap >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, iconMode)
            << qScriptValueFromValue(_q_engine, pixmap)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(opt))));
    }
}

QStyle::SubControl  QtScriptShell_QPlastiqueStyle::hitTestComplexControl(QStyle::ComplexControl  control, const QStyleOptionComplex*  option, const QPoint&  pos, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("hitTestComplexControl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hitTestComplexControl") & QScriptValue::QObjectMember)) {
        return QPlastiqueStyle::hitTestComplexControl(control, option, pos, widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QStyle::SubControl >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, control)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOptionComplex *>(option))
            << qScriptValueFromValue(_q_engine, pos)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
    }
}

QRect  QtScriptShell_QPlastiqueStyle::itemPixmapRect(const QRect&  r, int  flags, const QPixmap&  pixmap) const
{
    QScriptValue _q_function = __qtscript_self.property("itemPixmapRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemPixmapRect") & QScriptValue::QObjectMember)) {
        return QPlastiqueStyle::itemPixmapRect(r, flags, pixmap);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, r)
            << qScriptValueFromValue(_q_engine, flags)
            << qScriptValueFromValue(_q_engine, pixmap)));
    }
}

int  QtScriptShell_QPlastiqueStyle::pixelMetric(QStyle::PixelMetric  metric, const QStyleOption*  option, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("pixelMetric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("pixelMetric") & QScriptValue::QObjectMember)) {
        return QPlastiqueStyle::pixelMetric(metric, option, widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, metric)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(option))
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
    }
}

void QtScriptShell_QPlastiqueStyle::polish(QApplication*  app)
{
    QScriptValue _q_function = __qtscript_self.property("polish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("polish") & QScriptValue::QObjectMember)) {
        QPlastiqueStyle::polish(app);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, app));
    }
}

void QtScriptShell_QPlastiqueStyle::polish(QPalette&  pal)
{
    QScriptValue _q_function = __qtscript_self.property("polish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("polish") & QScriptValue::QObjectMember)) {
        QPlastiqueStyle::polish(pal);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, pal));
    }
}

void QtScriptShell_QPlastiqueStyle::polish(QWidget*  widget)
{
    QScriptValue _q_function = __qtscript_self.property("polish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("polish") & QScriptValue::QObjectMember)) {
        QPlastiqueStyle::polish(widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, widget));
    }
}

QSize  QtScriptShell_QPlastiqueStyle::sizeFromContents(QStyle::ContentsType  type, const QStyleOption*  option, const QSize&  size, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeFromContents");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeFromContents") & QScriptValue::QObjectMember)) {
        return QPlastiqueStyle::sizeFromContents(type, option, size, widget);
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

QPalette  QtScriptShell_QPlastiqueStyle::standardPalette() const
{
    QScriptValue _q_function = __qtscript_self.property("standardPalette");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("standardPalette") & QScriptValue::QObjectMember)) {
        return QPlastiqueStyle::standardPalette();
    } else {
        return qscriptvalue_cast<QPalette >(_q_function.call(__qtscript_self));
    }
}

QPixmap  QtScriptShell_QPlastiqueStyle::standardPixmap(QStyle::StandardPixmap  standardPixmap, const QStyleOption*  opt, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("standardPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("standardPixmap") & QScriptValue::QObjectMember)) {
        qFatal("QPlastiqueStyle::standardPixmap() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QPixmap >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, standardPixmap)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
    }
}

int  QtScriptShell_QPlastiqueStyle::styleHint(QStyle::StyleHint  hint, const QStyleOption*  option, const QWidget*  widget, QStyleHintReturn*  returnData) const
{
    QScriptValue _q_function = __qtscript_self.property("styleHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("styleHint") & QScriptValue::QObjectMember)) {
        return QPlastiqueStyle::styleHint(hint, option, widget, returnData);
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

QRect  QtScriptShell_QPlastiqueStyle::subControlRect(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, QStyle::SubControl  sc, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("subControlRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("subControlRect") & QScriptValue::QObjectMember)) {
        return QPlastiqueStyle::subControlRect(cc, opt, sc, widget);
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

QRect  QtScriptShell_QPlastiqueStyle::subElementRect(QStyle::SubElement  element, const QStyleOption*  option, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("subElementRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("subElementRect") & QScriptValue::QObjectMember)) {
        return QPlastiqueStyle::subElementRect(element, option, widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, element)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(option))
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
    }
}

void QtScriptShell_QPlastiqueStyle::timerEvent(QTimerEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QPlastiqueStyle::timerEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QPlastiqueStyle::unpolish(QApplication*  app)
{
    QScriptValue _q_function = __qtscript_self.property("unpolish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unpolish") & QScriptValue::QObjectMember)) {
        QPlastiqueStyle::unpolish(app);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, app));
    }
}

void QtScriptShell_QPlastiqueStyle::unpolish(QWidget*  widget)
{
    QScriptValue _q_function = __qtscript_self.property("unpolish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unpolish") & QScriptValue::QObjectMember)) {
        QPlastiqueStyle::unpolish(widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, widget));
    }
}

