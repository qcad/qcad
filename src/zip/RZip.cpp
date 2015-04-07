/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
//#include <QTextStream>
//#include <QResource>

#include "JlCompress.h"

#include "RZip.h"

bool RZip::unzipFile(const QString& fileName, const QString& path) {
    QStringList fileList = JlCompress::getFileList(fileName);
    JlCompress::extractFiles(fileName, fileList, path);
    return true;
}

//bool RZip::loadAsResource(const QString& fileName, const QString& mapRoot) {
//    QuaZip zip(fileName);
//    if (!zip.open(QuaZip::mdUnzip)) {
//        return false;
//    }

//    QStringList zFiles = zip.getFileNameList();
//    for (int i=0; i<zFiles.length(); i++) {
//        if (!zip.setCurrentFile(zFiles[i])) {
//            continue;
//        }

//        QuaZipFile zFile(&zip);
//        int method;
//        if (!zFile.open(QIODevice::ReadOnly, &method, NULL, false)) {
//            continue;
//        }
//        QTextStream stream(&zFile);
//        QString str = stream.readAll();
//        // TODO: add as resource
//        QResource::registerResource((const char*)str.toUtf8(), "");
//        zFile.close();
//    }
//    zip.close();
//    return true;
//}
