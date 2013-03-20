#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qwebpage.h>
#include <QVariant>
#include <qaction.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qlist.h>
#include <qmenu.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qobject.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>
#include <qstringlist.h>
#include <qundostack.h>
#include <qurl.h>
#include <qwebframe.h>
#include <qwebpage.h>
#include <qwebpluginfactory.h>
#include <qwebsettings.h>
#include <qwidget.h>

#include "qtscriptshell_QWebPage.h"

static const char * const qtscript_QWebPage_function_names[] = {
    "QWebPage"
    // static
    // prototype
    , "action"
    , "bytesReceived"
    , "createStandardContextMenu"
    , "currentFrame"
    , "extension"
    , "findText"
    , "focusNextPrevChild"
    , "frameAt"
    , "history"
    , "inputMethodQuery"
    , "mainFrame"
    , "networkAccessManager"
    , "pluginFactory"
    , "setNetworkAccessManager"
    , "setPluginFactory"
    , "setView"
    , "settings"
    , "supportsExtension"
    , "swallowContextMenuEvent"
    , "totalBytes"
    , "triggerAction"
    , "undoStack"
    , "updatePositionDependentActions"
    , "view"
    , "toString"
};

static const char * const qtscript_QWebPage_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "WebAction action"
    , ""
    , ""
    , ""
    , "Extension extension, QWebPage_ExtensionOption option, QWebPage_ExtensionReturn output"
    , "String subString, FindFlags options"
    , "bool next"
    , "QPoint pos"
    , ""
    , "InputMethodQuery property"
    , ""
    , ""
    , ""
    , "QNetworkAccessManager manager"
    , "QWebPluginFactory factory"
    , "QWidget view"
    , ""
    , "Extension extension"
    , "QContextMenuEvent event"
    , ""
    , "WebAction action, bool checked"
    , ""
    , "QPoint pos"
    , ""
""
};

static const int qtscript_QWebPage_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 0
    , 0
    , 3
    , 2
    , 1
    , 1
    , 0
    , 1
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 0
    , 1
    , 1
    , 0
    , 2
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QWebPage_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWebPage::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QWebPage_metaObject()
{
    return &QWebPage::staticMetaObject;
}

Q_DECLARE_METATYPE(QWebPage*)
Q_DECLARE_METATYPE(QtScriptShell_QWebPage*)
Q_DECLARE_METATYPE(QWebPage::ErrorDomain)
Q_DECLARE_METATYPE(QWebPage::NavigationType)
Q_DECLARE_METATYPE(QWebPage::WebAction)
Q_DECLARE_METATYPE(QWebPage::WebWindowType)
Q_DECLARE_METATYPE(QWebPage::FindFlag)
Q_DECLARE_METATYPE(QFlags<QWebPage::FindFlag>)
Q_DECLARE_METATYPE(QWebPage::Extension)
Q_DECLARE_METATYPE(QWebPage::LinkDelegationPolicy)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QMenu*)
Q_DECLARE_METATYPE(QWebFrame*)
Q_DECLARE_METATYPE(QWebPage::ExtensionOption*)
Q_DECLARE_METATYPE(QWebPage::ExtensionReturn*)
Q_DECLARE_METATYPE(QWebHistory*)
Q_DECLARE_METATYPE(Qt::InputMethodQuery)
Q_DECLARE_METATYPE(QNetworkAccessManager*)
Q_DECLARE_METATYPE(QWebPluginFactory*)
Q_DECLARE_METATYPE(QWebSettings*)
Q_DECLARE_METATYPE(QContextMenuEvent*)
Q_DECLARE_METATYPE(QUndoStack*)

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

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QWebPage::ErrorDomain
//

static const QWebPage::ErrorDomain qtscript_QWebPage_ErrorDomain_values[] = {
    QWebPage::QtNetwork
    , QWebPage::Http
    , QWebPage::WebKit
};

static const char * const qtscript_QWebPage_ErrorDomain_keys[] = {
    "QtNetwork"
    , "Http"
    , "WebKit"
};

