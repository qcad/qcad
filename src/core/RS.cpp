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
#include <QtGlobal>
#include <QDir>
#include <QFileInfo>
#include <QHostInfo>
#ifdef Q_OS_WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "RColor.h"
#include "RGlobal.h"
#include "RLinetype.h"
#include "RLineweight.h"
#include "RPropertyAttributes.h"
#include "RSettings.h"
#include "RVector.h"

#if defined(Q_WS_X11)
#include <X11/Xlib.h>
// fix clash between X11 Bool and QVariant::Bool:
#ifdef Bool
#undef Bool
#endif
#endif

const double RS::PointTolerance = 1.0e-9;
const double RS::AngleTolerance = 1.0e-9;

/**
 * \return Unique combination of system ID (linux, osx, win) and host name.
 * E.g. "linux_vertigo". Used for test data that may differ on different machines.
 */
QString RS::getHostId() {
    return QString("%1_%2")
            .arg(getSystemId())
#if defined(Q_OS_LINUX)
    .arg(getenv("HOSTNAME"));
#elif defined(Q_OS_MAC)
    // environment variable HOSTNAME not exported on OS X by default:
    .arg(QHostInfo::localHostName());
#elif defined(Q_OS_WIN)
    .arg(getenv("COMPUTERNAME"));
#else
    .arg("unknown");
#endif
}

/**
 * \return Unique system ID ("linux", "osx", "win").
 */
QString RS::getSystemId() {
#if defined(Q_OS_LINUX)
    return "linux";
#elif defined(Q_OS_MAC)
    return "osx";
#elif defined(Q_OS_WIN)
    return "win";
#else
    return "unknown";
#endif
}

QString RS::getWindowManagerId() {
    static QString wm = "";

#if defined(Q_WS_X11)
    Display *dpy;
    Window win;

    Atom wmCheckAtom;
    Atom windowAtom;
    Atom nameAtom;
    Atom utf8Atom;
    Atom type;

    int format;
    unsigned long nitems, bytes;
    unsigned char *data;

    char *wmname;
    int res;
#endif

    if (!wm.isEmpty()) {
        return wm;
    }

    wm = "unknown";

#if defined(Q_WS_MAC)
    wm = "osx";
#elif defined(Q_WS_WIN)
    wm = "win";
#elif defined(Q_WS_X11)

    dpy = NULL;
    data = NULL;

    dpy = XOpenDisplay(NULL);
    if (dpy) {

        wmCheckAtom = XInternAtom(dpy, "_NET_SUPPORTING_WM_CHECK", False);
        windowAtom = XInternAtom(dpy, "WINDOW", False);
        nameAtom = XInternAtom(dpy, "_NET_WM_NAME", False);
        utf8Atom = XInternAtom(dpy, "UTF8_STRING", False);

        res = XGetWindowProperty(
            dpy,
            RootWindow(dpy, 0),
            wmCheckAtom,
            0LL,
            ~0LL,
            False,
            windowAtom,
            &type,
            &format,
            &nitems,
            &bytes,
            &data);

        if ((res == Success) &&
            (type == windowAtom) &&
            (format == 32)) {

            win = *(Window *)data;
            XFree(data);

            res = XGetWindowProperty(
                dpy,
                win,
                nameAtom,
                0LL,
                ~0LL,
                False,
                utf8Atom,
                &type,
                &format,
                &nitems,
                &bytes,
                &data);

            if ((res == Success) &&
                (type == utf8Atom) &&
                (format == 8)) {

                wmname = (char *)malloc(nitems + 1);
                if (wmname) {
                    memcpy(wmname, data, nitems);
                    wmname[nitems] = '\0';
                    if (strncasecmp(wmname, "KWin", 4) == 0) {
                        wm = "kde";
                    } else if ((strncasecmp(wmname, "GNOME Shell", 11) == 0) ||
                               (strncasecmp(wmname, "Compiz", 6) == 0) ||
                               (strncasecmp(wmname, "Metacity", 8) == 0) ||
                               (strncasecmp(wmname, "Mutter", 6) == 0) ||
                               (strncasecmp(wmname, "Marco", 5) == 0)) {
                        wm = "gnome";
                    } else if (strncasecmp(wmname, "Xfwm", 4) == 0) {
                        wm = "xfce";
                    } else {
                        wm = "unknown";
                    }
                    free(wmname);
                    wmname = NULL;
                }
            }
        }
    }

    if (data) {
        XFree(data);
    }

    if (dpy) {
        XCloseDisplay(dpy);
    }
#endif

    return wm;
}

