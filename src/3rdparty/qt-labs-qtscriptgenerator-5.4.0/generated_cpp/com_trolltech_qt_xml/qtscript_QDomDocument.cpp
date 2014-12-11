#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qdom.h>
#include <QVariant>
#include <qbytearray.h>
#include <qdom.h>
#include <qiodevice.h>
#include <qtextstream.h>
#include <qxml.h>

static const char * const qtscript_QDomDocument_function_names[] = {
    "QDomDocument"
    // static
    // prototype
    , "createAttribute"
    , "createAttributeNS"
    , "createCDATASection"
    , "createComment"
    , "createDocumentFragment"
    , "createElement"
    , "createElementNS"
    , "createEntityReference"
    , "createProcessingInstruction"
    , "createTextNode"
    , "doctype"
    , "documentElement"
    , "elementById"
    , "elementsByTagName"
    , "elementsByTagNameNS"
    , "implementation"
    , "importNode"
    , "setContent"
    , "toByteArray"
    , "toString"
};

static const char * const qtscript_QDomDocument_function_signatures[] = {
    "\nQDomDocument x\nQDomDocumentType doctype\nString name"
    // static
    // prototype
    , "String name"
    , "String nsURI, String qName"
    , "String data"
    , "String data"
    , ""
    , "String tagName"
    , "String nsURI, String qName"
    , "String name"
    , "String target, String data"
    , "String data"
    , ""
    , ""
    , "String elementId"
    , "String tagname"
    , "String nsURI, String localName"
    , ""
    , "QDomNode importedNode, bool deep"
    , "QIODevice dev, String errorMsg, int errorLine, int errorColumn\nQIODevice dev, bool namespaceProcessing, String errorMsg, int errorLine, int errorColumn\nQXmlInputSource source, QXmlReader reader, String errorMsg, int errorLine, int errorColumn\nQXmlInputSource source, bool namespaceProcessing, String errorMsg, int errorLine, int errorColumn\nQByteArray text, String errorMsg, int errorLine, int errorColumn\nQByteArray text, bool namespaceProcessing, String errorMsg, int errorLine, int errorColumn\nString text, String errorMsg, int errorLine, int errorColumn\nString text, bool namespaceProcessing, String errorMsg, int errorLine, int errorColumn"
    , "int arg__1"
    , "int arg__1"
};

static const int qtscript_QDomDocument_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 2
    , 1
    , 1
    , 0
    , 1
    , 2
    , 1
    , 2
    , 1
    , 0
    , 0
    , 1
    , 1
    , 2
    , 0
    , 2
    , 5
    , 1
    , 1
};

static QScriptValue qtscript_QDomDocument_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDomDocument::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDomDocument)
Q_DECLARE_METATYPE(QDomDocument*)
Q_DECLARE_METATYPE(QDomAttr)
Q_DECLARE_METATYPE(QDomCDATASection)
Q_DECLARE_METATYPE(QDomComment)
Q_DECLARE_METATYPE(QDomDocumentFragment)
Q_DECLARE_METATYPE(QDomElement)
Q_DECLARE_METATYPE(QDomEntityReference)
Q_DECLARE_METATYPE(QDomProcessingInstruction)
Q_DECLARE_METATYPE(QDomText)
Q_DECLARE_METATYPE(QDomDocumentType)
Q_DECLARE_METATYPE(QDomNodeList)
Q_DECLARE_METATYPE(QDomImplementation)
Q_DECLARE_METATYPE(QDomNode)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QString*)
Q_DECLARE_METATYPE(int*)
Q_DECLARE_METATYPE(QXmlInputSource*)
Q_DECLARE_METATYPE(QXmlReader*)
Q_DECLARE_METATYPE(QDomNode*)

//
// QDomDocument
//

