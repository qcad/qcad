#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qgl.h>
#include <QImage>
#include <QPixmap>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgl.h>
#include <qglcolormap.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qimage.h>
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
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QGLWidget.h"

static const char * const qtscript_QGLWidget_function_names[] = {
    "QGLWidget"
    // static
    , "convertToGLFormat"
    // prototype
    , "colormap"
    , "context"
    , "doneCurrent"
    , "doubleBuffer"
    , "format"
    , "grabFrameBuffer"
    , "isSharing"
    , "isValid"
    , "makeCurrent"
    , "makeOverlayCurrent"
    , "overlayContext"
    , "qglClearColor"
    , "qglColor"
    , "renderPixmap"
    , "renderText"
    , "setColormap"
    , "swapBuffers"
    , "toString"
};

static const char * const qtscript_QGLWidget_function_signatures[] = {
    "QGLContext context, QWidget parent, QGLWidget shareWidget, WindowFlags f\nQWidget parent, QGLWidget shareWidget, WindowFlags f\nQGLFormat format, QWidget parent, QGLWidget shareWidget, WindowFlags f"
    // static
    , "QImage img"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , "bool withAlpha"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QColor c"
    , "QColor c"
    , "int w, int h, bool useContext"
    , "double x, double y, double z, String str, QFont fnt\nint x, int y, String str, QFont fnt"
    , "QGLColormap map"
    , ""
""
};

static const int qtscript_QGLWidget_function_lengths[] = {
    4
    // static
    , 1
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 3
    , 5
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QGLWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGLWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGLWidget*)
Q_DECLARE_METATYPE(QtScriptShell_QGLWidget*)
Q_DECLARE_METATYPE(QGLColormap)
Q_DECLARE_METATYPE(QGLContext*)
Q_DECLARE_METATYPE(QGLFormat)
Q_DECLARE_METATYPE(const QGLContext*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(const QGLWidget*)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)

//
// QGLWidget
//

