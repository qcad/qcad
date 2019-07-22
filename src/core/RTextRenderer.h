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
    static QString rxLineFeed;
    static QString rxAlignmentLeft;
    static QString rxAlignmentCenter;
    static QString rxAlignmentRight;
    static QString rxXAlignmentLeft;
    static QString rxXAlignmentCenter;
    static QString rxXAlignmentRight;
    static QString rxXSpaceMText;
    static QString rxTabMM;
    static QString rxTabIN;
    static QString rxParagraphFeed;
    static QString rxXFeed;
    static QString rxHeightChange;
    static QString rxUnderlineChange;
    //static QString rxRelativeHeightChange;
    static QString rxStackedText;
    static QString rxColorChangeIndex;
    static QString rxColorChangeCustom;
    static QString rxNonBreakingSpace;
    static QString rxOverlineOn;
    static QString rxOverlineOff;
    static QString rxUnderlineOn;
    static QString rxUnderlineOff;
    static QString rxStrikethroughOn;
    static QString rxStrikethroughOff;
    static QString rxWidthChange;
    static QString rxObliqueAngleChange;
    static QString rxTrackChange;
    static QString rxAlignmentChange;
    static QString rxFontChangeCad;
    static QString rxFontChangeTtf;
    static QString rxBeginBlock;
    static QString rxEndBlock;
    static QString rxBackslash;
    static QString rxCurlyOpen;
    static QString rxCurlyClose;
    static QString rxDegree;
    static QString escDegree;
    static QString rxPlusMinus;
    static QString escPlusMinus;
    static QString rxDiameter;
    static QString escDiameter;
    static QString rxUnderline;
    static QString escUnderline;
    static QString rxNoOp;
    static QString rxNoOpEnd;
    static QString escNoOp;
    static QString rxUnicode;

    static QString rxAll;

    static QChar chDegree;
    static QChar chPlusMinus;
    static QChar chDiameter;

private:
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
