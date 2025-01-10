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
#include <QFont>
#include <QFontMetricsF>
//#include <QTextBlock>
#include <QTextDocument>
#include <QMutex>

#include "RColor.h"
#include "RDxfServices.h"
#include "RFont.h"
#include "RFontList.h"
#include "RTextRenderer.h"
#include "RPainterPathDevice.h"
#include "RPolyline.h"
#include "RSettings.h"

QChar RTextRenderer::chDegree = QChar(0x00b0);
QChar RTextRenderer::chPlusMinus = QChar(0x00b1);
//QChar RTextRenderer::chDiameter = QChar(0x2300);
QChar RTextRenderer::chDiameter = QChar(0x00f8);

QString RTextRenderer::rxLineFeedStr = "\\\\p(?:x?i(-?\\d*\\.?\\d*)(?:,l-?\\d*\\.?\\d*)(?:,t-?\\d*\\.?\\d*);)?";
QRegularExpression RTextRenderer::rxLineFeed(rxLineFeedStr);
QString RTextRenderer::rxAlignmentLeftStr = "\\\\pql;";
QRegularExpression RTextRenderer::rxAlignmentLeft(rxAlignmentLeftStr);
QString RTextRenderer::rxAlignmentCenterStr = "\\\\pqc;";
QRegularExpression RTextRenderer::rxAlignmentCenter(rxAlignmentCenterStr);
QString RTextRenderer::rxAlignmentRightStr = "\\\\pqr;";
QRegularExpression RTextRenderer::rxAlignmentRight(rxAlignmentRightStr);
QString RTextRenderer::rxXAlignmentLeftStr = "\\\\pxql;";
QRegularExpression RTextRenderer::rxXAlignmentLeft(rxXAlignmentLeftStr);
QString RTextRenderer::rxXAlignmentCenterStr = "\\\\pxqc;";
QRegularExpression RTextRenderer::rxXAlignmentCenter(rxXAlignmentCenterStr);
QString RTextRenderer::rxXAlignmentRightStr = "\\\\pxqr;";
QRegularExpression RTextRenderer::rxXAlignmentRight(rxXAlignmentRightStr);
QString RTextRenderer::rxXSpaceMTextStr = "\\\\pxsm(\\d*\\.?\\d*),?[a-z]*;";
QRegularExpression RTextRenderer::rxXSpaceMText(rxXSpaceMTextStr);
QString RTextRenderer::rxTabMMStr = "\\\\pt(\\d*\\.?\\d*,?)*;";
QRegularExpression RTextRenderer::rxTabMM(rxTabMMStr);
QString RTextRenderer::rxTabINStr = "\\\\pxt(\\d*\\.?\\d*,?)*;";
QRegularExpression RTextRenderer::rxTabIN(rxTabINStr);
QString RTextRenderer::rxParagraphFeedStr = "\\\\P";
QRegularExpression RTextRenderer::rxParagraphFeed(rxParagraphFeedStr);
QString RTextRenderer::rxXFeedStr = "\\\\X";
QRegularExpression RTextRenderer::rxXFeed(rxXFeedStr);
QString RTextRenderer::rxHeightChangeStr = "\\\\H(\\d*\\.?\\d*)(x?);";
QRegularExpression RTextRenderer::rxHeightChange(rxHeightChangeStr);
QString RTextRenderer::rxUnderlineChangeStr = "\\\\L|\\\\l";
QRegularExpression RTextRenderer::rxUnderlineChange(rxUnderlineChangeStr);
//QString RTextRenderer::rxRelativeHeightChange = "";
QString RTextRenderer::rxStackedTextStr = "\\\\S([^^]*)\\^([^;]*);";
QRegularExpression RTextRenderer::rxStackedText(rxStackedTextStr);
QString RTextRenderer::rxColorChangeIndexStr = "\\\\C(\\d+);";
QRegularExpression RTextRenderer::rxColorChangeIndex(rxColorChangeIndexStr);
QString RTextRenderer::rxColorChangeCustomStr ="\\\\c(\\d+);";
QRegularExpression RTextRenderer::rxColorChangeCustom(rxColorChangeCustomStr);
QString RTextRenderer::rxNonBreakingSpaceStr = "\\\\~";
QRegularExpression RTextRenderer::rxNonBreakingSpace(rxNonBreakingSpaceStr);
// TODO: break at regular spaces for line breaking:
//QString RTextRenderer::rxSpaceStr = " ";
QString RTextRenderer::rxOverlineOnStr = "\\\\O";
QRegularExpression RTextRenderer::rxOverlineOn(rxOverlineOnStr);
QString RTextRenderer::rxOverlineOffStr = "\\\\o";
QRegularExpression RTextRenderer::rxOverlineOff(rxOverlineOffStr);
QString RTextRenderer::rxUnderlineOnStr = "\\\\L";
QRegularExpression RTextRenderer::rxUnderlineOn(rxUnderlineOnStr);
QString RTextRenderer::rxUnderlineOffStr = "\\\\l";
QRegularExpression RTextRenderer::rxUnderlineOff(rxUnderlineOffStr);
QString RTextRenderer::rxStrikethroughOnStr = "\\\\K";
QRegularExpression RTextRenderer::rxStrikethroughOn(rxStrikethroughOnStr);
QString RTextRenderer::rxStrikethroughOffStr = "\\\\k";
QRegularExpression RTextRenderer::rxStrikethroughOff(rxStrikethroughOffStr);
QString RTextRenderer::rxWidthChangeStr = "\\\\W(\\d*\\.?\\d*)x?;";
QRegularExpression RTextRenderer::rxWidthChange(rxWidthChangeStr);
QString RTextRenderer::rxObliqueAngleChangeStr = "\\\\Q(\\d*\\.?\\d*);";
QRegularExpression RTextRenderer::rxObliqueAngleChange(rxObliqueAngleChangeStr);
QString RTextRenderer::rxTrackChangeStr = "\\\\T(\\d*\\.?\\d*);";
QRegularExpression RTextRenderer::rxTrackChange(rxTrackChangeStr);
QString RTextRenderer::rxAlignmentChangeStr = "\\\\A(\\d+);";
QRegularExpression RTextRenderer::rxAlignmentChange(rxAlignmentChangeStr);
QString RTextRenderer::rxAlignmentChangeBlockStr = "\\\\A(\\d+)";
QRegularExpression RTextRenderer::rxAlignmentChangeBlock(rxAlignmentChangeStr);
QString RTextRenderer::rxFontChangeCadStr = "\\\\F([^|;]*)"    // \Ffont
                                         "[^;]*"            // ignore anything except ";"
                                         ";";               // require ";"
QRegularExpression RTextRenderer::rxFontChangeCad(rxFontChangeCadStr);
QString RTextRenderer::rxFontChangeTtfStr = "\\\\f([^|;]*)"
                                         "(?:\\|+([bicp])(\\d+))?"
                                         "(?:\\|+([bicp])(\\d+))?"
                                         "(?:\\|+([bicp])(\\d+))?"
                                         "(?:\\|+([bicp])(\\d+))?"
                                         //"\\|*" // optional "|" at end, see FS#1882
                                         "([^;]*)"            // ignore anything except ";"
                                         ";";
QRegularExpression RTextRenderer::rxFontChangeTtf(rxFontChangeTtfStr);
QString RTextRenderer::rxBeginBlockStr = "\\{";
QRegularExpression RTextRenderer::rxBeginBlock(rxBeginBlockStr);
QString RTextRenderer::rxEndBlockStr = "\\}";
QRegularExpression RTextRenderer::rxEndBlock(rxEndBlockStr);
QString RTextRenderer::rxBackslashStr = "\\\\\\\\";
QRegularExpression RTextRenderer::rxBackslash(rxBackslashStr);
QString RTextRenderer::rxCurlyOpenStr = "\\\\\\{";
QRegularExpression RTextRenderer::rxCurlyOpen(rxCurlyOpenStr);
QString RTextRenderer::rxCurlyCloseStr = "\\\\\\}";
QRegularExpression RTextRenderer::rxCurlyClose(rxCurlyCloseStr);
QString RTextRenderer::rxDegreeStr = "%%[dD]";
QRegularExpression RTextRenderer::rxDegree(rxDegreeStr);
QString RTextRenderer::escDegreeStr = "%%d";
QRegularExpression RTextRenderer::escDegree(escDegreeStr);
QString RTextRenderer::rxPlusMinusStr = "%%[pP]";
QRegularExpression RTextRenderer::rxPlusMinus(rxPlusMinusStr);
QString RTextRenderer::escPlusMinusStr = "%%p";
QRegularExpression RTextRenderer::escPlusMinus(escPlusMinusStr);
QString RTextRenderer::rxDiameterStr = "%%[cC]";
QRegularExpression RTextRenderer::rxDiameter(rxDiameterStr);
QString RTextRenderer::escDiameterStr = "%%c";
QRegularExpression RTextRenderer::escDiameter(escDiameterStr);
QString RTextRenderer::rxUnderlineStr = "%%[uU]";
QRegularExpression RTextRenderer::rxUnderline(rxUnderlineStr);
QString RTextRenderer::escUnderlineStr = "%%u";
QRegularExpression RTextRenderer::escUnderline(escUnderlineStr);
// invalid escape sequence (to replace %%x with "x"):
QString RTextRenderer::rxNoOpStr = "%%([^uUcCpPdD])";
QRegularExpression RTextRenderer::rxNoOp(rxNoOpStr);
QString RTextRenderer::rxNoOpEndStr = "%%$";
QRegularExpression RTextRenderer::rxNoOpEnd(rxNoOpEndStr);
QString RTextRenderer::escNoOpStr = "%%";
QRegularExpression RTextRenderer::escNoOp(escNoOpStr);
QString RTextRenderer::rxUnicodeStr = "\\\\[Uu]\\+([0-9a-fA-F]{4})";
QRegularExpression RTextRenderer::rxUnicode(rxUnicodeStr);
// optional break at space for wrapping text:
// TODO: add tabs and other whitespace:
QString RTextRenderer::rxOptionalBreakStr = "[ ]+";
//QString RTextRenderer::rxOptionalBreakStr = "[_]+";
QRegularExpression RTextRenderer::rxOptionalBreak(rxOptionalBreakStr);

