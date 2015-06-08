#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qwebsettings.h>
#include <QVariant>
#include <QUrl>
#include <qwebsettings.h>

static const char * const qtscript_QWebSettings_function_names[] = {
    "QWebSettings"
    // static
    , "clearIconDatabase"
    , "clearMemoryCaches"
    , "enablePersistentStorage"
    , "globalSettings"
    , "iconDatabasePath"
    , "iconForUrl"
    , "maximumPagesInCache"
    , "offlineStorageDefaultQuota"
    , "offlineStoragePath"
    , "offlineWebApplicationCachePath"
    , "offlineWebApplicationCacheQuota"
    , "setIconDatabasePath"
    , "setMaximumPagesInCache"
    , "setObjectCacheCapacities"
    , "setOfflineStorageDefaultQuota"
    , "setOfflineStoragePath"
    , "setOfflineWebApplicationCachePath"
    , "setOfflineWebApplicationCacheQuota"
    , "setWebGraphic"
    , "webGraphic"
    // prototype
    , "cssMediaType"
    , "defaultTextEncoding"
    , "fontFamily"
    , "fontSize"
    , "localStoragePath"
    , "resetAttribute"
    , "resetFontFamily"
    , "resetFontSize"
    , "setAttribute"
    , "setCSSMediaType"
    , "setDefaultTextEncoding"
    , "setFontFamily"
    , "setFontSize"
    , "setLocalStoragePath"
    , "setUserStyleSheetUrl"
    , "testAttribute"
    , "userStyleSheetUrl"
    , "toString"
};

static const char * const qtscript_QWebSettings_function_signatures[] = {
    ""
    // static
    , ""
    , ""
    , "String path"
    , ""
    , ""
    , "QUrl url"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String location"
    , "int pages"
    , "int cacheMinDeadCapacity, int cacheMaxDead, int totalCapacity"
    , "qint64 maximumSize"
    , "String path"
    , "String path"
    , "qint64 maximumSize"
    , "WebGraphic type, QPixmap graphic"
    , "WebGraphic type"
    // prototype
    , ""
    , ""
    , "FontFamily which"
    , "FontSize type"
    , ""
    , "WebAttribute attr"
    , "FontFamily which"
    , "FontSize type"
    , "WebAttribute attr, bool on"
    , "String arg__1"
    , "String encoding"
    , "FontFamily which, String family"
    , "FontSize type, int size"
    , "String path"
    , "QUrl location"
    , "WebAttribute attr"
    , ""
""
};

static const int qtscript_QWebSettings_function_lengths[] = {
    0
    // static
    , 0
    , 0
    , 1
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
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    // prototype
    , 0
    , 0
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 2
    , 2
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QWebSettings_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWebSettings::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWebSettings*)
Q_DECLARE_METATYPE(QWebSettings::WebAttribute)
Q_DECLARE_METATYPE(QWebSettings::WebGraphic)
Q_DECLARE_METATYPE(QWebSettings::FontSize)
Q_DECLARE_METATYPE(QWebSettings::FontFamily)

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
// QWebSettings::WebAttribute
//

static const QWebSettings::WebAttribute qtscript_QWebSettings_WebAttribute_values[] = {
    QWebSettings::AutoLoadImages
    , QWebSettings::JavascriptEnabled
    , QWebSettings::JavaEnabled
    , QWebSettings::PluginsEnabled
    , QWebSettings::PrivateBrowsingEnabled
    , QWebSettings::JavascriptCanOpenWindows
    , QWebSettings::JavascriptCanAccessClipboard
    , QWebSettings::DeveloperExtrasEnabled
    , QWebSettings::LinksIncludedInFocusChain
    , QWebSettings::ZoomTextOnly
    , QWebSettings::PrintElementBackgrounds
    , QWebSettings::OfflineStorageDatabaseEnabled
    , QWebSettings::OfflineWebApplicationCacheEnabled
    , QWebSettings::LocalStorageEnabled
    , QWebSettings::LocalContentCanAccessRemoteUrls
    , QWebSettings::DnsPrefetchEnabled
    , QWebSettings::XSSAuditingEnabled
    , QWebSettings::AcceleratedCompositingEnabled
    , QWebSettings::SpatialNavigationEnabled
    , QWebSettings::LocalContentCanAccessFileUrls
    , QWebSettings::TiledBackingStoreEnabled
    , QWebSettings::FrameFlatteningEnabled
    , QWebSettings::SiteSpecificQuirksEnabled
    , QWebSettings::JavascriptCanCloseWindows
    , QWebSettings::WebGLEnabled
    , QWebSettings::CSSRegionsEnabled
    , QWebSettings::HyperlinkAuditingEnabled
    , QWebSettings::CSSGridLayoutEnabled
    , QWebSettings::ScrollAnimatorEnabled
    , QWebSettings::CaretBrowsingEnabled
    , QWebSettings::NotificationsEnabled
    , QWebSettings::WebAudioEnabled
};

