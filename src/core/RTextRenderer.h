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

#ifndef RTEXTRENDERER_H
#define RTEXTRENDERER_H

#include "core_global.h"

#include <QTextLayout>
#include <QMutex>

#include "RDocument.h"
#include "REntityData.h"
#include "RPainterPath.h"
#include "RPainterPathSource.h"
#include "RTextBasedData.h"
#include "RTextLayout.h"
#include "RVector.h"

//class QTextDocument;

/**
 * Renders formatted text into painter paths.
 *
 * \scriptable
 * \ingroup entity
 */
class QCADCORE_EXPORT RTextRenderer {
public:
    enum Target {
        PainterPaths = 0x01,
        RichText = 0x02
        // TODO: TextLayout = 0x03
    };

public:
    RTextRenderer(const RTextBasedData& textData, bool draft, RTextRenderer::Target target, double fontHeightFactor = 1.0);

    void renderSimple();
    void render();

    QList<RPainterPath> getPainterPaths() const {
        return painterPaths;
    }

    QList<RTextLayout> getTextLayouts() const {
        return textLayouts;
    }

//    QList<QTransform> getTextTransforms() const {
//        return textTransforms;
//    }

    RBox getBoundingBox() const {
        return boundingBox;
    }

    double getHeight() const {
        return height;
    }

    double getWidth() const {
        return width;
    }

    QString getRichText() const {
        return richText;
    }

    static void lockForDrawing() {
        m.lock();
    }

    static void unlockForDrawing() {
        m.unlock();
    }

private:
    QList<RPainterPath> getPainterPathsForBlock(
        const QString& blockText,
        const QList<QTextLayout::FormatRange>& formats,
        double& horizontalAdvance,
        double& horizontalAdvanceNoSpacing,
        double& ascent,
        double& descent,
        double& usedHeight);

    QList<RPainterPath> getPainterPathsForBlockTtf(
        const QString& blockText,
        const QList<QTextLayout::FormatRange>& formats,
        double& horizontalAdvance,
        double& horizontalAdvanceNoSpacing,
        double& ascent,
        double& descent,
        double& usedHeight);

    QList<RPainterPath> getPainterPathsForBlockCad(
        const QString& blockText,
        const QList<QTextLayout::FormatRange>& formats,
        double& horizontalAdvance,
        double& horizontalAdvanceNoSpacing,
        double& ascent,
        double& descent,
        double& usedHeight);

    void preparePath(RPainterPath& path,
        const RColor& color,
        double cursor,
        double cxfScale);

    void preparePathColor(RPainterPath& path, const RColor& color);
    void preparePathTransform(RPainterPath& path, double cursor, double cxfScale);

    QRectF getCharacterRect(const QString& fontName, const QChar& ch) const;
    QRectF getCharacterRect(const QFont& font, const QChar& ch) const;

    QString getRichTextForBlock(const QString& blockText,
                                const QList<QTextLayout::FormatRange>& formats);

    void setBlockFont(const QString& f) {
        if (!blockFont.isEmpty()) {
            blockFont.top() = f;
        }
    }

    QString getBlockFont() const {
        if (!blockFont.isEmpty()) {
            return blockFont.top();
        }
        return "";
    }

    void setBlockFontFile(const QString& f) {
        if (!blockFontFile.isEmpty()) {
            blockFontFile.top() = f;
        }
    }

    QString getBlockFontFile() const {
        if (!blockFontFile.isEmpty()) {
            return blockFontFile.top();
        }
        return "";
    }

    void setUseCadFont(bool on) {
        if (!useCadFont.isEmpty()) {
            useCadFont.top() = on;
        }
    }

    bool getUseCadFont() const {
        if (!useCadFont.isEmpty()) {
            return useCadFont.top();
        }
        return false;
    }

    void setBlockBold(bool on) {
        if (!blockBold.isEmpty()) {
            blockBold.top() = on;
        }
    }

    bool getBlockBold() const {
        if (!blockBold.isEmpty()) {
            return blockBold.top();
        }
        return false;
    }

    void setBlockItalic(bool on) {
        if (!blockItalic.isEmpty()) {
            blockItalic.top() = on;
        }
    }

    bool getBlockItalic() const {
        if (!blockItalic.isEmpty()) {
            return blockItalic.top();
        }
        return false;
    }

    void setBlockUnderline(bool on) {
        if (!blockUnderline.isEmpty()) {
            blockUnderline.top() = on;
        }
    }

    bool getBlockUnderline() const {
        if (!blockUnderline.isEmpty()) {
            return blockUnderline.top();
        }
        return false;
    }

    void setBlockHeight(double h) {
        if (!blockHeight.isEmpty()) {
            blockHeight.top() = h;
        }
    }

    double getBlockHeight() const {
        if (!blockHeight.isEmpty()) {
            return blockHeight.top();
        }
        return 1.0;
    }

    void setCurrentFormat(QTextCharFormat f) {
        if (!currentFormat.isEmpty()) {
            currentFormat.top() = f;
        }
    }

