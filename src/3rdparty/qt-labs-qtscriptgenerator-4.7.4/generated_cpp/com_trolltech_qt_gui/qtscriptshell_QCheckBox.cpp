#include "qtscriptshell_QCheckBox.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbuttongroup.h>
#include <qbytearray.h>
#include <qcheckbox.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qinputcontext.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QActionEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QCloseEvent*)
Q_DECLARE_METATYPE(QContextMenuEvent*)
Q_DECLARE_METATYPE(QDragEnterEvent*)
Q_DECLARE_METATYPE(QDragLeaveEvent*)
Q_DECLARE_METATYPE(QDragMoveEvent*)
Q_DECLARE_METATYPE(QDropEvent*)
Q_DECLARE_METATYPE(QFocusEvent*)
Q_DECLARE_METATYPE(QHideEvent*)
Q_DECLARE_METATYPE(QInputMethodEvent*)
Q_DECLARE_METATYPE(Qt::InputMethodQuery)
Q_DECLARE_METATYPE(QKeyEvent*)
Q_DECLARE_METATYPE(QPaintDevice::PaintDeviceMetric)
Q_DECLARE_METATYPE(QMouseEvent*)
Q_DECLARE_METATYPE(QMoveEvent*)
Q_DECLARE_METATYPE(QPaintEngine*)
Q_DECLARE_METATYPE(QPaintEvent*)
Q_DECLARE_METATYPE(QResizeEvent*)
Q_DECLARE_METATYPE(QShowEvent*)
Q_DECLARE_METATYPE(QTabletEvent*)
Q_DECLARE_METATYPE(QTimerEvent*)
Q_DECLARE_METATYPE(QWheelEvent*)

QtScriptShell_QCheckBox::QtScriptShell_QCheckBox(QWidget*  parent)
    : QCheckBox(parent) {}

QtScriptShell_QCheckBox::QtScriptShell_QCheckBox(const QString&  text, QWidget*  parent)
    : QCheckBox(text, parent) {}

QtScriptShell_QCheckBox::~QtScriptShell_QCheckBox() {}

