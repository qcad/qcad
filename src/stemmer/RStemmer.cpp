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
#include <QDebug>

#include "stemmer/include/libstemmer.h"

#include "RStemmer.h"


QString RStemmer::stem(const QString& word, const QString& locale) {
    static QString prevLocale = "";
    static struct sb_stemmer* stemmer = NULL;

    // keep always the last used stemmer in memory:
    if (locale!=prevLocale) {
        if (stemmer!=NULL) {
            sb_stemmer_delete(stemmer);
            stemmer = NULL;
        }
        stemmer = sb_stemmer_new(locale.toUtf8(), "UTF_8");
        prevLocale = locale;
    }

    if (stemmer == NULL) {
        qWarning() << "No stemmer found for locale: " << locale;
        return word;
    }

    QByteArray ba = word.toUtf8();

    int lim = 10;
    sb_symbol* sbWord = (sb_symbol*)malloc(lim * sizeof(sb_symbol));
    int i = 0;
    int inlen = 0;

    while (1) {
        if (i==ba.length()) {
            break;
        }
        int ch = ba.at(i);
        if (i == lim) {
            sb_symbol * newb;
            newb = (sb_symbol*)realloc(sbWord, (lim + 10) * sizeof(sb_symbol));
            if (newb == 0) {
                Q_ASSERT(false);
                qWarning() << "RStemmer::stem: Memory allocation error.";
            }
            sbWord = newb;
            lim = lim + 10;
        }
        // Update count of utf-8 characters.
        if (ch < 0x80 || ch > 0xBF) {
            inlen += 1;
        }
        // force lower case:
        //if (isupper(ch)) {
        //    ch = tolower(ch);
        //}

        sbWord[i] = ch;
        i++;
    }

    const sb_symbol* sbStemmed = sb_stemmer_stem(stemmer, sbWord, i);
    QString stemmed;

    i=0;
    while(1) {
        if (sbStemmed[i]==0) {
            break;
        }
        stemmed += QChar(sbStemmed[i]);
        i++;
    }

    return stemmed;
}

