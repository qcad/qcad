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

#ifndef RFONTLIST_H
#define RFONTLIST_H

#include "core_global.h"

#include "RFont.h"
#include "RResourceList.h"

/**
 * The global list of fonts.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RFontList {
public:
    static void init();
    static void initSubstitutions();
    static void uninit();

    static QStringList getNames();
    static QString getSubName(const QString& resName);
    static RFont* get(const QString& resName, bool substitute = true);
    static bool isCadFont(const QString& fontName, const QString& fontFile);

private:
    static RResourceList<RFont> res;
};

Q_DECLARE_METATYPE(RFontList)
Q_DECLARE_METATYPE(RFontList*)
Q_DECLARE_METATYPE(RResourceList<RFont>*)

#endif