bool RS::compare(const QVariant& v1, const QVariant& v2) {
    //qDebug() << "RS::compare: " << v1 << v2;
    // 20120609: tolerance when comparing doubles (property editor)
    // 20140513: handle basic types since Qt 5 thinks it can convert double, bool, int to line type
    if (v1.type()==QVariant::Double && v2.type()==QVariant::Double) {
        return fabs(v1.toDouble() - v2.toDouble()) < RS::PointTolerance;
    }
    if (v1.type()==QVariant::Bool && v2.type()==QVariant::Bool) {
        return v1.toBool()==v2.toBool();
    }
    if (v1.type()==QVariant::Int && v2.type()==QVariant::Int) {
        return v1.toInt()==v2.toInt();
    }
    if (v1.type()==QVariant::UInt && v2.type()==QVariant::UInt) {
        return v1.toUInt()==v2.toUInt();
    }
    if (v1.type()==QVariant::LongLong && v2.type()==QVariant::LongLong) {
        return v1.toLongLong()==v2.toLongLong();
    }
    if (v1.type()==QVariant::ULongLong && v2.type()==QVariant::ULongLong) {
        return v1.toULongLong()==v2.toULongLong();
    }
    if (v1.type()==QVariant::String && v2.type()==QVariant::String) {
        return v1.toString()==v2.toString();
    }

    if (v1.canConvert<RColor> () && v2.canConvert<RColor> ()) {
        return v1.value<RColor> () == v2.value<RColor> ();
    }
    if (v1.canConvert<RLinetype> () && v2.canConvert<RLinetype> ()) {
        return v1.value<RLinetype> () == v2.value<RLinetype> ();
    }
    if (v1.canConvert<RLineweight::Lineweight> () && v2.canConvert<RLineweight::Lineweight> ()) {
        return v1.value<RLineweight::Lineweight> () == v2.value<RLineweight::Lineweight> ();
    }
    if (v1.canConvert<QList<RVector> > () && v2.canConvert<QList<RVector> > ()) {
        //qDebug() << "list 1: " << v1.value<QList<RVector> >();
        //qDebug() << "list 2: " << v2.value<QList<RVector> >();
        //qDebug() << "equal: " << (v1.value<QList<RVector> > () == v2.value<QList<RVector> > ());
        return v1.value<QList<RVector> > () == v2.value<QList<RVector> > ();
    }
//    if (v1.canConvert<QList<double> > () && v2.canConvert<QList<double> > ()) {
//        qDebug() << "list 1: " << v1.value<QList<double> >();
//        qDebug() << "list 2: " << v2.value<QList<double> >();
//        qDebug() << "equal: " << (v1.value<QList<double> > () == v2.value<QList<double> > ());
//        return v1.value<QList<double> > () == v2.value<QList<double> > ();
//    }

//    if (v1.canConvert<QList<QPair<int, double> > >() && v2.canConvert<QList<QPair<int, double> > >()) {
//        qDebug() << "list 1 len: " << v1.value<QList<QPair<int, double> > >().length();
//        qDebug() << "list 2 len: " << v2.value<QList<QPair<int, double> > >().length();
//        qDebug() << "list 1: " << v1.value<QList<QPair<int, double> > >();
//        qDebug() << "list 2: " << v2.value<QList<QPair<int, double> > >();
//        qDebug() << "equal (variant): " << (v1 == v2);
//        qDebug() << "equal: " << (v1.value<QList<QPair<int, double> > > () == v2.value<QList<QPair<int, double> > > ());
//        return v1.value<QList<QPair<int, double> > >() == v2.value<QList<QPair<int, double> > >();
//        //return false;
//    }

    //qDebug() << "using ==";
    return v1 == v2;
}

bool RS::compare(const QPair<QVariant, RPropertyAttributes>& p1, const QPair<
        QVariant, RPropertyAttributes>& p2) {
    return compare(p1.first, p2.first);
}

/**
 * \return Number of CPU cores available.
 */
