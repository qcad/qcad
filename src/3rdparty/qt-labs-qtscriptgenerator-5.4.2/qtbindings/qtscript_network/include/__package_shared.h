
#pragma once

#include <qobject.h>

#ifdef QT_NO_SSL
class QSslError : public QObject {
	Q_OBJECT
public:
	QSslError(): QObject() {}
	QSslError(const QSslError &) : QObject() {}
};
class QSslConfiguration : public QObject {
	Q_OBJECT
public:
	QSslConfiguration() : QObject() {}
	QSslConfiguration(const QSslConfiguration &) : QObject() {}
};
#endif

