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
#include <QtGui>
#include <QToolTip>

#include "RCharacterWidget.h"

RCharacterWidget::RCharacterWidget(QWidget *parent) :
    QWidget(parent) {
    squareSize = 24;
    columns = 16;
    lastKey = -1;
    setMouseTracking(true);
}

QFont RCharacterWidget::getDisplayFont() {
    return displayFont;
}

void RCharacterWidget::updateFont(const QFont &font) {
    displayFont.setFamily(font.family());
    squareSize = qMax(24, QFontMetrics(displayFont).xHeight() * 3);
    adjustSize();
    update();
}

void RCharacterWidget::updateSize(const QString &fontSize) {
    displayFont.setPointSize(fontSize.toInt());
    squareSize = qMax(24, QFontMetrics(displayFont).xHeight() * 3);
    adjustSize();
    update();
}

void RCharacterWidget::updateStyle(const QString &fontStyle) {
    QFontDatabase fontDatabase;
    const QFont::StyleStrategy oldStrategy = displayFont.styleStrategy();
    displayFont = fontDatabase.font(displayFont.family(), fontStyle,
            displayFont.pointSize());
    displayFont.setStyleStrategy(oldStrategy);
    squareSize = qMax(24, QFontMetrics(displayFont).xHeight() * 3);
    adjustSize();
    update();
}

void RCharacterWidget::updateFontMerging(bool enable) {
    if (enable)
        displayFont.setStyleStrategy(QFont::PreferDefault);
    else
        displayFont.setStyleStrategy(QFont::NoFontMerging);
    adjustSize();
    update();
}

QSize RCharacterWidget::sizeHint() const {
    return QSize(columns * squareSize, (65536 / columns) * squareSize);
}

void RCharacterWidget::mouseMoveEvent(QMouseEvent *event) {
    QPoint widgetPosition = mapFromGlobal(event->globalPos());
    uint key = (widgetPosition.y() / squareSize) * columns + widgetPosition.x()
            / squareSize;

    QString text = QString::fromLatin1(
        "<p>Character: <span style=\"font-size: 24pt; font-family: %1\">").arg(
        displayFont.family()) + QChar(key)
        + QString::fromLatin1("</span><p>Value: 0x")
        + QString::number(key, 16);
    QToolTip::showText(event->globalPos(), text, this);
}

void RCharacterWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastKey = (event->y() / squareSize) * columns + event->x() / squareSize;
#if QT_VERSION < 0x050000
        if (QChar(lastKey).category() != QChar::NoCategory)
#endif
            emit characterSelected(QString(QChar(lastKey)));
        update();
    } else
        QWidget::mousePressEvent(event);
}

void RCharacterWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), QBrush(Qt::white));
    painter.setFont(displayFont);

    QRect redrawRect = event->rect();
    int beginRow = redrawRect.top() / squareSize;
    int endRow = redrawRect.bottom() / squareSize;
    int beginColumn = redrawRect.left() / squareSize;
    int endColumn = redrawRect.right() / squareSize;

    painter.setPen(QPen(Qt::gray));
    for (int row = beginRow; row <= endRow; ++row) {
        for (int column = beginColumn; column <= endColumn; ++column) {
            painter.drawRect(column * squareSize, row * squareSize, squareSize,
                    squareSize);
        }
    }

    QFontMetrics fontMetrics(displayFont);
    painter.setPen(QPen(Qt::black));
    for (int row = beginRow; row <= endRow; ++row) {

        for (int column = beginColumn; column <= endColumn; ++column) {

            int key = row * columns + column;
            painter.setClipRect(column * squareSize, row * squareSize,
                    squareSize, squareSize);

            if (key == lastKey)
                painter.fillRect(column * squareSize + 1, row * squareSize + 1,
                        squareSize, squareSize, QBrush(Qt::red));

            painter.drawText(column * squareSize + (squareSize / 2)
                    - fontMetrics.width(QChar(key)) / 2, row * squareSize + 4
                    + fontMetrics.ascent(), QString(QChar(key)));
        }
    }
}
