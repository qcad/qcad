/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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
#include <QDebug>

#include <QByteArray>
#include <QDir>
#include <QLibraryInfo>

#include <QMessageBox>


#include "RDebug.h"
#include "RHelpBrowser.h"
#include "RSettings.h"

RHelpBrowser::RHelpBrowser() :
    proc(0) {
}

RHelpBrowser::~RHelpBrowser() {
    if (proc && proc->state() == QProcess::Running) {
        proc->terminate();
        proc->waitForFinished(3000);
    }
    delete proc;
}

RHelpBrowser& RHelpBrowser::getInstance() {
    return RSingleton::getInstance<RHelpBrowser>();
}

void RHelpBrowser::showDocumentation(const QString &page) {
    if (!startAssistant()) {
        return;
    }

    QByteArray ba("SetSource ");
    // ba.append("qthelp://com.ribbonsoft.qcad3/usermanual/");
    ba.append("qthelp://com.ribbonsoft.qcad3/usermanual/support/doc/manual/");

    proc->write(ba + page.toLocal8Bit() + '\0');
}

bool RHelpBrowser::startAssistant() {
    if (!proc) {
        proc = new QProcess();
    }

    if (proc->state() != QProcess::Running) {
        QString app;
#if defined(Q_OS_WIN)
        app = QString("assistant.exe");
#elif defined(Q_OS_MAC)
        //app += QLatin1String("Assistant.app/Contents/MacOS/Assistant");
        //app = QString("../MacOS/Assistant");
        app = QString("../Resources/bin/Assistant.app/Contents/MacOS/Assistant");
#else
        qDebug() << "current dir: " << QDir::currentPath();
        qDebug() << "app dir: " << QApplication::applicationDirPath();

        app = QApplication::applicationDirPath() + QString("/assistant");

        //QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        //env.insert("LD_LIBRARY_PATH", ".");
        //proc->setProcessEnvironment(env);
#endif
        //QProcessEnvironment env = proc->processEnvironment();
        //env.value("LD_LIBRARY_PATH");

        // look up appropriate documentation:
        QString localeString = RSettings::getLocale();
        QLocale locale(localeString);
        //QString countryString = QLocale::countryToString(locale.country());
        QString languageString = QLocale::languageToString(locale.language());

        // look first for qcad_user_manual_de_ch.qhc,
        // then qcad_user_manual_de.qhc,
        // then qcad_user_manual.qhc
        QStringList qhcFiles;
        qhcFiles << "doc/manual/qcad_user_manual_" + localeString.toLower() + ".qhc";
        qhcFiles << "doc/manual/qcad_user_manual_" + languageString.toLower() + ".qhc";

        // fall back: english user manual:
        qhcFiles << "doc/manual/qcad_user_manual_en.qhc";

        QString qhcFile;
        for (int i=0; i<qhcFiles.count(); i++) {
            if (QFileInfo(qhcFiles[i]).exists()) {
                qhcFile = qhcFiles[i];
                break;
            }
        }

        if (qhcFile.isEmpty()) {
            qWarning() << "no user manual found, tried: " << qhcFiles.join(", ");
            QMessageBox::warning(0, QCoreApplication::applicationName(),
                    QObject::tr("Cannot find user manual at: %1").arg(qhcFiles.join(", ")));
            return false;
        }

        QStringList args;
        args << "-collectionFile"
             << qhcFile
             << "-enableRemoteControl";

        proc->start(app, args);

        connect(proc, SIGNAL(error(QProcess::ProcessError)), SLOT(error(QProcess::ProcessError)));
        connect(proc, SIGNAL(readyReadStandardOutput()), SLOT(readStandardOutput()));
        connect(proc, SIGNAL(readyReadStandardError()), SLOT(readStandardError()));

        if (!proc->waitForStarted()) {
            qDebug() << "assistent process exit status: " << (int)proc->exitStatus();
            qDebug() << "assistent process exit code: " << proc->exitCode();
            QMessageBox::critical(0, QCoreApplication::applicationName(),
                    QObject::tr("Unable to launch Qt Assistant (%1)").arg(app));
            return false;
        }
    }
    return true;
}

void RHelpBrowser::error(QProcess::ProcessError e) {
    qDebug() << "assistent process error: " << (int)e;
}

void RHelpBrowser::readStandardOutput() {
    if (proc==NULL) {
        return;
    }

    QByteArray ba = proc->readAllStandardOutput();
    qDebug() << "Assistant process (stdout): " << ba.constData();
}

void RHelpBrowser::readStandardError() {
    if (proc==NULL) {
        return;
    }

    QByteArray ba = proc->readAllStandardError();
    qDebug() << "Assistant process (stderr): " << ba.constData();
}

