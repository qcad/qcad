#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qbytearray.h>
#include <QNoImplicitBoolCast>
#include <QVariant>
#include <qbytearray.h>
#include <qdatastream.h>
#include <qlist.h>

static const char * const qtscript_QByteArray_function_names[] = {
    "QByteArray"
    // static
    , "fromBase64"
    , "fromHex"
    , "fromInt"
    , "fromLongLong"
    , "fromPercentEncoding"
    , "number"
    // prototype
    , "append"
    , "appendByte"
    , "at"
    , "capacity"
    , "chop"
    , "clear"
    , "count"
    , "endsWith"
    , "fill"
    , "indexOf"
    , "indexOfByte"
    , "insert"
    , "insertByte"
    , "isEmpty"
    , "isNull"
    , "isSharedWith"
    , "lastIndexOf"
    , "lastIndexOfByte"
    , "left"
    , "leftJustified"
    , "length"
    , "mid"
    , "operator_assign"
    , "equals"
    , "operator_less"
    , "prepend"
    , "prependByte"
    , "readFrom"
    , "remove"
    , "repeated"
    , "replace"
    , "reserve"
    , "resize"
    , "right"
    , "rightJustified"
    , "setDouble"
    , "setFloat"
    , "setInt"
    , "setLongLong"
    , "setRawData"
    , "setShort"
    , "simplified"
    , "size"
    , "split"
    , "squeeze"
    , "startsWith"
    , "toBase64"
    , "toDouble"
    , "toFloat"
    , "toHex"
    , "toInt"
    , "toLower"
    , "toPercentEncoding"
    , "toUShort"
    , "toUpper"
    , "trimmed"
    , "truncate"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QByteArray_function_signatures[] = {
    "\nQByteArray arg__1\nchar arg__1\nint size, char c"
    // static
    , "QByteArray base64"
    , "QByteArray hexEncoded"
    , "int arg__1, int base"
    , "qlonglong arg__1, int base"
    , "QByteArray pctEncoded, char percent"
    , "double arg__1, char f, int prec"
    // prototype
    , "QByteArray a\nString s\nchar s, int len"
    , "char c"
    , "int i"
    , ""
    , "int n"
    , ""
    , "char c\nQByteArray a"
    , "char c\nQByteArray a"
    , "char c, int size"
    , "QByteArray a, int from\nString s, int from"
    , "char c, int from"
    , "int i, QByteArray a\nint i, String s\nint i, char s, int len"
    , "int i, char c"
    , ""
    , ""
    , "QByteArray other"
    , "QByteArray a, int from\nString s, int from"
    , "char c, int from"
    , "int len"
    , "int width, char fill, bool truncate"
    , ""
    , "int index, int len"
    , "QByteArray arg__1"
    , "QByteArray a2\nString s2"
    , "QByteArray a2\nString s2"
    , "QByteArray a\nchar s, int len"
    , "char c"
    , "QDataStream arg__1"
    , "int index, int len"
    , "int times"
    , "char before, char after\nchar before, QByteArray after\nchar c, String after\nQByteArray before, QByteArray after\nString before, QByteArray after\nchar before, int bsize, char after, int asize\nint index, int len, QByteArray s\nint index, int len, char s, int alen"
    , "int size"
    , "int size"
    , "int len"
    , "int width, char fill, bool truncate"
    , "double arg__1, char f, int prec"
    , "float arg__1, char f, int prec"
    , "int arg__1, int base"
    , "qlonglong arg__1, int base"
    , "char a, uint n"
    , "short arg__1, int base"
    , ""
    , ""
    , "char sep"
    , ""
    , "char c\nQByteArray a"
    , ""
    , ""
    , ""
    , ""
    , "int base"
    , ""
    , "QByteArray exclude, QByteArray include, char percent"
    , "int base"
    , ""
    , ""
    , "int pos"
    , "QDataStream arg__1"
""
};

static const int qtscript_QByteArray_function_lengths[] = {
    2
    // static
    , 1
    , 1
    , 2
    , 2
    , 2
    , 3
    // prototype
    , 2
    , 1
    , 1
    , 0
    , 1
    , 0
    , 1
    , 1
    , 2
    , 2
    , 2
    , 3
    , 2
    , 0
    , 0
    , 1
    , 2
    , 2
    , 1
    , 3
    , 0
    , 2
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 2
    , 1
    , 4
    , 1
    , 1
    , 1
    , 3
    , 3
    , 3
    , 2
    , 2
    , 2
    , 2
    , 0
    , 0
    , 1
    , 0
    , 1
    , 0
    , 1
    , 1
    , 0
    , 2
    , 0
    , 3
    , 2
    , 0
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QByteArray_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QByteArray::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QByteArray*)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(QList<QByteArray>)


    Q_DECLARE_METATYPE(QScriptValue)
    
//
// QByteArray
//

static QScriptValue qtscript_QByteArray_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 58;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QByteArray* _q_self = qscriptvalue_cast<QByteArray*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QByteArray.%0(): this object is not a QByteArray")
            .arg(qtscript_QByteArray_function_names[_id+7]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            _q_self->append(_q_arg0);
            return context->thisObject();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->append(_q_arg0);
            return context->thisObject();
        }
    }
    if (context->argumentCount() == 2) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QByteArray _q_result = _q_self->append(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
        _q_self->append(_q_arg0);
        return context->thisObject();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {

        // TEMPLATE - core.convert_int_arg_and_check_range - START
          int _q_arg0 = context->argument(0).toInt32();
          if ((_q_arg0 < 0) || (_q_self->size() < _q_arg0)) {
              return context->throwError(QScriptContext::RangeError,
                                         QString::fromLatin1("QByteArray::at(): index out of range"));
          }
    // TEMPLATE - core.convert_int_arg_and_check_range - END
                char _q_result = _q_self->at(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->capacity();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->chop(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<char>() == context->argument(0).toVariant().userType())) {
            char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
            int _q_result = _q_self->count(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            int _q_result = _q_self->count(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<char>() == context->argument(0).toVariant().userType())) {
            char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
            bool _q_result = _q_self->endsWith(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            bool _q_result = _q_self->endsWith(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
        _q_self->fill(_q_arg0);
        return context->thisObject();
    }
    if (context->argumentCount() == 2) {
        char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->fill(_q_arg0, _q_arg1);
        return context->thisObject();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            int _q_result = _q_self->indexOf(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            int _q_result = _q_self->indexOf(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_result = _q_self->indexOf(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            int _q_arg1 = context->argument(1).toInt32();
            int _q_result = _q_self->indexOf(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
        int _q_result = _q_self->indexOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->indexOf(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isNumber()
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            _q_self->insert(_q_arg0, _q_arg1);
            return context->thisObject();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isString()) {
            int _q_arg0 = context->argument(0).toInt32();
            QString _q_arg1 = context->argument(1).toString();
            _q_self->insert(_q_arg0, _q_arg1);
            return context->thisObject();
        }
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        char* _q_arg1 = qscriptvalue_cast<char*>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QByteArray _q_result = _q_self->insert(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
        _q_self->insert(_q_arg0, _q_arg1);
        return context->thisObject();
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        bool _q_result = _q_self->isSharedWith(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            int _q_result = _q_self->lastIndexOf(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            int _q_result = _q_self->lastIndexOf(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_result = _q_self->lastIndexOf(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            int _q_arg1 = context->argument(1).toInt32();
            int _q_result = _q_self->lastIndexOf(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
        int _q_result = _q_self->lastIndexOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->lastIndexOf(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QByteArray _q_result = _q_self->left(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QByteArray _q_result = _q_self->leftJustified(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
        QByteArray _q_result = _q_self->leftJustified(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
        bool _q_arg2 = context->argument(2).toBoolean();
        QByteArray _q_result = _q_self->leftJustified(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->length();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QByteArray _q_result = _q_self->mid(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QByteArray _q_result = _q_self->mid(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_result = _q_self->operator=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            bool _q_result = _q_self->operator==(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = _q_self->operator==(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            bool _q_result = _q_self->operator<(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = _q_self->operator<(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->prepend(_q_arg0);
        return context->thisObject();
    }
    if (context->argumentCount() == 2) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QByteArray _q_result = _q_self->prepend(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
        _q_self->prepend(_q_arg0);
        return context->thisObject();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->remove(_q_arg0, _q_arg1);
        return context->thisObject();
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QByteArray _q_result = _q_self->repeated(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<char>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<char>() == context->argument(1).toVariant().userType())) {
            char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
            char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
            _q_self->replace(_q_arg0, _q_arg1);
            return context->thisObject();
        } else if ((qMetaTypeId<char>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            _q_self->replace(_q_arg0, _q_arg1);
            return context->thisObject();
        } else if ((qMetaTypeId<char>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            _q_self->replace(_q_arg0, _q_arg1);
            return context->thisObject();
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            _q_self->replace(_q_arg0, _q_arg1);
            return context->thisObject();
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            _q_self->replace(_q_arg0, _q_arg1);
            return context->thisObject();
        }
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QByteArray _q_arg2 = qscriptvalue_cast<QByteArray>(context->argument(2));
        _q_self->replace(_q_arg0, _q_arg1, _q_arg2);
        return context->thisObject();
    }
    if (context->argumentCount() == 4) {
        if (qscriptvalue_cast<char*>(context->argument(0))
            && context->argument(1).isNumber()
            && qscriptvalue_cast<char*>(context->argument(2))
            && context->argument(3).isNumber()) {
            char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            char* _q_arg2 = qscriptvalue_cast<char*>(context->argument(2));
            int _q_arg3 = context->argument(3).toInt32();
            QByteArray _q_result = _q_self->replace(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && qscriptvalue_cast<char*>(context->argument(2))
            && context->argument(3).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            char* _q_arg2 = qscriptvalue_cast<char*>(context->argument(2));
            int _q_arg3 = context->argument(3).toInt32();
            QByteArray _q_result = _q_self->replace(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->reserve(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->resize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QByteArray _q_result = _q_self->right(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QByteArray _q_result = _q_self->rightJustified(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
        QByteArray _q_result = _q_self->rightJustified(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
        bool _q_arg2 = context->argument(2).toBoolean();
        QByteArray _q_result = _q_self->rightJustified(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        double _q_arg0 = context->argument(0).toNumber();
        _q_self->setNum(_q_arg0);
        return context->thisObject();
    }
    if (context->argumentCount() == 2) {
        double _q_arg0 = context->argument(0).toNumber();
        char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
        _q_self->setNum(_q_arg0, _q_arg1);
        return context->thisObject();
    }
    if (context->argumentCount() == 3) {
        double _q_arg0 = context->argument(0).toNumber();
        char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->setNum(_q_arg0, _q_arg1, _q_arg2);
        return context->thisObject();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        _q_self->setNum(_q_arg0);
        return context->thisObject();
    }
    if (context->argumentCount() == 2) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
        _q_self->setNum(_q_arg0, _q_arg1);
        return context->thisObject();
    }
    if (context->argumentCount() == 3) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->setNum(_q_arg0, _q_arg1, _q_arg2);
        return context->thisObject();
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setNum(_q_arg0);
        return context->thisObject();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setNum(_q_arg0, _q_arg1);
        return context->thisObject();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        qlonglong _q_arg0 = qscriptvalue_cast<qlonglong>(context->argument(0));
        _q_self->setNum(_q_arg0);
        return context->thisObject();
    }
    if (context->argumentCount() == 2) {
        qlonglong _q_arg0 = qscriptvalue_cast<qlonglong>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setNum(_q_arg0, _q_arg1);
        return context->thisObject();
    }
    break;

    case 39:
    if (context->argumentCount() == 2) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        uint _q_arg1 = context->argument(1).toUInt32();
        QByteArray _q_result = _q_self->setRawData(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        short _q_arg0 = qscriptvalue_cast<short>(context->argument(0));
        _q_self->setNum(_q_arg0);
        return context->thisObject();
    }
    if (context->argumentCount() == 2) {
        short _q_arg0 = qscriptvalue_cast<short>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setNum(_q_arg0, _q_arg1);
        return context->thisObject();
    }
    break;

    case 41:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->simplified();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 42:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->size();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 43:
    if (context->argumentCount() == 1) {
        char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
        QList<QByteArray> _q_result = _q_self->split(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 44:
    if (context->argumentCount() == 0) {
        _q_self->squeeze();
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<char>() == context->argument(0).toVariant().userType())) {
            char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
            bool _q_result = _q_self->startsWith(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            bool _q_result = _q_self->startsWith(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 46:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->toBase64();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 47:
    if (context->argumentCount() == 0) {

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg0 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                  double _q_result = _q_self->toDouble(_q_arg0);
        
          // TEMPLATE - core.convert_to_null_or_primitive - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = QScriptValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_primitive - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 48:
    if (context->argumentCount() == 0) {

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg0 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                  float _q_result = _q_self->toFloat(_q_arg0);
        
          // TEMPLATE - core.convert_to_null_or_primitive - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = QScriptValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_primitive - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 49:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->toHex();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 50:
    if (context->argumentCount() == 0) {

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg0 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                  int _q_result = _q_self->toInt(_q_arg0);
        
          // TEMPLATE - core.convert_to_null_or_primitive - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = QScriptValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_primitive - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    if (context->argumentCount() == 1) {

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg0 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                  int _q_arg1 = context->argument(0).toInt32();
        int _q_result = _q_self->toInt(_q_arg0, _q_arg1);
        
          // TEMPLATE - core.convert_to_null_or_primitive - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = QScriptValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_primitive - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 51:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->toLower();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 52:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->toPercentEncoding();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_result = _q_self->toPercentEncoding(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
        QByteArray _q_result = _q_self->toPercentEncoding(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
        char _q_arg2 = qscriptvalue_cast<char>(context->argument(2));
        QByteArray _q_result = _q_self->toPercentEncoding(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 53:
    if (context->argumentCount() == 0) {

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg0 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                  ushort _q_result = _q_self->toUShort(_q_arg0);
        
          // TEMPLATE - core.convert_to_null_or_primitive - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = QScriptValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_primitive - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    if (context->argumentCount() == 1) {

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg0 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                  int _q_arg1 = context->argument(0).toInt32();
        ushort _q_result = _q_self->toUShort(_q_arg0, _q_arg1);
        
          // TEMPLATE - core.convert_to_null_or_primitive - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = QScriptValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_primitive - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 54:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->toUpper();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 55:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->trimmed();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 56:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->truncate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 57:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 58: {
    QString result = QString::fromLatin1("QByteArray");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QByteArray_throw_ambiguity_error_helper(context,
        qtscript_QByteArray_function_names[_id+7],
        qtscript_QByteArray_function_signatures[_id+7]);
}

static QScriptValue qtscript_QByteArray_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QByteArray(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QByteArray _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QByteArray _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg0 = context->argument(0).toString().toLatin1();
          const char * _q_arg0 = tmp__q_arg0.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    QByteArray _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
        QByteArray _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_result = QByteArray::fromBase64(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_result = QByteArray::fromHex(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QByteArray _q_result = QByteArray::number(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QByteArray _q_result = QByteArray::number(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        qlonglong _q_arg0 = qscriptvalue_cast<qlonglong>(context->argument(0));
        QByteArray _q_result = QByteArray::number(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        qlonglong _q_arg0 = qscriptvalue_cast<qlonglong>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QByteArray _q_result = QByteArray::number(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_result = QByteArray::fromPercentEncoding(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
        QByteArray _q_result = QByteArray::fromPercentEncoding(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        double _q_arg0 = context->argument(0).toNumber();
        QByteArray _q_result = QByteArray::number(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        double _q_arg0 = context->argument(0).toNumber();
        char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
        QByteArray _q_result = QByteArray::number(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        double _q_arg0 = context->argument(0).toNumber();
        char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QByteArray _q_result = QByteArray::number(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QByteArray_throw_ambiguity_error_helper(context,
        qtscript_QByteArray_function_names[_id],
        qtscript_QByteArray_function_signatures[_id]);
}

QScriptValue qtscript_create_QByteArray_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QByteArray*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QByteArray*)0));
    for (int i = 0; i < 59; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QByteArray_prototype_call, qtscript_QByteArray_function_lengths[i+7]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QByteArray_function_names[i+7]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QByteArray>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QByteArray*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QByteArray_static_call, proto, qtscript_QByteArray_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QByteArray_static_call,
            qtscript_QByteArray_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QByteArray_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
