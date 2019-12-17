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
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QHostInfo>
#include <QThread>
#ifdef Q_OS_WIN
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "RGlobal.h"

#if defined(Q_WS_X11)
#include <X11/Xlib.h>
/**
 * If things magically start not working with weird and unexpected
 * errors, see FS#1050 for a likely cause.
 */
#endif

/**
 * \return Unique combination of system ID (linux, freebsd, netbsd, openbsd, solaris, osx, win) and host name.
 * E.g. "linux_vertigo". Used for test data that may differ on different machines.
 */
QString RS::getHostId() {
    return QString("%1_%2")
            .arg(getSystemId())
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD) || defined(Q_OS_NETBSD) || defined(Q_OS_OPENBSD) || defined(Q_OS_SOLARIS)
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
 * \return Unique system ID ("linux", "freebsd", "netbsd", "openbsd", "solaris", "osx", "win").
 */
QString RS::getSystemId() {
#if defined(Q_OS_LINUX)
    return "linux";
#elif defined(Q_OS_FREEBSD)
    return "freebsd";
#elif defined(Q_OS_NETBSD)
    return "netbsd";
#elif defined(Q_OS_OPENBSD)
    return "openbsd";
#elif defined(Q_OS_SOLARIS)
    return "solaris";
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

/**
 * \return Number of CPU cores available.
 */
int RS::getCpuCores() {
    static int cores = -1;

    if (cores!=-1) {
        return cores;
    }

#ifdef Q_OS_WIN
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
 * \return Ideal thread count for multithreading.
 */
int RS::getIdealThreadCount() {
    return QThread::idealThreadCount();
}

/**
 * \return x32 or x64, depending on the architecture the binary was built for.
 */
QString RS::getBuildCpuArchitecture() {
#if QT_VERSION >= 0x050400
    return QSysInfo::buildCpuArchitecture();
#else
#if defined(QT_ARCH_I386)
    return "i386";
#elif defined(QT_ARCH_IA64)
    return "ia64";
#elif defined(QT_ARCH_POWERPC)
    return "ppc";
#elif defined(QT_ARCH_X86_64)
    return "x86_64";
#else
    return "";
#endif
#endif
}