    QTextCharFormat getCurrentFormat() const {
        if (!currentFormat.isEmpty()) {
            return currentFormat.top();
        }
        return QTextCharFormat();
    }

public:
    static QString rxLineFeedStr;
    static QRegExp rxLineFeed;
    static QString rxAlignmentLeftStr;
    static QRegExp rxAlignmentLeft;
    static QString rxAlignmentCenterStr;
    static QRegExp rxAlignmentCenter;
    static QString rxAlignmentRightStr;
    static QRegExp rxAlignmentRight;
    static QString rxXAlignmentLeftStr;
    static QRegExp rxXAlignmentLeft;
    static QString rxXAlignmentCenterStr;
    static QRegExp rxXAlignmentCenter;
    static QString rxXAlignmentRightStr;
    static QRegExp rxXAlignmentRight;
    static QString rxXSpaceMTextStr;
    static QRegExp rxXSpaceMText;
    static QString rxTabMMStr;
    static QRegExp rxTabMM;
    static QString rxTabINStr;
    static QRegExp rxTabIN;
    static QString rxParagraphFeedStr;
    static QRegExp rxParagraphFeed;
    static QString rxXFeedStr;
    static QRegExp rxXFeed;
    static QString rxHeightChangeStr;
    static QRegExp rxHeightChange;
    static QString rxUnderlineChangeStr;
    static QRegExp rxUnderlineChange;
    //static QString rxRelativeHeightChange;
    static QString rxStackedTextStr;
    static QRegExp rxStackedText;
    static QString rxColorChangeIndexStr;
    static QRegExp rxColorChangeIndex;
    static QString rxColorChangeCustomStr;
    static QRegExp rxColorChangeCustom;
    static QString rxNonBreakingSpaceStr;
    static QRegExp rxNonBreakingSpace;
    static QString rxOverlineOnStr;
    static QRegExp rxOverlineOn;
    static QString rxOverlineOffStr;
    static QRegExp rxOverlineOff;
    static QString rxUnderlineOnStr;
    static QRegExp rxUnderlineOn;
    static QString rxUnderlineOffStr;
    static QRegExp rxUnderlineOff;
    static QString rxStrikethroughOnStr;
    static QRegExp rxStrikethroughOn;
    static QString rxStrikethroughOffStr;
    static QRegExp rxStrikethroughOff;
    static QString rxWidthChangeStr;
    static QRegExp rxWidthChange;
    static QString rxObliqueAngleChangeStr;
    static QRegExp rxObliqueAngleChange;
    static QString rxTrackChangeStr;
    static QRegExp rxTrackChange;
    static QString rxAlignmentChangeStr;
    static QRegExp rxAlignmentChange;
    static QString rxFontChangeCadStr;
    static QRegExp rxFontChangeCad;
    static QString rxFontChangeTtfStr;
    static QRegExp rxFontChangeTtf;
    static QString rxBeginBlockStr;
    static QRegExp rxBeginBlock;
    static QString rxEndBlockStr;
    static QRegExp rxEndBlock;
    static QString rxBackslashStr;
    static QRegExp rxBackslash;
    static QString rxCurlyOpenStr;
    static QRegExp rxCurlyOpen;
    static QString rxCurlyCloseStr;
    static QRegExp rxCurlyClose;
    static QString rxDegreeStr;
    static QRegExp rxDegree;
    static QString escDegreeStr;
    static QRegExp escDegree;
    static QString rxPlusMinusStr;
    static QRegExp rxPlusMinus;
    static QString escPlusMinusStr;
    static QRegExp escPlusMinus;
    static QString rxDiameterStr;
    static QRegExp rxDiameter;
    static QString escDiameterStr;
    static QRegExp escDiameter;
    static QString rxUnderlineStr;
    static QRegExp rxUnderline;
    static QString escUnderlineStr;
    static QRegExp escUnderline;
    static QString rxNoOpStr;
    static QRegExp rxNoOp;
    static QString rxNoOpEndStr;
    static QRegExp rxNoOpEnd;
    static QString escNoOpStr;
    static QRegExp escNoOp;
    static QString rxUnicodeStr;
    static QRegExp rxUnicode;

    static QString rxAllStr;
    static QRegExp rxAll;

    static QChar chDegree;
    static QChar chPlusMinus;
    static QChar chDiameter;

private:
    static QMutex m;

    const RTextBasedData& textData;

    Target target;

    // painter paths used to draw text geometry as painter path:
    QList<RPainterPath> painterPaths;

    // text layouts and transformations used to draw text as QTextLayout instead of painter paths:
    QList<RTextLayout> textLayouts;
    // list of block transforms of all QTextLayout blocks of the current line:
    QList<QTransform> lineBlockTransforms;

    RBox boundingBox;
    double height;
    double width;
    bool draft;
    QString richText;
    double fontHeightFactor;

    QStack<bool> useCadFont;
    QStack<QTextCharFormat> currentFormat;
    QStack<double> blockHeight;
    QStack<QString> blockFont;
    QStack<QString> blockFontFile;
    QStack<bool> blockBold;
    QStack<bool> blockItalic;
    QStack<bool> blockUnderline;
    QStack<QStringList> openTags;
};


Q_DECLARE_METATYPE(RTextRenderer*)
Q_DECLARE_METATYPE(RTextRenderer::Target)
Q_DECLARE_METATYPE(RTextRenderer::Target*)

#endif