QString rxAllTmp =
    RTextRenderer::rxAlignmentLeftStr + "|"
    + RTextRenderer::rxAlignmentCenterStr + "|"
    + RTextRenderer::rxAlignmentRightStr + "|"
    + RTextRenderer::rxXAlignmentLeftStr + "|"
    + RTextRenderer::rxXAlignmentCenterStr + "|"
    + RTextRenderer::rxXAlignmentRightStr + "|"
    + RTextRenderer::rxXSpaceMTextStr + "|"
    + RTextRenderer::rxTabMMStr + "|"
    + RTextRenderer::rxTabINStr + "|"
    + RTextRenderer::rxParagraphFeedStr + "|"
    + RTextRenderer::rxXFeedStr + "|"
    + RTextRenderer::rxHeightChangeStr + "|"
    + RTextRenderer::rxStackedTextStr + "|"
    + RTextRenderer::rxColorChangeIndexStr + "|"
    + RTextRenderer::rxColorChangeCustomStr + "|"
    + RTextRenderer::rxNonBreakingSpaceStr + "|"
    + RTextRenderer::rxOverlineOnStr + "|"
    + RTextRenderer::rxOverlineOffStr + "|"
    + RTextRenderer::rxUnderlineOnStr + "|"
    + RTextRenderer::rxUnderlineOffStr + "|"
    + RTextRenderer::rxStrikethroughOnStr + "|"
    + RTextRenderer::rxStrikethroughOffStr + "|"
    + RTextRenderer::rxWidthChangeStr + "|"
    + RTextRenderer::rxObliqueAngleChangeStr + "|"
    + RTextRenderer::rxTrackChangeStr + "|"
    + RTextRenderer::rxAlignmentChangeStr + "|"
    + RTextRenderer::rxAlignmentChangeBlockStr + "|"
    + RTextRenderer::rxFontChangeCadStr + "|"
    + RTextRenderer::rxFontChangeTtfStr + "|"
    + RTextRenderer::rxBeginBlockStr + "|"
    + RTextRenderer::rxEndBlockStr + "|"
    + RTextRenderer::rxBackslashStr + "|"
    + RTextRenderer::rxCurlyOpenStr + "|"
    + RTextRenderer::rxCurlyCloseStr + "|"
    + RTextRenderer::rxDegreeStr + "|"
    + RTextRenderer::rxPlusMinusStr + "|"
    + RTextRenderer::rxDiameterStr + "|"
    + RTextRenderer::rxUnderlineStr + "|"
    + RTextRenderer::rxUnicodeStr + "|"
      // keep at the end as replacing \p first will break \pqc;, etc.
    + RTextRenderer::rxLineFeedStr;

QString RTextRenderer::rxAllStr = "(" + rxAllTmp + ")";
QString RTextRenderer::rxAllBreakStr = "(" + rxAllTmp + "|" + RTextRenderer::rxOptionalBreakStr + ")";
QRegularExpression RTextRenderer::rxAll(RTextRenderer::rxAllStr);
QRegularExpression RTextRenderer::rxAllBreak(RTextRenderer::rxAllBreakStr);

QMutex RTextRenderer::m;


RTextRenderer::RTextRenderer(const RTextBasedData& textData, bool draft, Target target, double fontHeightFactor)
    : textData(textData), target(target), height(0.0), width(0.0),
      draft(draft), fontHeightFactor(fontHeightFactor) {

    if (textData.isSimple()) {
        renderSimple();
    }
    else {
        render();
    }
}


/**
 * Renders the text data into painter paths.
 */
void RTextRenderer::renderSimple() {
    boundingBox = RBox();
    painterPaths.clear();
    textLayouts.clear();
    richText = "";

    if (textData.getRenderedText().isEmpty()) {
        return;
    }

    RVector pos = textData.getAlignmentPoint();
    if (textData.getHAlign()==RS::HAlignFit) {
        pos = textData.getPosition();
    }
    QString text = textData.getRenderedText();
    double textHeight = textData.getTextHeight();
    RS::VAlign verticalAlignment = textData.getVAlign();
    RS::HAlign horizontalAlignment = textData.getHAlign();
    QString fontName = textData.getFontName();
    QString fontFile = textData.getFontFile();
    bool bold = textData.isBold();
    bool italic = textData.isItalic();
    bool underline = false;
    double angle = textData.getAngle();

    // degree:
    text.replace(RTextRenderer::rxDegree, RTextRenderer::chDegree);
    // plus minus:
    text.replace(RTextRenderer::rxPlusMinus, RTextRenderer::chPlusMinus);
    // diameter:
    text.replace(RTextRenderer::rxDiameter, RTextRenderer::chDiameter);
    // underlined:
    //text.replace(QRegExp(RTextRenderer::rxUnderline), "");
    // no op (%%x -> x):
    text.replace(RTextRenderer::rxNoOp, "\\1");
    // no op at end of string (%% -> ""):
    text.replace(RTextRenderer::rxNoOpEnd, "");
    // unicode:
    text = RDxfServices::parseUnicode(text);
//    QRegExp reg;
//    reg.setPattern(rxUnicode);
//    int ucPos = 0;
//    bool ok = true;
//    int uc = 0;
//    while ((ucPos = reg.indexIn(text, 0)) != -1) {
//        uc = reg.cap(1).toInt(&ok, 16);
//        if (!ok) {
//            break;
//        }
//        text.replace(ucPos, reg.matchedLength(), QChar(uc));
//    }

    bool leadingSpaces = false;
    bool trailingSpaces = false;

    if (!text.isEmpty()) {
        if (text.at(0).isSpace()) {
            leadingSpaces = true;
        }
        if (text.at(text.length()-1).isSpace()) {
            trailingSpaces = true;
        }
    }

    // implicit top level format block:
    QTextCharFormat f;
    f.setForeground(QBrush(QColor()));
    currentFormat.push(f);
    QTextLayout::FormatRange fr;
    fr.start = 0;
    fr.length = text.length();
    fr.format = currentFormat.top();
    QList<QTextLayout::FormatRange> formats;
    formats.append(fr);
    blockHeight.push(textHeight);
    blockFont.push(fontName);
    blockFontFile.push(fontFile);
    blockBold.push(bold);
    blockItalic.push(italic);
    blockUnderline.push(underline);
    useCadFont.push(RFontList::isCadFont(getBlockFont(), getBlockFontFile()));
    openTags.push(QStringList());

    double horizontalAdvance = 0.0;
    double horizontalAdvanceNoSpacing = 0.0;
    double horizontalAdvanceNoTrailingSpace = 0.0;
    double ascent = 0.0;
    double descent = 0.0;
    double usedHeight = 0.0;

    {
        // handle underlining formats:
        bool found = true;
        QList<int> underlineOnOff;
        QRegularExpression rx(RTextRenderer::rxUnderline);
#if QT_VERSION >= 0x050000
        QRegularExpressionMatch match;
        while (found) {
            found = false;
            int i = RS::indexIn(rx, match, text);
            int len = RS::matchedLength(rx, match);

            if (i!=-1) {
                found = true;
                underlineOnOff.append(i);
                text.replace(i, len, "");
            }
        }
#else
        while (found) {
            found = false;
            int i = rx.indexIn(text);
            int len = rx.matchedLength();

            if (i!=-1) {
                found = true;
                underlineOnOff.append(i);
                text.replace(i, len, "");
            }
        }
#endif

        int maxI = text.length()-1;
        QTextCharFormat fUnderlined;
        fUnderlined.setUnderlineStyle(QTextCharFormat::SingleUnderline);
        for (int i=0; i<underlineOnOff.length(); i+=2) {
            QTextLayout::FormatRange fr;
            fr.start = underlineOnOff[i];
            int end = i+1<underlineOnOff.length() ? underlineOnOff[i+1] : maxI + 1;
            fr.length = end - fr.start;
            fr.format = fUnderlined;
            formats.append(fr);
        }
    }

    // get painter paths for text at height 1.0:
    painterPaths = getPainterPathsForBlock(
                text, formats,
                horizontalAdvance,
                horizontalAdvanceNoSpacing,
                horizontalAdvanceNoTrailingSpace,
                ascent, descent,
                usedHeight);

    width = horizontalAdvanceNoSpacing * textHeight * textData.getXScale();

    // transform to scale text from 1.0 to current text height:
    QTransform sizeTransform;
    sizeTransform.scale(textHeight * textData.getXScale(), textHeight);

    //TODO: textTransforms.append(sizeTransform);
//    if (!textLayouts.isEmpty()) {
//        textLayouts.last().transform = sizeTransform;
//    }

    // transform paths of text:
    boundingBox = RBox();
    for (int i=0; i<painterPaths.size(); ++i) {

        // we don't use transform here:
        // a non-uniform scaling operation here drops the original shapes in
        // the painterpath:
        //painterPaths[i].transform(sizeTransform);
        painterPaths[i].scale(textHeight * textData.getXScale(), textHeight);
        boundingBox.growToInclude(painterPaths[i].getBoundingBox());
    }

    for (int i=0; i<textLayouts.length(); ++i) {
        if (!lineBlockTransforms.isEmpty()) {
            textLayouts[i].transform *= lineBlockTransforms.last();
        }
        textLayouts[i].transform *= sizeTransform;
    }

    //for (int i=0; i<textLayouts.length(); ++i) {
    //    textLayouts[i].transform = sizeTransform;
    //}

    // feature size of a text is its height
    // determines if text is displayed or only bounding box
    double featureSize = boundingBox.getHeight();

    QPen pen;
    for (int i=0; i<painterPaths.size(); ++i) {
        if (i==0) {
            pen = painterPaths[i].getPen();
            if (pen.style()==Qt::NoPen) {
                pen = QPen(painterPaths[i].getBrush().color());
            }
        }
        painterPaths[i].setFeatureSize(featureSize);
    }

    // add bounding box with negative feature size:
    // only shown when text is smaller than threshold:
    RPainterPath bbPath;
    bbPath.addBox(boundingBox);
    bbPath.setFeatureSize(-featureSize);
    bbPath.setPen(pen);
    painterPaths.append(bbPath);

    //height = boundingBox.getHeight();

    double topLine = textHeight;
    double baseLine = 0.0;
    double bottomLine = descent * textHeight;

    // at this point, the text is at 0/0 with the base line of the
    // first text line at y==0

    double xOffset = 0.0;
    double yOffset = 0.0;

    switch (verticalAlignment) {
    case RS::VAlignTop:
        yOffset = -topLine;
        break;
    case RS::VAlignMiddle:
        yOffset = -textHeight/2.0;
        break;
    case RS::VAlignBase:
        yOffset = -baseLine;
        break;
    case RS::VAlignBottom:
        yOffset = -bottomLine;
        break;
    }

    switch (horizontalAlignment) {
    default:
    case RS::HAlignAlign:
    case RS::HAlignFit:
    case RS::HAlignLeft:
        if (!leadingSpaces) {
            if (RSettings::getSimpleTextAlignLeft()) {
                // move completely to the left (left border is 0.0):
                // backwards compatibility:
                xOffset = -boundingBox.getMinimum().x;
            }
        }
        else {
            xOffset = 0.0;
        }
        break;
    case RS::HAlignMid:
    case RS::HAlignCenter:
        if (!leadingSpaces && !trailingSpaces) {
            xOffset =  -(boundingBox.getMinimum().x +
                          boundingBox.getMaximum().x)/2.0;
        }
        else {
            xOffset = -horizontalAdvance/2.0*textHeight;
        }
        break;
    case RS::HAlignRight:
        if (!trailingSpaces) {
            xOffset = -boundingBox.getMaximum().x;
        }
        else {
            xOffset = -horizontalAdvance*textHeight;
        }
        break;
    }

    height = boundingBox.getHeight();

    QTransform globalTransform;
    globalTransform.translate(pos.x, pos.y);
    globalTransform.rotate(RMath::rad2deg(angle));

    // TODO: mirror in X / Y:
    if (textData.isBackward() && textData.isUpsideDown()) {
        globalTransform.scale(-1, -1);
    }
    else if (textData.isBackward()) {
        globalTransform.scale(-1, 1);
    }
    else if (textData.isUpsideDown()) {
        globalTransform.scale(1, -1);
    }

    globalTransform.translate(xOffset, yOffset);

    // apply global transform for position, angle and vertical alignment:
    boundingBox = RBox();
    for (int i=0; i<painterPaths.size(); ++i) {
        painterPaths[i].transform(globalTransform);

        boundingBox.growToInclude(painterPaths[i].getBoundingBox());
    }

    for (int i=0; i<textLayouts.length(); ++i) {
        textLayouts[i].transform *= globalTransform;
    }
}

