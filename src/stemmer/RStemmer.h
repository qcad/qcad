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

#ifndef RSTEMMER_H
#define RSTEMMER_H

#include "stemmer_global.h"

#include <QMetaType>
#include <QString>


/**
 * Stemmer, used for indexing and searching word stems 
 * (e.g. 'draw' for 'drawing', 'drawn', 'draws', ...).
 *
 * \ingroup stemmer
 * \scriptable
 */
class QCADSTEMMER_EXPORT RStemmer {
public:
    static QString stem(const QString& word, const QString& locale);
};

Q_DECLARE_METATYPE(RStemmer*);

#endif