int RS::getCpuCores() {
    static int cores = -1;

    if (cores!=-1) {
        return cores;
    }

#ifdef Q_OS_WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo( &sysinfo );
    cores = sysinfo.dwNumberOfProcessors;
#elif defined(Q_OS_UNIX)
    cores = sysconf( _SC_NPROCESSORS_ONLN );
#elif defined (Q_OS_MAC) || defined (Q_OS_BSD4) || defined (Q_OS_FREEBSD) || defined (Q_OS_NETBSD) || defined (Q_OS_OPENBSD)
    nt mib[4];
    size_t len;

    /* set the mib for hw.ncpu */
    mib[0] = CTL_HW;
    mib[1] = HW_AVAILCPU; // alternatively, try HW_NCPU;

    /* get the number of CPUs from the system */
    sysctl(mib, 2, &cores, &len, NULL, 0);

    if (cores < 1) {
        mib[1] = HW_NCPU;
        sysctl( mib, 2, &cores, &len, NULL, 0 );
    }
#elif defined(Q_OS_HPUX)
    cores = mpctl(MPC_GETNUMSPUS, NULL, NULL);
#elif defined(Q_OS_IRIX)
    cores = sysconf( _SC_NPROC_ONLN );
#endif

    if (cores < 1) {
        cores = 1;
    }
    return cores;
}

/**
 * \return List of all directories in subdirectory 'subDirectory' in
 * all possible QCAD directories.
 */
QStringList RS::getDirectoryList(const QString& subDirectory) {
    QStringList dirList;

    QString appDir = QCoreApplication::applicationDirPath();
    QFileInfo fi(appDir);
    if (fi.fileName() == "debug" || fi.fileName() == "release") {
        appDir = fi.absolutePath();
    }

#ifdef Q_OS_MAC
    // Mac OS X app bundle:
    dirList.append(appDir + "/../Resources/" + subDirectory);
    dirList.append(appDir + "/../../../" + subDirectory);
    dirList.append(QDir::currentPath() + "/" + subDirectory);
#else
    dirList.append(appDir + "/" + subDirectory);
#endif

    /*
#ifdef Q_OS_MAC
    if (subDirectory!="library") {
#endif
        //local (application) directory has priority over other dirs:
        dirList.append(appDir + QDir::separator() + subDirectory);

 #ifdef Q_OS_LINUX
        QString appDirName = QSettings.applicationName();
        // Redhat style:
        dirList.append("/usr/share/" + appDirName + "/" + subDirectory);

        // SuSE style:
        dirList.append("/usr/X11R6/" + appDirName + "/" + subDirectory);

        dirList.append("/usr/X11R6/share/" + appDirName + "/" + subDirectory);
        dirList.append(QDir::homePath() + "/." + appDirName + "/" + subDirectory);
#endif

#ifdef Q_OS_MAC
    }
#endif
    */

    // Individual directories:
    /*
    // TODO:
    RS_SETTINGS->beginGroup("/Paths");
    RS_String opt;
    if (subDirectory=="fonts") {
        opt = "/Fonts";
    } else if (subDirectory=="patterns") {
        opt = "/Patterns";
    } else if (subDirectory.startsWith("scripts")) {
        opt = "/Scripts";
    } else if (subDirectory.startsWith("library")) {
        opt = "/Library";
    } else if (subDirectory.startsWith("po")) {
        opt = "/Translations";
    }
    if (!opt.isEmpty()) {
        dirList += RS_SETTINGS->readEntry(opt, "")
                .split(RS_RegExp("[;]"));
    }
    RS_SETTINGS->endGroup();
    */

    QStringList ret;
    for (int i=0; i<dirList.size(); i++) {
        QFileInfo fi(dirList.at(i));
        QString dir = fi.canonicalFilePath();
        if (fi.isDir() && !ret.contains(dir)) {
            ret.append(dir);
        }
    }

    return ret;
}

/**
 * Searches for files in various directories under the given
 * subdirectory which match the given file extension.
 *
 * \return List of the absolute paths of the files found.
 */
QStringList RS::getFileList(const QString& subDirectory,
                                   const QString& fileExtension) {

    QStringList dirList = getDirectoryList(subDirectory);

    QStringList fileList;
    QString path;
    QDir dir;

    for (int i=0; i<dirList.size(); ++i) {
        path = dirList.at(i);
        dir = QDir(path);

        if (dir.exists() && dir.isReadable()) {
            // this seems to be case insensitive by default:
            QStringList files =
                dir.entryList(QStringList("*." + fileExtension), QDir::Files|QDir::Readable);
            for (int k=0; k<files.size(); ++k) {
                QString f = path + QDir::separator() + files.at(k);
                fileList.append(f);
            }
        }
    }

    return fileList;
}

/**
 * \return A list of absolute paths to all font files found.
 */
QStringList RS::getFontList() {
    return getFileList("fonts", "cxf");
}

/**
 * \return A list of absolute paths to all pattern files found.
 */
QStringList RS::getPatternList(bool metric) {
    if (metric) {
        return getFileList("patterns/metric", "pat");
    }
    else {
        return getFileList("patterns/imperial", "pat");
    }
}