static QString qtscript_QWebPage_ErrorDomain_toStringHelper(QWebPage::ErrorDomain value)
{
    if ((value >= QWebPage::QtNetwork) && (value <= QWebPage::WebKit))
        return qtscript_QWebPage_ErrorDomain_keys[static_cast<int>(value)-static_cast<int>(QWebPage::QtNetwork)];
    return QString();
}

static QScriptValue qtscript_QWebPage_ErrorDomain_toScriptValue(QScriptEngine *engine, const QWebPage::ErrorDomain &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWebPage"));
    return clazz.property(qtscript_QWebPage_ErrorDomain_toStringHelper(value));
}

static void qtscript_QWebPage_ErrorDomain_fromScriptValue(const QScriptValue &value, QWebPage::ErrorDomain &out)
{
    out = qvariant_cast<QWebPage::ErrorDomain>(value.toVariant());
}

static QScriptValue qtscript_construct_QWebPage_ErrorDomain(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QWebPage::QtNetwork) && (arg <= QWebPage::WebKit))
        return qScriptValueFromValue(engine,  static_cast<QWebPage::ErrorDomain>(arg));
    return context->throwError(QString::fromLatin1("ErrorDomain(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWebPage_ErrorDomain_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::ErrorDomain value = qscriptvalue_cast<QWebPage::ErrorDomain>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebPage_ErrorDomain_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::ErrorDomain value = qscriptvalue_cast<QWebPage::ErrorDomain>(context->thisObject());
    return QScriptValue(engine, qtscript_QWebPage_ErrorDomain_toStringHelper(value));
}

static QScriptValue qtscript_create_QWebPage_ErrorDomain_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWebPage_ErrorDomain,
        qtscript_QWebPage_ErrorDomain_valueOf, qtscript_QWebPage_ErrorDomain_toString);
    qScriptRegisterMetaType<QWebPage::ErrorDomain>(engine, qtscript_QWebPage_ErrorDomain_toScriptValue,
        qtscript_QWebPage_ErrorDomain_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWebPage_ErrorDomain_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWebPage_ErrorDomain_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWebPage::NavigationType
//

static const QWebPage::NavigationType qtscript_QWebPage_NavigationType_values[] = {
    QWebPage::NavigationTypeLinkClicked
    , QWebPage::NavigationTypeFormSubmitted
    , QWebPage::NavigationTypeBackOrForward
    , QWebPage::NavigationTypeReload
    , QWebPage::NavigationTypeFormResubmitted
    , QWebPage::NavigationTypeOther
};

static const char * const qtscript_QWebPage_NavigationType_keys[] = {
    "NavigationTypeLinkClicked"
    , "NavigationTypeFormSubmitted"
    , "NavigationTypeBackOrForward"
    , "NavigationTypeReload"
    , "NavigationTypeFormResubmitted"
    , "NavigationTypeOther"
};

static QString qtscript_QWebPage_NavigationType_toStringHelper(QWebPage::NavigationType value)
{
    const QMetaObject *meta = qtscript_QWebPage_metaObject();
    int idx = meta->indexOfEnumerator("NavigationType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QWebPage_NavigationType_toScriptValue(QScriptEngine *engine, const QWebPage::NavigationType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWebPage"));
    return clazz.property(qtscript_QWebPage_NavigationType_toStringHelper(value));
}

static void qtscript_QWebPage_NavigationType_fromScriptValue(const QScriptValue &value, QWebPage::NavigationType &out)
{
    out = qvariant_cast<QWebPage::NavigationType>(value.toVariant());
}

