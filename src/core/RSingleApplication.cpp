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
#include <QAbstractEventDispatcher>
#include <QFileOpenEvent>
#include <QLabel>
#include <QMessageBox>
#include <QUrl>
#include <QTimer>
#include <QThread>
#include <QWidget>
#include <QQueue>

#include "RLocalPeer.h"
#include "RMainWindow.h"
#include "RSettings.h"
#include "RSingleApplication.h"

RSingleApplication* RSingleApplication::instance = NULL;

void RSingleApplication::sysInit(const QString &appId) {
    mutexEventsLocker = NULL;
    instance = this;
    actWin = 0;
    peer = new RLocalPeer(this, appId);
    connect(peer, SIGNAL(messageReceived(const QString&)), SIGNAL(messageReceived(const QString&)));
    //setStartDragDistance(10);
}

RSingleApplication::RSingleApplication(int &argc, char **argv, bool GUIenabled)
    : QApplication(argc, argv, GUIenabled) {
    sysInit();
}

RSingleApplication::RSingleApplication(const QString &appId, int &argc, char **argv, bool GUIenabled)
    : QApplication(argc, argv, GUIenabled)
{
    sysInit(appId);
}

/*
RSingleApplication::RSingleApplication(int &argc, char **argv, Type type)
    : QApplication(argc, argv, type) {
    sysInit();
}
*/


#if defined(Q_OS_X11)
RSingleApplication::RSingleApplication(Display* dpy, Qt::HANDLE visual, Qt::HANDLE cmap)
    : QApplication(dpy, visual, cmap) {
    sysInit();
}

RSingleApplication::RSingleApplication(Display *dpy, int &argc, char **argv, Qt::HANDLE visual, Qt::HANDLE cmap)
    : QApplication(dpy, argc, argv, visual, cmap) {
    sysInit();
}

RSingleApplication::RSingleApplication(Display* dpy, const QString &appId, int argc, char **argv, Qt::HANDLE visual, Qt::HANDLE cmap)
    : QApplication(dpy, argc, argv, visual, cmap) {
    sysInit(appId);
}
#endif

RSingleApplication::~RSingleApplication() {
}

RSingleApplication* RSingleApplication::getInstance() {
    return instance;
}

bool RSingleApplication::isRunning() {
    return peer->isClient();
}

bool RSingleApplication::sendMessage(const QString &message, int timeout) {
    return peer->sendMessage(message, timeout);
}

QString RSingleApplication::id() const {
    return peer->applicationId();
}

void RSingleApplication::setActivationWindow(QWidget* aw, bool activateOnMessage) {
    actWin = aw;
    if (activateOnMessage)
        connect(peer, SIGNAL(messageReceived(const QString&)), this, SLOT(activateWindow()));
    else
        disconnect(peer, SIGNAL(messageReceived(const QString&)), this, SLOT(activateWindow()));
}

QWidget* RSingleApplication::activationWindow() const {
    return actWin;
}

void RSingleApplication::activateWindow() {
    if (actWin) {
        actWin->setWindowState(actWin->windowState() & ~Qt::WindowMinimized);
        actWin->raise();
        actWin->activateWindow();
    }
}

bool RSingleApplication::event(QEvent* e) {
    QFileOpenEvent* foe = dynamic_cast<QFileOpenEvent*>(e);
    if (foe!=NULL) {
        emit(fileOpenRequestReceived(foe->file()));
        e->accept();
        //qDebug() << "RSingleApplication::event: type: " << e->type() << ": OK";
        //QMessageBox::information(NULL, "debug", QString("opening of file requested: %1 (%2)").arg(foe->file()).arg(foe->url().toString()));
        return true;
    }

    bool ret = QApplication::event(e);
    return ret;
}
