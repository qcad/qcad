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
#include "RAttributeDefinitionData.h"


RAttributeDefinitionData::RAttributeDefinitionData(RDocument* document, const RAttributeDefinitionData& data)
    : RTextBasedData(document, data) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RAttributeDefinitionData::RAttributeDefinitionData(const RTextBasedData& textData, const QString& tag, const QString& prompt)
    : RTextBasedData(textData), tag(tag), prompt(prompt) {

}

QString RAttributeDefinitionData::getRenderedText(bool escUnicode) const {
    if (escUnicode) {
        return escapeUnicode(getTag());
    }
    else {
        return getTag();
    }
}

QDebug operator<<(QDebug dbg, const RAttributeDefinitionData& t) {
    dbg.nospace() << "RAttributeDefinitionData("
                  << "text: " << t.getEscapedText()
                  << ", tag: " << t.tag
                  << ", prompt: " << t.prompt
                  << ", position: " << t.getPosition()
                  << ")";
    return dbg;
}
