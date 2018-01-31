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

#ifndef RFILESYSTEMMODEL_H_
#define RFILESYSTEMMODEL_H_

#include "gui_global.h"

#include <QFileSystemModel>

#define RDEFAULT_QMODELINDEX QModelIndex()

/**
 * \scriptable
 * \ingroup gui
 */
class QCADGUI_EXPORT RFileSystemModel: public QFileSystemModel {

Q_OBJECT

public:
    RFileSystemModel(QObject* parent = 0);

    QModelIndex setRootPath(const QString& newPath);
    QString rootPath () const;
    QModelIndex pathIndex(const QString& path, int column = 0) const;
    QModelIndex index(int row, int column, const QModelIndex & parent = RDEFAULT_QMODELINDEX) const;
    QString filePath(const QModelIndex& index) const;
    void setFilter(QDir::Filters filters);
    bool isDir(const QModelIndex& index) const;
    bool setHeaderData(int section, Qt::Orientation orientation, const QString& value, int role = Qt::EditRole);
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role = Qt::EditRole);
    int rowCount(const QModelIndex & parent = RDEFAULT_QMODELINDEX) const;
    void setIconProvider(QFileIconProvider* provider);
    void setNameFilter(const QString& filter);
    void setNameFilters(const QStringList& filters);
    void setNameFilterDisables(bool enable);
    bool setItemData(const QModelIndex& index, const QMap<int, QVariant>& roles);
    bool setItemData(const QModelIndex& index, Qt::ItemDataRole role, const QString& value);
    bool setItemData(const QModelIndex& index, Qt::ItemDataRole role, const QColor& value);
    QMap<int, QVariant> itemData(const QModelIndex & index) const;
    bool canFetchMore(const QModelIndex & parent) const;
    void fetchMore(const QModelIndex & parent);
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool removeRow(int row, const QModelIndex & parent = QModelIndex());
    //virtual Qt::ItemFlags flags(const QModelIndex & index) const;
};

Q_DECLARE_METATYPE(RFileSystemModel*)

#endif /* RFILESYSTEMMODEL_H_ */
