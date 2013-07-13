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

#ifndef RMETATYPES_H
#define RMETATYPES_H

// MSVC <= 2008 does not have this:
//#include <stdint.h>

#include <QAbstractItemModel>
#include <QAbstractProxyModel>
#include <QSortFilterProxyModel>
#include <QAction>
#include <QActionEvent>
#include <QApplication>
#include <QBuffer>
#include <QByteArray>
#include <QCloseEvent>
#include <QComboBox>
#include <QDateTime>
#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QDockWidget>
#include <QDomNode>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QEvent>
#include <QFocusEvent>
#include <QFocusFrame>
#include <QFont>
#include <QFontDatabase>
#include <QFile>
#include <QFileIconProvider>
#include <QFileSystemModel>
#include <QFrame>
#include <QGestureEvent>
#include <QGLWidget>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGridLayout>
#include <QHelpEvent>
#include <QHideEvent>
#include <QInputMethodEvent>
#include <QImage>
#include <QKeyEvent>
#include <QLayout>
#include <QLayoutItem>
#include <QList>
#include <QListView>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLocale>
#include <QMap>
#include <QMainWindow>
#include <QMdiArea>
#include <QMenu>
#include <QModelIndex>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QMultiMap>
#include <QObject>
#include <QPainter>
#include <QPainterPath>
#include <QPair>
#include <QPinchGesture>
#include <QPlainTextEdit>
#include <QPointF>
#include <QPrinter>
#include <QProcess>
#include <QProgressBar>
#include <QQuaternion>
#include <QSet>
#include <QSettings>
#include <QSharedPointer>
#include <QShowEvent>
#include <QStringList>
#include <QStyleOption>
#include <QStyleOptionViewItem>
#include <QSwipeGesture>
#include <QTabBar>
#include <QTemporaryFile>
#include <QTextBrowser>
#include <QTextCodec>
#include <QTextEdit>
#include <QThread>
#include <QToolBar>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QUrl>
#include <QVariant>
#include <QVector>
#include <QWebView>
#include <QWheelEvent>
#include <QWidget>
#include <QXmlResultItems>
#include <QXmlStreamWriter>
#include <QXmlQuery>

#include "RSingleApplication.h"

