#include "qtscriptshell_AbstractVideoWidget.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(Phonon::VideoWidget::AspectRatio)
Q_DECLARE_METATYPE(Phonon::VideoWidget::ScaleMode)

QtScriptShell_AbstractVideoWidget::QtScriptShell_AbstractVideoWidget()
    : Phonon::VideoWidgetInterface() {}

QtScriptShell_AbstractVideoWidget::~QtScriptShell_AbstractVideoWidget() {}

Phonon::VideoWidget::AspectRatio  QtScriptShell_AbstractVideoWidget::aspectRatio() const
{
    QScriptValue _q_function = __qtscript_self.property("aspectRatio");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("aspectRatio") & QScriptValue::QObjectMember)) {
        qFatal("AbstractVideoWidget::aspectRatio() is abstract!");
    } else {
        return qscriptvalue_cast<Phonon::VideoWidget::AspectRatio >(_q_function.call(__qtscript_self));
    }
}

qreal  QtScriptShell_AbstractVideoWidget::brightness() const
{
    QScriptValue _q_function = __qtscript_self.property("brightness");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("brightness") & QScriptValue::QObjectMember)) {
        qFatal("AbstractVideoWidget::brightness() is abstract!");
    } else {
        return qscriptvalue_cast<qreal >(_q_function.call(__qtscript_self));
    }
}

qreal  QtScriptShell_AbstractVideoWidget::contrast() const
{
    QScriptValue _q_function = __qtscript_self.property("contrast");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contrast") & QScriptValue::QObjectMember)) {
        qFatal("AbstractVideoWidget::contrast() is abstract!");
    } else {
        return qscriptvalue_cast<qreal >(_q_function.call(__qtscript_self));
    }
}

qreal  QtScriptShell_AbstractVideoWidget::hue() const
{
    QScriptValue _q_function = __qtscript_self.property("hue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hue") & QScriptValue::QObjectMember)) {
        qFatal("AbstractVideoWidget::hue() is abstract!");
    } else {
        return qscriptvalue_cast<qreal >(_q_function.call(__qtscript_self));
    }
}

qreal  QtScriptShell_AbstractVideoWidget::saturation() const
{
    QScriptValue _q_function = __qtscript_self.property("saturation");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("saturation") & QScriptValue::QObjectMember)) {
        qFatal("AbstractVideoWidget::saturation() is abstract!");
    } else {
        return qscriptvalue_cast<qreal >(_q_function.call(__qtscript_self));
    }
}

Phonon::VideoWidget::ScaleMode  QtScriptShell_AbstractVideoWidget::scaleMode() const
{
    QScriptValue _q_function = __qtscript_self.property("scaleMode");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("scaleMode") & QScriptValue::QObjectMember)) {
        qFatal("AbstractVideoWidget::scaleMode() is abstract!");
    } else {
        return qscriptvalue_cast<Phonon::VideoWidget::ScaleMode >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_AbstractVideoWidget::setAspectRatio(Phonon::VideoWidget::AspectRatio  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setAspectRatio");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setAspectRatio") & QScriptValue::QObjectMember)) {
        qFatal("AbstractVideoWidget::setAspectRatio() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_AbstractVideoWidget::setBrightness(qreal  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setBrightness");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setBrightness") & QScriptValue::QObjectMember)) {
        qFatal("AbstractVideoWidget::setBrightness() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_AbstractVideoWidget::setContrast(qreal  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setContrast");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setContrast") & QScriptValue::QObjectMember)) {
        qFatal("AbstractVideoWidget::setContrast() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_AbstractVideoWidget::setHue(qreal  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setHue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setHue") & QScriptValue::QObjectMember)) {
        qFatal("AbstractVideoWidget::setHue() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_AbstractVideoWidget::setSaturation(qreal  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setSaturation");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSaturation") & QScriptValue::QObjectMember)) {
        qFatal("AbstractVideoWidget::setSaturation() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_AbstractVideoWidget::setScaleMode(Phonon::VideoWidget::ScaleMode  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setScaleMode");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setScaleMode") & QScriptValue::QObjectMember)) {
        qFatal("AbstractVideoWidget::setScaleMode() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

QWidget*  QtScriptShell_AbstractVideoWidget::widget()
{
    QScriptValue _q_function = __qtscript_self.property("widget");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("widget") & QScriptValue::QObjectMember)) {
        qFatal("AbstractVideoWidget::widget() is abstract!");
    } else {
        return qscriptvalue_cast<QWidget* >(_q_function.call(__qtscript_self));
    }
}

