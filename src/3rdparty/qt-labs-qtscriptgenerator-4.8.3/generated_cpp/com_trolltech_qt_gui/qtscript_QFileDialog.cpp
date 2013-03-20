#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qfiledialog.h>
#include <QUrl>
#include <QVariant>
#include <qabstractitemdelegate.h>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdir.h>
#include <qevent.h>
#include <qfiledialog.h>
#include <qfileiconprovider.h>
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
#include <qstringlist.h>
#include <qstyle.h>
#include <qurl.h>
#include <qwidget.h>

#include "qtscriptshell_QFileDialog.h"

static const char * const qtscript_QFileDialog_function_names[] = {
    "QFileDialog"
    // static
    , "getExistingDirectory"
    , "getOpenFileName"
    , "getOpenFileNames"
    , "getSaveFileName"
    // prototype
    , "directory"
    , "filter"
    , "filters"
    , "history"
    , "iconProvider"
    , "isNameFilterDetailsVisible"
    , "itemDelegate"
    , "labelText"
    , "nameFilters"
    , "open"
    , "proxyModel"
    , "restoreState"
    , "saveState"
    , "selectFile"
    , "selectFilter"
    , "selectNameFilter"
    , "selectedFiles"
    , "selectedFilter"
    , "selectedNameFilter"
    , "setDirectory"
    , "setFilter"
    , "setFilters"
    , "setHistory"
    , "setIconProvider"
    , "setItemDelegate"
    , "setLabelText"
    , "setNameFilter"
    , "setNameFilterDetailsVisible"
    , "setNameFilters"
    , "setOption"
    , "setProxyModel"
    , "setSidebarUrls"
    , "sidebarUrls"
    , "testOption"
    , "toString"
};

static const char * const qtscript_QFileDialog_function_signatures[] = {
    "QWidget parent, WindowFlags f\nQWidget parent, String caption, String directory, String filter"
    // static
    , "QWidget parent, String caption, String dir, Options options"
    , "QWidget parent, String caption, String dir, String filter, String selectedFilter, Options options"
    , "QWidget parent, String caption, String dir, String filter, String selectedFilter, Options options"
    , "QWidget parent, String caption, String dir, String filter, String selectedFilter, Options options"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "DialogLabel label"
    , ""
    , "QObject receiver, char member"
    , ""
    , "QByteArray state"
    , ""
    , "String filename"
    , "String filter"
    , "String filter"
    , ""
    , ""
    , ""
    , "QDir directory\nString directory"
    , "Filters filters\nString filter"
    , "List filters"
    , "List paths"
    , "QFileIconProvider provider"
    , "QAbstractItemDelegate delegate"
    , "DialogLabel label, String text"
    , "String filter"
    , "bool enabled"
    , "List filters"
    , "Option option, bool on"
    , "QAbstractProxyModel model"
    , "List urls"
    , ""
    , "Option option"
""
};

static const int qtscript_QFileDialog_function_lengths[] = {
    4
    // static
    , 4
    , 6
    , 6
    , 6
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 2
    , 0
    , 1
    , 0
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QFileDialog_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFileDialog::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QFileDialog_metaObject()
{
    return &QFileDialog::staticMetaObject;
}

Q_DECLARE_METATYPE(QFileDialog*)
Q_DECLARE_METATYPE(QtScriptShell_QFileDialog*)
Q_DECLARE_METATYPE(QFileDialog::FileMode)
Q_DECLARE_METATYPE(QFileDialog::Option)
Q_DECLARE_METATYPE(QFlags<QFileDialog::Option>)
Q_DECLARE_METATYPE(QFileDialog::DialogLabel)
Q_DECLARE_METATYPE(QFileDialog::ViewMode)
Q_DECLARE_METATYPE(QFileDialog::AcceptMode)
Q_DECLARE_METATYPE(QDir)
Q_DECLARE_METATYPE(QFlags<QDir::Filter>)
Q_DECLARE_METATYPE(QFileIconProvider*)
Q_DECLARE_METATYPE(QAbstractItemDelegate*)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QAbstractProxyModel*)
Q_DECLARE_METATYPE(QList<QUrl>)
Q_DECLARE_METATYPE(QString*)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)
Q_DECLARE_METATYPE(QDialog*)

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
// QFileDialog::FileMode
//