static QScriptValue qtscript_QDomDocument_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 20;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDomDocument* _q_self = qscriptvalue_cast<QDomDocument*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDomDocument.%0(): this object is not a QDomDocument")
            .arg(qtscript_QDomDocument_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomAttr _q_result = _q_self->createAttribute(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QDomAttr _q_result = _q_self->createAttributeNS(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomCDATASection _q_result = _q_self->createCDATASection(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomComment _q_result = _q_self->createComment(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QDomDocumentFragment _q_result = _q_self->createDocumentFragment();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomElement _q_result = _q_self->createElement(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QDomElement _q_result = _q_self->createElementNS(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomEntityReference _q_result = _q_self->createEntityReference(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QDomProcessingInstruction _q_result = _q_self->createProcessingInstruction(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomText _q_result = _q_self->createTextNode(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QDomDocumentType _q_result = _q_self->doctype();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QDomElement _q_result = _q_self->documentElement();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomElement _q_result = _q_self->elementById(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomNodeList _q_result = _q_self->elementsByTagName(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QDomNodeList _q_result = _q_self->elementsByTagNameNS(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QDomImplementation _q_result = _q_self->implementation();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        QDomNode _q_arg0 = qscriptvalue_cast<QDomNode>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        QDomNode _q_result = _q_self->importNode(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            bool _q_result = _q_self->setContent(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            bool _q_result = _q_self->setContent(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = _q_self->setContent(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && qscriptvalue_cast<QString*>(context->argument(1))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QString* _q_arg1 = qscriptvalue_cast<QString*>(context->argument(1));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && context->argument(1).isBoolean()) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            bool _q_arg1 = context->argument(1).toBoolean();
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QXmlInputSource*>(context->argument(0))
            && qscriptvalue_cast<QXmlReader*>(context->argument(1))) {
            QXmlInputSource* _q_arg0 = qscriptvalue_cast<QXmlInputSource*>(context->argument(0));
            QXmlReader* _q_arg1 = qscriptvalue_cast<QXmlReader*>(context->argument(1));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QXmlInputSource*>(context->argument(0))
            && context->argument(1).isBoolean()) {
            QXmlInputSource* _q_arg0 = qscriptvalue_cast<QXmlInputSource*>(context->argument(0));
            bool _q_arg1 = context->argument(1).toBoolean();
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QString*>(context->argument(1))) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QString* _q_arg1 = qscriptvalue_cast<QString*>(context->argument(1));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && context->argument(1).isBoolean()) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            bool _q_arg1 = context->argument(1).toBoolean();
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && qscriptvalue_cast<QString*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            QString* _q_arg1 = qscriptvalue_cast<QString*>(context->argument(1));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isBoolean()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_arg1 = context->argument(1).toBoolean();
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && qscriptvalue_cast<QString*>(context->argument(1))
            && qscriptvalue_cast<int*>(context->argument(2))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QString* _q_arg1 = qscriptvalue_cast<QString*>(context->argument(1));
            int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && context->argument(1).isBoolean()
            && qscriptvalue_cast<QString*>(context->argument(2))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            bool _q_arg1 = context->argument(1).toBoolean();
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QXmlInputSource*>(context->argument(0))
            && qscriptvalue_cast<QXmlReader*>(context->argument(1))
            && qscriptvalue_cast<QString*>(context->argument(2))) {
            QXmlInputSource* _q_arg0 = qscriptvalue_cast<QXmlInputSource*>(context->argument(0));
            QXmlReader* _q_arg1 = qscriptvalue_cast<QXmlReader*>(context->argument(1));
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QXmlInputSource*>(context->argument(0))
            && context->argument(1).isBoolean()
            && qscriptvalue_cast<QString*>(context->argument(2))) {
            QXmlInputSource* _q_arg0 = qscriptvalue_cast<QXmlInputSource*>(context->argument(0));
            bool _q_arg1 = context->argument(1).toBoolean();
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QString*>(context->argument(1))
            && qscriptvalue_cast<int*>(context->argument(2))) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QString* _q_arg1 = qscriptvalue_cast<QString*>(context->argument(1));
            int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && context->argument(1).isBoolean()
            && qscriptvalue_cast<QString*>(context->argument(2))) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            bool _q_arg1 = context->argument(1).toBoolean();
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && qscriptvalue_cast<QString*>(context->argument(1))
            && qscriptvalue_cast<int*>(context->argument(2))) {
            QString _q_arg0 = context->argument(0).toString();
            QString* _q_arg1 = qscriptvalue_cast<QString*>(context->argument(1));
            int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isBoolean()
            && qscriptvalue_cast<QString*>(context->argument(2))) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_arg1 = context->argument(1).toBoolean();
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 4) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && qscriptvalue_cast<QString*>(context->argument(1))
            && qscriptvalue_cast<int*>(context->argument(2))
            && qscriptvalue_cast<int*>(context->argument(3))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QString* _q_arg1 = qscriptvalue_cast<QString*>(context->argument(1));
            int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
            int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && context->argument(1).isBoolean()
            && qscriptvalue_cast<QString*>(context->argument(2))
            && qscriptvalue_cast<int*>(context->argument(3))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            bool _q_arg1 = context->argument(1).toBoolean();
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QXmlInputSource*>(context->argument(0))
            && qscriptvalue_cast<QXmlReader*>(context->argument(1))
            && qscriptvalue_cast<QString*>(context->argument(2))
            && qscriptvalue_cast<int*>(context->argument(3))) {
            QXmlInputSource* _q_arg0 = qscriptvalue_cast<QXmlInputSource*>(context->argument(0));
            QXmlReader* _q_arg1 = qscriptvalue_cast<QXmlReader*>(context->argument(1));
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QXmlInputSource*>(context->argument(0))
            && context->argument(1).isBoolean()
            && qscriptvalue_cast<QString*>(context->argument(2))
            && qscriptvalue_cast<int*>(context->argument(3))) {
            QXmlInputSource* _q_arg0 = qscriptvalue_cast<QXmlInputSource*>(context->argument(0));
            bool _q_arg1 = context->argument(1).toBoolean();
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QString*>(context->argument(1))
            && qscriptvalue_cast<int*>(context->argument(2))
            && qscriptvalue_cast<int*>(context->argument(3))) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QString* _q_arg1 = qscriptvalue_cast<QString*>(context->argument(1));
            int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
            int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && context->argument(1).isBoolean()
            && qscriptvalue_cast<QString*>(context->argument(2))
            && qscriptvalue_cast<int*>(context->argument(3))) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            bool _q_arg1 = context->argument(1).toBoolean();
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && qscriptvalue_cast<QString*>(context->argument(1))
            && qscriptvalue_cast<int*>(context->argument(2))
            && qscriptvalue_cast<int*>(context->argument(3))) {
            QString _q_arg0 = context->argument(0).toString();
            QString* _q_arg1 = qscriptvalue_cast<QString*>(context->argument(1));
            int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
            int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isBoolean()
            && qscriptvalue_cast<QString*>(context->argument(2))
            && qscriptvalue_cast<int*>(context->argument(3))) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_arg1 = context->argument(1).toBoolean();
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 5) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && context->argument(1).isBoolean()
            && qscriptvalue_cast<QString*>(context->argument(2))
            && qscriptvalue_cast<int*>(context->argument(3))
            && qscriptvalue_cast<int*>(context->argument(4))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            bool _q_arg1 = context->argument(1).toBoolean();
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
            int* _q_arg4 = qscriptvalue_cast<int*>(context->argument(4));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QXmlInputSource*>(context->argument(0))
            && qscriptvalue_cast<QXmlReader*>(context->argument(1))
            && qscriptvalue_cast<QString*>(context->argument(2))
            && qscriptvalue_cast<int*>(context->argument(3))
            && qscriptvalue_cast<int*>(context->argument(4))) {
            QXmlInputSource* _q_arg0 = qscriptvalue_cast<QXmlInputSource*>(context->argument(0));
            QXmlReader* _q_arg1 = qscriptvalue_cast<QXmlReader*>(context->argument(1));
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
            int* _q_arg4 = qscriptvalue_cast<int*>(context->argument(4));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QXmlInputSource*>(context->argument(0))
            && context->argument(1).isBoolean()
            && qscriptvalue_cast<QString*>(context->argument(2))
            && qscriptvalue_cast<int*>(context->argument(3))
            && qscriptvalue_cast<int*>(context->argument(4))) {
            QXmlInputSource* _q_arg0 = qscriptvalue_cast<QXmlInputSource*>(context->argument(0));
            bool _q_arg1 = context->argument(1).toBoolean();
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
            int* _q_arg4 = qscriptvalue_cast<int*>(context->argument(4));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && context->argument(1).isBoolean()
            && qscriptvalue_cast<QString*>(context->argument(2))
            && qscriptvalue_cast<int*>(context->argument(3))
            && qscriptvalue_cast<int*>(context->argument(4))) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            bool _q_arg1 = context->argument(1).toBoolean();
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
            int* _q_arg4 = qscriptvalue_cast<int*>(context->argument(4));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isBoolean()
            && qscriptvalue_cast<QString*>(context->argument(2))
            && qscriptvalue_cast<int*>(context->argument(3))
            && qscriptvalue_cast<int*>(context->argument(4))) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_arg1 = context->argument(1).toBoolean();
            QString* _q_arg2 = qscriptvalue_cast<QString*>(context->argument(2));
            int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
            int* _q_arg4 = qscriptvalue_cast<int*>(context->argument(4));
            bool _q_result = _q_self->setContent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->toByteArray();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QByteArray _q_result = _q_self->toByteArray(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toString();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->toString(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomDocument_throw_ambiguity_error_helper(context,
        qtscript_QDomDocument_function_names[_id+1],
        qtscript_QDomDocument_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDomDocument_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDomDocument(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QDomDocument _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QDomDocument>() == context->argument(0).toVariant().userType())) {
            QDomDocument _q_arg0 = qscriptvalue_cast<QDomDocument>(context->argument(0));
            QDomDocument _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QDomDocumentType>() == context->argument(0).toVariant().userType())) {
            QDomDocumentType _q_arg0 = qscriptvalue_cast<QDomDocumentType>(context->argument(0));
            QDomDocument _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QDomDocument _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomDocument_throw_ambiguity_error_helper(context,
        qtscript_QDomDocument_function_names[_id],
        qtscript_QDomDocument_function_signatures[_id]);
}

QScriptValue qtscript_create_QDomDocument_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDomDocument*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDomDocument*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDomNode*>()));
    for (int i = 0; i < 20; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDomDocument_prototype_call, qtscript_QDomDocument_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDomDocument_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDomDocument>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QDomDocument*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDomDocument_static_call, proto, qtscript_QDomDocument_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