/**
 * Renders the text data into painter paths.
 */
void RTextRenderer::render() {
    //qDebug() << "=========================================================";
    bool wrap = textData.getTextWidth()>0.0;
    //qDebug() << "wrap:" << wrap;
    //wrap = false;

    //qDebug() << "rxAllStr:" << rxAllStr;

    boundingBox = RBox();
    painterPaths.clear();
    textLayouts.clear();
    richText = "";

    QString text = textData.getRenderedText();
    //RVector position = textData.getPosition();
    RVector position = textData.getAlignmentPoint();
    double textHeight = textData.getTextHeight();
    RS::VAlign verticalAlignment = textData.getVAlign();
    RS::HAlign horizontalAlignment = textData.getHAlign();
    double lineSpacingFactor = textData.getLineSpacingFactor();
    QString fontName = textData.getFontName();
    QString fontFile = textData.getFontFile();
    bool bold = textData.isBold();
    bool italic = textData.isItalic();
    bool underline = false;
    double angle = textData.getAngle();
    //RColor color = textData.getColor(true);

    // split up text where separation is required due to line feed,
    // or any type of height change, color change, or other formatting change
    // (\P, \H[0-9]*.?[0-9]+;, \S*/*;, ...)

    // split up text at every formatting change:
    QRegularExpression rxAllLocal = rxAll;
    if (wrap) {
        rxAllLocal = rxAllBreak;
    }
    QStringList literals = text.split(rxAllLocal);

    // collect formatting change information for after every literal:
    QStringList formattings;
    int pos = 0;
    int i=1;
    QRegularExpressionMatch match;
    while ((pos = RS::indexIn(rxAllLocal, match, text, pos)) != -1) {
        QString formatting = RS::captured(rxAllLocal, match, 1);
        //qDebug() << "formatting:" << formatting;

        // space is literal and also formatting (optional line break):
        if (RS::exactMatch(rxOptionalBreak, formatting)) {
            literals.insert(i++, formatting);
            formattings.append(formatting);
        }

        formattings.append(formatting);
        pos += RS::matchedLength(rxAllLocal, match);
        i++;
    }

//    qDebug() << "literals with space:" << literals;
//    qDebug() << "formattings (after block):" << formattings;
    Q_ASSERT(formattings.length()==literals.length()-1);

    // x position in real units:
    double xCursor = 0.0;
    // y position for next text line:
    double yCursor = 0.0;
    // painter paths for current text line:
    QList<RPainterPath> linePaths;
    // max ascent of current text line:
    double maxAscent = 0.0;
    // max descent of current line:
    double minDescent = 0.0;
    // max descent of _previous_ line:
    double minDescentPrevious = 0.0;
    // maximum used height of current line:
    double usedHeight = 0.0;
    // true for the first block of the current line:
    bool firstBlockInLine = true;
    // current line has leading spaces:
    bool leadingSpaces = false;
    // current line has trailing spaces:
    bool trailingSpaces = false;
    // text has leading empty lines:
    bool leadingEmptyLines = false;
    // text has trailing empty lines:
    bool trailingEmptyLines = false;
    int lineCounter = 0;
    QString textBlock;
    QList<QTextLayout::FormatRange> formats;

    bool blockChangedHeightOrFont = false;

    // implicit top level format block:
    QTextCharFormat f;
    f.setForeground(QBrush(QColor()));
    currentFormat.push(f);
    QTextLayout::FormatRange fr;
    fr.start = 0;
    fr.length = 0;
    fr.format = currentFormat.top();
    formats.append(fr);
    blockHeight.push(textHeight);
    blockFont.push(fontName);
    blockFontFile.push(fontFile);
    blockBold.push(bold);
    blockItalic.push(italic);
    blockUnderline.push(underline);
    useCadFont.push(RFontList::isCadFont(fontName, fontFile));
    openTags.push(QStringList());

    width = 0.0;
    height = 0.0;

    bool insertLineBreak = false;
    // don't wrap first block in line:
    bool noBreakFirstBlock = true;

    QList<QTextLayout::FormatRange> breakPointFormats = formats;
    QStack<QTextCharFormat> breakPointCurrentFormat = currentFormat;
    int breakPointTextLayoutsLength = -1;
    int breakPointI = -1;
    int breakPointLinePathsLength = -1;
    int breakPointLineBlockTransformsLength = -1;
    //int breakPointPainterPathsLength = -1;

    // iterate through all text blocks:
    for (int i=0; i<literals.size() || insertLineBreak; ++i) {
//        qDebug() << "------------------------------------------------------------------------------------------------- rendering literal:" << i;

        // insert auto line wrap and render same block again but on new line:
        // remove already rendered block that extends over width of text box:
        if (insertLineBreak) {
            //qDebug() << "break and rollback";
            insertLineBreak = false;

            if (breakPointI>0) {

//                qDebug() << "roll back to literal:" << breakPointI;
                // roll back to previous potential break point:
                formats = breakPointFormats;
                currentFormat = breakPointCurrentFormat;
                //lineBlockTransforms = breakPointLineBlockTransforms;
                i = breakPointI;
//                while (textLayouts.length() > breakPointTextLayoutsLength && breakPointTextLayoutsLength>0) {
//                    textLayouts.removeLast();
//                }
//                while (lineBlockTransforms.length() > breakPointLineBlockTransformsLength && breakPointLineBlockTransformsLength>0) {
//                    lineBlockTransforms.removeLast();
//                }
//                while (painterPaths.length() > breakPointPainterPathsLength && breakPointPainterPathsLength>0) {
//                    painterPaths.removeLast();
//                }
//                while (linePaths.length() > breakPointLinePathsLength && breakPointLinePathsLength>0) {
//                    linePaths.removeLast();
//                }

                //qDebug() << "after rb: tls:" << textLayouts.length();
                //qDebug() << "after rb: pps:" << painterPaths.length();

                breakPointI = -1;
                breakPointTextLayoutsLength = -1;
                breakPointLinePathsLength = -1;
                breakPointLineBlockTransformsLength = -1;
                //breakPointPainterPathsLength = -1;
            }
        }

//        formatsPrev = formats;
//        currentFormatPrev = currentFormat;

        // the literal text, e.g. "ABC":
        QString literal = literals.at(i);

        // the formatting _after_ the text, e.g. "\C1;"
        QString formatting;
        if (i<formattings.size()) {
            formatting = formattings.at(i);
        }

//        qDebug() << "block: " << i;
//        qDebug() << "  literal: " << literal;
//        qDebug() << "  literal length: " << literal.length();
//        qDebug() << "  formatting _after_ text block: " << formatting;
//        qDebug() << "  font: " << blockFont.top();
//        qDebug() << "  height: " << blockHeight.top();
//        qDebug() << "  cad font: " << useCadFont.top();
//        qDebug() << "  xCursor: " << xCursor;

        // handle literal:
        textBlock.append(literal);

        if (firstBlockInLine) {
            if (!literal.isEmpty()) {
                if (literal.at(0).isSpace()) {
//                    qDebug() << "got leading space";
                    leadingSpaces = true;
                }
            }
            else {
                if (formatting=="\\~" || (!formatting.isEmpty() && formatting.at(0).isSpace())) {
//                    qDebug() << "got leading space";
                    leadingSpaces = true;
                }
            }
            firstBlockInLine = false;
        }

        bool lineFeed = false;
        bool paragraphFeed = false;
        bool xFeed = false;
        bool heightChange = false;
        bool stackedText = false;
        bool fontChange = false;
        bool underlineChange = false;
        bool colorChange = false;
        bool blockEnd = false;
        bool optionalBreak = false;
        bool optionalBreakText = false;

        // detect formatting that ends the current text block:
        if (!formatting.isEmpty()) {
            fontChange = RS::exactMatch(rxFontChangeTtf, formatting) ||
                RS::exactMatch(rxFontChangeCad, formatting);
            underlineChange = RS::exactMatch(rxUnderlineChange, formatting);
            colorChange = RS::exactMatch(rxColorChangeCustom, formatting) ||
                RS::exactMatch(rxColorChangeIndex, formatting);
            heightChange = RS::exactMatch(rxHeightChange, formatting);
            stackedText = RS::exactMatch(rxStackedText, formatting);
            lineFeed = RS::exactMatch(rxLineFeed, formatting);
            paragraphFeed = RS::exactMatch(rxParagraphFeed, formatting);
            if (textData.isDimensionLabel()) {
                xFeed = RS::exactMatch(rxXFeed, formatting);
            }
            blockEnd = RS::exactMatch(rxEndBlock, formatting);
            optionalBreak = RS::exactMatch(rxOptionalBreak, formatting);
        }

        optionalBreakText = RS::exactMatch(rxOptionalBreak, textBlock);

        bool start = (i==0);
        bool end = (i==literals.size()-1);

        // first line is empty:
        if (textBlock.trimmed().isEmpty() && (lineFeed || paragraphFeed || xFeed || end)) {
            if (start) {
                leadingEmptyLines = true;
            }
            else if (end) {
                trailingEmptyLines = true;
            }
        }

        // reached a new text block that needs to be rendered separately
        // due to line feed, height change, font change, ...:
        if (target==RichText ||
            lineFeed || paragraphFeed || xFeed || heightChange || underlineChange || stackedText ||
            fontChange || colorChange || end ||
            (blockEnd && blockChangedHeightOrFont) ||
            optionalBreak) {

            // render block _before_ format change that requires new block:
            if (textBlock!="") {

                // fix format lengths to match up. each format stops where
                // the next one starts. formatting that is carried over is set
                // again for the new format.
                for (int k=0; k<formats.size(); k++) {
                    int nextStart;
                    if (k<formats.size()-1) {
                        nextStart = formats[k+1].start;
                    }
                    else {
                        nextStart = textBlock.length();
                    }
                    formats[k].length = nextStart - formats[k].start;
                }

                if (target==RichText) {
                    richText += getRichTextForBlock(textBlock, formats);
                }

                if (target==PainterPaths) {

                    // potential line break:
                    // back up various data to roll back in case of line wrap:
                    if (RS::exactMatch(rxOptionalBreak, textBlock)) {
//                        qDebug() << "potential break at:" << textBlock << i;
//                        //qDebug() << "painterPaths:" << painterPaths.length();
//                        qDebug() << "textLayouts:" << textLayouts.length();

//                        // potential future line break:
//                        // remember state at this point:
//                        breakPointFormats = formats;
//                        breakPointCurrentFormat = currentFormat;
//                        // start new line _after_ white space and skip whitespace in case of break:
//                        breakPointI = i+1;
                        breakPointTextLayoutsLength = textLayouts.length();
                        breakPointLineBlockTransformsLength = lineBlockTransforms.length();
                        breakPointLinePathsLength = linePaths.length();
//                        //breakPointPainterPathsLength = painterPaths.length();
                    }

                    double horizontalAdvance = 0.0;
                    double horizontalAdvanceNoSpacing = 0.0;
                    double horizontalAdvanceNoTrailingSpace = 0.0;
                    double ascent = 0.0;
                    double descent = 0.0;
                    QList<RPainterPath> paths;

                    /*
                    qDebug() << "== render: " << textBlock << "==";
                    qDebug() << "formatting after:" << formatting;
                    qDebug() << "formats:" << formats.length();
                    for (int k=0; k<formats.length(); k++) {
                        QTextLayout::FormatRange f = formats[k];
                        qDebug() << "  start:" << f.start;
                        qDebug() << "  length:" << f.length;
                        qDebug() << "  fmt:" << f.format;
                        qDebug() << "  col:" << f.format.foreground();
                    }
                    */

                    // get painter paths for current text block at height 1.0, position 0,0:
                    paths = getPainterPathsForBlock(
                                textBlock, formats,
                                horizontalAdvance,
                                horizontalAdvanceNoSpacing,
                                horizontalAdvanceNoTrailingSpace,
                                ascent, descent,
                                usedHeight);

//                    qDebug() << "horizontalAdvance" << horizontalAdvance * getBlockHeight();
//                    qDebug() << "horizontalAdvanceNoSpacing" << horizontalAdvanceNoSpacing * getBlockHeight();
//                    qDebug() << "horizontalAdvanceNoTrailingSpace" << horizontalAdvanceNoTrailingSpace * getBlockHeight();

                    // detected wrap:
//                    qDebug() << "detect wrap";
                    if (!noBreakFirstBlock && breakPointI>=0) {
//                        qDebug() << "detect wrap: 001";
//                        qDebug() << "detect wrap cur: " << xCursor + horizontalAdvanceNoTrailingSpace * getBlockHeight() * textData.getXScale();
//                        qDebug() << "detect wrap text w: " << textData.getTextWidth();
                        // line break needed:
                        if (wrap && xCursor + horizontalAdvanceNoTrailingSpace * getBlockHeight() * textData.getXScale() > textData.getTextWidth()) {
//                            qDebug() << "insert wrap before:" << textBlock;

                            insertLineBreak = true;
                        }
                    }
                    else {
                        noBreakFirstBlock = false;
                    }

                    // transform to scale text from 1.0 to current text height:
                    QTransform sizeTransform;
                    sizeTransform.scale(getBlockHeight() * textData.getXScale(), getBlockHeight());

                    // transform for current block due to xCursor position:
                    QTransform blockTransform;
                    blockTransform.translate(xCursor, 0);
//                    qDebug() << "blockTransform: xCursor:" << xCursor;

                    // combine transforms for current text block:
                    QTransform allTransforms = sizeTransform;
                    allTransforms *= blockTransform;

                    //textTransforms.append(allTransforms);
                    if (!lineBlockTransforms.isEmpty()) {
                        lineBlockTransforms.last() *= allTransforms;
                    }

                    maxAscent = qMax(maxAscent, ascent * getBlockHeight());
                    minDescent = qMin(minDescent, descent * getBlockHeight());

                    //qDebug() << "maxAscent" << maxAscent;
                    //qDebug() << "minDescent" << minDescent;

                    // transform paths of current block and append to paths
                    // of current text line:
                    for (int k=0; k<paths.size(); ++k) {
                        RPainterPath p = paths.at(k);
                        // ### TODO ###:
                        p.transform(allTransforms);
                        linePaths.append(p);
                    }

                    //qDebug() << "xCursor" << xCursor;
                    //qDebug() << "yCursor" << yCursor;

                    xCursor += horizontalAdvance * getBlockHeight() * textData.getXScale();
                }
            }

            // empty text, might be line feed, we need ascent, descent anyway:
            else if ((lineFeed || paragraphFeed || xFeed || end) && !blockHeight.isEmpty()) {
                if (target==PainterPaths) {
                    double horizontalAdvance = 0.0;
                    double horizontalAdvanceNoSpacing = 0.0;
                    double horizontalAdvanceNoTrailingSpace = 0.0;
                    double ascent = 0.0;
                    double descent = 0.0;
                    double usedHeight = 0.0;

                    // get painter paths for current text block at height 1.0:
                    getPainterPathsForBlock(
                                "A", QList<QTextLayout::FormatRange>(),
                                horizontalAdvance,
                                horizontalAdvanceNoSpacing,
                                horizontalAdvanceNoTrailingSpace,
                                ascent, descent,
                                usedHeight);

                    // make sure the "A" is not rendered:
                    textLayouts.removeLast();
                    lineBlockTransforms.removeLast();

                    maxAscent = qMax(maxAscent, ascent * getBlockHeight());
                    minDescent = qMin(minDescent, descent * getBlockHeight());
                }
            }

            // handle stacked text:
            if (stackedText) {
//                qDebug() << "stacked text";

                //QRegExp reg(rxStackedText);
                //reg.setPattern(rxStackedText);
                QRegularExpressionMatch match;
                RS::exactMatch(rxStackedText, match, formatting);

//                qDebug() << "before: textLayouts.length:" << textLayouts.length();
//                qDebug() << "before: linePaths.length:" << linePaths.length();
//                qDebug() << "before: lineBlockTransforms.length:" << lineBlockTransforms.length();

                if (target==PainterPaths) {
                    double horizontalAdvance[2];
                    horizontalAdvance[0] = 0.0;
                    horizontalAdvance[1] = 0.0;
                    double horizontalAdvanceNoSpacing[2];
                    horizontalAdvanceNoSpacing[0] = 0.0;
                    horizontalAdvanceNoSpacing[1] = 0.0;
                    // TODO: make adjustable:
                    double heightFactor = 0.4;

                    // s==0: superscript, s==1: subscript:
                    for (int s=0; s<=1; ++s) {
                        QString script = RS::captured(rxStackedText, match, s+1);
                        if (script.isEmpty()) {
                            continue;
                        }

                        // replace special characters in sub/super script:
                        script.replace(rxDiameter, chDiameter);
                        script.replace(rxPlusMinus, chPlusMinus);
                        script.replace(rxDegree, chDegree);

                        QList<RPainterPath> paths;

                        double ascent = 0.0;
                        double descent = 0.0;
                        double usedHeight = 0.0;
                        double horizontalAdvanceNoTrailingSpace = 0.0;

                        QList<QTextLayout::FormatRange> localFormats;

                        QTextLayout::FormatRange fr;
                        fr.start = 0;
                        fr.length = script.length();
                        fr.format = currentFormat.top();
                        localFormats.append(fr);

                        // get painter paths for superscript / subscript at height 1.0:
                        paths = getPainterPathsForBlock(
                                    script, localFormats,
                                    horizontalAdvance[s],
                                    horizontalAdvanceNoSpacing[s],
                                    horizontalAdvanceNoTrailingSpace,
                                    ascent, descent,
                                    usedHeight);

                        if (s==0) {
                            maxAscent = qMax(maxAscent, ascent * getBlockHeight() * heightFactor + getBlockHeight()*(1.0-heightFactor));
                        }
                        else {
                            minDescent = qMin(minDescent, descent * getBlockHeight() * heightFactor);
                        }

                        // transform to scale text from 1.0 to current text height * 0.4:
                        QTransform sizeTransform;
                        sizeTransform.scale(getBlockHeight()*heightFactor*textData.getXScale(), getBlockHeight()*heightFactor);

                        // adjust height stored in layout accordingly:
                        if (!textLayouts.isEmpty()) {
                            textLayouts.last().height = getBlockHeight()*heightFactor;
                        }

                        // move top text more to the right for italic texts:
                        double xOffset = 0.0;
                        if (s==0 && getBlockItalic()==true) {
                            double y = getBlockHeight()*(1.0-heightFactor);
                            // assume italic means roughly 12 degrees:
                            xOffset = tan(RMath::deg2rad(12)) * y;
                        }

                        // transform for current block due to xCursor position
                        // and top or bottom text position:
                        QTransform blockTransform;
                        blockTransform.translate(xCursor + xOffset,
                                                 s==0 ? getBlockHeight()*(1.0-heightFactor) : 0.0);

                        horizontalAdvance[s] += xOffset / (getBlockHeight() * heightFactor);

                        // combine transforms for current text block:
                        QTransform allTransforms = sizeTransform;
                        allTransforms *= blockTransform;

                        // transform paths of current block and append to paths
                        // of current text line:
                        for (int k=0; k<paths.size(); ++k) {
                            RPainterPath p = paths.at(k);
                            // ### TODO ###:
                            p.transform(allTransforms);
                            linePaths.append(p);
                        }

                        if (!lineBlockTransforms.isEmpty()) {
                            lineBlockTransforms.last() *= allTransforms;
                        }
                    }

                    // detected wrap:
                    if (!noBreakFirstBlock && breakPointI>=0) {
                        // line break needed:
                        if (wrap && xCursor + qMax(horizontalAdvance[0], horizontalAdvance[1]) * getBlockHeight() * heightFactor > textData.getTextWidth()) {
//                            qDebug() << "insert wrap before stacked text:" << textBlock;

                            insertLineBreak = true;
                        }
                    }
                    else {
                        noBreakFirstBlock = false;
                    }

                    xCursor += qMax(horizontalAdvance[0], horizontalAdvance[1]) * getBlockHeight() * heightFactor;
                }

//                qDebug() << "after: textLayouts.length:" << textLayouts.length();
//                qDebug() << "after: linePaths.length:" << linePaths.length();
//                qDebug() << "after: lineBlockTransforms.length:" << lineBlockTransforms.length();

                if (target==RichText) {
                    QString super = RS::captured(rxStackedText, match, 1);
                    QString sub = RS::captured(rxStackedText, match, 2);
                    if (!super.isEmpty()) {
                        richText += QString("<span style=\"vertical-align:super;\">%1</span>").arg(super);
                    }
                    if (!sub.isEmpty()) {
                        richText += QString("<span style=\"vertical-align:sub;\">%1</span>").arg(sub);
                    }
                }
            }
            // end of stacked text handling

            // prepare for next text block:
            if (lineFeed || paragraphFeed || xFeed || end) {
                if (!textBlock.isEmpty()) {
                    if (textBlock.at(textBlock.length()-1).isSpace()) {
                        trailingSpaces = true;
                    }
                }
//                else {
//                    if (formatting=="\\~") {
//                        trailingSpaces = true;
//                    }
//                }
            }

            textBlock = "";
            formats.clear();
            QTextLayout::FormatRange fr;
            fr.start = 0;
            fr.length = 0;
            if (!currentFormat.isEmpty()) {
                fr.format = currentFormat.top();
            }
            //qDebug() << "appending format:" << fr.format.foreground();
            formats.append(fr);

            // handle text line.
            // add all painter paths of the current line to result set of
            // painter paths. apply line feed transformations.
            if (insertLineBreak || lineFeed || paragraphFeed || xFeed || end) {
//                qDebug() << "lineFeed: adding text line:";
//                qDebug() << "  maxAscent: " << maxAscent;
//                qDebug() << "  minDescent: " << minDescent;
//                qDebug() << "  minDescentPrevious: " << minDescentPrevious;
//                qDebug() << "got line feed or end";
//                qDebug() << "  trailingSpaces: " << trailingSpaces;
//                qDebug() << "  leadingSpaces: " << leadingSpaces;

                if (target==RichText) {
                    if (lineFeed || paragraphFeed || xFeed) {
                        richText += "<br/>";
                    }
                }

                if (lineCounter!=0) {
                    yCursor += (minDescentPrevious - maxAscent) * lineSpacingFactor;
                }

                if (insertLineBreak) {
//                    qDebug() << "got line break: roll back last rendered block";
                    //qDebug() << "linePaths:" << linePaths.length();

                    // remove paths of blocks that are wrapped to next line:
                    // this is done here to make sure alignments and bounding boxes are correct:
                    while (linePaths.length() > breakPointLinePathsLength && (breakPointLinePathsLength>0 || leadingSpaces)) {
                        linePaths.removeLast();
                    }
//                    qDebug() << "breakPointTextLayoutsLength:" << breakPointTextLayoutsLength;
//                    qDebug() << "textLayouts.length():" << textLayouts.length();
                    while (textLayouts.length() > breakPointTextLayoutsLength && (breakPointTextLayoutsLength>0 || leadingSpaces)) {
//                        qDebug() << "remove last text layout";
                        textLayouts.removeLast();
                    }
                    while (lineBlockTransforms.length() > breakPointLineBlockTransformsLength && (breakPointLineBlockTransformsLength>0 || leadingSpaces)) {
                        lineBlockTransforms.removeLast();
                    }
                }

                // calculate line bounding box for alignment without spaces at borders:
                RBox lineBoundingBox;
                for (int k=0; k<linePaths.size(); ++k) {
                    RPainterPath p = linePaths.at(k);
                    lineBoundingBox.growToInclude(p.getBoundingBox());
                }

                if (lineBoundingBox.getHeight()<usedHeight) {
                    lineBoundingBox.c2.y = lineBoundingBox.c1.y + usedHeight;
                }

                // make sure bounding box includes actually used text height:
                boundingBox.growToInclude(lineBoundingBox);
//                qDebug() << "bb of line:" << boundingBox;

                double featureSize = lineBoundingBox.getHeight();

                QTransform lineTransform;

                switch (horizontalAlignment) {
                case RS::HAlignAlign:
                case RS::HAlignFit:
                case RS::HAlignLeft:
                    if (!leadingSpaces) {
                        // move completely to the left (left border is 0.0):
                        lineTransform.translate(
                                    -lineBoundingBox.getMinimum().x,
                                    yCursor);
                    }
                    else {
                        lineTransform.translate(0, yCursor);
                    }
                    break;
                case RS::HAlignMid:
                case RS::HAlignCenter:
                    if (!leadingSpaces && !trailingSpaces) {
                        lineTransform.translate(
                                    -(lineBoundingBox.getMinimum().x +
                                      lineBoundingBox.getMaximum().x)/2.0,
                                    yCursor);
                    }
                    else {
                        lineTransform.translate(-xCursor/2.0, yCursor);
                    }
                    break;
                case RS::HAlignRight:
                    if (!trailingSpaces) {
                        lineTransform.translate(-lineBoundingBox.getMaximum().x, yCursor);
                    }
                    else {
                        lineTransform.translate(-xCursor, yCursor);
                    }
                    break;
                }

                width = qMax(width, lineBoundingBox.getMaximum().x - qMin(0.0, lineBoundingBox.getMinimum().x));

                // apply transforms of current text line to all text layouts of current line:
                //qDebug() << "{{{";
                //qDebug() << "apply line transforms...:" << lineBlockTransforms.length();
                for (int n=0; n<lineBlockTransforms.length(); ++n) {
                    //qDebug() << " line transforms:" << lineTransform;
                    lineBlockTransforms[n] *= lineTransform;
                    if (!textLayouts.isEmpty()) {
                        int k = textLayouts.length()-lineBlockTransforms.length()+n;
                        if (k>=0 && k<textLayouts.length()) {
                            //qDebug() << "tl for:" << textLayouts[k].getText();
                            textLayouts[k].transform *= lineBlockTransforms[n];
                            //qDebug() << "tl trans:" << textLayouts[k].transform;
                        }
                    }
                }
                //qDebug() << "}}}";
                //textTransforms.append(lineBlockTransforms);
                //if (!textLayouts.isEmpty()) {
                //    textLayouts.last().second = lineBlockTransforms;
                //}
                lineBlockTransforms.clear();

                // add current text line to result set:
                // one painter path per text block:
                QPen pen;
                for (int k=0; k<linePaths.size(); ++k) {
                    RPainterPath p = linePaths[k];
                    if (k==0) {
                        pen = p.getPen();
                        if (pen.style()==Qt::NoPen) {
                           pen = QPen(p.getBrush().color());
                        }
                    }
                    p.transform(lineTransform);
                    p.setFeatureSize(featureSize);
                    painterPaths.append(p);
                    //if (!xFeed) {
                        // TODO: don't count line after xfeed for vertical alignment:
                    //}
                    RBox bb = p.getBoundingBox();
                    if (bb.isSane() && !bb.getSize().isZero()) {
                        boundingBox.growToInclude(bb);
                    }
                }

                // add bounding box painter path for whole line for speedy rendering of very small texts:
                //qDebug() << "adding bb";
                //qDebug() << "got tls before:" << textLayouts.length();
                RPainterPath bbPath;
                bbPath.addBox(lineBoundingBox);
                bbPath.transform(lineTransform);
                bbPath.setFeatureSize(-featureSize);
                bbPath.setPen(pen);
                painterPaths.append(bbPath);
                RTextLayout tl;
                //tl.correspondingPainterPaths = 1;
                textLayouts.append(tl);

                lineCounter++;
                xCursor = 0.0;
                maxAscent = 0.0;
                minDescentPrevious = minDescent;
                minDescent = 0.0;
                linePaths.clear();
                firstBlockInLine = true;
                leadingSpaces = false;
                trailingSpaces = false;
                usedHeight = 0.0;
                noBreakFirstBlock = true;

                //breakPointFormats = formats;
                //breakPointCurrentFormat = currentFormat;

                if (!insertLineBreak) {
                    // starting new line, not due to auto wrap:
                    breakPointI = -1;
//                    breakPointTextLayoutsLength = -1;
                    breakPointLineBlockTransformsLength = -1;
                }
            }
        }

        // optional break: backup data for roll back in case of auto wrap:
        if (optionalBreakText) {
//            qDebug() << "optional break found";
//            qDebug() << "back up roll back point:" << i+1;
            breakPointFormats = formats;
            breakPointCurrentFormat = currentFormat;
            // start new line _after_ white space and skip whitespace in case of break:
            breakPointI = i+1;
            //breakPointLineBlockTransformsLength = lineBlockTransforms.length();
            //breakPointLinePathsLength = linePaths.length();

            //breakPointTextLayoutsLength = textLayouts.length();
            //breakPointPainterPathsLength = painterPaths.length();

            //qDebug() << "breakPointTextLayoutsLength:" << breakPointTextLayoutsLength;
            //qDebug() << "breakPointPainterPathsLength:" << breakPointPainterPathsLength;
        }

        // handle formatting after text block, that applies either
        // to the next text block(s) or the rest of the current text block:
        if (formatting.isEmpty()) {
            continue;
        }

        //QRegExp reg;

        // unicode:
        //reg = rxUnicode;
        {
            QRegularExpressionMatch match;
            if (RS::exactMatch(rxUnicode, match, formatting)) {
                textBlock += QChar(RS::captured(rxUnicode, match, 1).toInt(0, 16));
                continue;
            }
        }

//        // unicode (5 hex digits):
//        reg.setPattern(rxUnicodeM);
//        if (RS::exactMatch(reg, formatting)) {
//            uint code = reg.cap(1).toInt(0, 16);
//            qDebug() << QString("M code: %1").arg(code, 0, 16);
//            QString c = QString::fromUcs4(&code, 1);
//            qDebug() << QString("M char: %1").arg(c);
//            textBlock += c;
//            continue;
//        }

        // curly braket open:
        //reg = rxCurlyOpen;
        if (RS::exactMatch(rxCurlyOpen, formatting)) {
            textBlock += "{";
            continue;
        }

        // curly braket close:
        //reg.setPattern(rxCurlyClose);
        if (RS::exactMatch(rxCurlyClose, formatting)) {
            textBlock += "}";
            continue;
        }

        // degree:
        //reg.setPattern(rxDegree);
        if (RS::exactMatch(rxDegree, formatting)) {
            textBlock += chDegree;
            continue;
        }

        // plus/minus:
        //reg.setPattern(rxPlusMinus);
        if (RS::exactMatch(rxPlusMinus, formatting)) {
            textBlock += chPlusMinus;
            continue;
        }

        // diameter:
        //reg.setPattern(rxDiameter);
        if (RS::exactMatch(rxDiameter, formatting)) {
            textBlock += chDiameter;
            continue;
        }

        // underlined:
        //reg.setPattern(rxUnderline);
        if (RS::exactMatch(rxUnderline, formatting)) {
            if (target==RichText) {
                if (!underline) {
                    richText += QString("<span style=\"text-decoration:underline;\">");
                    openTags.top().append("span");
                    underline = true;
                }
                else {
                    richText += QString("<span style=\"text-decoration:none;\">");
                    openTags.top().append("span");
                    underline = false;
                }
            }
            continue;
        }

        // underline on:
        //reg.setPattern(rxUnderlineOn);
        if (RS::exactMatch(rxUnderlineOn, formatting)) {
            setBlockUnderline(true);

            if (target==RichText) {
                richText += QString("<span style=\"text-decoration:underline;\">");
                openTags.top().append("span");
                underline = true;
            }
            continue;
        }

        // underline off:
        //reg.setPattern(rxUnderlineOff);
        if (RS::exactMatch(rxUnderlineOff, formatting)) {
            setBlockUnderline(false);

            if (target==RichText) {
                richText += QString("<span style=\"text-decoration:none;\">");
                openTags.top().append("span");
                underline = false;
            }
            continue;
        }

        // backslash:
        //reg.setPattern(rxBackslash);
        if (RS::exactMatch(rxBackslash, formatting)) {
            textBlock += "\\";
            continue;
        }

        // non-breaking space:
        //reg.setPattern(rxNonBreakingSpace);
        if (RS::exactMatch(rxNonBreakingSpace, formatting)) {
            if (target==PainterPaths) {
                textBlock += QChar(QChar::Nbsp);
            }
            if (target==RichText) {
                textBlock += "&nbsp;";
                //textBlock += QChar(QChar::Nbsp);
            }
            continue;
        }

        {
            // font change (TTF):
            //reg.setPattern(rxFontChangeTtf);
            QRegularExpressionMatch match;
            if (RS::exactMatch(rxFontChangeTtf, match, formatting)) {
                setBlockFont(RS::captured(rxFontChangeTtf, match, 1));
                for (int k=2; k<rxFontChangeTtf.captureCount()-1; k+=2) {
                    // code: i, b, c, p
                    QString code = RS::captured(rxFontChangeTtf, match, k);
                    // value: 0/1
                    int value = RS::captured(rxFontChangeTtf, match, k+1).toInt();

                    if (code.toLower()=="b") {
                        setBlockBold(value!=0);
                    }
                    else if (code.toLower()=="i") {
                        setBlockItalic(value!=0);
                    }
                }
                if (getBlockFont()=="gdt") {
                    setUseCadFont(true);
                }
                else {
                    setUseCadFont(false);
                }
                blockChangedHeightOrFont = true;

                if (target==RichText) {
                    QString style;
                    style += QString("font-family:%1;").arg(getBlockFont());
                    if (!useCadFont.top()) {
                        style += QString("font-weight:%1;").arg(getBlockBold() ? "bold" : "normal");
                        style += QString("font-style:%1;").arg(getBlockItalic() ? "italic" : "normal");
                    }
                    richText += QString("<span style=\"%1\">").arg(style);
                    openTags.top().append("span");
                }
                continue;
            }
        }

        {
            // font change (CAD):
            //reg.setPattern(rxFontChangeCad);
            QRegularExpressionMatch match;
            if (RS::exactMatch(rxFontChangeCad, match, formatting)) {
                setBlockFont(RS::captured(rxFontChangeCad, match, 1));
                bool prevTtf = !getUseCadFont();
                setUseCadFont(true);
                if (xCursor>RS::PointTolerance) {
                    RFont* f = RFontList::get(getBlockFont());
                    if (f!=NULL && f->isValid()) {
                        if (prevTtf) {
                            xCursor += f->getLetterSpacing() / 9.0 * getBlockHeight() * textData.getXScale();
                        }
                    }
                }
                blockChangedHeightOrFont = true;

                if (target==RichText) {
                    QString style;
                    style += QString("font-family:%1;").arg(getBlockFont());
                    richText += QString("<span style=\"%1\">").arg(style);
                    openTags.top().append("span");
                }
                continue;
            }
        }

        {
            // height change:
            //reg.setPattern(rxHeightChange);
            QRegularExpressionMatch match;
            if (RS::exactMatch(rxHeightChange, match, formatting)) {
                bool factor = RS::captured(rxHeightChange, match, 2)=="x";

                if (factor) {
                    if (!blockHeight.isEmpty()) {
                        setBlockHeight(getBlockHeight() * RS::captured(rxHeightChange, match, 1).toDouble());
                    }
                }
                else {
                    if (!blockHeight.isEmpty()) {
                        setBlockHeight(RS::captured(rxHeightChange, match, 1).toDouble());
                    }
                }
                blockChangedHeightOrFont = true;

                if (target==RichText && !blockHeight.isEmpty() && !openTags.isEmpty()) {
                    QString style;
                    style += QString("font-size:%1pt;").arg(getBlockHeight() * fontHeightFactor);
                    richText += QString("<span style=\"%1\">").arg(style);
                    openTags.top().append("span");
                }
                continue;
            }
        }

        QTextLayout::FormatRange fr;
        fr.start = textBlock.length();
        fr.length = 0;

        // start format block:
        //reg.setPattern(rxBeginBlock);
        if (RS::exactMatch(rxBeginBlock, formatting)) {
            currentFormat.push(getCurrentFormat());
            blockFont.push(getBlockFont());
            blockBold.push(getBlockBold());
            blockItalic.push(getBlockItalic());
            blockUnderline.push(getBlockUnderline());
            blockHeight.push(getBlockHeight());
            useCadFont.push(getUseCadFont());
            if (target==RichText) {
                openTags.push(QStringList());
            }
            blockChangedHeightOrFont = false;
            continue;
        }

        // end format block:
        //reg.setPattern(rxEndBlock);
        if (RS::exactMatch(rxEndBlock, formatting)) {
            if (insertLineBreak) {
                // we're inserting an automatic line break before this
                // block, so don't pop formatting yet
                // block will be repeated after line break:
                continue;
            }
            if (!currentFormat.isEmpty()) {
                currentFormat.pop();
            }
            if (!currentFormat.isEmpty()) {
                fr.format = currentFormat.top();
                formats.append(fr);
            }
            if (!blockFont.isEmpty()) {
                blockFont.pop();
            }
            if (!blockBold.isEmpty()) {
                blockBold.pop();
            }
            if (!blockItalic.isEmpty()) {
                blockItalic.pop();
            }
            if (!blockUnderline.isEmpty()) {
                blockUnderline.pop();
            }
            if (!blockHeight.isEmpty()) {
                blockHeight.pop();
            }
            if (!useCadFont.isEmpty()) {
                useCadFont.pop();
            }
            blockChangedHeightOrFont = false;

            if (target==RichText) {
                // close all tags that were opened in this block:
                if (!openTags.isEmpty()) {
                    for (int k=openTags.top().size()-1; k>=0; --k) {
                        QString tag = openTags.top().at(k);
                        richText += QString("</%1>").arg(tag);
                    }
                    openTags.pop();
                }
            }

            continue;
        }

        {
            // color change (indexed):
            //reg.setPattern(rxColorChangeIndex);
            QRegularExpressionMatch match;
            if (RS::exactMatch(rxColorChangeIndex, match, formatting)) {
                RColor blockColor = RColor::createFromCadIndex(RS::captured(rxColorChangeIndex, match, 1));
                //qDebug() << "block color:" << blockColor;
                if (!currentFormat.isEmpty()) {
                    //qDebug() << "001";
                    if (blockColor.isByLayer()) {
                        currentFormat.top().setForeground(RColor::CompatByLayer);
                    } else if (blockColor.isByBlock()) {
                        currentFormat.top().setForeground(RColor::CompatByBlock);
                    }
                    else {
                        currentFormat.top().setForeground(blockColor);
                    }
                    fr.format = currentFormat.top();
                    formats.append(fr);
                    //qDebug() << "appending format 2:" << fr.format.foreground();
                }

                if (target==RichText && !openTags.isEmpty()) {
                    QString style;
                    style += QString("color:%1;").arg(blockColor.name());
                    richText += QString("<span style=\"%1\">").arg(style);
                    openTags.top().append("span");
                }
                continue;
            }
        }

        {
            // color change (custom):
            //reg.setPattern(rxColorChangeCustom);
            QRegularExpressionMatch match;
            if (RS::exactMatch(rxColorChangeCustom, match, formatting)) {
                RColor blockColor = RColor::createFromCadCustom(RS::captured(rxColorChangeCustom, match, 1));
                if (!currentFormat.isEmpty()) {
                    currentFormat.top().setForeground(blockColor);
                    fr.format = currentFormat.top();
                    formats.append(fr);
                    //qDebug() << "formatting:" << formatting;
                    //qDebug() << "appending format 3:" << fr.format.foreground();
                }

                if (target==RichText && !openTags.isEmpty()) {
                    QString style;
                    style += QString("color:%1;").arg(blockColor.name());
                    richText += QString("<span style=\"%1\">").arg(style);
                    openTags.top().append("span");
                }
                continue;
            }
        }

//        if (RS::exactMatch(rxOptionalBreak, textBlock)) {
//            qDebug() << "potential break at:" << textBlock << i;
//            qDebug() << "painterPaths:" << painterPaths.length();
//            //breakPointPainterPathsLength = painterPaths.length();
//        }
    }

    if (target==PainterPaths) {
        // at this point, the text is at 0/0 with the base line of the
        // first text line at y==0

        // vertical alignment:
        // use bounding box (was adjusted for used text height):
        double topLine = boundingBox.getMaximum().y;
        double bottomLine = qMin(0.0, boundingBox.getMinimum().y);

        QTransform globalTransform;
        globalTransform.translate(position.x, position.y);
        globalTransform.rotate(RMath::rad2deg(angle));
        switch (verticalAlignment) {
        case RS::VAlignTop:
            //if (!leadingEmptyLines) {
                globalTransform.translate(0.0, -topLine);
            //}
            break;
        case RS::VAlignMiddle:
            if (leadingEmptyLines || trailingEmptyLines) {
                globalTransform.translate(0.0, -(yCursor+textHeight)/2.0);
            }
            else {
                globalTransform.translate(0.0, -(bottomLine + topLine) / 2.0);
            }
            break;
        case RS::VAlignBottom:
        case RS::VAlignBase:
            if (trailingEmptyLines) {
                globalTransform.translate(0.0, -yCursor);
            }
            else {
                globalTransform.translate(0.0, -bottomLine);
            }
            break;
        }

        height = boundingBox.getHeight();

        //qDebug() << "painterPaths: " << painterPaths.length();
        //qDebug() << "textLayouts: " << textLayouts.length();

        // apply global transform for position, angle and vertical alignment
        // to painter paths:
        boundingBox = RBox();
        for (int i=0; i<painterPaths.length(); ++i) {
            painterPaths[i].transform(globalTransform);
            RBox bb = painterPaths[i].getBoundingBox();
            if (bb.isSane() && !bb.getSize().isZero()) {
                boundingBox.growToInclude(bb);
            }
        }

        // apply global transform for position, angle and vertical alignment
        // to layouts:
        int k=0;
        //qDebug() << "text layout bbs...";
        for (int i=0; i<textLayouts.length(); ++i) {
            textLayouts[i].transform *= globalTransform;

            //qDebug() << "tl for: " << textLayouts[i].getText();

            // compute bounding box of layout based on corresponding painter paths:
            textLayouts[i].boundingBox = RBox();
            if (textLayouts[i].correspondingPainterPaths==0) {
//                qDebug() << "no corr pps";
//                qDebug() << "layout empty:" << textLayouts[i].isEmpty();
//                qDebug() << "txt:" << textLayouts[i].getText();

                //if (textLayouts[i].getText()!=" ") {
                //if (textLayouts[i].getLayout().isNull() && textLayouts[i].getText()!=" ") {
                if (!textLayouts[i].isTTF()) {
                    // CAD font text block with only one painter path:
                    if (k<painterPaths.length()) {
                        RBox bb = painterPaths[k].getBoundingBox();
                        if (bb.isSane() && !bb.getSize().isZero()) {
                            textLayouts[i].boundingBox.growToInclude(bb);
                        }
                    }
                    k++;
                }
            }
            else {
                // TTF:
                //qDebug() << "tl has " << textLayouts[i].correspondingPainterPaths << " pps";
                for (int n=0; n<textLayouts[i].correspondingPainterPaths; n++) {
                    if (k<painterPaths.length()) {
                        RBox bb = painterPaths[k].getBoundingBox();
                        if (bb.isSane() && !bb.getSize().isZero()) {
                            textLayouts[i].boundingBox.growToInclude(bb);
                        }
                        k++;
                    }
                }
            }

            //qDebug() << "tl bb: " << textLayouts[i].boundingBox;
        }
    }

    if (target==RichText) {
        // close all tags that were opened:
        if (!openTags.isEmpty()) {
            for (int i=openTags.top().size()-1; i>=0; --i) {
                QString tag = openTags.top().at(i);
                richText += QString("</%1>").arg(tag);
            }
        }
    }
}