Q_DECLARE_METATYPE(int*)
Q_DECLARE_METATYPE(unsigned int*)
Q_DECLARE_METATYPE(qint64*)
//Q_DECLARE_METATYPE(uint8_t*)
#if !defined Q_OS_WIN32 && !defined Q_OS_LINUX
Q_DECLARE_METATYPE(size_t*)
#endif
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(const char*)

Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(QAbstractProxyModel*)
Q_DECLARE_METATYPE(QSortFilterProxyModel*)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QActionEvent*)
Q_DECLARE_METATYPE(QApplication*)
Q_DECLARE_METATYPE(QBrush)
Q_DECLARE_METATYPE(QBrush*)
Q_DECLARE_METATYPE(QBuffer*)
Q_DECLARE_METATYPE(QByteArray*)
Q_DECLARE_METATYPE(QCloseEvent*)
Q_DECLARE_METATYPE(QColor)
Q_DECLARE_METATYPE(QColor*)
Q_DECLARE_METATYPE(const QColor*)
Q_DECLARE_METATYPE(QComboBox*)
Q_DECLARE_METATYPE(QDateTime*)
Q_DECLARE_METATYPE(QContextMenuEvent*)
Q_DECLARE_METATYPE(QCursor*)
Q_DECLARE_METATYPE(const QCursor*)
Q_DECLARE_METATYPE(QDebug*)
Q_DECLARE_METATYPE(QDialog*)
Q_DECLARE_METATYPE(QDockWidget*)
Q_DECLARE_METATYPE(QDomNode)
Q_DECLARE_METATYPE(QDomNode*)
Q_DECLARE_METATYPE(QDragEnterEvent*)
Q_DECLARE_METATYPE(QDragMoveEvent*)
Q_DECLARE_METATYPE(QDragLeaveEvent*)
Q_DECLARE_METATYPE(QDropEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QFile*)
Q_DECLARE_METATYPE(QFileIconProvider*)
Q_DECLARE_METATYPE(QFileSystemModel*)
Q_DECLARE_METATYPE(QFocusEvent*)
Q_DECLARE_METATYPE(QFocusFrame*)
Q_DECLARE_METATYPE(QFont*)
Q_DECLARE_METATYPE(QFontDatabase*)
Q_DECLARE_METATYPE(QFrame*)
Q_DECLARE_METATYPE(QGestureEvent*)
Q_DECLARE_METATYPE(QGLWidget*)
Q_DECLARE_METATYPE(QGraphicsView*)
Q_DECLARE_METATYPE(QGridLayout*)
Q_DECLARE_METATYPE(QHelpEvent*)
Q_DECLARE_METATYPE(QHideEvent*)
Q_DECLARE_METATYPE(QImage*)
Q_DECLARE_METATYPE(QInputEvent*)
Q_DECLARE_METATYPE(QInputMethodEvent*)
Q_DECLARE_METATYPE(QItemSelection*)
Q_DECLARE_METATYPE(QKeyEvent*)
Q_DECLARE_METATYPE(QKeySequence*)
Q_DECLARE_METATYPE(QLayout*)
Q_DECLARE_METATYPE(QLayoutItem*)
Q_DECLARE_METATYPE(QLineEdit*)
Q_DECLARE_METATYPE(QListView*)
Q_DECLARE_METATYPE(QListWidget*)
Q_DECLARE_METATYPE(QListWidgetItem*)
Q_DECLARE_METATYPE(QLocale*)
Q_DECLARE_METATYPE(QMainWindow*)
Q_DECLARE_METATYPE(QMdiArea*)
Q_DECLARE_METATYPE(QMdiSubWindow*)
Q_DECLARE_METATYPE(QMenu*)
Q_DECLARE_METATYPE(QModelIndex)
Q_DECLARE_METATYPE(QModelIndex*)
Q_DECLARE_METATYPE(QMouseEvent*)
Q_DECLARE_METATYPE(QMoveEvent*)
Q_DECLARE_METATYPE(QObject*)
Q_DECLARE_METATYPE(QPaintDevice*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(QPainterPath*)
Q_DECLARE_METATYPE(QPainterPath::Element)
Q_DECLARE_METATYPE(QPainterPath::Element*)
Q_DECLARE_METATYPE(QPainterPath::ElementType)
Q_DECLARE_METATYPE(QPaintEvent*)
Q_DECLARE_METATYPE(QPanGesture*)
Q_DECLARE_METATYPE(QPen*)
Q_DECLARE_METATYPE(QPinchGesture*)
Q_DECLARE_METATYPE(QPlainTextEdit*)
Q_DECLARE_METATYPE(QPointF*)
Q_DECLARE_METATYPE(QPrinter*)
Q_DECLARE_METATYPE(QProgressBar*)
Q_DECLARE_METATYPE(QProcess::ProcessError*)
Q_DECLARE_METATYPE(QQuaternion*)
Q_DECLARE_METATYPE(QRect*)
Q_DECLARE_METATYPE(const QRect*)
Q_DECLARE_METATYPE(QRectF*)
Q_DECLARE_METATYPE(const QRectF*)
Q_DECLARE_METATYPE(QResizeEvent*)
Q_DECLARE_METATYPE(QSettings*)
Q_DECLARE_METATYPE(QSize*)
Q_DECLARE_METATYPE(QShowEvent*)
Q_DECLARE_METATYPE(QStaticText*)
Q_DECLARE_METATYPE(QString)
Q_DECLARE_METATYPE(QStringList*)
Q_DECLARE_METATYPE(QStyleOption)
Q_DECLARE_METATYPE(QStyleOption*)
Q_DECLARE_METATYPE(QStyleOptionViewItem*)
Q_DECLARE_METATYPE(QSwipeGesture*)
Q_DECLARE_METATYPE(QTextDocument*)
Q_DECLARE_METATYPE(QTabBar*)
Q_DECLARE_METATYPE(QTabletEvent*)
Q_DECLARE_METATYPE(QTemporaryFile*)
Q_DECLARE_METATYPE(QTextBrowser*)
Q_DECLARE_METATYPE(QTextCodec*)
Q_DECLARE_METATYPE(QTextEdit*)
Q_DECLARE_METATYPE(QThread*)
Q_DECLARE_METATYPE(QToolBar*)
Q_DECLARE_METATYPE(QTransform*)
Q_DECLARE_METATYPE(QTreeWidget*)
Q_DECLARE_METATYPE(QTreeWidgetItem*)
Q_DECLARE_METATYPE(QUrl*)
Q_DECLARE_METATYPE(QVariant*)
Q_DECLARE_METATYPE(QWebView*)
Q_DECLARE_METATYPE(QWheelEvent*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QXmlQuery)
Q_DECLARE_METATYPE(QXmlQuery*)
Q_DECLARE_METATYPE(QXmlStreamWriter*)
Q_DECLARE_METATYPE(QXmlResultItems*)

Q_DECLARE_METATYPE(QFlags<Qt::MouseButton>)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QFlags<QDir::Filter>*)

