#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qpixmap.h>
#include <QVariant>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcolor.h>
#include <qdatastream.h>
#include <qimage.h>
#include <qimagereader.h>
#include <qimagewriter.h>
#include <qiodevice.h>
#include <qmatrix.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qtransform.h>
#include <qwidget.h>

#include "qtscriptshell_QPixmap.h"

static const char * const qtscript_QPixmap_function_names[] = {
    "QPixmap"
    // static
    , "defaultDepth"
    , "fromImage"
    , "fromImageReader"
    , "grabWidget"
    , "grabWindow"
    , "trueMatrix"
    // prototype
    , "alphaChannel"
    , "cacheKey"
    , "convertFromImage"
    , "copy"
    , "createHeuristicMask"
    , "createMaskFromColor"
    , "fill"
    , "hasAlpha"
    , "hasAlphaChannel"
    , "isNull"
    , "isQBitmap"
    , "load"
    , "loadFromData"
    , "mask"
    , "readFrom"
    , "rect"
    , "save"
    , "scaled"
    , "scaledToHeight"
    , "scaledToWidth"
    , "scroll"
    , "setAlphaChannel"
    , "setMask"
    , "size"
    , "toImage"
    , "transformed"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QPixmap_function_signatures[] = {
    "\nQPixmap arg__1\nQSize arg__1\nString fileName, char format, ImageConversionFlags flags\nchar xpm\nint w, int h"
    // static
    , ""
    , "QImage image, ImageConversionFlags flags"
    , "QImageReader imageReader, ImageConversionFlags flags"
    , "QWidget widget, QRect rect\nQWidget widget, int x, int y, int w, int h"
    , "WId arg__1, int x, int y, int w, int h"
    , "QMatrix m, int w, int h\nQTransform m, int w, int h"
    // prototype
    , ""
    , ""
    , "QImage img, ImageConversionFlags flags"
    , "QRect rect\nint x, int y, int width, int height"
    , "bool clipTight"
    , "QColor maskColor\nQColor maskColor, MaskMode mode"
    , "QColor fillColor\nQWidget widget, QPoint ofs\nQWidget widget, int xofs, int yofs"
    , ""
    , ""
    , ""
    , ""
    , "String fileName, char format, ImageConversionFlags flags"
    , "QByteArray data, char format, ImageConversionFlags flags"
    , ""
    , "QDataStream arg__1"
    , ""
    , "QIODevice device, char format, int quality\nString fileName, char format, int quality"
    , "QSize s, AspectRatioMode aspectMode, TransformationMode mode\nint w, int h, AspectRatioMode aspectMode, TransformationMode mode"
    , "int h, TransformationMode mode"
    , "int w, TransformationMode mode"
    , "int dx, int dy, QRect rect, QRegion exposed\nint dx, int dy, int x, int y, int width, int height, QRegion exposed"
    , "QPixmap arg__1"
    , "QBitmap arg__1"
    , ""
    , ""
    , "QMatrix arg__1, TransformationMode mode\nQTransform arg__1, TransformationMode mode"
    , "QDataStream arg__1"
""
};

static const int qtscript_QPixmap_function_lengths[] = {
    3
    // static
    , 0
    , 2
    , 2
    , 5
    , 5
    , 3
    // prototype
    , 0
    , 0
    , 2
    , 4
    , 1
    , 2
    , 3
    , 0
    , 0
    , 0
    , 0
    , 3
    , 3
    , 0
    , 1
    , 0
    , 3
    , 4
    , 2
    , 2
    , 7
    , 1
    , 1
    , 0
    , 0
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QPixmap_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPixmap::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPixmap*)
Q_DECLARE_METATYPE(QtScriptShell_QPixmap)
Q_DECLARE_METATYPE(QtScriptShell_QPixmap*)
Q_DECLARE_METATYPE(QFlags<Qt::ImageConversionFlag>)
Q_DECLARE_METATYPE(Qt::MaskMode)
Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(Qt::AspectRatioMode)
Q_DECLARE_METATYPE(Qt::TransformationMode)
Q_DECLARE_METATYPE(QRegion*)
Q_DECLARE_METATYPE(QImageReader*)
Q_DECLARE_METATYPE(WId)
Q_DECLARE_METATYPE(char**)
Q_DECLARE_METATYPE(QPaintDevice*)

//
// QPixmap
//

static QScriptValue qtscript_QPixmap_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 27;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPixmap* _q_self = qscriptvalue_cast<QPixmap*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPixmap.%0(): this object is not a QPixmap")
            .arg(qtscript_QPixmap_function_names[_id+7]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QPixmap _q_result = _q_self->alphaChannel();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->cacheKey();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
        bool _q_result = _q_self->convertFromImage(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
        QFlags<Qt::ImageConversionFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(1));
        bool _q_result = _q_self->convertFromImage(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QPixmap _q_result = _q_self->copy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        QPixmap _q_result = _q_self->copy(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QPixmap _q_result = _q_self->copy(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QBitmap _q_result = _q_self->createHeuristicMask();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        QBitmap _q_result = _q_self->createHeuristicMask(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        QBitmap _q_result = _q_self->createMaskFromColor(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        Qt::MaskMode _q_arg1 = qscriptvalue_cast<Qt::MaskMode>(context->argument(1));
        QBitmap _q_result = _q_self->createMaskFromColor(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        _q_self->fill();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        _q_self->fill(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
        _q_self->fill(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->fill(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasAlpha();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasAlphaChannel();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isQBitmap();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->load(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                bool _q_result = _q_self->load(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                QFlags<Qt::ImageConversionFlag> _q_arg2 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(2));
        bool _q_result = _q_self->load(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        bool _q_result = _q_self->loadFromData(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                bool _q_result = _q_self->loadFromData(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                QFlags<Qt::ImageConversionFlag> _q_arg2 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(2));
        bool _q_result = _q_self->loadFromData(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QBitmap _q_result = _q_self->mask();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->rect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            bool _q_result = _q_self->save(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = _q_self->save(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && context->argument(1).isString()) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    bool _q_result = _q_self->save(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    bool _q_result = _q_self->save(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && context->argument(1).isString()
            && context->argument(2).isNumber()) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    int _q_arg2 = context->argument(2).toInt32();
            bool _q_result = _q_self->save(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isString()
            && context->argument(2).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    int _q_arg2 = context->argument(2).toInt32();
            bool _q_result = _q_self->save(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        QPixmap _q_result = _q_self->scaled(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QSize>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::AspectRatioMode>() == context->argument(1).toVariant().userType())) {
            QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
            Qt::AspectRatioMode _q_arg1 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(1));
            QPixmap _q_result = _q_self->scaled(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QPixmap _q_result = _q_self->scaled(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QSize>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::AspectRatioMode>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<Qt::TransformationMode>() == context->argument(2).toVariant().userType())) {
            QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
            Qt::AspectRatioMode _q_arg1 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(1));
            Qt::TransformationMode _q_arg2 = qscriptvalue_cast<Qt::TransformationMode>(context->argument(2));
            QPixmap _q_result = _q_self->scaled(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && (qMetaTypeId<Qt::AspectRatioMode>() == context->argument(2).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            Qt::AspectRatioMode _q_arg2 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(2));
            QPixmap _q_result = _q_self->scaled(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        Qt::AspectRatioMode _q_arg2 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(2));
        Qt::TransformationMode _q_arg3 = qscriptvalue_cast<Qt::TransformationMode>(context->argument(3));
        QPixmap _q_result = _q_self->scaled(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QPixmap _q_result = _q_self->scaledToHeight(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::TransformationMode _q_arg1 = qscriptvalue_cast<Qt::TransformationMode>(context->argument(1));
        QPixmap _q_result = _q_self->scaledToHeight(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QPixmap _q_result = _q_self->scaledToWidth(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::TransformationMode _q_arg1 = qscriptvalue_cast<Qt::TransformationMode>(context->argument(1));
        QPixmap _q_result = _q_self->scaledToWidth(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
        _q_self->scroll(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
        QRegion* _q_arg3 = qscriptvalue_cast<QRegion*>(context->argument(3));
        _q_self->scroll(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        _q_self->scroll(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 7) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        QRegion* _q_arg6 = qscriptvalue_cast<QRegion*>(context->argument(6));
        _q_self->scroll(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
        _q_self->setAlphaChannel(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QBitmap _q_arg0 = qscriptvalue_cast<QBitmap>(context->argument(0));
        _q_self->setMask(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->size();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        QImage _q_result = _q_self->toImage();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QMatrix>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::TransformationMode>() == context->argument(1).toVariant().userType())) {
            QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
            Qt::TransformationMode _q_arg1 = qscriptvalue_cast<Qt::TransformationMode>(context->argument(1));
            QPixmap _q_result = _q_self->transformed(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTransform>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::TransformationMode>() == context->argument(1).toVariant().userType())) {
            QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
            Qt::TransformationMode _q_arg1 = qscriptvalue_cast<Qt::TransformationMode>(context->argument(1));
            QPixmap _q_result = _q_self->transformed(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 27: {
    QString result = QString::fromLatin1("QPixmap");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPixmap_throw_ambiguity_error_helper(context,
        qtscript_QPixmap_function_names[_id+7],
        qtscript_QPixmap_function_signatures[_id+7]);
}

static QScriptValue qtscript_QPixmap_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPixmap(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPixmap _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPixmap)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPixmap>() == context->argument(0).toVariant().userType())) {
            QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
            QtScriptShell_QPixmap _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPixmap)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QSize>() == context->argument(0).toVariant().userType())) {
            QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
            QtScriptShell_QPixmap _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPixmap)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QPixmap _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPixmap)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<char**>(context->argument(0))) {
            char** _q_arg0 = qscriptvalue_cast<char**>(context->argument(0));
            QtScriptShell_QPixmap _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPixmap)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    QtScriptShell_QPixmap _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPixmap)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QtScriptShell_QPixmap _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPixmap)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                QFlags<Qt::ImageConversionFlag> _q_arg2 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(2));
        QtScriptShell_QPixmap _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPixmap)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = QPixmap::defaultDepth();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
        QPixmap _q_result = QPixmap::fromImage(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
        QFlags<Qt::ImageConversionFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(1));
        QPixmap _q_result = QPixmap::fromImage(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QImageReader* _q_arg0 = qscriptvalue_cast<QImageReader*>(context->argument(0));
        QPixmap _q_result = QPixmap::fromImageReader(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QImageReader* _q_arg0 = qscriptvalue_cast<QImageReader*>(context->argument(0));
        QFlags<Qt::ImageConversionFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(1));
        QPixmap _q_result = QPixmap::fromImageReader(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QPixmap _q_result = QPixmap::grabWidget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && (qMetaTypeId<QRect>() == context->argument(1).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QRect _q_arg1 = qscriptvalue_cast<QRect>(context->argument(1));
            QPixmap _q_result = QPixmap::grabWidget(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && context->argument(1).isNumber()) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QPixmap _q_result = QPixmap::grabWidget(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QPixmap _q_result = QPixmap::grabWidget(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QPixmap _q_result = QPixmap::grabWidget(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        QPixmap _q_result = QPixmap::grabWidget(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        WId _q_arg0 = qscriptvalue_cast<WId>(context->argument(0));
        QPixmap _q_result = QPixmap::grabWindow(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        WId _q_arg0 = qscriptvalue_cast<WId>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QPixmap _q_result = QPixmap::grabWindow(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        WId _q_arg0 = qscriptvalue_cast<WId>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QPixmap _q_result = QPixmap::grabWindow(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        WId _q_arg0 = qscriptvalue_cast<WId>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QPixmap _q_result = QPixmap::grabWindow(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        WId _q_arg0 = qscriptvalue_cast<WId>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        QPixmap _q_result = QPixmap::grabWindow(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QMatrix>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            QMatrix _q_result = QPixmap::trueMatrix(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTransform>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            QTransform _q_result = QPixmap::trueMatrix(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPixmap_throw_ambiguity_error_helper(context,
        qtscript_QPixmap_function_names[_id],
        qtscript_QPixmap_function_signatures[_id]);
}

QScriptValue qtscript_create_QPixmap_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPixmap*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPixmap*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QPaintDevice*>()));
    for (int i = 0; i < 28; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPixmap_prototype_call, qtscript_QPixmap_function_lengths[i+7]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPixmap_function_names[i+7]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPixmap>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QPixmap*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPixmap_static_call, proto, qtscript_QPixmap_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPixmap_static_call,
            qtscript_QPixmap_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QPixmap_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