QList<RPainterPath> RTextRenderer::getPainterPathsForBlock(
    const QString& blockText,
    const QList<QTextLayout::FormatRange>& formats,
    double& horizontalAdvance,
    double& horizontalAdvanceNoSpacing,
    double& horizontalAdvanceNoTrailingSpace,
    double& ascent,
    double& descent,
    double& usedHeight) {

    if (getUseCadFont()) {
        return getPainterPathsForBlockCad(
                    blockText,
                    formats,
                    horizontalAdvance,
                    horizontalAdvanceNoSpacing,
                    horizontalAdvanceNoTrailingSpace,
                    ascent, descent,
                    usedHeight);
    }
    else {
        return getPainterPathsForBlockTtf(
                    blockText,
                    formats,
                    horizontalAdvance,
                    horizontalAdvanceNoSpacing,
                    horizontalAdvanceNoTrailingSpace,
                    ascent, descent,
                    usedHeight);
    }
}

/**
 * \return Painter paths for the given text block in TTF font,
 *      positioned at 0/0 (bottom left corner) and with a font size of
 *      1 drawing unit.
 */
QList<RPainterPath> RTextRenderer::getPainterPathsForBlockTtf(
    const QString& blockText,
    const QList<QTextLayout::FormatRange>& formats,
    double& horizontalAdvance,
    double& horizontalAdvanceNoSpacing,
    double& horizontalAdvanceNoTrailingSpace,
    double& ascent,
    double& descent,
    double& usedHeight) {

    Q_UNUSED(horizontalAdvanceNoSpacing)

//    qDebug() << "formats: ";
//    for (int i=0; i<formats.length(); i++) {
//        qDebug() << "\tfont: " << formats[i].format.font();
//        qDebug() << "\tpt: " << formats[i].format.fontPointSize();
//        qDebug() << "\ttip: " << formats[i].format.toolTip();
//        qDebug() << "\tstart: " << formats[i].start;
//        qDebug() << "\tlength: " << formats[i].length;
//        qDebug() << "";
//    }

    // leading spaces:
    double leadingSpace = 0.0;

    // spaces are sometimes dropped in Qt 4.8.x (use Qt 4.7.4 instead for now)
//    if (!formats.isEmpty() && blockText.startsWith(' ') && !blockText.trimmed().isEmpty()) {
//        qDebug() << "got leading spaces";
//        QRegExp ex("^[ ]*");
//        if (ex.indexIn(blockText)==0) {
//            double dummy;
//            getPainterPathsForBlockTtf(
//                blockText.left(ex.matchedLength()),
//                formats,
//                leadingSpace,
//                dummy, dummy, dummy);
//            qDebug() << "leading space is: " << leadingSpace;
//        }
//    }

    QString subFont = RFontList::getSubName(getBlockFont());
    QFont font(subFont);
    // drawing with a 1pt font will freak out Windows:
    font.setPointSizeF(100.0);
    font.setBold(getBlockBold());
    font.setItalic(getBlockItalic());
    font.setUnderline(getBlockUnderline());

    // bounding boxes for 1.0 height font:
    QRectF boxA = getCharacterRect(font, 'A');
    QRectF boxG = getCharacterRect(font, 'g');

    double heightA = boxA.height() * 100.0;

    // scale to scale from 100.0pt font to a font size where an 'A' is
    // exactly 1 unit tall:
    double ttfScale = 1.0 / heightA;
    descent = (boxA.bottom()*100 - boxG.bottom()*100) * ttfScale;
    QFontMetricsF fm(font);
    ascent = fm.ascent() * ttfScale;
    double topSpacing = boxA.y() * 100.0;

    QTransform t;
    // scale to make an A 1.0 height:
    t.scale(ttfScale, -ttfScale);
    // move to align top of A with top line:
    t.translate(leadingSpace/ttfScale, -topSpacing-heightA);
    lineBlockTransforms.append(t);

    // empty text, e.g. line feed only:
    if (blockText=="") {
        horizontalAdvance = 0.0;
        textLayouts.append(RTextLayout());
        return QList<RPainterPath>() << RPainterPath();
    }

    // render text into painter paths using a QTextLayout:
    QTextLayout* layout = new QTextLayout();
    layout->setCacheEnabled(true);

    layout->setFont(font);
    layout->setText(blockText);
#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    layout->setFormats(formats.toVector());
#else
    layout->setAdditionalFormats(formats);
#endif

    layout->beginLayout();
    QTextLine line = layout->createLine();
    if (!line.isValid()) {
        horizontalAdvance = 0.0;
        RTextLayout tl;
        //tl.correspondingPainterPaths = 1;
        textLayouts.append(tl);
        qWarning("RTextRenderer::getPainterPathsForBlock: got not a single line");
        return QList<RPainterPath>() << RPainterPath();
    }
    layout->endLayout();
    horizontalAdvance = line.horizontalAdvance() * ttfScale;

    // same block without trailing spaces:
//    QString blockTextNoTrailingSpace = blockText;
//    blockTextNoTrailingSpace.replace(QRegExp("[ ]+$"), "");
//    if (blockTextNoTrailingSpace!=blockText) {
//        QTextLayout l;
//        l.setCacheEnabled(true);
//        l.setFont(font);
//        l.setText(blockText);
//#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0))
//        l.setFormats(formats.toVector());
//#else
//        l.setAdditionalFormats(formats);
//#endif
//        l.setText(blockTextNoTrailingSpace);
//        l.beginLayout();
//        line = l.createLine();
//        l.endLayout();
//        horizontalAdvanceNoTrailingSpace = line.horizontalAdvance() * ttfScale;
//    }
//    else {
//        horizontalAdvanceNoTrailingSpace = horizontalAdvance;
//    }

    horizontalAdvanceNoTrailingSpace = horizontalAdvance;

    //qDebug() << "horizontalAdvance:" << horizontalAdvance;
    //qDebug() << "horizontalAdvanceNoTrailingSpace:" << horizontalAdvanceNoTrailingSpace;

    RPainterPathDevice ppd;
    QPainter ppPainter(&ppd);
    {
        RTextRenderer::lockForDrawing();
        layout->draw(&ppPainter, QPoint(0,0));
        RTextRenderer::unlockForDrawing();
    }
    ppPainter.end();

    QColor currentColor = Qt::white;
    if (!currentFormat.isEmpty()) {
        currentColor = currentFormat.top().foreground().color();
    }

    // transform to exactly 1.0 height for an 'A',
    // reference point is bottom left (to make sure that texts of different
    // heights are aligned at the bottom, not top):
    RTextLayout tl(QSharedPointer<QTextLayout>(layout), QTransform(), currentColor);
    tl.height = getBlockHeight();
    //tl.position = RVector(horizontalAdvance, ascent);
    //getBlockFont();
    //getBlockBold();
    //getBlockItalic();

//    qDebug() << "text:" << blockText;
//    qDebug() << "bounding box for an A:" << boxA;
//    qDebug() << "x cursor" << xCursor;
//    qDebug() << "transform: " << t;

//    qDebug() << "x:" << horizontalAdvance;
//    qDebug() << "y:" << ascent;

    QList<RPainterPath> ret;
    QList<RPainterPath> paths = ppd.getPainterPaths();
    for (int i=0; i<paths.size(); ++i) {
        RPainterPath p = paths.at(i);
        p.transform(t);
        ret.append(p);
    }

    tl.correspondingPainterPaths = paths.size();
    textLayouts.append(tl);

    if (!ret.isEmpty()) {
        usedHeight = qMax(usedHeight, getBlockHeight());
    }

    return ret;
}

