#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

#ifndef Q_OS_WIN
QScriptValue qtscript_create_QSslKey_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSslConfiguration_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSslError_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSslCertificate_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSslCipher_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSsl_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSslSocket_class(QScriptEngine *engine);
#endif

QScriptValue qtscript_create_QNetworkProxyQuery_class(QScriptEngine *engine);
QScriptValue qtscript_create_QUrlInfo_class(QScriptEngine *engine);
QScriptValue qtscript_create_QHostInfo_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkCacheMetaData_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkCookie_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkProxyFactory_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkAddressEntry_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkInterface_class(QScriptEngine *engine);
QScriptValue qtscript_create_QHostAddress_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkProxy_class(QScriptEngine *engine);
QScriptValue qtscript_create_QIPv6Address_class(QScriptEngine *engine);
QScriptValue qtscript_create_QHttpHeader_class(QScriptEngine *engine);
QScriptValue qtscript_create_QAuthenticator_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkRequest_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkAccessManager_class(QScriptEngine *engine);
QScriptValue qtscript_create_QTcpServer_class(QScriptEngine *engine);
QScriptValue qtscript_create_QFtp_class(QScriptEngine *engine);
QScriptValue qtscript_create_QHttpResponseHeader_class(QScriptEngine *engine);
QScriptValue qtscript_create_QAbstractNetworkCache_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkCookieJar_class(QScriptEngine *engine);
QScriptValue qtscript_create_QHttp_class(QScriptEngine *engine);
QScriptValue qtscript_create_QLocalServer_class(QScriptEngine *engine);
QScriptValue qtscript_create_QHttpRequestHeader_class(QScriptEngine *engine);
QScriptValue qtscript_create_QAbstractSocket_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkDiskCache_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkReply_class(QScriptEngine *engine);
QScriptValue qtscript_create_QLocalSocket_class(QScriptEngine *engine);
QScriptValue qtscript_create_QUdpSocket_class(QScriptEngine *engine);
QScriptValue qtscript_create_QTcpSocket_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_network_class_names[] = {
#ifndef Q_OS_WIN
    "QSslKey",
#endif
    "QNetworkProxyQuery"
#ifndef Q_OS_WIN
    , "QSslConfiguration"
#endif
    , "QUrlInfo"
    , "QHostInfo"
    , "QNetworkCacheMetaData"
    , "QNetworkCookie"
    , "QNetworkProxyFactory"
    , "QNetworkAddressEntry"
    , "QNetworkInterface"
#ifndef Q_OS_WIN
    , "QSslError"
    , "QSslCertificate"
    , "QSslCipher"
#endif
    , "QHostAddress"
    , "QNetworkProxy"
    , "QIPv6Address"
    , "QHttpHeader"
#ifndef Q_OS_WIN
    , "QSsl"
#endif
    , "QAuthenticator"
    , "QNetworkRequest"
    , "QNetworkAccessManager"
    , "QTcpServer"
    , "QFtp"
    , "QHttpResponseHeader"
    , "QAbstractNetworkCache"
    , "QNetworkCookieJar"
    , "QHttp"
    , "QLocalServer"
    , "QHttpRequestHeader"
    , "QAbstractSocket"
    , "QNetworkDiskCache"
    , "QNetworkReply"
    , "QLocalSocket"
    , "QUdpSocket"
    , "QTcpSocket"
#ifndef Q_OS_WIN
    , "QSslSocket"
#endif
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_network_class_functions[] = {
#ifndef Q_OS_WIN
    qtscript_create_QSslKey_class,
#endif
    qtscript_create_QNetworkProxyQuery_class
#ifndef Q_OS_WIN
    , qtscript_create_QSslConfiguration_class
#endif
    , qtscript_create_QUrlInfo_class
    , qtscript_create_QHostInfo_class
    , qtscript_create_QNetworkCacheMetaData_class
    , qtscript_create_QNetworkCookie_class
    , qtscript_create_QNetworkProxyFactory_class
    , qtscript_create_QNetworkAddressEntry_class
    , qtscript_create_QNetworkInterface_class
#ifndef Q_OS_WIN
    , qtscript_create_QSslError_class
    , qtscript_create_QSslCertificate_class
    , qtscript_create_QSslCipher_class
#endif
    , qtscript_create_QHostAddress_class
    , qtscript_create_QNetworkProxy_class
    , qtscript_create_QIPv6Address_class
    , qtscript_create_QHttpHeader_class
#ifndef Q_OS_WIN
    , qtscript_create_QSsl_class
#endif
    , qtscript_create_QAuthenticator_class
    , qtscript_create_QNetworkRequest_class
    , qtscript_create_QNetworkAccessManager_class
    , qtscript_create_QTcpServer_class
    , qtscript_create_QFtp_class
    , qtscript_create_QHttpResponseHeader_class
    , qtscript_create_QAbstractNetworkCache_class
    , qtscript_create_QNetworkCookieJar_class
    , qtscript_create_QHttp_class
    , qtscript_create_QLocalServer_class
    , qtscript_create_QHttpRequestHeader_class
    , qtscript_create_QAbstractSocket_class
    , qtscript_create_QNetworkDiskCache_class
    , qtscript_create_QNetworkReply_class
    , qtscript_create_QLocalSocket_class
    , qtscript_create_QUdpSocket_class
    , qtscript_create_QTcpSocket_class
#ifndef Q_OS_WIN
    , qtscript_create_QSslSocket_class
#endif
};

void qtscript_initialize_com_trolltech_qt_network_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
#ifndef Q_OS_WIN
    for (int i = 0; i < 29; ++i) {
#else
    for (int i = 0; i < 36; ++i) {
#endif
        extensionObject.setProperty(qtscript_com_trolltech_qt_network_class_names[i],
            qtscript_com_trolltech_qt_network_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
