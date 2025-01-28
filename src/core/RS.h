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

#ifndef RS_H
#define RS_H

#include "core_global.h"

#include <QPair>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QMetaType>
#include <QTextCharFormat>

#if QT_VERSION >= 0x060000
#include <QPageLayout>
#else
#include <QPrinter>
#endif

// Qt < 5.10
#if QT_VERSION < 0x050A00
#  ifdef ssize_t
#    define qsizetype ssize_t
#  else
#    define qsizetype int
#  endif
#endif

#if QT_VERSION >= 0x050000
#  include <QRegularExpression>
#else
#  include <QRegExp>
#  ifndef QRegularExpression
#    define QRegularExpression QRegExp
#  endif
#endif

#if QT_VERSION >= 0x060000
#  ifndef qSort
#    define qSort std::sort
#  endif
#endif

class RPropertyAttributes;

/**
 * Some useful macros for OS detection.
 */
#if defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
#  define ROS_WINDOWS
#  define ROS_WIN32
#  define ROS_WIN64
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define ROS_WINDOWS
#  define ROS_WIN32
#else
#  define ROS_POSIX
#endif

#if QT_VERSION < 0x050000
class QRegularExpressionMatch {
};
/*
#  ifndef QRegularExpressionMatch
#    define QRegularExpressionMatch int
#  endif
*/
#endif

#include "RSEnums.h"

/**
 * Namespace for various global enums.
 *
 * Most enums fit in a class, but some are truly global, others
 * cannot be declared in a class because this would result in
 * problems with include files that depend on each other (note that
 * there is no way to forward-declare nested classes or enums).
 *
 * \ingroup core
 * \scriptable
 */
namespace QCADCORE_EXPORT RS {
Q_NAMESPACE

    bool compare(const QVariant& v1, const QVariant& v2, bool noTolerance = false);
    bool compare(const QPair<QVariant, RPropertyAttributes>& p1,
                 const QPair<QVariant, RPropertyAttributes>& p2,
                 bool noTolerance = false);
    int getCpuCores();
    int getIdealThreadCount();
    QString getBuildCpuArchitecture();

    QString getHostId();
    QString getSystemId();
    QString getWindowManagerId();
    QString getCpuArchitecture();

    bool showInFileManager(const QString& filePaths);

    QStringList getDirectoryList(const QString& subDirectory);
    QStringList getFileList(const QString& subDirectory,
                            const QString& fileExtension);
    QStringList getFontList();
    QStringList getPatternList(bool metric);
    QStringList getLinetypeList(bool metric);

    template<class T>
    bool mapContainsCaseInsensitive(const QMap<QString, T>& map, const QString& key) {
        return QStringList(map.keys()).contains(key, Qt::CaseInsensitive);
    }

    template<class T>
    T mapValueCaseInsensitive(const QMap<QString, T>& map, const QString& key) {
        QMapIterator<QString, T> it(map);
        while (it.hasNext()) {
            it.next();
            if (QString::compare(it.key(), key, Qt::CaseInsensitive)==0) {
                return it.value();
            }
        }

        return T();
    }

    QStringList sortAlphanumerical(const QStringList& list);
    QStringList compareChunkify(const QString& s);
    int compareAlphanumerical(const QString& s1, const QString& s2);
    bool lessThanAlphanumerical(const QString& s1, const QString& s2);

    // workaround for Qt 6 deprecating QSet::toList:
    template<class T>
    QList<T> toList(const QSet<T>& set) {
#if QT_VERSION >= 0x060000
        return QList<T>(set.begin(), set.end());
#else
        return set.toList();
#endif
    }

    // workaround for Qt 6 deprecating QList::toSet:
    template<class T>
    QSet<T> toSet(const QList<T>& list) {
#if QT_VERSION >= 0x060000
        return QSet<T>(list.begin(), list.end());
#else
        return list.toSet();
#endif
    }

    // workaround for Qt 6 deprecating QList::toSet / QSet::toList:
    template<class T>
    QList<T> unique(const QList<T>& list) {
#if QT_VERSION >= 0x060000
        return RS::toList<T>(RS::toSet<T>(list));
#else
        return list.toSet().toList();
#endif
    }

    QString getFontFamily(const QTextCharFormat& format);

    int getPageSizeId(const QString& name);
    QSizeF getPageSize(const QString& name);