static QScriptValue qtscript_construct_QWebPage_NavigationType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QWebPage_metaObject();
    int idx = meta->indexOfEnumerator("NavigationType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QWebPage::NavigationType>(arg));
    return context->throwError(QString::fromLatin1("NavigationType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWebPage_NavigationType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::NavigationType value = qscriptvalue_cast<QWebPage::NavigationType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebPage_NavigationType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::NavigationType value = qscriptvalue_cast<QWebPage::NavigationType>(context->thisObject());
    return QScriptValue(engine, qtscript_QWebPage_NavigationType_toStringHelper(value));
}

static QScriptValue qtscript_create_QWebPage_NavigationType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWebPage_NavigationType,
        qtscript_QWebPage_NavigationType_valueOf, qtscript_QWebPage_NavigationType_toString);
    qScriptRegisterMetaType<QWebPage::NavigationType>(engine, qtscript_QWebPage_NavigationType_toScriptValue,
        qtscript_QWebPage_NavigationType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWebPage_NavigationType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWebPage_NavigationType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWebPage::WebAction
//

static const QWebPage::WebAction qtscript_QWebPage_WebAction_values[] = {
    QWebPage::NoWebAction
    , QWebPage::OpenLink
    , QWebPage::OpenLinkInNewWindow
    , QWebPage::OpenFrameInNewWindow
    , QWebPage::DownloadLinkToDisk
    , QWebPage::CopyLinkToClipboard
    , QWebPage::OpenImageInNewWindow
    , QWebPage::DownloadImageToDisk
    , QWebPage::CopyImageToClipboard
    , QWebPage::Back
    , QWebPage::Forward
    , QWebPage::Stop
    , QWebPage::Reload
    , QWebPage::Cut
    , QWebPage::Copy
    , QWebPage::Paste
    , QWebPage::Undo
    , QWebPage::Redo
    , QWebPage::MoveToNextChar
    , QWebPage::MoveToPreviousChar
    , QWebPage::MoveToNextWord
    , QWebPage::MoveToPreviousWord
    , QWebPage::MoveToNextLine
    , QWebPage::MoveToPreviousLine
    , QWebPage::MoveToStartOfLine
    , QWebPage::MoveToEndOfLine
    , QWebPage::MoveToStartOfBlock
    , QWebPage::MoveToEndOfBlock
    , QWebPage::MoveToStartOfDocument
    , QWebPage::MoveToEndOfDocument
    , QWebPage::SelectNextChar
    , QWebPage::SelectPreviousChar
    , QWebPage::SelectNextWord
    , QWebPage::SelectPreviousWord
    , QWebPage::SelectNextLine
    , QWebPage::SelectPreviousLine
    , QWebPage::SelectStartOfLine
    , QWebPage::SelectEndOfLine
    , QWebPage::SelectStartOfBlock
    , QWebPage::SelectEndOfBlock
    , QWebPage::SelectStartOfDocument
    , QWebPage::SelectEndOfDocument
    , QWebPage::DeleteStartOfWord
    , QWebPage::DeleteEndOfWord
    , QWebPage::SetTextDirectionDefault
    , QWebPage::SetTextDirectionLeftToRight
    , QWebPage::SetTextDirectionRightToLeft
    , QWebPage::ToggleBold
    , QWebPage::ToggleItalic
    , QWebPage::ToggleUnderline
    , QWebPage::InspectElement
    , QWebPage::InsertParagraphSeparator
    , QWebPage::InsertLineSeparator
    , QWebPage::SelectAll
    , QWebPage::ReloadAndBypassCache
    , QWebPage::PasteAndMatchStyle
    , QWebPage::RemoveFormat
    , QWebPage::ToggleStrikethrough
    , QWebPage::ToggleSubscript
    , QWebPage::ToggleSuperscript
    , QWebPage::InsertUnorderedList
    , QWebPage::InsertOrderedList
    , QWebPage::Indent
    , QWebPage::Outdent
    , QWebPage::AlignCenter
    , QWebPage::AlignJustified
    , QWebPage::AlignLeft
    , QWebPage::AlignRight
    , QWebPage::StopScheduledPageRefresh
    , QWebPage::WebActionCount
};

static const char * const qtscript_QWebPage_WebAction_keys[] = {
    "NoWebAction"
    , "OpenLink"
    , "OpenLinkInNewWindow"
    , "OpenFrameInNewWindow"
    , "DownloadLinkToDisk"
    , "CopyLinkToClipboard"
    , "OpenImageInNewWindow"
    , "DownloadImageToDisk"
    , "CopyImageToClipboard"
    , "Back"
    , "Forward"
    , "Stop"
    , "Reload"
    , "Cut"
    , "Copy"
    , "Paste"
    , "Undo"
    , "Redo"
    , "MoveToNextChar"
    , "MoveToPreviousChar"
    , "MoveToNextWord"
    , "MoveToPreviousWord"
    , "MoveToNextLine"
    , "MoveToPreviousLine"
    , "MoveToStartOfLine"
    , "MoveToEndOfLine"
    , "MoveToStartOfBlock"
    , "MoveToEndOfBlock"
    , "MoveToStartOfDocument"
    , "MoveToEndOfDocument"
    , "SelectNextChar"
    , "SelectPreviousChar"
    , "SelectNextWord"
    , "SelectPreviousWord"
    , "SelectNextLine"
    , "SelectPreviousLine"
    , "SelectStartOfLine"
    , "SelectEndOfLine"
    , "SelectStartOfBlock"
    , "SelectEndOfBlock"
    , "SelectStartOfDocument"
    , "SelectEndOfDocument"
    , "DeleteStartOfWord"
    , "DeleteEndOfWord"
    , "SetTextDirectionDefault"
    , "SetTextDirectionLeftToRight"
    , "SetTextDirectionRightToLeft"
    , "ToggleBold"
    , "ToggleItalic"
    , "ToggleUnderline"
    , "InspectElement"
    , "InsertParagraphSeparator"
    , "InsertLineSeparator"
    , "SelectAll"
    , "ReloadAndBypassCache"
    , "PasteAndMatchStyle"
    , "RemoveFormat"
    , "ToggleStrikethrough"
    , "ToggleSubscript"
    , "ToggleSuperscript"
    , "InsertUnorderedList"
    , "InsertOrderedList"
    , "Indent"
    , "Outdent"
    , "AlignCenter"
    , "AlignJustified"
    , "AlignLeft"
    , "AlignRight"
    , "StopScheduledPageRefresh"
    , "WebActionCount"
};

static QString qtscript_QWebPage_WebAction_toStringHelper(QWebPage::WebAction value)
{
    const QMetaObject *meta = qtscript_QWebPage_metaObject();
    int idx = meta->indexOfEnumerator("WebAction");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QWebPage_WebAction_toScriptValue(QScriptEngine *engine, const QWebPage::WebAction &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWebPage"));
    return clazz.property(qtscript_QWebPage_WebAction_toStringHelper(value));
}

static void qtscript_QWebPage_WebAction_fromScriptValue(const QScriptValue &value, QWebPage::WebAction &out)
{
    out = qvariant_cast<QWebPage::WebAction>(value.toVariant());
}

static QScriptValue qtscript_construct_QWebPage_WebAction(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QWebPage_metaObject();
    int idx = meta->indexOfEnumerator("WebAction");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QWebPage::WebAction>(arg));
    return context->throwError(QString::fromLatin1("WebAction(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWebPage_WebAction_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::WebAction value = qscriptvalue_cast<QWebPage::WebAction>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebPage_WebAction_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::WebAction value = qscriptvalue_cast<QWebPage::WebAction>(context->thisObject());
    return QScriptValue(engine, qtscript_QWebPage_WebAction_toStringHelper(value));
}

static QScriptValue qtscript_create_QWebPage_WebAction_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWebPage_WebAction,
        qtscript_QWebPage_WebAction_valueOf, qtscript_QWebPage_WebAction_toString);
    qScriptRegisterMetaType<QWebPage::WebAction>(engine, qtscript_QWebPage_WebAction_toScriptValue,
        qtscript_QWebPage_WebAction_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 70; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWebPage_WebAction_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWebPage_WebAction_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWebPage::WebWindowType
//

static const QWebPage::WebWindowType qtscript_QWebPage_WebWindowType_values[] = {
    QWebPage::WebBrowserWindow
    , QWebPage::WebModalDialog
};

static const char * const qtscript_QWebPage_WebWindowType_keys[] = {
    "WebBrowserWindow"
    , "WebModalDialog"
};

static QString qtscript_QWebPage_WebWindowType_toStringHelper(QWebPage::WebWindowType value)
{
    if ((value >= QWebPage::WebBrowserWindow) && (value <= QWebPage::WebModalDialog))
        return qtscript_QWebPage_WebWindowType_keys[static_cast<int>(value)-static_cast<int>(QWebPage::WebBrowserWindow)];
    return QString();
}

static QScriptValue qtscript_QWebPage_WebWindowType_toScriptValue(QScriptEngine *engine, const QWebPage::WebWindowType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWebPage"));
    return clazz.property(qtscript_QWebPage_WebWindowType_toStringHelper(value));
}

static void qtscript_QWebPage_WebWindowType_fromScriptValue(const QScriptValue &value, QWebPage::WebWindowType &out)
{
    out = qvariant_cast<QWebPage::WebWindowType>(value.toVariant());
}

static QScriptValue qtscript_construct_QWebPage_WebWindowType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QWebPage::WebBrowserWindow) && (arg <= QWebPage::WebModalDialog))
        return qScriptValueFromValue(engine,  static_cast<QWebPage::WebWindowType>(arg));
    return context->throwError(QString::fromLatin1("WebWindowType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWebPage_WebWindowType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::WebWindowType value = qscriptvalue_cast<QWebPage::WebWindowType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebPage_WebWindowType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::WebWindowType value = qscriptvalue_cast<QWebPage::WebWindowType>(context->thisObject());
    return QScriptValue(engine, qtscript_QWebPage_WebWindowType_toStringHelper(value));
}

static QScriptValue qtscript_create_QWebPage_WebWindowType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWebPage_WebWindowType,
        qtscript_QWebPage_WebWindowType_valueOf, qtscript_QWebPage_WebWindowType_toString);
    qScriptRegisterMetaType<QWebPage::WebWindowType>(engine, qtscript_QWebPage_WebWindowType_toScriptValue,
        qtscript_QWebPage_WebWindowType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWebPage_WebWindowType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWebPage_WebWindowType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWebPage::FindFlag
//

static const QWebPage::FindFlag qtscript_QWebPage_FindFlag_values[] = {
    QWebPage::FindBackward
    , QWebPage::FindCaseSensitively
    , QWebPage::FindWrapsAroundDocument
    , QWebPage::HighlightAllOccurrences
};

static const char * const qtscript_QWebPage_FindFlag_keys[] = {
    "FindBackward"
    , "FindCaseSensitively"
    , "FindWrapsAroundDocument"
    , "HighlightAllOccurrences"
};

static QString qtscript_QWebPage_FindFlag_toStringHelper(QWebPage::FindFlag value)
{
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QWebPage_FindFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QWebPage_FindFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QWebPage_FindFlag_toScriptValue(QScriptEngine *engine, const QWebPage::FindFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWebPage"));
    return clazz.property(qtscript_QWebPage_FindFlag_toStringHelper(value));
}

static void qtscript_QWebPage_FindFlag_fromScriptValue(const QScriptValue &value, QWebPage::FindFlag &out)
{
    out = qvariant_cast<QWebPage::FindFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QWebPage_FindFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QWebPage_FindFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QWebPage::FindFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("FindFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWebPage_FindFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::FindFlag value = qscriptvalue_cast<QWebPage::FindFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebPage_FindFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::FindFlag value = qscriptvalue_cast<QWebPage::FindFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QWebPage_FindFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QWebPage_FindFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWebPage_FindFlag,
        qtscript_QWebPage_FindFlag_valueOf, qtscript_QWebPage_FindFlag_toString);
    qScriptRegisterMetaType<QWebPage::FindFlag>(engine, qtscript_QWebPage_FindFlag_toScriptValue,
        qtscript_QWebPage_FindFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWebPage_FindFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWebPage_FindFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWebPage::FindFlags
//

static QScriptValue qtscript_QWebPage_FindFlags_toScriptValue(QScriptEngine *engine, const QWebPage::FindFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QWebPage_FindFlags_fromScriptValue(const QScriptValue &value, QWebPage::FindFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QWebPage::FindFlags>())
        out = qvariant_cast<QWebPage::FindFlags>(var);
    else if (var.userType() == qMetaTypeId<QWebPage::FindFlag>())
        out = qvariant_cast<QWebPage::FindFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QWebPage_FindFlags(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::FindFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QWebPage::FindFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QWebPage::FindFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("FindFlags(): argument %0 is not of type FindFlag").arg(i));
            }
            result |= qvariant_cast<QWebPage::FindFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QWebPage_FindFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::FindFlags value = qscriptvalue_cast<QWebPage::FindFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebPage_FindFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::FindFlags value = qscriptvalue_cast<QWebPage::FindFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 4; ++i) {
        if ((value & qtscript_QWebPage_FindFlag_values[i]) == qtscript_QWebPage_FindFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QWebPage_FindFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QWebPage_FindFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QWebPage::FindFlags>() == otherObj.value<QWebPage::FindFlags>())));
}

static QScriptValue qtscript_create_QWebPage_FindFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QWebPage_FindFlags, qtscript_QWebPage_FindFlags_valueOf,
        qtscript_QWebPage_FindFlags_toString, qtscript_QWebPage_FindFlags_equals);
    qScriptRegisterMetaType<QWebPage::FindFlags>(engine, qtscript_QWebPage_FindFlags_toScriptValue,
        qtscript_QWebPage_FindFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QWebPage::Extension
//

static const QWebPage::Extension qtscript_QWebPage_Extension_values[] = {
    QWebPage::ChooseMultipleFilesExtension
    , QWebPage::ErrorPageExtension
};

static const char * const qtscript_QWebPage_Extension_keys[] = {
    "ChooseMultipleFilesExtension"
    , "ErrorPageExtension"
};

static QString qtscript_QWebPage_Extension_toStringHelper(QWebPage::Extension value)
{
    if ((value >= QWebPage::ChooseMultipleFilesExtension) && (value <= QWebPage::ErrorPageExtension))
        return qtscript_QWebPage_Extension_keys[static_cast<int>(value)-static_cast<int>(QWebPage::ChooseMultipleFilesExtension)];
    return QString();
}

static QScriptValue qtscript_QWebPage_Extension_toScriptValue(QScriptEngine *engine, const QWebPage::Extension &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWebPage"));
    return clazz.property(qtscript_QWebPage_Extension_toStringHelper(value));
}

static void qtscript_QWebPage_Extension_fromScriptValue(const QScriptValue &value, QWebPage::Extension &out)
{
    out = qvariant_cast<QWebPage::Extension>(value.toVariant());
}

static QScriptValue qtscript_construct_QWebPage_Extension(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QWebPage::ChooseMultipleFilesExtension) && (arg <= QWebPage::ErrorPageExtension))
        return qScriptValueFromValue(engine,  static_cast<QWebPage::Extension>(arg));
    return context->throwError(QString::fromLatin1("Extension(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWebPage_Extension_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::Extension value = qscriptvalue_cast<QWebPage::Extension>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebPage_Extension_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::Extension value = qscriptvalue_cast<QWebPage::Extension>(context->thisObject());
    return QScriptValue(engine, qtscript_QWebPage_Extension_toStringHelper(value));
}

static QScriptValue qtscript_create_QWebPage_Extension_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWebPage_Extension,
        qtscript_QWebPage_Extension_valueOf, qtscript_QWebPage_Extension_toString);
    qScriptRegisterMetaType<QWebPage::Extension>(engine, qtscript_QWebPage_Extension_toScriptValue,
        qtscript_QWebPage_Extension_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWebPage_Extension_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWebPage_Extension_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWebPage::LinkDelegationPolicy
//

static const QWebPage::LinkDelegationPolicy qtscript_QWebPage_LinkDelegationPolicy_values[] = {
    QWebPage::DontDelegateLinks
    , QWebPage::DelegateExternalLinks
    , QWebPage::DelegateAllLinks
};

static const char * const qtscript_QWebPage_LinkDelegationPolicy_keys[] = {
    "DontDelegateLinks"
    , "DelegateExternalLinks"
    , "DelegateAllLinks"
};

static QString qtscript_QWebPage_LinkDelegationPolicy_toStringHelper(QWebPage::LinkDelegationPolicy value)
{
    const QMetaObject *meta = qtscript_QWebPage_metaObject();
    int idx = meta->indexOfEnumerator("LinkDelegationPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QWebPage_LinkDelegationPolicy_toScriptValue(QScriptEngine *engine, const QWebPage::LinkDelegationPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWebPage"));
    return clazz.property(qtscript_QWebPage_LinkDelegationPolicy_toStringHelper(value));
}

static void qtscript_QWebPage_LinkDelegationPolicy_fromScriptValue(const QScriptValue &value, QWebPage::LinkDelegationPolicy &out)
{
    out = qvariant_cast<QWebPage::LinkDelegationPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_QWebPage_LinkDelegationPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QWebPage_metaObject();
    int idx = meta->indexOfEnumerator("LinkDelegationPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QWebPage::LinkDelegationPolicy>(arg));
    return context->throwError(QString::fromLatin1("LinkDelegationPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWebPage_LinkDelegationPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::LinkDelegationPolicy value = qscriptvalue_cast<QWebPage::LinkDelegationPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebPage_LinkDelegationPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebPage::LinkDelegationPolicy value = qscriptvalue_cast<QWebPage::LinkDelegationPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_QWebPage_LinkDelegationPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_QWebPage_LinkDelegationPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWebPage_LinkDelegationPolicy,
        qtscript_QWebPage_LinkDelegationPolicy_valueOf, qtscript_QWebPage_LinkDelegationPolicy_toString);
    qScriptRegisterMetaType<QWebPage::LinkDelegationPolicy>(engine, qtscript_QWebPage_LinkDelegationPolicy_toScriptValue,
        qtscript_QWebPage_LinkDelegationPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWebPage_LinkDelegationPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWebPage_LinkDelegationPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWebPage
//

static QScriptValue qtscript_QWebPage_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 24;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QWebPage* _q_self = qscriptvalue_cast<QWebPage*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWebPage.%0(): this object is not a QWebPage")
            .arg(qtscript_QWebPage_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QWebPage::WebAction _q_arg0 = qscriptvalue_cast<QWebPage::WebAction>(context->argument(0));
        QAction* _q_result = _q_self->action(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        unsigned long long _q_result = _q_self->bytesReceived();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QMenu* _q_result = _q_self->createStandardContextMenu();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QWebFrame* _q_result = _q_self->currentFrame();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QWebPage::Extension _q_arg0 = qscriptvalue_cast<QWebPage::Extension>(context->argument(0));
        bool _q_result = _q_self->extension(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QWebPage::Extension _q_arg0 = qscriptvalue_cast<QWebPage::Extension>(context->argument(0));
        QWebPage::ExtensionOption* _q_arg1 = qscriptvalue_cast<QWebPage::ExtensionOption*>(context->argument(1));
        bool _q_result = _q_self->extension(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QWebPage::Extension _q_arg0 = qscriptvalue_cast<QWebPage::Extension>(context->argument(0));
        QWebPage::ExtensionOption* _q_arg1 = qscriptvalue_cast<QWebPage::ExtensionOption*>(context->argument(1));
        QWebPage::ExtensionReturn* _q_arg2 = qscriptvalue_cast<QWebPage::ExtensionReturn*>(context->argument(2));
        bool _q_result = _q_self->extension(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->findText(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<QWebPage::FindFlag> _q_arg1 = qscriptvalue_cast<QFlags<QWebPage::FindFlag> >(context->argument(1));
        bool _q_result = _q_self->findText(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        bool _q_result = _q_self->focusNextPrevChild(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QWebFrame* _q_result = _q_self->frameAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QWebHistory* _q_result = _q_self->history();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        Qt::InputMethodQuery _q_arg0 = qscriptvalue_cast<Qt::InputMethodQuery>(context->argument(0));
        QVariant _q_result = _q_self->inputMethodQuery(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QWebFrame* _q_result = _q_self->mainFrame();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QNetworkAccessManager* _q_result = _q_self->networkAccessManager();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QWebPluginFactory* _q_result = _q_self->pluginFactory();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QNetworkAccessManager* _q_arg0 = qscriptvalue_cast<QNetworkAccessManager*>(context->argument(0));
        _q_self->setNetworkAccessManager(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QWebPluginFactory* _q_arg0 = qscriptvalue_cast<QWebPluginFactory*>(context->argument(0));
        _q_self->setPluginFactory(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setView(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QWebSettings* _q_result = _q_self->settings();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QWebPage::Extension _q_arg0 = qscriptvalue_cast<QWebPage::Extension>(context->argument(0));
        bool _q_result = _q_self->supportsExtension(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QContextMenuEvent* _q_arg0 = qscriptvalue_cast<QContextMenuEvent*>(context->argument(0));
        bool _q_result = _q_self->swallowContextMenuEvent(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        unsigned long long _q_result = _q_self->totalBytes();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QWebPage::WebAction _q_arg0 = qscriptvalue_cast<QWebPage::WebAction>(context->argument(0));
        _q_self->triggerAction(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QWebPage::WebAction _q_arg0 = qscriptvalue_cast<QWebPage::WebAction>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->triggerAction(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        QUndoStack* _q_result = _q_self->undoStack();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->updatePositionDependentActions(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->view();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 24: {
    QString result = QString::fromLatin1("QWebPage");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebPage_throw_ambiguity_error_helper(context,
        qtscript_QWebPage_function_names[_id+1],
        qtscript_QWebPage_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWebPage_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWebPage(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QWebPage* _q_cpp_result = new QtScriptShell_QWebPage();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWebPage*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QWebPage* _q_cpp_result = new QtScriptShell_QWebPage(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWebPage*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebPage_throw_ambiguity_error_helper(context,
        qtscript_QWebPage_function_names[_id],
        qtscript_QWebPage_function_signatures[_id]);
}

static QScriptValue qtscript_QWebPage_toScriptValue(QScriptEngine *engine, QWebPage* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QWebPage_fromScriptValue(const QScriptValue &value, QWebPage* &out)
{
    out = qobject_cast<QWebPage*>(value.toQObject());
}

QScriptValue qtscript_create_QWebPage_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWebPage*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWebPage*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 25; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWebPage_prototype_call, qtscript_QWebPage_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWebPage_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QWebPage*>(engine, qtscript_QWebPage_toScriptValue, 
        qtscript_QWebPage_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWebPage_static_call, proto, qtscript_QWebPage_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ErrorDomain"),
        qtscript_create_QWebPage_ErrorDomain_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("NavigationType"),
        qtscript_create_QWebPage_NavigationType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("WebAction"),
        qtscript_create_QWebPage_WebAction_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("WebWindowType"),
        qtscript_create_QWebPage_WebWindowType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FindFlag"),
        qtscript_create_QWebPage_FindFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FindFlags"),
        qtscript_create_QWebPage_FindFlags_class(engine));
    ctor.setProperty(QString::fromLatin1("Extension"),
        qtscript_create_QWebPage_Extension_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("LinkDelegationPolicy"),
        qtscript_create_QWebPage_LinkDelegationPolicy_class(engine, ctor));
    return ctor;
}