static QScriptValue qtscript_QGLWidget_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 17;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGLWidget* _q_self = qscriptvalue_cast<QGLWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGLWidget.%0(): this object is not a QGLWidget")
            .arg(qtscript_QGLWidget_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        const QGLColormap& _q_result = _q_self->colormap();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QGLContext* _q_result = _q_self->context();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->doneCurrent();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->doubleBuffer();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QGLFormat _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QImage _q_result = _q_self->grabFrameBuffer();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        QImage _q_result = _q_self->grabFrameBuffer(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSharing();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        _q_self->makeCurrent();
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        _q_self->makeOverlayCurrent();
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        const QGLContext* _q_result = const_cast<const QGLContext*>(_q_self->overlayContext());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        _q_self->qglClearColor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        _q_self->qglColor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QPixmap _q_result = _q_self->renderPixmap();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QPixmap _q_result = _q_self->renderPixmap(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QPixmap _q_result = _q_self->renderPixmap(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_arg2 = context->argument(2).toBoolean();
        QPixmap _q_result = _q_self->renderPixmap(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QString _q_arg2 = context->argument(2).toString();
        _q_self->renderText(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isString()) {
            double _q_arg0 = context->argument(0).toNumber();
            double _q_arg1 = context->argument(1).toNumber();
            double _q_arg2 = context->argument(2).toNumber();
            QString _q_arg3 = context->argument(3).toString();
            _q_self->renderText(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isString()
            && (qMetaTypeId<QFont>() == context->argument(3).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QString _q_arg2 = context->argument(2).toString();
            QFont _q_arg3 = qscriptvalue_cast<QFont>(context->argument(3));
            _q_self->renderText(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 5) {
        double _q_arg0 = context->argument(0).toNumber();
        double _q_arg1 = context->argument(1).toNumber();
        double _q_arg2 = context->argument(2).toNumber();
        QString _q_arg3 = context->argument(3).toString();
        QFont _q_arg4 = qscriptvalue_cast<QFont>(context->argument(4));
        _q_self->renderText(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QGLColormap _q_arg0 = qscriptvalue_cast<QGLColormap>(context->argument(0));
        _q_self->setColormap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        _q_self->swapBuffers();
        return context->engine()->undefinedValue();
    }
    break;

    case 17: {
    QString result = QString::fromLatin1("QGLWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLWidget_throw_ambiguity_error_helper(context,
        qtscript_QGLWidget_function_names[_id+2],
        qtscript_QGLWidget_function_signatures[_id+2]);
}

static QScriptValue qtscript_QGLWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGLWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGLWidget* _q_cpp_result = new QtScriptShell_QGLWidget();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QGLContext*>(context->argument(0))) {
            QGLContext* _q_arg0 = qscriptvalue_cast<QGLContext*>(context->argument(0));
            QtScriptShell_QGLWidget* _q_cpp_result = new QtScriptShell_QGLWidget(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QGLWidget* _q_cpp_result = new QtScriptShell_QGLWidget(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QGLFormat>() == context->argument(0).toVariant().userType())) {
            QGLFormat _q_arg0 = qscriptvalue_cast<QGLFormat>(context->argument(0));
            QtScriptShell_QGLWidget* _q_cpp_result = new QtScriptShell_QGLWidget(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QGLContext*>(context->argument(0))
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            QGLContext* _q_arg0 = qscriptvalue_cast<QGLContext*>(context->argument(0));
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            QtScriptShell_QGLWidget* _q_cpp_result = new QtScriptShell_QGLWidget(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && qscriptvalue_cast<const QGLWidget*>(context->argument(1))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            const QGLWidget* _q_arg1 = qscriptvalue_cast<const QGLWidget*>(context->argument(1));
            QtScriptShell_QGLWidget* _q_cpp_result = new QtScriptShell_QGLWidget(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QGLFormat>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            QGLFormat _q_arg0 = qscriptvalue_cast<QGLFormat>(context->argument(0));
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            QtScriptShell_QGLWidget* _q_cpp_result = new QtScriptShell_QGLWidget(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<QGLContext*>(context->argument(0))
            && qscriptvalue_cast<QWidget*>(context->argument(1))
            && qscriptvalue_cast<const QGLWidget*>(context->argument(2))) {
            QGLContext* _q_arg0 = qscriptvalue_cast<QGLContext*>(context->argument(0));
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            const QGLWidget* _q_arg2 = qscriptvalue_cast<const QGLWidget*>(context->argument(2));
            QtScriptShell_QGLWidget* _q_cpp_result = new QtScriptShell_QGLWidget(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && qscriptvalue_cast<const QGLWidget*>(context->argument(1))
            && (qMetaTypeId<QFlags<Qt::WindowType> >() == context->argument(2).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            const QGLWidget* _q_arg1 = qscriptvalue_cast<const QGLWidget*>(context->argument(1));
            QFlags<Qt::WindowType> _q_arg2 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(2));
            QtScriptShell_QGLWidget* _q_cpp_result = new QtScriptShell_QGLWidget(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QGLFormat>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QWidget*>(context->argument(1))
            && qscriptvalue_cast<const QGLWidget*>(context->argument(2))) {
            QGLFormat _q_arg0 = qscriptvalue_cast<QGLFormat>(context->argument(0));
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            const QGLWidget* _q_arg2 = qscriptvalue_cast<const QGLWidget*>(context->argument(2));
            QtScriptShell_QGLWidget* _q_cpp_result = new QtScriptShell_QGLWidget(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 4) {
        if (qscriptvalue_cast<QGLContext*>(context->argument(0))
            && qscriptvalue_cast<QWidget*>(context->argument(1))
            && qscriptvalue_cast<const QGLWidget*>(context->argument(2))
            && (qMetaTypeId<QFlags<Qt::WindowType> >() == context->argument(3).toVariant().userType())) {
            QGLContext* _q_arg0 = qscriptvalue_cast<QGLContext*>(context->argument(0));
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            const QGLWidget* _q_arg2 = qscriptvalue_cast<const QGLWidget*>(context->argument(2));
            QFlags<Qt::WindowType> _q_arg3 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(3));
            QtScriptShell_QGLWidget* _q_cpp_result = new QtScriptShell_QGLWidget(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QGLFormat>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QWidget*>(context->argument(1))
            && qscriptvalue_cast<const QGLWidget*>(context->argument(2))
            && (qMetaTypeId<QFlags<Qt::WindowType> >() == context->argument(3).toVariant().userType())) {
            QGLFormat _q_arg0 = qscriptvalue_cast<QGLFormat>(context->argument(0));
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            const QGLWidget* _q_arg2 = qscriptvalue_cast<const QGLWidget*>(context->argument(2));
            QFlags<Qt::WindowType> _q_arg3 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(3));
            QtScriptShell_QGLWidget* _q_cpp_result = new QtScriptShell_QGLWidget(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
        QImage _q_result = QGLWidget::convertToGLFormat(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLWidget_throw_ambiguity_error_helper(context,
        qtscript_QGLWidget_function_names[_id],
        qtscript_QGLWidget_function_signatures[_id]);
}

static QScriptValue qtscript_QGLWidget_toScriptValue(QScriptEngine *engine, QGLWidget* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGLWidget_fromScriptValue(const QScriptValue &value, QGLWidget* &out)
{
    out = qobject_cast<QGLWidget*>(value.toQObject());
}

QScriptValue qtscript_create_QGLWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGLWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGLWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 18; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGLWidget_prototype_call, qtscript_QGLWidget_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGLWidget_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGLWidget*>(engine, qtscript_QGLWidget_toScriptValue, 
        qtscript_QGLWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGLWidget_static_call, proto, qtscript_QGLWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGLWidget_static_call,
            qtscript_QGLWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QGLWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