    // workarounds for Qt 6 QRegExp changes:
    /**
     * \nonscriptable
     */
    bool exactMatch(const QRegularExpression& rx, const QString& string);
    /**
     * \nonscriptable
     */
    bool exactMatch(const QRegularExpression& rx, QRegularExpressionMatch& match, const QString& string);
    /**
     * \nonscriptable
     */
    bool exactMatch(const QString& rxStr, const QString& string);
    /**
     * \nonscriptable
     */
    int indexIn(const QRegularExpression& rx, QRegularExpressionMatch& match, const QString& string, int from = 0);
    /**
     * \nonscriptable
     */
    QString captured(const QRegularExpression& rx, const QRegularExpressionMatch& match, int nth = 0);
    /**
     * \nonscriptable
     */
    int matchedLength(const QRegularExpression& rx, const QRegularExpressionMatch& match);
    /**
     * \nonscriptable
     */
    QRegularExpression createRegEpCI(const QString& str, bool regExp2 = false);

    void setUtf8Codec(QTextStream& ts);

    QString escape(const QString& plain);

    int getScreenCount();

    QSize getAvailableGeometry(int screen);

    /**
     * \nonscriptable
     */
    QString convert(const QByteArray& str, const QString& codecName);

    int getMetaType(const QVariant& v);

#if QT_VERSION >= 0x060000
    static const Qt::MouseButton MiddleButton = Qt::MiddleButton;
#else
    static const Qt::MouseButton MiddleButton = Qt::MidButton;
#endif

#if QT_VERSION >= 0x060000
    static const QPageLayout::Orientation Portrait = QPageLayout::Portrait;
    static const QPageLayout::Orientation Landscape = QPageLayout::Landscape;
#else
    static const QPrinter::Orientation Portrait = QPrinter::Portrait;
    static const QPrinter::Orientation Landscape = QPrinter::Landscape;
#endif
}

Q_DECLARE_METATYPE(RS::MetaType)
Q_DECLARE_METATYPE(RS::MetaType*)
Q_DECLARE_METATYPE(RS::AngleFormat)
Q_DECLARE_METATYPE(RS::AngleFormat*)
Q_DECLARE_METATYPE(RS::AngleUnit)
Q_DECLARE_METATYPE(RS::EntityType)
Q_DECLARE_METATYPE(RS::EntityType*)
Q_DECLARE_METATYPE(RS::From)
Q_DECLARE_METATYPE(RS::From*)
Q_DECLARE_METATYPE(RS::HAlign)
Q_DECLARE_METATYPE(RS::HAlign*)
Q_DECLARE_METATYPE(RS::IsoProjectionType)
Q_DECLARE_METATYPE(RS::IsoProjectionType*)
Q_DECLARE_METATYPE(RS::OrthoMode)
Q_DECLARE_METATYPE(RS::OrthoMode*)
// RS::KnownVariable declarations are in RPropertyTypeId.h
Q_DECLARE_METATYPE(RS::KnownVariableType)
Q_DECLARE_METATYPE(RS::KnownVariableType*)
Q_DECLARE_METATYPE(RS::LinearFormat)
Q_DECLARE_METATYPE(RS::LinearFormat*)
Q_DECLARE_METATYPE(RS::MessageType)
Q_DECLARE_METATYPE(RS::ProjectionRenderingHint)
Q_DECLARE_METATYPE(RS::Side)
Q_DECLARE_METATYPE(RS::Ending)
Q_DECLARE_METATYPE(RS::Ending*)
Q_DECLARE_METATYPE(RS::TextDrawingDirection)
Q_DECLARE_METATYPE(RS::TextDrawingDirection*)
Q_DECLARE_METATYPE(RS::TextLineSpacingStyle)
Q_DECLARE_METATYPE(RS::TextLineSpacingStyle*)
Q_DECLARE_METATYPE(RS::Unit)
Q_DECLARE_METATYPE(RS::Measurement)
Q_DECLARE_METATYPE(RS::Measurement*)
Q_DECLARE_METATYPE(RS::VAlign)
Q_DECLARE_METATYPE(RS::VAlign*)
Q_DECLARE_METATYPE(RS::BooleanOperation)
Q_DECLARE_METATYPE(RS::FillType)
Q_DECLARE_METATYPE(RS::Orientation)
Q_DECLARE_METATYPE(RS::JoinType)
Q_DECLARE_METATYPE(RS::EndType)
Q_DECLARE_METATYPE(RS::Easing)
Q_DECLARE_METATYPE(RS::Easing*)
Q_DECLARE_METATYPE(QList<RS::EntityType>)

#endif