void QtScriptShell_QCheckBox::actionEvent(QActionEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("actionEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("actionEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::actionEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::changeEvent(QEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("changeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("changeEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::changeEvent(e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
    }
}

void QtScriptShell_QCheckBox::checkStateSet()
{
    QScriptValue _q_function = __qtscript_self.property("checkStateSet");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("checkStateSet") & QScriptValue::QObjectMember)) {
        QCheckBox::checkStateSet();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QCheckBox::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::closeEvent(QCloseEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("closeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("closeEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::closeEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::contextMenuEvent(QContextMenuEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("contextMenuEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contextMenuEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::contextMenuEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

int  QtScriptShell_QCheckBox::devType() const
{
    QScriptValue _q_function = __qtscript_self.property("devType");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("devType") & QScriptValue::QObjectMember)) {
        return QCheckBox::devType();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QCheckBox::dragEnterEvent(QDragEnterEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("dragEnterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragEnterEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::dragEnterEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::dragLeaveEvent(QDragLeaveEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("dragLeaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragLeaveEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::dragLeaveEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::dragMoveEvent(QDragMoveEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("dragMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragMoveEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::dragMoveEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::dropEvent(QDropEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("dropEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dropEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::dropEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::enterEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("enterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("enterEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::enterEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QCheckBox::event(QEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QCheckBox::event(e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e)));
    }
}

bool  QtScriptShell_QCheckBox::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QCheckBox::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

void QtScriptShell_QCheckBox::focusInEvent(QFocusEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("focusInEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusInEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::focusInEvent(e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
    }
}

bool  QtScriptShell_QCheckBox::focusNextPrevChild(bool  next)
{
    QScriptValue _q_function = __qtscript_self.property("focusNextPrevChild");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusNextPrevChild") & QScriptValue::QObjectMember)) {
        return QCheckBox::focusNextPrevChild(next);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, next)));
    }
}

void QtScriptShell_QCheckBox::focusOutEvent(QFocusEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("focusOutEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusOutEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::focusOutEvent(e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
    }
}

int  QtScriptShell_QCheckBox::heightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("heightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("heightForWidth") & QScriptValue::QObjectMember)) {
        return QCheckBox::heightForWidth(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

void QtScriptShell_QCheckBox::hideEvent(QHideEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("hideEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hideEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::hideEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QCheckBox::hitButton(const QPoint&  pos) const
{
    QScriptValue _q_function = __qtscript_self.property("hitButton");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hitButton") & QScriptValue::QObjectMember)) {
        return QCheckBox::hitButton(pos);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, pos)));
    }
}

void QtScriptShell_QCheckBox::inputMethodEvent(QInputMethodEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::inputMethodEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

QVariant  QtScriptShell_QCheckBox::inputMethodQuery(Qt::InputMethodQuery  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodQuery");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodQuery") & QScriptValue::QObjectMember)) {
        return QCheckBox::inputMethodQuery(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

void QtScriptShell_QCheckBox::keyPressEvent(QKeyEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("keyPressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyPressEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::keyPressEvent(e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
    }
}

void QtScriptShell_QCheckBox::keyReleaseEvent(QKeyEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("keyReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyReleaseEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::keyReleaseEvent(e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
    }
}

void QtScriptShell_QCheckBox::languageChange()
{
    QScriptValue _q_function = __qtscript_self.property("languageChange");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("languageChange") & QScriptValue::QObjectMember)) {
        QCheckBox::languageChange();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QCheckBox::leaveEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("leaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("leaveEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::leaveEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

int  QtScriptShell_QCheckBox::metric(QPaintDevice::PaintDeviceMetric  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("metric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metric") & QScriptValue::QObjectMember)) {
        return QCheckBox::metric(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

QSize  QtScriptShell_QCheckBox::minimumSizeHint() const
{
    QScriptValue _q_function = __qtscript_self.property("getMinimumSizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("getMinimumSizeHint") & QScriptValue::QObjectMember)) {
        return QCheckBox::minimumSizeHint();
    } else {
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QCheckBox::mouseDoubleClickEvent(QMouseEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("mouseDoubleClickEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseDoubleClickEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::mouseDoubleClickEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::mouseMoveEvent(QMouseEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("mouseMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseMoveEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::mouseMoveEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::mousePressEvent(QMouseEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("mousePressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mousePressEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::mousePressEvent(e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
    }
}

void QtScriptShell_QCheckBox::mouseReleaseEvent(QMouseEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("mouseReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseReleaseEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::mouseReleaseEvent(e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
    }
}

void QtScriptShell_QCheckBox::moveEvent(QMoveEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("moveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("moveEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::moveEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::nextCheckState()
{
    QScriptValue _q_function = __qtscript_self.property("nextCheckState");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("nextCheckState") & QScriptValue::QObjectMember)) {
        QCheckBox::nextCheckState();
    } else {
        _q_function.call(__qtscript_self);
    }
}

QPaintEngine*  QtScriptShell_QCheckBox::paintEngine() const
{
    QScriptValue _q_function = __qtscript_self.property("paintEngine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEngine") & QScriptValue::QObjectMember)) {
        return QCheckBox::paintEngine();
    } else {
        return qscriptvalue_cast<QPaintEngine* >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QCheckBox::paintEvent(QPaintEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("paintEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::paintEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::resizeEvent(QResizeEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("resizeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("resizeEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::resizeEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::showEvent(QShowEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("showEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("showEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::showEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::tabletEvent(QTabletEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("tabletEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("tabletEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::tabletEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCheckBox::timerEvent(QTimerEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::timerEvent(e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
    }
}

void QtScriptShell_QCheckBox::wheelEvent(QWheelEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("wheelEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("wheelEvent") & QScriptValue::QObjectMember)) {
        QCheckBox::wheelEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