Q_DECLARE_METATYPE(QList<int>)
Q_DECLARE_METATYPE(QList<double>)
Q_DECLARE_METATYPE(QList<QGraphicsItem*>)
Q_DECLARE_METATYPE(QList<QString>)
Q_DECLARE_METATYPE(QList<QKeySequence>)
typedef QPair<int, double> _RPairIntDouble;
Q_DECLARE_METATYPE(QList<_RPairIntDouble>)

Q_DECLARE_METATYPE(QSet<QString>)
typedef QMap<int, QVariant> _RMapIntVariant;
Q_DECLARE_METATYPE(_RMapIntVariant)
Q_DECLARE_METATYPE(_RMapIntVariant*)
typedef QMap<QString, QString> _RMapQStringQString;
Q_DECLARE_METATYPE(_RMapQStringQString)
typedef QMap<QString, QVariant> _RMapQStringQVariant;
Q_DECLARE_METATYPE(_RMapQStringQVariant)
Q_DECLARE_METATYPE(_RMapQStringQVariant*)
typedef QMultiMap<QString, QString> _RMultiMapQStringQString;
Q_DECLARE_METATYPE(_RMultiMapQStringQString)
Q_DECLARE_METATYPE(_RMultiMapQStringQString*)
typedef QMap<int, QSet<int> > _RMapIntSetInt;
Q_DECLARE_METATYPE(_RMapIntSetInt)
Q_DECLARE_METATYPE(_RMapIntSetInt*)

Q_DECLARE_METATYPE(QVector<qreal>)
Q_DECLARE_METATYPE(QVector<qreal>*)

Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(Qt::DropActions)
Q_DECLARE_METATYPE(Qt::CursorShape)
Q_DECLARE_METATYPE(Qt::GlobalColor)
Q_DECLARE_METATYPE(Qt::MouseButton)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(Qt::PenStyle)
Q_DECLARE_METATYPE(Qt::BrushStyle)
Q_DECLARE_METATYPE(Qt::ItemDataRole)
Q_DECLARE_METATYPE(Qt::WindowFlags)
Q_DECLARE_METATYPE(QPrinter::PaperSize)
Q_DECLARE_METATYPE(QVariant::Type)

Q_DECLARE_METATYPE(QtMsgType*)
Q_DECLARE_METATYPE(QtMsgType)

Q_DECLARE_METATYPE(QSet<int>)
Q_DECLARE_METATYPE(QSet<int>*)

//Q_DECLARE_METATYPE(QtScriptShell_QListView*)

#endif
