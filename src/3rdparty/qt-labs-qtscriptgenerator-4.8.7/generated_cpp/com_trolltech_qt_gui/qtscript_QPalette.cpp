#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qpalette.h>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qdatastream.h>
#include <qpalette.h>

static const char * const qtscript_QPalette_function_names[] = {
    "QPalette"
    // static
    // prototype
    , "alternateBase"
    , "base"
    , "brightText"
    , "brush"
    , "button"
    , "buttonText"
    , "cacheKey"
    , "color"
    , "currentColorGroup"
    , "dark"
    , "highlight"
    , "highlightedText"
    , "isBrushSet"
    , "isCopyOf"
    , "isEqual"
    , "light"
    , "link"
    , "linkVisited"
    , "mid"
    , "midlight"
    , "equals"
    , "readFrom"
    , "resolve"
    , "setBrush"
    , "setColor"
    , "setColorGroup"
    , "setCurrentColorGroup"
    , "shadow"
    , "text"
    , "toolTipBase"
    , "toolTipText"
    , "window"
    , "windowText"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QPalette_function_signatures[] = {
    "\nGlobalColor button\nQBrush windowText, QBrush button, QBrush light, QBrush dark, QBrush mid, QBrush text, QBrush bright_text, QBrush base, QBrush window\nQColor button\nQColor button, QColor window\nQPalette palette"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "ColorGroup cg, ColorRole cr\nColorRole cr"
    , ""
    , ""
    , ""
    , "ColorGroup cg, ColorRole cr\nColorRole cr"
    , ""
    , ""
    , ""
    , ""
    , "ColorGroup cg, ColorRole cr"
    , "QPalette p"
    , "ColorGroup cr1, ColorGroup cr2"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QPalette p"
    , "QDataStream ds"
    , "\nQPalette arg__1\nuint mask"
    , "ColorGroup cg, ColorRole cr, QBrush brush\nColorRole cr, QBrush brush"
    , "ColorGroup cg, ColorRole cr, QColor color\nColorRole cr, QColor color"
    , "ColorGroup cr, QBrush windowText, QBrush button, QBrush light, QBrush dark, QBrush mid, QBrush text, QBrush bright_text, QBrush base, QBrush window"
    , "ColorGroup cg"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QDataStream ds"
""
};

static const int qtscript_QPalette_function_lengths[] = {
    9
    // static
    // prototype
    , 0
    , 0
    , 0
    , 2
    , 0
    , 0
    , 0
    , 2
    , 0
    , 0
    , 0
    , 0
    , 2
    , 1
    , 2
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 3
    , 3
    , 10
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QPalette_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPalette::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QPalette_metaObject()
{
    return &QPalette::staticMetaObject;
}

Q_DECLARE_METATYPE(QPalette*)
Q_DECLARE_METATYPE(QPalette::ColorGroup)
Q_DECLARE_METATYPE(QPalette::ColorRole)
Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(Qt::GlobalColor)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QPalette::ColorGroup
//

static const QPalette::ColorGroup qtscript_QPalette_ColorGroup_values[] = {
    QPalette::Active
    , QPalette::Disabled
    , QPalette::Inactive
    , QPalette::NColorGroups
    , QPalette::Current
    , QPalette::All
};

static const char * const qtscript_QPalette_ColorGroup_keys[] = {
    "Active"
    , "Disabled"
    , "Inactive"
    , "NColorGroups"
    , "Current"
    , "All"
};

static QString qtscript_QPalette_ColorGroup_toStringHelper(QPalette::ColorGroup value)
{
    const QMetaObject *meta = qtscript_QPalette_metaObject();
    int idx = meta->indexOfEnumerator("ColorGroup");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QPalette_ColorGroup_toScriptValue(QScriptEngine *engine, const QPalette::ColorGroup &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPalette"));
    return clazz.property(qtscript_QPalette_ColorGroup_toStringHelper(value));
}

static void qtscript_QPalette_ColorGroup_fromScriptValue(const QScriptValue &value, QPalette::ColorGroup &out)
{
    out = qvariant_cast<QPalette::ColorGroup>(value.toVariant());
}

static QScriptValue qtscript_construct_QPalette_ColorGroup(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QPalette_metaObject();
    int idx = meta->indexOfEnumerator("ColorGroup");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QPalette::ColorGroup>(arg));
    return context->throwError(QString::fromLatin1("ColorGroup(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPalette_ColorGroup_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPalette::ColorGroup value = qscriptvalue_cast<QPalette::ColorGroup>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPalette_ColorGroup_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPalette::ColorGroup value = qscriptvalue_cast<QPalette::ColorGroup>(context->thisObject());
    return QScriptValue(engine, qtscript_QPalette_ColorGroup_toStringHelper(value));
}

static QScriptValue qtscript_create_QPalette_ColorGroup_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPalette_ColorGroup,
        qtscript_QPalette_ColorGroup_valueOf, qtscript_QPalette_ColorGroup_toString);
    qScriptRegisterMetaType<QPalette::ColorGroup>(engine, qtscript_QPalette_ColorGroup_toScriptValue,
        qtscript_QPalette_ColorGroup_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPalette_ColorGroup_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPalette_ColorGroup_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPalette::ColorRole
//

static const QPalette::ColorRole qtscript_QPalette_ColorRole_values[] = {
    QPalette::WindowText
    , QPalette::Button
    , QPalette::Light
    , QPalette::Midlight
    , QPalette::Dark
    , QPalette::Mid
    , QPalette::Text
    , QPalette::BrightText
    , QPalette::ButtonText
    , QPalette::Base
    , QPalette::Window
    , QPalette::Shadow
    , QPalette::Highlight
    , QPalette::HighlightedText
    , QPalette::Link
    , QPalette::LinkVisited
    , QPalette::AlternateBase
    , QPalette::NoRole
    , QPalette::ToolTipBase
    , QPalette::ToolTipText
    , QPalette::NColorRoles
};

static const char * const qtscript_QPalette_ColorRole_keys[] = {
    "WindowText"
    , "Button"
    , "Light"
    , "Midlight"
    , "Dark"
    , "Mid"
    , "Text"
    , "BrightText"
    , "ButtonText"
    , "Base"
    , "Window"
    , "Shadow"
    , "Highlight"
    , "HighlightedText"
    , "Link"
    , "LinkVisited"
    , "AlternateBase"
    , "NoRole"
    , "ToolTipBase"
    , "ToolTipText"
    , "NColorRoles"
};

static QString qtscript_QPalette_ColorRole_toStringHelper(QPalette::ColorRole value)
{
    const QMetaObject *meta = qtscript_QPalette_metaObject();
    int idx = meta->indexOfEnumerator("ColorRole");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QPalette_ColorRole_toScriptValue(QScriptEngine *engine, const QPalette::ColorRole &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPalette"));
    return clazz.property(qtscript_QPalette_ColorRole_toStringHelper(value));
}

static void qtscript_QPalette_ColorRole_fromScriptValue(const QScriptValue &value, QPalette::ColorRole &out)
{
    out = qvariant_cast<QPalette::ColorRole>(value.toVariant());
}

static QScriptValue qtscript_construct_QPalette_ColorRole(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QPalette_metaObject();
    int idx = meta->indexOfEnumerator("ColorRole");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QPalette::ColorRole>(arg));
    return context->throwError(QString::fromLatin1("ColorRole(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPalette_ColorRole_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPalette::ColorRole value = qscriptvalue_cast<QPalette::ColorRole>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPalette_ColorRole_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPalette::ColorRole value = qscriptvalue_cast<QPalette::ColorRole>(context->thisObject());
    return QScriptValue(engine, qtscript_QPalette_ColorRole_toStringHelper(value));
}

static QScriptValue qtscript_create_QPalette_ColorRole_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPalette_ColorRole,
        qtscript_QPalette_ColorRole_valueOf, qtscript_QPalette_ColorRole_toString);
    qScriptRegisterMetaType<QPalette::ColorRole>(engine, qtscript_QPalette_ColorRole_toScriptValue,
        qtscript_QPalette_ColorRole_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 21; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPalette_ColorRole_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPalette_ColorRole_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPalette
//

static QScriptValue qtscript_QPalette_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 34;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPalette* _q_self = qscriptvalue_cast<QPalette*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPalette.%0(): this object is not a QPalette")
            .arg(qtscript_QPalette_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->alternateBase();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->base();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->brightText();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QPalette::ColorRole _q_arg0 = qscriptvalue_cast<QPalette::ColorRole>(context->argument(0));
        QBrush _q_result = _q_self->brush(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QPalette::ColorGroup _q_arg0 = qscriptvalue_cast<QPalette::ColorGroup>(context->argument(0));
        QPalette::ColorRole _q_arg1 = qscriptvalue_cast<QPalette::ColorRole>(context->argument(1));
        QBrush _q_result = _q_self->brush(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->button();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->buttonText();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->cacheKey();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QPalette::ColorRole _q_arg0 = qscriptvalue_cast<QPalette::ColorRole>(context->argument(0));
        QColor _q_result = _q_self->color(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QPalette::ColorGroup _q_arg0 = qscriptvalue_cast<QPalette::ColorGroup>(context->argument(0));
        QPalette::ColorRole _q_arg1 = qscriptvalue_cast<QPalette::ColorRole>(context->argument(1));
        QColor _q_result = _q_self->color(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QPalette::ColorGroup _q_result = _q_self->currentColorGroup();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->dark();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->highlight();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->highlightedText();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        QPalette::ColorGroup _q_arg0 = qscriptvalue_cast<QPalette::ColorGroup>(context->argument(0));
        QPalette::ColorRole _q_arg1 = qscriptvalue_cast<QPalette::ColorRole>(context->argument(1));
        bool _q_result = _q_self->isBrushSet(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QPalette _q_arg0 = qscriptvalue_cast<QPalette>(context->argument(0));
        bool _q_result = _q_self->isCopyOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 2) {
        QPalette::ColorGroup _q_arg0 = qscriptvalue_cast<QPalette::ColorGroup>(context->argument(0));
        QPalette::ColorGroup _q_arg1 = qscriptvalue_cast<QPalette::ColorGroup>(context->argument(1));
        bool _q_result = _q_self->isEqual(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->light();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->link();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->linkVisited();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->mid();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->midlight();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QPalette _q_arg0 = qscriptvalue_cast<QPalette>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        uint _q_result = _q_self->resolve();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPalette>() == context->argument(0).toVariant().userType())) {
            QPalette _q_arg0 = qscriptvalue_cast<QPalette>(context->argument(0));
            QPalette _q_result = _q_self->resolve(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            uint _q_arg0 = context->argument(0).toUInt32();
            _q_self->resolve(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 23:
    if (context->argumentCount() == 2) {
        QPalette::ColorRole _q_arg0 = qscriptvalue_cast<QPalette::ColorRole>(context->argument(0));
        QBrush _q_arg1 = qscriptvalue_cast<QBrush>(context->argument(1));
        _q_self->setBrush(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QPalette::ColorGroup _q_arg0 = qscriptvalue_cast<QPalette::ColorGroup>(context->argument(0));
        QPalette::ColorRole _q_arg1 = qscriptvalue_cast<QPalette::ColorRole>(context->argument(1));
        QBrush _q_arg2 = qscriptvalue_cast<QBrush>(context->argument(2));
        _q_self->setBrush(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 2) {
        QPalette::ColorRole _q_arg0 = qscriptvalue_cast<QPalette::ColorRole>(context->argument(0));
        QColor _q_arg1 = qscriptvalue_cast<QColor>(context->argument(1));
        _q_self->setColor(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QPalette::ColorGroup _q_arg0 = qscriptvalue_cast<QPalette::ColorGroup>(context->argument(0));
        QPalette::ColorRole _q_arg1 = qscriptvalue_cast<QPalette::ColorRole>(context->argument(1));
        QColor _q_arg2 = qscriptvalue_cast<QColor>(context->argument(2));
        _q_self->setColor(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 10) {
        QPalette::ColorGroup _q_arg0 = qscriptvalue_cast<QPalette::ColorGroup>(context->argument(0));
        QBrush _q_arg1 = qscriptvalue_cast<QBrush>(context->argument(1));
        QBrush _q_arg2 = qscriptvalue_cast<QBrush>(context->argument(2));
        QBrush _q_arg3 = qscriptvalue_cast<QBrush>(context->argument(3));
        QBrush _q_arg4 = qscriptvalue_cast<QBrush>(context->argument(4));
        QBrush _q_arg5 = qscriptvalue_cast<QBrush>(context->argument(5));
        QBrush _q_arg6 = qscriptvalue_cast<QBrush>(context->argument(6));
        QBrush _q_arg7 = qscriptvalue_cast<QBrush>(context->argument(7));
        QBrush _q_arg8 = qscriptvalue_cast<QBrush>(context->argument(8));
        QBrush _q_arg9 = qscriptvalue_cast<QBrush>(context->argument(9));
        _q_self->setColorGroup(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7, _q_arg8, _q_arg9);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QPalette::ColorGroup _q_arg0 = qscriptvalue_cast<QPalette::ColorGroup>(context->argument(0));
        _q_self->setCurrentColorGroup(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->shadow();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->text();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->toolTipBase();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->toolTipText();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->window();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->windowText();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 34: {
    QString result = QString::fromLatin1("QPalette");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPalette_throw_ambiguity_error_helper(context,
        qtscript_QPalette_function_names[_id+1],
        qtscript_QPalette_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPalette_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPalette(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QPalette _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Qt::GlobalColor>() == context->argument(0).toVariant().userType())) {
            Qt::GlobalColor _q_arg0 = qscriptvalue_cast<Qt::GlobalColor>(context->argument(0));
            QPalette _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QColor>() == context->argument(0).toVariant().userType())) {
            QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
            QPalette _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QPalette>() == context->argument(0).toVariant().userType())) {
            QPalette _q_arg0 = qscriptvalue_cast<QPalette>(context->argument(0));
            QPalette _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        QColor _q_arg1 = qscriptvalue_cast<QColor>(context->argument(1));
        QPalette _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 9) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        QBrush _q_arg1 = qscriptvalue_cast<QBrush>(context->argument(1));
        QBrush _q_arg2 = qscriptvalue_cast<QBrush>(context->argument(2));
        QBrush _q_arg3 = qscriptvalue_cast<QBrush>(context->argument(3));
        QBrush _q_arg4 = qscriptvalue_cast<QBrush>(context->argument(4));
        QBrush _q_arg5 = qscriptvalue_cast<QBrush>(context->argument(5));
        QBrush _q_arg6 = qscriptvalue_cast<QBrush>(context->argument(6));
        QBrush _q_arg7 = qscriptvalue_cast<QBrush>(context->argument(7));
        QBrush _q_arg8 = qscriptvalue_cast<QBrush>(context->argument(8));
        QPalette _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7, _q_arg8);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPalette_throw_ambiguity_error_helper(context,
        qtscript_QPalette_function_names[_id],
        qtscript_QPalette_function_signatures[_id]);
}

QScriptValue qtscript_create_QPalette_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPalette*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPalette*)0));
    for (int i = 0; i < 35; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPalette_prototype_call, qtscript_QPalette_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPalette_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPalette>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QPalette*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPalette_static_call, proto, qtscript_QPalette_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ColorGroup"),
        qtscript_create_QPalette_ColorGroup_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ColorRole"),
        qtscript_create_QPalette_ColorRole_class(engine, ctor));
    return ctor;
}