/**
 * \return Painter paths for the given text block in CAD font,
 *      positioned at 0/0 (bottom left corner) and with a font size of
 *      1 drawing unit.
 */
QList<RPainterPath> RTextRenderer::getPainterPathsForBlockCad(
    const QString& blockText,
    const QList<QTextLayout::FormatRange>& formats,
    double& horizontalAdvance,
    double& horizontalAdvanceNoSpacing,
    double& horizontalAdvanceNoTrailingSpace,
    double& ascent,
    double& descent,
    double& usedHeight) {

    QList<RPainterPath> ret;

    RFont* font = RFontList::get(getBlockFont());
    if (font==NULL || !font->isValid()) {
        if (blockFont.isEmpty()) {
            qWarning() << "RTextRenderer::getPainterPathsForBlockCad: "
                   << "invalid font: stack empty - using 'standard' instead...";
        }

        // 20120309: resort to standard font (better than nothing):
        // 20191009: no substitution
        font = RFontList::get("Standard", false);
        if (font==NULL) {
            qWarning() << "standard font not found";
            // make sure layout and transforms are always added:
            lineBlockTransforms.append(QTransform());
            RTextLayout tl;
            //tl.correspondingPainterPaths = 1;
            textLayouts.append(tl);
            return QList<RPainterPath>() << RPainterPath();
        }
    }

    double cursor = 0.0;
    // cxf fonts define glyphs at a scale of 9:1:
    double cxfScale = 1.0/9.0;
    // invalid color, default, means use color of entity:
    QColor currentColor = currentFormat.top().foreground().color();
    bool gotLetterSpacing = false;
    QMap<int, double> indexToCursorStart;
    QMap<int, double> indexToCursorEnd;
    QList<int> underlinedIndices;

    RPainterPath ppBlock;
    preparePathColor(ppBlock, currentColor);

    for (int i=0; i<blockText.length(); ++i) {
        QChar ch = blockText.at(i);

        //if (i==0) {
            indexToCursorStart.insert(i, cursor);
        //}

        bool isSpace = false;
        if (ch==' ' || ch==QChar(Qt::Key_nobreakspace)) {
            if (gotLetterSpacing) {
                cursor -= font->getLetterSpacing() * cxfScale;
            }
            cursor += font->getWordSpacing() * cxfScale;
            indexToCursorEnd.insert(i, cursor);
            gotLetterSpacing = false;
            isSpace = true;
        }

        // handle color and other format changes within the same block:
        for (int fi=0; fi<formats.size(); ++fi) {
            QTextLayout::FormatRange format = formats.at(fi);

            if (format.start==i && format.start+format.length>i) {
                QColor color = format.format.foreground().color();
                if (currentColor!=color) {
                    currentColor = color;
                    // forced break in underline due to color change:
                    underlinedIndices.append(-1);
                }
            }

            if (format.start<=i && format.start+format.length>i) {
                if (format.format.underlineStyle()==QTextCharFormat::SingleUnderline) {
                    underlinedIndices.append(i);
                }
            }
        }

        if (isSpace) {
            continue;
        }

        RPainterPath glyph = font->getGlyph(ch, draft);
        // glyph not available in font (show as question mark):
        if (glyph.elementCount()==0) {
            glyph = font->getGlyph('?', draft);
        }
        // if question mark is not available, show nothing:
        if (glyph.elementCount()>0) {
            RPainterPath path(glyph);
            preparePathTransform(path, cursor, cxfScale);
            ppBlock.addPath(path);

            // letter spacing:
            cursor += path.boundingRect().width();
            indexToCursorEnd.insert(i, cursor);
            cursor += font->getLetterSpacing() * cxfScale;
            gotLetterSpacing = true;
        }
    }

    //qDebug() << "indexToCursor: " << indexToCursorStart;

    // whole block is underlined:
    if (getBlockUnderline()) {
        underlinedIndices.clear();
        for (int i=0; i<blockText.length(); i++) {
            underlinedIndices.append(i);
        }
    }

    if (!underlinedIndices.isEmpty()) {
        underlinedIndices.append(-1);
    }

    //qDebug() << "underlines: " << underlinedIndices;

    RLine line;
    int lastIndex = -1;
    for (int i=0; i<underlinedIndices.length(); i++) {
        int idx = underlinedIndices[i];

        bool prevUnderlined = lastIndex!=-1 && lastIndex==idx-1;
        lastIndex = idx;

        if (!prevUnderlined) {
            if (line.isValid()) {
                //qDebug() << "underline: " << line;
                RPainterPath path;
                path.moveTo(line.getStartPoint());
                path.lineTo(line.getEndPoint());
                path.addOriginalShape(line.clone());
                preparePathTransform(path, 0.0, 1.0);
                ppBlock.addPath(path);
                line = RLine();
            }
            if (idx!=-1) {
                line.setStartPoint(RVector(indexToCursorStart[idx], -0.1));
                line.setEndPoint(RVector(indexToCursorEnd[idx], -0.1));
                //prevUnderlined = true;
            }
        }
        else {
            if (idx!=-1) {
                line.setEndPoint(RVector(indexToCursorEnd[idx], -0.1));
            }
        }
        //qDebug() << "line: " << line;
        //qDebug() << "cxfScale: " << cxfScale;
    }

    ret.append(ppBlock);

    horizontalAdvance = cursor;
    horizontalAdvanceNoSpacing = cursor - font->getLetterSpacing() * cxfScale;
    horizontalAdvanceNoTrailingSpace = horizontalAdvanceNoSpacing;
    ascent = 1.08;
    descent = -0.36;

    if (blockText==" ") {
        horizontalAdvance = horizontalAdvanceNoTrailingSpace;
    }

    // add text layout with paths to indicate we have to use painter paths for this text block:
    lineBlockTransforms.append(QTransform());
    RTextLayout tl(ret, currentColor);
    QFont font1 = getBlockFont();
    font1.setUnderline(getBlockUnderline());
    tl.layout = QSharedPointer<QTextLayout>(new QTextLayout(blockText, font1));
    tl.height = getBlockHeight();
    textLayouts.append(tl);

    if (!ret.isEmpty()) {
        usedHeight = qMax(usedHeight, getBlockHeight());
    }

//    qDebug() << "horizontalAdvance:" << horizontalAdvance;

    return ret;
}

