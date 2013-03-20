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

#ifndef RHELPBROWSER_H
#define RHELPBROWSER_H

#include <QObject>
#include <QProcess>
#include <QString>

#include "RSingleton.h"

/**
 * \ingroup gui_qt
 *
 * \scriptable
 */
class RHelpBrowser: public QObject, public RSingleton {
    Q_OBJECT

    friend class RSingleton;

public:
    RHelpBrowser();
    ~RHelpBrowser();
    void showDocumentation(const QString &file);
    static RHelpBrowser& getInstance();

public slots:
    void error(QProcess::ProcessError e);
    void readStandardOutput();
    void readStandardError();
    
private:
    bool startAssistant();
    QProcess *proc;
};

Q_DECLARE_METATYPE(RHelpBrowser*)

#endif
