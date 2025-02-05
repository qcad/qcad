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
#include <QStack>

#include "RPainterPath.h"
#include "RTextLayout.h"

class RColor;
class RTextBasedData;

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
        double& horizontalAdvanceNoTrailingSpace,
        double& ascent,
        double& descent,
        double& usedHeight);

    QList<RPainterPath> getPainterPathsForBlockTtf(
        const QString& blockText,
        const QList<QTextLayout::FormatRange>& formats,
        double& horizontalAdvance,
        double& horizontalAdvanceNoSpacing,
        double& horizontalAdvanceNoTrailingSpace,
        double& ascent,
        double& descent,
        double& usedHeight);

    QList<RPainterPath> getPainterPathsForBlockCad(
        const QString& blockText,
        const QList<QTextLayout::FormatRange>& formats,
        double& horizontalAdvance,
        double& horizontalAdvanceNoSpacing,
        double& horizontalAdvanceNoTrailingSpace,
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
    static QRegularExpression rxLineFeed;
    static QString rxAlignmentLeftStr;
    static QRegularExpression rxAlignmentLeft;
    static QString rxAlignmentCenterStr;
    static QRegularExpression rxAlignmentCenter;
    static QString rxAlignmentRightStr;
    static QRegularExpression rxAlignmentRight;
    static QString rxXAlignmentLeftStr;
    static QRegularExpression rxXAlignmentLeft;
    static QString rxXAlignmentCenterStr;
    static QRegularExpression rxXAlignmentCenter;
    static QString rxXAlignmentRightStr;
    static QRegularExpression rxXAlignmentRight;
    static QString rxXSpaceMTextStr;
    static QRegularExpression rxXSpaceMText;
    static QString rxTabMMStr;
    static QRegularExpression rxTabMM;
    static QString rxTabINStr;
    static QRegularExpression rxTabIN;
    static QString rxParagraphFeedStr;
    static QRegularExpression rxParagraphFeed;
    static QString rxXFeedStr;
    static QRegularExpression rxXFeed;
    static QString rxHeightChangeStr;
    static QRegularExpression rxHeightChange;
    static QString rxUnderlineChangeStr;
    static QRegularExpression rxUnderlineChange;
    //static QString rxRelativeHeightChange;
    static QString rxStackedTextStr;
    static QRegularExpression rxStackedText;
    static QString rxColorChangeIndexStr;
    static QRegularExpression rxColorChangeIndex;
    static QString rxColorChangeCustomStr;
    static QRegularExpression rxColorChangeCustom;
    static QString rxNonBreakingSpaceStr;
    static QRegularExpression rxNonBreakingSpace;
    static QString rxOverlineOnStr;
    static QRegularExpression rxOverlineOn;
    static QString rxOverlineOffStr;
    static QRegularExpression rxOverlineOff;
    static QString rxUnderlineOnStr;
    static QRegularExpression rxUnderlineOn;
    static QString rxUnderlineOffStr;
    static QRegularExpression rxUnderlineOff;
    static QString rxStrikethroughOnStr;
    static QRegularExpression rxStrikethroughOn;
    static QString rxStrikethroughOffStr;
    static QRegularExpression rxStrikethroughOff;
    static QString rxWidthChangeStr;
    static QRegularExpression rxWidthChange;
    static QString rxObliqueAngleChangeStr;
    static QRegularExpression rxObliqueAngleChange;
    static QString rxTrackChangeStr;
    static QRegularExpression rxTrackChange;
    static QString rxAlignmentChangeStr;
    static QRegularExpression rxAlignmentChange;
    static QString rxAlignmentChangeBlockStr;
    static QRegularExpression rxAlignmentChangeBlock;
    static QString rxFontChangeCadStr;
    static QRegularExpression rxFontChangeCad;
    static QString rxFontChangeTtfStr;
    static QRegularExpression rxFontChangeTtf;
    static QString rxBeginBlockStr;
    static QRegularExpression rxBeginBlock;
    static QString rxEndBlockStr;
    static QRegularExpression rxEndBlock;
    static QString rxBackslashStr;
    static QRegularExpression rxBackslash;
    static QString rxCurlyOpenStr;
    static QRegularExpression rxCurlyOpen;
    static QString rxCurlyCloseStr;
    static QRegularExpression rxCurlyClose;
    static QString rxDegreeStr;
    static QRegularExpression rxDegree;
    static QString escDegreeStr;
    static QRegularExpression escDegree;
    static QString rxPlusMinusStr;
    static QRegularExpression rxPlusMinus;
    static QString escPlusMinusStr;
    static QRegularExpression escPlusMinus;
    static QString rxDiameterStr;
    static QRegularExpression rxDiameter;
    static QString escDiameterStr;
    static QRegularExpression escDiameter;
    static QString rxUnderlineStr;
    static QRegularExpression rxUnderline;
    static QString escUnderlineStr;
    static QRegularExpression escUnderline;
    static QString rxNoOpStr;
    static QRegularExpression rxNoOp;
    static QString rxNoOpEndStr;
    static QRegularExpression rxNoOpEnd;
    static QString escNoOpStr;
    static QRegularExpression escNoOp;
    static QString rxUnicodeStr;
    static QRegularExpression rxUnicode;
    static QString rxOptionalBreakStr;
    static QRegularExpression rxOptionalBreak;

    static QString rxAllStr;
    static QString rxAllBreakStr;
    static QRegularExpression rxAll;
    static QRegularExpression rxAllBreak;

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