static const QFileDialog::FileMode qtscript_QFileDialog_FileMode_values[] = {
    QFileDialog::AnyFile
    , QFileDialog::ExistingFile
    , QFileDialog::Directory
    , QFileDialog::ExistingFiles
    , QFileDialog::DirectoryOnly
};

static const char * const qtscript_QFileDialog_FileMode_keys[] = {
    "AnyFile"
    , "ExistingFile"
    , "Directory"
    , "ExistingFiles"
    , "DirectoryOnly"
};

static QString qtscript_QFileDialog_FileMode_toStringHelper(QFileDialog::FileMode value)
{
    const QMetaObject *meta = qtscript_QFileDialog_metaObject();
    int idx = meta->indexOfEnumerator("FileMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QFileDialog_FileMode_toScriptValue(QScriptEngine *engine, const QFileDialog::FileMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFileDialog"));
    return clazz.property(qtscript_QFileDialog_FileMode_toStringHelper(value));
}

static void qtscript_QFileDialog_FileMode_fromScriptValue(const QScriptValue &value, QFileDialog::FileMode &out)
{
    out = qvariant_cast<QFileDialog::FileMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QFileDialog_FileMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QFileDialog_metaObject();
    int idx = meta->indexOfEnumerator("FileMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QFileDialog::FileMode>(arg));
    return context->throwError(QString::fromLatin1("FileMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFileDialog_FileMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFileDialog::FileMode value = qscriptvalue_cast<QFileDialog::FileMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFileDialog_FileMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFileDialog::FileMode value = qscriptvalue_cast<QFileDialog::FileMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QFileDialog_FileMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QFileDialog_FileMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFileDialog_FileMode,
        qtscript_QFileDialog_FileMode_valueOf, qtscript_QFileDialog_FileMode_toString);
    qScriptRegisterMetaType<QFileDialog::FileMode>(engine, qtscript_QFileDialog_FileMode_toScriptValue,
        qtscript_QFileDialog_FileMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFileDialog_FileMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFileDialog_FileMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFileDialog::Option
//

static const QFileDialog::Option qtscript_QFileDialog_Option_values[] = {
    QFileDialog::ShowDirsOnly
    , QFileDialog::DontResolveSymlinks
    , QFileDialog::DontConfirmOverwrite
    , QFileDialog::DontUseSheet
    , QFileDialog::DontUseNativeDialog
    , QFileDialog::ReadOnly
    , QFileDialog::HideNameFilterDetails
};

static const char * const qtscript_QFileDialog_Option_keys[] = {
    "ShowDirsOnly"
    , "DontResolveSymlinks"
    , "DontConfirmOverwrite"
    , "DontUseSheet"
    , "DontUseNativeDialog"
    , "ReadOnly"
    , "HideNameFilterDetails"
};

static QString qtscript_QFileDialog_Option_toStringHelper(QFileDialog::Option value)
{
    const QMetaObject *meta = qtscript_QFileDialog_metaObject();
    int idx = meta->indexOfEnumerator("Option");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QFileDialog_Option_toScriptValue(QScriptEngine *engine, const QFileDialog::Option &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFileDialog"));
    return clazz.property(qtscript_QFileDialog_Option_toStringHelper(value));
}

static void qtscript_QFileDialog_Option_fromScriptValue(const QScriptValue &value, QFileDialog::Option &out)
{
    out = qvariant_cast<QFileDialog::Option>(value.toVariant());
}

static QScriptValue qtscript_construct_QFileDialog_Option(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QFileDialog_metaObject();
    int idx = meta->indexOfEnumerator("Option");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QFileDialog::Option>(arg));
    return context->throwError(QString::fromLatin1("Option(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFileDialog_Option_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFileDialog::Option value = qscriptvalue_cast<QFileDialog::Option>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFileDialog_Option_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFileDialog::Option value = qscriptvalue_cast<QFileDialog::Option>(context->thisObject());
    return QScriptValue(engine, qtscript_QFileDialog_Option_toStringHelper(value));
}

static QScriptValue qtscript_create_QFileDialog_Option_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFileDialog_Option,
        qtscript_QFileDialog_Option_valueOf, qtscript_QFileDialog_Option_toString);
    qScriptRegisterMetaType<QFileDialog::Option>(engine, qtscript_QFileDialog_Option_toScriptValue,
        qtscript_QFileDialog_Option_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFileDialog_Option_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFileDialog_Option_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFileDialog::Options
//

static QScriptValue qtscript_QFileDialog_Options_toScriptValue(QScriptEngine *engine, const QFileDialog::Options &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QFileDialog_Options_fromScriptValue(const QScriptValue &value, QFileDialog::Options &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QFileDialog::Options>())
        out = qvariant_cast<QFileDialog::Options>(var);
    else if (var.userType() == qMetaTypeId<QFileDialog::Option>())
        out = qvariant_cast<QFileDialog::Option>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QFileDialog_Options(QScriptContext *context, QScriptEngine *engine)
{
    QFileDialog::Options result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QFileDialog::Options>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QFileDialog::Option>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("Options(): argument %0 is not of type Option").arg(i));
            }
            result |= qvariant_cast<QFileDialog::Option>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QFileDialog_Options_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFileDialog::Options value = qscriptvalue_cast<QFileDialog::Options>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFileDialog_Options_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFileDialog::Options value = qscriptvalue_cast<QFileDialog::Options>(context->thisObject());
    QString result;
    for (int i = 0; i < 7; ++i) {
        if ((value & qtscript_QFileDialog_Option_values[i]) == qtscript_QFileDialog_Option_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QFileDialog_Option_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QFileDialog_Options_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QFileDialog::Options>() == otherObj.value<QFileDialog::Options>())));
}

static QScriptValue qtscript_create_QFileDialog_Options_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QFileDialog_Options, qtscript_QFileDialog_Options_valueOf,
        qtscript_QFileDialog_Options_toString, qtscript_QFileDialog_Options_equals);
    qScriptRegisterMetaType<QFileDialog::Options>(engine, qtscript_QFileDialog_Options_toScriptValue,
        qtscript_QFileDialog_Options_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QFileDialog::DialogLabel
//

static const QFileDialog::DialogLabel qtscript_QFileDialog_DialogLabel_values[] = {
    QFileDialog::LookIn
    , QFileDialog::FileName
    , QFileDialog::FileType
    , QFileDialog::Accept
    , QFileDialog::Reject
};

static const char * const qtscript_QFileDialog_DialogLabel_keys[] = {
    "LookIn"
    , "FileName"
    , "FileType"
    , "Accept"
    , "Reject"
};

static QString qtscript_QFileDialog_DialogLabel_toStringHelper(QFileDialog::DialogLabel value)
{
    if ((value >= QFileDialog::LookIn) && (value <= QFileDialog::Reject))
        return qtscript_QFileDialog_DialogLabel_keys[static_cast<int>(value)-static_cast<int>(QFileDialog::LookIn)];
    return QString();
}

static QScriptValue qtscript_QFileDialog_DialogLabel_toScriptValue(QScriptEngine *engine, const QFileDialog::DialogLabel &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFileDialog"));
    return clazz.property(qtscript_QFileDialog_DialogLabel_toStringHelper(value));
}

static void qtscript_QFileDialog_DialogLabel_fromScriptValue(const QScriptValue &value, QFileDialog::DialogLabel &out)
{
    out = qvariant_cast<QFileDialog::DialogLabel>(value.toVariant());
}

static QScriptValue qtscript_construct_QFileDialog_DialogLabel(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFileDialog::LookIn) && (arg <= QFileDialog::Reject))
        return qScriptValueFromValue(engine,  static_cast<QFileDialog::DialogLabel>(arg));
    return context->throwError(QString::fromLatin1("DialogLabel(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFileDialog_DialogLabel_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFileDialog::DialogLabel value = qscriptvalue_cast<QFileDialog::DialogLabel>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFileDialog_DialogLabel_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFileDialog::DialogLabel value = qscriptvalue_cast<QFileDialog::DialogLabel>(context->thisObject());
    return QScriptValue(engine, qtscript_QFileDialog_DialogLabel_toStringHelper(value));
}

static QScriptValue qtscript_create_QFileDialog_DialogLabel_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFileDialog_DialogLabel,
        qtscript_QFileDialog_DialogLabel_valueOf, qtscript_QFileDialog_DialogLabel_toString);
    qScriptRegisterMetaType<QFileDialog::DialogLabel>(engine, qtscript_QFileDialog_DialogLabel_toScriptValue,
        qtscript_QFileDialog_DialogLabel_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFileDialog_DialogLabel_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFileDialog_DialogLabel_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFileDialog::ViewMode
//

static const QFileDialog::ViewMode qtscript_QFileDialog_ViewMode_values[] = {
    QFileDialog::Detail
    , QFileDialog::List
};

static const char * const qtscript_QFileDialog_ViewMode_keys[] = {
    "Detail"
    , "List"
};

static QString qtscript_QFileDialog_ViewMode_toStringHelper(QFileDialog::ViewMode value)
{
    const QMetaObject *meta = qtscript_QFileDialog_metaObject();
    int idx = meta->indexOfEnumerator("ViewMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QFileDialog_ViewMode_toScriptValue(QScriptEngine *engine, const QFileDialog::ViewMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFileDialog"));
    return clazz.property(qtscript_QFileDialog_ViewMode_toStringHelper(value));
}

static void qtscript_QFileDialog_ViewMode_fromScriptValue(const QScriptValue &value, QFileDialog::ViewMode &out)
{
    out = qvariant_cast<QFileDialog::ViewMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QFileDialog_ViewMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QFileDialog_metaObject();
    int idx = meta->indexOfEnumerator("ViewMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QFileDialog::ViewMode>(arg));
    return context->throwError(QString::fromLatin1("ViewMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFileDialog_ViewMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFileDialog::ViewMode value = qscriptvalue_cast<QFileDialog::ViewMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFileDialog_ViewMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFileDialog::ViewMode value = qscriptvalue_cast<QFileDialog::ViewMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QFileDialog_ViewMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QFileDialog_ViewMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFileDialog_ViewMode,
        qtscript_QFileDialog_ViewMode_valueOf, qtscript_QFileDialog_ViewMode_toString);
    qScriptRegisterMetaType<QFileDialog::ViewMode>(engine, qtscript_QFileDialog_ViewMode_toScriptValue,
        qtscript_QFileDialog_ViewMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFileDialog_ViewMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFileDialog_ViewMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFileDialog::AcceptMode
//

static const QFileDialog::AcceptMode qtscript_QFileDialog_AcceptMode_values[] = {
    QFileDialog::AcceptOpen
    , QFileDialog::AcceptSave
};

static const char * const qtscript_QFileDialog_AcceptMode_keys[] = {
    "AcceptOpen"
    , "AcceptSave"
};

static QString qtscript_QFileDialog_AcceptMode_toStringHelper(QFileDialog::AcceptMode value)
{
    const QMetaObject *meta = qtscript_QFileDialog_metaObject();
    int idx = meta->indexOfEnumerator("AcceptMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QFileDialog_AcceptMode_toScriptValue(QScriptEngine *engine, const QFileDialog::AcceptMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFileDialog"));
    return clazz.property(qtscript_QFileDialog_AcceptMode_toStringHelper(value));
}

static void qtscript_QFileDialog_AcceptMode_fromScriptValue(const QScriptValue &value, QFileDialog::AcceptMode &out)
{
    out = qvariant_cast<QFileDialog::AcceptMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QFileDialog_AcceptMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QFileDialog_metaObject();
    int idx = meta->indexOfEnumerator("AcceptMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QFileDialog::AcceptMode>(arg));
    return context->throwError(QString::fromLatin1("AcceptMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFileDialog_AcceptMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFileDialog::AcceptMode value = qscriptvalue_cast<QFileDialog::AcceptMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFileDialog_AcceptMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFileDialog::AcceptMode value = qscriptvalue_cast<QFileDialog::AcceptMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QFileDialog_AcceptMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QFileDialog_AcceptMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFileDialog_AcceptMode,
        qtscript_QFileDialog_AcceptMode_valueOf, qtscript_QFileDialog_AcceptMode_toString);
    qScriptRegisterMetaType<QFileDialog::AcceptMode>(engine, qtscript_QFileDialog_AcceptMode_toScriptValue,
        qtscript_QFileDialog_AcceptMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFileDialog_AcceptMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFileDialog_AcceptMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFileDialog
//

static QScriptValue qtscript_QFileDialog_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QFileDialog* _q_self = qscriptvalue_cast<QFileDialog*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFileDialog.%0(): this object is not a QFileDialog")
            .arg(qtscript_QFileDialog_function_names[_id+5]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QDir _q_result = _q_self->directory();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QFlags<QDir::Filter> _q_result = _q_self->filter();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->filters();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->history();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QFileIconProvider* _q_result = _q_self->iconProvider();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNameFilterDetailsVisible();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QAbstractItemDelegate* _q_result = _q_self->itemDelegate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QFileDialog::DialogLabel _q_arg0 = qscriptvalue_cast<QFileDialog::DialogLabel>(context->argument(0));
        QString _q_result = _q_self->labelText(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->nameFilters();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        char* _q_arg1 = qscriptvalue_cast<char*>(context->argument(1));
        _q_self->open(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QAbstractProxyModel* _q_result = _q_self->proxyModel();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        bool _q_result = _q_self->restoreState(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->saveState();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->selectFile(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->selectFilter(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->selectNameFilter(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->selectedFiles();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->selectedFilter();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->selectedNameFilter();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QDir>() == context->argument(0).toVariant().userType())) {
            QDir _q_arg0 = qscriptvalue_cast<QDir>(context->argument(0));
            _q_self->setDirectory(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->setDirectory(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QFlags<QDir::Filter> >() == context->argument(0).toVariant().userType())) {
            QFlags<QDir::Filter> _q_arg0 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(0));
            _q_self->setFilter(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->setFilter(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setFilters(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setHistory(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QFileIconProvider* _q_arg0 = qscriptvalue_cast<QFileIconProvider*>(context->argument(0));
        _q_self->setIconProvider(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QAbstractItemDelegate* _q_arg0 = qscriptvalue_cast<QAbstractItemDelegate*>(context->argument(0));
        _q_self->setItemDelegate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 2) {
        QFileDialog::DialogLabel _q_arg0 = qscriptvalue_cast<QFileDialog::DialogLabel>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setLabelText(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setNameFilter(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setNameFilterDetailsVisible(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setNameFilters(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        QFileDialog::Option _q_arg0 = qscriptvalue_cast<QFileDialog::Option>(context->argument(0));
        _q_self->setOption(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QFileDialog::Option _q_arg0 = qscriptvalue_cast<QFileDialog::Option>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setOption(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QAbstractProxyModel* _q_arg0 = qscriptvalue_cast<QAbstractProxyModel*>(context->argument(0));
        _q_self->setProxyModel(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QList<QUrl> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setSidebarUrls(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        QList<QUrl> _q_result = _q_self->sidebarUrls();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        QFileDialog::Option _q_arg0 = qscriptvalue_cast<QFileDialog::Option>(context->argument(0));
        bool _q_result = _q_self->testOption(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 34: {
    QString result = QString::fromLatin1("QFileDialog");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFileDialog_throw_ambiguity_error_helper(context,
        qtscript_QFileDialog_function_names[_id+5],
        qtscript_QFileDialog_function_signatures[_id+5]);
}

static QScriptValue qtscript_QFileDialog_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFileDialog(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QFileDialog* _q_cpp_result = new QtScriptShell_QFileDialog();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFileDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QFileDialog* _q_cpp_result = new QtScriptShell_QFileDialog(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFileDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && (qMetaTypeId<QFlags<Qt::WindowType> >() == context->argument(1).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
            QtScriptShell_QFileDialog* _q_cpp_result = new QtScriptShell_QFileDialog(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFileDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && context->argument(1).isString()) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QtScriptShell_QFileDialog* _q_cpp_result = new QtScriptShell_QFileDialog(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFileDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QtScriptShell_QFileDialog* _q_cpp_result = new QtScriptShell_QFileDialog(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFileDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 4) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        QtScriptShell_QFileDialog* _q_cpp_result = new QtScriptShell_QFileDialog(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFileDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = QFileDialog::getExistingDirectory();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_result = QFileDialog::getExistingDirectory(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_result = QFileDialog::getExistingDirectory(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_result = QFileDialog::getExistingDirectory(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QFlags<QFileDialog::Option> _q_arg3 = qscriptvalue_cast<QFlags<QFileDialog::Option> >(context->argument(3));
        QString _q_result = QFileDialog::getExistingDirectory(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = QFileDialog::getOpenFileName();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_result = QFileDialog::getOpenFileName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_result = QFileDialog::getOpenFileName(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_result = QFileDialog::getOpenFileName(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        QString _q_result = QFileDialog::getOpenFileName(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        QString* _q_arg4 = qscriptvalue_cast<QString*>(context->argument(4));
        QString _q_result = QFileDialog::getOpenFileName(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 6) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        QString* _q_arg4 = qscriptvalue_cast<QString*>(context->argument(4));
        QFlags<QFileDialog::Option> _q_arg5 = qscriptvalue_cast<QFlags<QFileDialog::Option> >(context->argument(5));
        QString _q_result = QFileDialog::getOpenFileName(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QStringList _q_result = QFileDialog::getOpenFileNames();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QStringList _q_result = QFileDialog::getOpenFileNames(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QStringList _q_result = QFileDialog::getOpenFileNames(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QStringList _q_result = QFileDialog::getOpenFileNames(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        QStringList _q_result = QFileDialog::getOpenFileNames(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        QString* _q_arg4 = qscriptvalue_cast<QString*>(context->argument(4));
        QStringList _q_result = QFileDialog::getOpenFileNames(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 6) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        QString* _q_arg4 = qscriptvalue_cast<QString*>(context->argument(4));
        QFlags<QFileDialog::Option> _q_arg5 = qscriptvalue_cast<QFlags<QFileDialog::Option> >(context->argument(5));
        QStringList _q_result = QFileDialog::getOpenFileNames(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = QFileDialog::getSaveFileName();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_result = QFileDialog::getSaveFileName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_result = QFileDialog::getSaveFileName(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_result = QFileDialog::getSaveFileName(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        QString _q_result = QFileDialog::getSaveFileName(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        QString* _q_arg4 = qscriptvalue_cast<QString*>(context->argument(4));
        QString _q_result = QFileDialog::getSaveFileName(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 6) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        QString* _q_arg4 = qscriptvalue_cast<QString*>(context->argument(4));
        QFlags<QFileDialog::Option> _q_arg5 = qscriptvalue_cast<QFlags<QFileDialog::Option> >(context->argument(5));
        QString _q_result = QFileDialog::getSaveFileName(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFileDialog_throw_ambiguity_error_helper(context,
        qtscript_QFileDialog_function_names[_id],
        qtscript_QFileDialog_function_signatures[_id]);
}

static QScriptValue qtscript_QFileDialog_toScriptValue(QScriptEngine *engine, QFileDialog* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QFileDialog_fromScriptValue(const QScriptValue &value, QFileDialog* &out)
{
    out = qobject_cast<QFileDialog*>(value.toQObject());
}

QScriptValue qtscript_create_QFileDialog_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFileDialog*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFileDialog*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDialog*>()));
    for (int i = 0; i < 35; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFileDialog_prototype_call, qtscript_QFileDialog_function_lengths[i+5]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFileDialog_function_names[i+5]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QFileDialog*>(engine, qtscript_QFileDialog_toScriptValue, 
        qtscript_QFileDialog_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFileDialog_static_call, proto, qtscript_QFileDialog_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFileDialog_static_call,
            qtscript_QFileDialog_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QFileDialog_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("FileMode"),
        qtscript_create_QFileDialog_FileMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Option"),
        qtscript_create_QFileDialog_Option_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Options"),
        qtscript_create_QFileDialog_Options_class(engine));
    ctor.setProperty(QString::fromLatin1("DialogLabel"),
        qtscript_create_QFileDialog_DialogLabel_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ViewMode"),
        qtscript_create_QFileDialog_ViewMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("AcceptMode"),
        qtscript_create_QFileDialog_AcceptMode_class(engine, ctor));
    return ctor;
}
