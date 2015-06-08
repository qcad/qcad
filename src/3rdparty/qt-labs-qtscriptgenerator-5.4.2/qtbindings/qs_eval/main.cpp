/****************************************************************************
**
** Copyright (C) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Script Generator project on Qt Labs.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QtScript>
#if QT_VERSION >= 0x040500
#include <QtScriptTools>
#endif
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QStringList>
#include <QApplication>

#include <stdlib.h>

static bool wantsToQuit;

static QScriptValue qtscript_quit(QScriptContext *ctx, QScriptEngine *eng)
{
    Q_UNUSED(ctx);
    wantsToQuit = true;
    return eng->undefinedValue();
}

static QScriptValue qtscript_describe(QScriptContext *ctx, QScriptEngine *eng)
{
    QStringList result;
    QScriptValue obj = ctx->argument(0);
    while (obj.isObject()) {
        QScriptValueIterator it(obj);
        while (it.hasNext()) {
            it.next();
            result.append(it.name());
        }
        obj = obj.prototype();
    }
    return eng->toScriptValue(result);
}

static void interactive(QScriptEngine *eng)
{
    QScriptValue global = eng->globalObject();
    QScriptValue quitFunction = eng->newFunction(qtscript_quit);
    if (!global.property(QLatin1String("exit")).isValid())
        global.setProperty(QLatin1String("exit"), quitFunction);
    if (!global.property(QLatin1String("quit")).isValid())
        global.setProperty(QLatin1String("quit"), quitFunction);
    wantsToQuit = false;
    global.setProperty(QLatin1String("describe"),
                       eng->newFunction(qtscript_describe));
   
    QTextStream qin(stdin, QFile::ReadOnly);

    const char *qscript_prompt = "qs> ";
    const char *dot_prompt = ".... ";
    const char *prompt = qscript_prompt;

    QString code;

    forever {
        QString line;

        printf("%s", prompt);
        fflush(stdout);

        line = qin.readLine();
        if (line.isNull())
            break;

        code += line;
        code += QLatin1Char('\n');

        if (line.trimmed().isEmpty()) {
            continue;

        } else if (! eng->canEvaluate(code)) {
            prompt = dot_prompt;

        } else {
            QScriptValue result = eng->evaluate(code, QLatin1String("typein"));

            code.clear();
            prompt = qscript_prompt;

            if (! result.isUndefined())
                fprintf(stderr, "%s\n", qPrintable(result.toString()));

            if (wantsToQuit)
                break;
        }
    }
}

static QScriptValue importExtension(QScriptContext *context, QScriptEngine *engine)
{
    return engine->importExtension(context->argument(0).toString());
}

int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc, argv);

    QDir dir(QApplication::applicationDirPath());
    if (dir.dirName() == QLatin1String("debug") || dir.dirName() == QLatin1String("release"))
        dir.cdUp();
    dir.cdUp();
    dir.cdUp();
    if (!dir.cd("plugins")) {
        fprintf(stderr, "plugins folder does not exist -- did you build the bindings?\n");
        return(-1);
    }
    QStringList paths = app->libraryPaths();
    paths <<  dir.absolutePath();
    app->setLibraryPaths(paths);

    QScriptEngine *eng = new QScriptEngine();

    QStringList extensions;
    extensions << "qt.core"
               << "qt.gui"
               << "qt.widgets"
               << "qt.printsupport"
               << "qt.xml"
               << "qt.svg"
               << "qt.network"
               << "qt.sql"
               << "qt.opengl"
               << "qt.webkit"
               << "qt.webkitwidgets"
               << "qt.xmlpatterns"
               << "qt.uitools";
    QStringList failExtensions;
    foreach (const QString &ext, extensions) {
        QScriptValue ret = eng->importExtension(ext);
        if (ret.isError())
            failExtensions.append(ext);
    }
    if (!failExtensions.isEmpty()) {
        if (failExtensions.size() == extensions.size()) {
            qWarning("Failed to import Qt bindings!\n"
                     "Plugins directory searched: %s/script\n"
                     "Make sure that the bindings have been built, "
                     "and that this executable and the plugins are "
                     "using compatible Qt libraries.", qPrintable(dir.absolutePath()));
        } else {
            qWarning("Failed to import some Qt bindings: %s\n"
                     "Plugins directory searched: %s/script\n"
                     "Make sure that the bindings have been built, "
                     "and that this executable and the plugins are "
                     "using compatible Qt libraries.",
                     qPrintable(failExtensions.join(", ")), qPrintable(dir.absolutePath()));
        }
    }

#if QT_VERSION >= 0x040500
    QScriptEngineDebugger *dbg = new QScriptEngineDebugger();
    dbg->attachTo(eng);
#endif

    QScriptValue globalObject = eng->globalObject();
    globalObject.setProperty("qApp", eng->newQObject(app));
    {
        QScriptValue qscript = eng->newObject();
        qscript.setProperty("importExtension", eng->newFunction(importExtension));
        globalObject.property("qt").setProperty("script", qscript);
    }

    if (! *++argv) {
        interactive(eng);
        return EXIT_SUCCESS;
    }

    while (const char *arg = *argv++) {
        QString fn = QString::fromLocal8Bit(arg);

        if (fn == QLatin1String("-i")) {
            interactive(eng);
            break;
        }

        QString contents;
        int lineNumber = 1;

        if (fn == QLatin1String("-")) {
            QTextStream stream(stdin, QFile::ReadOnly);
            contents = stream.readAll();
        }

        else {
            QFile file(fn);

            if (file.open(QFile::ReadOnly)) {
                QTextStream stream(&file);
                contents = stream.readAll();
                file.close();

                // strip off #!/usr/bin/env qscript line
                if (contents.startsWith("#!")) {
                    contents.remove(0, contents.indexOf("\n"));
                    ++lineNumber;
                }
            }
        }

        if (contents.isEmpty())
            continue;

        QScriptValue r = eng->evaluate(contents, fn, lineNumber);
        if (eng->hasUncaughtException()) {
            QStringList backtrace = eng->uncaughtExceptionBacktrace();
            fprintf (stderr, "    %s\n%s\n\n", qPrintable(r.toString()),
                     qPrintable(backtrace.join("\n")));
            return EXIT_FAILURE;
        }
    }

    delete eng;
#if QT_VERSION >= 0x040500
    delete dbg;
#endif
    delete app;

    return EXIT_SUCCESS;
}