void RTextRenderer::preparePath(RPainterPath& path, const RColor& color, double cursor, double cxfScale) {
    preparePathColor(path, color);
    preparePathTransform(path, cursor, cxfScale);
}

void RTextRenderer::preparePathColor(RPainterPath& path, const RColor& color) {
    QPen pen = path.getPen();
    pen.setStyle(Qt::SolidLine);
    pen.setColor(color);
    path.setPen(pen);
    // invalid color means color from entity, otherwise fixed color:
    if (color.isValid()) {
        if (color!=RColor::CompatByLayer && color!=RColor::CompatByBlock) {
            // fixed color:
            path.setFixedPenColor(true);
        }
    }
}

void RTextRenderer::preparePathTransform(RPainterPath& path, double cursor, double cxfScale) {
    QTransform transform;
    transform.translate(cursor, 0);
    transform.scale(cxfScale, cxfScale);
    path.transform(transform);
}

/**
 * \return Bounding box of the given character with the given font in
 *      size '1', rendered at 0/0. Used to find out the CAD relevant height,
 *      ascent and descent of the font.
 */
QRectF RTextRenderer::getCharacterRect(const QString& fontName, const QChar& ch) const {
    return getCharacterRect(QFont(fontName), ch);
}

/**
 * \overload
 */
QRectF RTextRenderer::getCharacterRect(const QFont& font, const QChar& ch) const {
    QFont font1(font);
    font1.setPointSizeF(100.0);
    font1.setUnderline(false);

    QTextLayout layout;
    layout.setFont(font1);
    layout.setText(QString(ch));

    layout.beginLayout();
    layout.createLine();
    layout.endLayout();

    RPainterPathDevice ppd;
    QPainter ppPainter(&ppd);
    {
        RTextRenderer::lockForDrawing();
        layout.draw(&ppPainter, QPoint(0,0));
        RTextRenderer::unlockForDrawing();
    }
    ppPainter.end();

    QPainterPath p;
    QList<RPainterPath> paths = ppd.getPainterPaths();
    for (int i=0; i<paths.size(); i++) {
        p.addPath(paths.at(i));
    }

    QRectF rect = p.boundingRect();
    return QRectF(rect.left()/100.0, rect.top()/100.0, rect.width()/100.0, rect.height()/100.0);
}

QString RTextRenderer::getRichTextForBlock(
                            const QString& blockText,
                            const QList<QTextLayout::FormatRange>& formats) {

    Q_UNUSED(formats)

    return RS::escape(blockText).replace(' ', "&nbsp;");
    //return blockText;
}
