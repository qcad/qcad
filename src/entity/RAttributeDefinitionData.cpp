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

/*double RAttributeDefinitionData::getDistanceTo(const RVector& point, bool limited, double range, bool draft) const {
    if (document==NULL) {
        return RNANDOUBLE;
    }

    // if we are editing the block this attribute definition belongs to,
    // use the tag as text:
    if (getBlockId()==document->getCurrentBlockId()) {
        RTextData data = *this;
        data.setText(getTag());
        return data.getDistanceTo(point, limited, range, draft);
    }

    return RNANDOUBLE;
}*/

QString RAttributeDefinitionData::getRenderedText(bool escUnicode) const {
    //qDebug() << "RAttributeDefinitionData::getRenderedText";
    //if (document!=NULL && getBlockId()==document->getCurrentBlockId()) {
    if (escUnicode) {
        return escapeUnicode(getTag());
    }
    else {
        return getTag();
    }
    //}
    //else {
    //    return QString();
    //}
}

//QList<RPainterPath> RAttributeDefinitionData::getPainterPaths(bool draft) const {
//    return RTextBasedData::getPainterPaths(draft);
//    /*
//    RTextBasedData data = getRenderedTextData();
//    //return data.getPainterPaths(draft);
//    painterPaths = data.getPainterPaths(draft);
//    boundingBox = data.getBoundingBox();
//    height = data.getHeight();
//    width = data.getWidth();

//    dirty = false;
//    gotDraft = draft;
//    return painterPaths;
//    */
//}

//RTextBasedData RAttributeDefinitionData::getRenderedTextData() const {
//    qDebug() << "RAttributeDefinitionData::getRenderedTextData";
//    // invalid data  (returned if we are not editing the block this
//    // attribute definition belongs to):
//    RTextBasedData ret;

//    if (document!=NULL && getBlockId()==document->getCurrentBlockId()) {
//        ret = *this;
//        ret.setText(getTag());
//    }

//    return ret;
//}

QDebug operator<<(QDebug dbg, const RAttributeDefinitionData& t) {
    dbg.nospace() << "RAttributeDefinitionData("
                  << "text: " << t.getEscapedText()
                  << ", tag: " << t.tag
                  << ", prompt: " << t.prompt
                  << ", position: " << t.getPosition()
                  << ")";
    return dbg;
}