static const char * const qtscript_QWebSettings_WebAttribute_keys[] = {
    "AutoLoadImages"
    , "JavascriptEnabled"
    , "JavaEnabled"
    , "PluginsEnabled"
    , "PrivateBrowsingEnabled"
    , "JavascriptCanOpenWindows"
    , "JavascriptCanAccessClipboard"
    , "DeveloperExtrasEnabled"
    , "LinksIncludedInFocusChain"
    , "ZoomTextOnly"
    , "PrintElementBackgrounds"
    , "OfflineStorageDatabaseEnabled"
    , "OfflineWebApplicationCacheEnabled"
    , "LocalStorageEnabled"
    , "LocalContentCanAccessRemoteUrls"
    , "DnsPrefetchEnabled"
    , "XSSAuditingEnabled"
    , "AcceleratedCompositingEnabled"
    , "SpatialNavigationEnabled"
    , "LocalContentCanAccessFileUrls"
    , "TiledBackingStoreEnabled"
    , "FrameFlatteningEnabled"
    , "SiteSpecificQuirksEnabled"
    , "JavascriptCanCloseWindows"
    , "WebGLEnabled"
    , "CSSRegionsEnabled"
    , "HyperlinkAuditingEnabled"
    , "CSSGridLayoutEnabled"
    , "ScrollAnimatorEnabled"
    , "CaretBrowsingEnabled"
    , "NotificationsEnabled"
    , "WebAudioEnabled"
};

static QString qtscript_QWebSettings_WebAttribute_toStringHelper(QWebSettings::WebAttribute value)
{
    if ((value >= QWebSettings::AutoLoadImages) && (value <= QWebSettings::WebAudioEnabled))
        return qtscript_QWebSettings_WebAttribute_keys[static_cast<int>(value)-static_cast<int>(QWebSettings::AutoLoadImages)];
    return QString();
}

static QScriptValue qtscript_QWebSettings_WebAttribute_toScriptValue(QScriptEngine *engine, const QWebSettings::WebAttribute &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWebSettings"));
    return clazz.property(qtscript_QWebSettings_WebAttribute_toStringHelper(value));
}

static void qtscript_QWebSettings_WebAttribute_fromScriptValue(const QScriptValue &value, QWebSettings::WebAttribute &out)
{
    out = qvariant_cast<QWebSettings::WebAttribute>(value.toVariant());
}

