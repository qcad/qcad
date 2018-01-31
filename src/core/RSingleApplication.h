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

#ifndef RSINGLEAPPLICATION_H
#define RSINGLEAPPLICATION_H

#include "core_global.h"

#include <QApplication>
#include <QMetaType>
#include <QMutex>

class RLocalPeer;

class QCADCORE_EXPORT RSingleApplication : public QApplication {
    Q_OBJECT

public:
    RSingleApplication(int& argc, char **argv, bool GUIenabled = true);
    RSingleApplication(const QString& id, int& argc, char **argv, bool GUIenabled = true);
    //RSingleApplication(int& argc, char **argv, Type type);
#if defined(Q_OS_X11)
    RSingleApplication(Display* dpy, Qt::HANDLE visual = 0, Qt::HANDLE colormap = 0);
    RSingleApplication(Display *dpy, int& argc, char **argv, Qt::HANDLE visual = 0, Qt::HANDLE cmap= 0);
    RSingleApplication(Display* dpy, const QString& appId, int argc, char **argv, Qt::HANDLE visual = 0, Qt::HANDLE colormap = 0);
#endif

    ~RSingleApplication();

    static RSingleApplication* getInstance();

    bool isRunning();
    QString id() const;

    void setActivationWindow(QWidget* aw, bool activateOnMessage = true);
    QWidget* activationWindow() const;

public slots:
    bool sendMessage(const QString& message, int timeout = 5000);
    void activateWindow();

signals:
    void messageReceived(const QString& message);
    void fileOpenRequestReceived(const QString& fileName);

protected:
    virtual bool event(QEvent* e);

private:
    void sysInit(const QString& appId = QString());
    RLocalPeer* peer;
    QWidget* actWin;
    QMutex mutexEvents;
    QThread* mutexEventsLocker;
    static RSingleApplication* instance;
};

Q_DECLARE_METATYPE(RSingleApplication*)

#endif
