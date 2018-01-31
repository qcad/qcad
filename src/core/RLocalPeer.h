/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

#ifndef RLOCALPEER_H
#define RLOCALPEER_H

#include "core_global.h"

#include <QLocalServer>
#include <QLocalSocket>
#include <QDir>

#include "RLockedFile.h"

class QCADCORE_EXPORT RLocalPeer : public QObject {
    Q_OBJECT

public:
    RLocalPeer(QObject* parent=0, const QString& appId = QString());
    bool isClient();
    bool sendMessage(const QString &message, int timeout);
    QString applicationId() const {
        return id;
    }

signals:
    void messageReceived(const QString& message);

protected slots:
    void receiveConnection();

protected:
    QString id;
    QString socketName;
    QLocalServer* server;
    RLockedFile lockFile;

private:
    static const char* ack;
};

#endif