static QScriptValue qtscript_construct_QWebSettings_WebAttribute(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QWebSettings::AutoLoadImages) && (arg <= QWebSettings::WebAudioEnabled))
        return qScriptValueFromValue(engine,  static_cast<QWebSettings::WebAttribute>(arg));
    return context->throwError(QString::fromLatin1("WebAttribute(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWebSettings_WebAttribute_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebSettings::WebAttribute value = qscriptvalue_cast<QWebSettings::WebAttribute>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebSettings_WebAttribute_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebSettings::WebAttribute value = qscriptvalue_cast<QWebSettings::WebAttribute>(context->thisObject());
    return QScriptValue(engine, qtscript_QWebSettings_WebAttribute_toStringHelper(value));
}

static QScriptValue qtscript_create_QWebSettings_WebAttribute_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWebSettings_WebAttribute,
        qtscript_QWebSettings_WebAttribute_valueOf, qtscript_QWebSettings_WebAttribute_toString);
    qScriptRegisterMetaType<QWebSettings::WebAttribute>(engine, qtscript_QWebSettings_WebAttribute_toScriptValue,
        qtscript_QWebSettings_WebAttribute_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 32; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWebSettings_WebAttribute_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWebSettings_WebAttribute_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWebSettings::WebGraphic
//

static const QWebSettings::WebGraphic qtscript_QWebSettings_WebGraphic_values[] = {
    QWebSettings::MissingImageGraphic
    , QWebSettings::MissingPluginGraphic
    , QWebSettings::DefaultFrameIconGraphic
    , QWebSettings::TextAreaSizeGripCornerGraphic
    , QWebSettings::DeleteButtonGraphic
    , QWebSettings::InputSpeechButtonGraphic
    , QWebSettings::SearchCancelButtonGraphic
    , QWebSettings::SearchCancelButtonPressedGraphic
};

static const char * const qtscript_QWebSettings_WebGraphic_keys[] = {
    "MissingImageGraphic"
    , "MissingPluginGraphic"
    , "DefaultFrameIconGraphic"
    , "TextAreaSizeGripCornerGraphic"
    , "DeleteButtonGraphic"
    , "InputSpeechButtonGraphic"
    , "SearchCancelButtonGraphic"
    , "SearchCancelButtonPressedGraphic"
};

static QString qtscript_QWebSettings_WebGraphic_toStringHelper(QWebSettings::WebGraphic value)
{
    if ((value >= QWebSettings::MissingImageGraphic) && (value <= QWebSettings::SearchCancelButtonPressedGraphic))
        return qtscript_QWebSettings_WebGraphic_keys[static_cast<int>(value)-static_cast<int>(QWebSettings::MissingImageGraphic)];
    return QString();
}

static QScriptValue qtscript_QWebSettings_WebGraphic_toScriptValue(QScriptEngine *engine, const QWebSettings::WebGraphic &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWebSettings"));
    return clazz.property(qtscript_QWebSettings_WebGraphic_toStringHelper(value));
}

static void qtscript_QWebSettings_WebGraphic_fromScriptValue(const QScriptValue &value, QWebSettings::WebGraphic &out)
{
    out = qvariant_cast<QWebSettings::WebGraphic>(value.toVariant());
}

static QScriptValue qtscript_construct_QWebSettings_WebGraphic(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QWebSettings::MissingImageGraphic) && (arg <= QWebSettings::SearchCancelButtonPressedGraphic))
        return qScriptValueFromValue(engine,  static_cast<QWebSettings::WebGraphic>(arg));
    return context->throwError(QString::fromLatin1("WebGraphic(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWebSettings_WebGraphic_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebSettings::WebGraphic value = qscriptvalue_cast<QWebSettings::WebGraphic>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebSettings_WebGraphic_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebSettings::WebGraphic value = qscriptvalue_cast<QWebSettings::WebGraphic>(context->thisObject());
    return QScriptValue(engine, qtscript_QWebSettings_WebGraphic_toStringHelper(value));
}

static QScriptValue qtscript_create_QWebSettings_WebGraphic_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWebSettings_WebGraphic,
        qtscript_QWebSettings_WebGraphic_valueOf, qtscript_QWebSettings_WebGraphic_toString);
    qScriptRegisterMetaType<QWebSettings::WebGraphic>(engine, qtscript_QWebSettings_WebGraphic_toScriptValue,
        qtscript_QWebSettings_WebGraphic_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWebSettings_WebGraphic_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWebSettings_WebGraphic_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWebSettings::FontSize
//

static const QWebSettings::FontSize qtscript_QWebSettings_FontSize_values[] = {
    QWebSettings::MinimumFontSize
    , QWebSettings::MinimumLogicalFontSize
    , QWebSettings::DefaultFontSize
    , QWebSettings::DefaultFixedFontSize
};

static const char * const qtscript_QWebSettings_FontSize_keys[] = {
    "MinimumFontSize"
    , "MinimumLogicalFontSize"
    , "DefaultFontSize"
    , "DefaultFixedFontSize"
};

static QString qtscript_QWebSettings_FontSize_toStringHelper(QWebSettings::FontSize value)
{
    if ((value >= QWebSettings::MinimumFontSize) && (value <= QWebSettings::DefaultFixedFontSize))
        return qtscript_QWebSettings_FontSize_keys[static_cast<int>(value)-static_cast<int>(QWebSettings::MinimumFontSize)];
    return QString();
}

static QScriptValue qtscript_QWebSettings_FontSize_toScriptValue(QScriptEngine *engine, const QWebSettings::FontSize &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWebSettings"));
    return clazz.property(qtscript_QWebSettings_FontSize_toStringHelper(value));
}

static void qtscript_QWebSettings_FontSize_fromScriptValue(const QScriptValue &value, QWebSettings::FontSize &out)
{
    out = qvariant_cast<QWebSettings::FontSize>(value.toVariant());
}

static QScriptValue qtscript_construct_QWebSettings_FontSize(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QWebSettings::MinimumFontSize) && (arg <= QWebSettings::DefaultFixedFontSize))
        return qScriptValueFromValue(engine,  static_cast<QWebSettings::FontSize>(arg));
    return context->throwError(QString::fromLatin1("FontSize(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWebSettings_FontSize_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebSettings::FontSize value = qscriptvalue_cast<QWebSettings::FontSize>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebSettings_FontSize_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebSettings::FontSize value = qscriptvalue_cast<QWebSettings::FontSize>(context->thisObject());
    return QScriptValue(engine, qtscript_QWebSettings_FontSize_toStringHelper(value));
}

static QScriptValue qtscript_create_QWebSettings_FontSize_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWebSettings_FontSize,
        qtscript_QWebSettings_FontSize_valueOf, qtscript_QWebSettings_FontSize_toString);
    qScriptRegisterMetaType<QWebSettings::FontSize>(engine, qtscript_QWebSettings_FontSize_toScriptValue,
        qtscript_QWebSettings_FontSize_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWebSettings_FontSize_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWebSettings_FontSize_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWebSettings::FontFamily
//

static const QWebSettings::FontFamily qtscript_QWebSettings_FontFamily_values[] = {
    QWebSettings::StandardFont
    , QWebSettings::FixedFont
    , QWebSettings::SerifFont
    , QWebSettings::SansSerifFont
    , QWebSettings::CursiveFont
    , QWebSettings::FantasyFont
};

static const char * const qtscript_QWebSettings_FontFamily_keys[] = {
    "StandardFont"
    , "FixedFont"
    , "SerifFont"
    , "SansSerifFont"
    , "CursiveFont"
    , "FantasyFont"
};

static QString qtscript_QWebSettings_FontFamily_toStringHelper(QWebSettings::FontFamily value)
{
    if ((value >= QWebSettings::StandardFont) && (value <= QWebSettings::FantasyFont))
        return qtscript_QWebSettings_FontFamily_keys[static_cast<int>(value)-static_cast<int>(QWebSettings::StandardFont)];
    return QString();
}

static QScriptValue qtscript_QWebSettings_FontFamily_toScriptValue(QScriptEngine *engine, const QWebSettings::FontFamily &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWebSettings"));
    return clazz.property(qtscript_QWebSettings_FontFamily_toStringHelper(value));
}

static void qtscript_QWebSettings_FontFamily_fromScriptValue(const QScriptValue &value, QWebSettings::FontFamily &out)
{
    out = qvariant_cast<QWebSettings::FontFamily>(value.toVariant());
}

static QScriptValue qtscript_construct_QWebSettings_FontFamily(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QWebSettings::StandardFont) && (arg <= QWebSettings::FantasyFont))
        return qScriptValueFromValue(engine,  static_cast<QWebSettings::FontFamily>(arg));
    return context->throwError(QString::fromLatin1("FontFamily(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWebSettings_FontFamily_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebSettings::FontFamily value = qscriptvalue_cast<QWebSettings::FontFamily>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebSettings_FontFamily_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebSettings::FontFamily value = qscriptvalue_cast<QWebSettings::FontFamily>(context->thisObject());
    return QScriptValue(engine, qtscript_QWebSettings_FontFamily_toStringHelper(value));
}

static QScriptValue qtscript_create_QWebSettings_FontFamily_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWebSettings_FontFamily,
        qtscript_QWebSettings_FontFamily_valueOf, qtscript_QWebSettings_FontFamily_toString);
    qScriptRegisterMetaType<QWebSettings::FontFamily>(engine, qtscript_QWebSettings_FontFamily_toScriptValue,
        qtscript_QWebSettings_FontFamily_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWebSettings_FontFamily_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWebSettings_FontFamily_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWebSettings
//

static QScriptValue qtscript_QWebSettings_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QWebSettings* _q_self = qscriptvalue_cast<QWebSettings*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWebSettings.%0(): this object is not a QWebSettings")
            .arg(qtscript_QWebSettings_function_names[_id+21]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->cssMediaType();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->defaultTextEncoding();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QWebSettings::FontFamily _q_arg0 = qscriptvalue_cast<QWebSettings::FontFamily>(context->argument(0));
        QString _q_result = _q_self->fontFamily(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QWebSettings::FontSize _q_arg0 = qscriptvalue_cast<QWebSettings::FontSize>(context->argument(0));
        int _q_result = _q_self->fontSize(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->localStoragePath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QWebSettings::WebAttribute _q_arg0 = qscriptvalue_cast<QWebSettings::WebAttribute>(context->argument(0));
        _q_self->resetAttribute(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QWebSettings::FontFamily _q_arg0 = qscriptvalue_cast<QWebSettings::FontFamily>(context->argument(0));
        _q_self->resetFontFamily(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QWebSettings::FontSize _q_arg0 = qscriptvalue_cast<QWebSettings::FontSize>(context->argument(0));
        _q_self->resetFontSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        QWebSettings::WebAttribute _q_arg0 = qscriptvalue_cast<QWebSettings::WebAttribute>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setAttribute(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setCSSMediaType(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setDefaultTextEncoding(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        QWebSettings::FontFamily _q_arg0 = qscriptvalue_cast<QWebSettings::FontFamily>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setFontFamily(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        QWebSettings::FontSize _q_arg0 = qscriptvalue_cast<QWebSettings::FontSize>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setFontSize(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setLocalStoragePath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        _q_self->setUserStyleSheetUrl(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QWebSettings::WebAttribute _q_arg0 = qscriptvalue_cast<QWebSettings::WebAttribute>(context->argument(0));
        bool _q_result = _q_self->testAttribute(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QUrl _q_result = _q_self->userStyleSheetUrl();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17: {
    QString result = QString::fromLatin1("QWebSettings");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebSettings_throw_ambiguity_error_helper(context,
        qtscript_QWebSettings_function_names[_id+21],
        qtscript_QWebSettings_function_signatures[_id+21]);
}

static QScriptValue qtscript_QWebSettings_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QWebSettings cannot be constructed"));
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QWebSettings::clearIconDatabase();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QWebSettings::clearMemoryCaches();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QWebSettings::enablePersistentStorage();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QWebSettings::enablePersistentStorage(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QWebSettings* _q_result = QWebSettings::globalSettings();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = QWebSettings::iconDatabasePath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        QIcon _q_result = QWebSettings::iconForUrl(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = QWebSettings::maximumPagesInCache();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        qint64 _q_result = QWebSettings::offlineStorageDefaultQuota();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QString _q_result = QWebSettings::offlineStoragePath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QString _q_result = QWebSettings::offlineWebApplicationCachePath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        qint64 _q_result = QWebSettings::offlineWebApplicationCacheQuota();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QWebSettings::setIconDatabasePath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QWebSettings::setMaximumPagesInCache(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QWebSettings::setObjectCacheCapacities(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        QWebSettings::setOfflineStorageDefaultQuota(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QWebSettings::setOfflineStoragePath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QWebSettings::setOfflineWebApplicationCachePath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        QWebSettings::setOfflineWebApplicationCacheQuota(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 2) {
        QWebSettings::WebGraphic _q_arg0 = qscriptvalue_cast<QWebSettings::WebGraphic>(context->argument(0));
        QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
        QWebSettings::setWebGraphic(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QWebSettings::WebGraphic _q_arg0 = qscriptvalue_cast<QWebSettings::WebGraphic>(context->argument(0));
        QPixmap _q_result = QWebSettings::webGraphic(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebSettings_throw_ambiguity_error_helper(context,
        qtscript_QWebSettings_function_names[_id],
        qtscript_QWebSettings_function_signatures[_id]);
}

QScriptValue qtscript_create_QWebSettings_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWebSettings*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWebSettings*)0));
    for (int i = 0; i < 18; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWebSettings_prototype_call, qtscript_QWebSettings_function_lengths[i+21]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWebSettings_function_names[i+21]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QWebSettings*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWebSettings_static_call, proto, qtscript_QWebSettings_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 20; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWebSettings_static_call,
            qtscript_QWebSettings_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QWebSettings_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("WebAttribute"),
        qtscript_create_QWebSettings_WebAttribute_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("WebGraphic"),
        qtscript_create_QWebSettings_WebGraphic_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FontSize"),
        qtscript_create_QWebSettings_FontSize_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FontFamily"),
        qtscript_create_QWebSettings_FontFamily_class(engine, ctor));
    return ctor;
}
