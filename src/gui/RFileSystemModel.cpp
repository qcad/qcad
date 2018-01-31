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
#include "RFileSystemModel.h"

#include <QDebug>

RFileSystemModel::RFileSystemModel(QObject* parent) :
    QFileSystemModel(parent) {
    //setReadOnly(true);
}

QVariant RFileSystemModel::data(const QModelIndex & index, int role) const {
//  if (index.parent() == this->index(rootPath())) {
//      qDebug() << "RFileSystemModel::data: " << index;
//      return QVariant();
//  }
    return QFileSystemModel::data(index, role);
}

void RFileSystemModel::fetchMore(const QModelIndex & parent) {
    QFileSystemModel::fetchMore(parent);
}

bool RFileSystemModel::canFetchMore(const QModelIndex & parent) const {
    return QFileSystemModel::canFetchMore(parent);
}

QModelIndex RFileSystemModel::setRootPath(const QString & newPath) {
    return QFileSystemModel::setRootPath(newPath);
}

QString RFileSystemModel::rootPath() const {
    return QFileSystemModel::rootPath();
}

QModelIndex RFileSystemModel::pathIndex(const QString& path, int column) const {
    return QFileSystemModel::index(path, column);
}

QModelIndex RFileSystemModel::index(int row, int column,
        const QModelIndex & parent) const {
    return QFileSystemModel::index(row, column, parent);
}

QString RFileSystemModel::filePath(const QModelIndex& index) const {
    return QFileSystemModel::filePath(index);
}

void RFileSystemModel::setFilter(QDir::Filters filters) {
    QFileSystemModel::setFilter(filters);
}

bool RFileSystemModel::isDir(const QModelIndex& index) const {
    return QFileSystemModel::isDir(index);
}

bool RFileSystemModel::setHeaderData(int section, Qt::Orientation orientation,
        const QString& value, int role) {
    return setHeaderData(section, orientation, QVariant(value), role);
}

bool RFileSystemModel::setHeaderData(int section, Qt::Orientation orientation,
        const QVariant& value, int role) {
    return QFileSystemModel::setHeaderData(section, orientation, value, role);
}

int RFileSystemModel::rowCount(const QModelIndex & parent) const {
    return QFileSystemModel::rowCount(parent);
}

void RFileSystemModel::setIconProvider(QFileIconProvider* provider) {
    QFileSystemModel::setIconProvider(provider);
}

void RFileSystemModel::setNameFilter(const QString& filter) {
    setNameFilters(QStringList(filter));
}

void RFileSystemModel::setNameFilters(const QStringList& filters) {
    QFileSystemModel::setNameFilters(filters);
}

void RFileSystemModel::setNameFilterDisables(bool enable) {
    QFileSystemModel::setNameFilterDisables(enable);
}

bool RFileSystemModel::setItemData(const QModelIndex& index, const QMap<int,
        QVariant>& roles) {
    return QFileSystemModel::setItemData(index, roles);
}

bool RFileSystemModel::setItemData(const QModelIndex& index,
        Qt::ItemDataRole role, const QString& value) {
    QMap<int, QVariant> map;
    map.insert(role, value);
    return QFileSystemModel::setItemData(index, map);
}

bool RFileSystemModel::setItemData(const QModelIndex& index,
        Qt::ItemDataRole role, const QColor& value) {
    QMap<int, QVariant> map;
    map.insert(role, value);
    return QFileSystemModel::setItemData(index, map);
}

QMap<int, QVariant> RFileSystemModel::itemData(const QModelIndex & index) const {
    return QFileSystemModel::itemData(index);
}

bool RFileSystemModel::removeRow(int row, const QModelIndex & parent) {
    return QFileSystemModel::removeRow(row, parent);
}

//Qt::ItemFlags RFileSystemModel::flags(const QModelIndex &index) const {
//    return Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsEnabled;
//}
