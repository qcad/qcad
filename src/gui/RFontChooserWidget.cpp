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
#include <QColorDialog>
#include <QColor>
#include <QMapIterator>
#include <QCoreApplication>
#include <QHBoxLayout>
#include <QFontComboBox>
#include <QComboBox>
#include <QLabel>
#include <QDebug>

#include "RDebug.h"
#include "RFontChooserWidget.h"

// TODO non-TTF fonts fails to save / load
// TODO test case for saving / loading fonts with RSettings

RFontChooserWidget::RFontChooserWidget(QWidget *parent) :
    QWidget(parent), font(QFont()), cbSize(NULL), cbFont(NULL), lbSampleText(
            NULL) {

    QGridLayout* layout = new QGridLayout;
    layout->setMargin(0);

    lbLabel = new QLabel("");
    layout->addWidget(lbLabel, 0,0);

    cbFont = new QFontComboBox();
    cbFont->setObjectName("FontFamily");
    cbFont->setFontFilters(QFontComboBox::ScalableFonts);
//  cbFont->setFontFilters(QFontComboBox::ProportionalFonts);
//  cbFont->setFontFilters(QFontComboBox::NonScalableFonts);

    connect(cbFont, SIGNAL(currentFontChanged(const QFont&)), this,
            SLOT(fontChanged(const QFont &)));
    layout->addWidget(cbFont, 0, 1);

    cbSize = new QComboBox();
    cbSize->setObjectName("FontSize");
    connect(cbSize, SIGNAL(activated(int)), this,
            SLOT(sizeChanged(int)));
    layout->addWidget(cbSize, 0, 2);

    lbSampleText = new QLabel("The quick brown fox jumps over the lazy dog");
    lbSampleText->setMinimumWidth(0);
    layout->addWidget(lbSampleText, 1, 0, 1, 3);

    QLabel* lbSpace = new QLabel();
    lbSpace->setBaseSize(8, 8);
    layout->addWidget(lbSpace, 2, 0, 1, 3);

    setLayout(layout);
}

void RFontChooserWidget::updateSizeCombo() {
    if (cbSize == NULL) {
        return;
    }

    cbSize->clear();
    QFontDatabase fontDb;
//    qDebug() << "font: " << font.family();
//    qDebug() << "font sizes: " << fontDb.pointSizes(font.family());
    QListIterator<int> i(fontDb.pointSizes(font.family()));
    while (i.hasNext()) {
        int s = i.next();
        cbSize->addItem(QString("%1").arg(s), s);
    }
    int s = font.pointSize();
    if (cbSize->findData(s)==-1) {
        cbSize->addItem(QString("%1").arg(s), s);
    }
    cbSize->setCurrentIndex(cbSize->findData(s));
}

void RFontChooserWidget::fontChanged(const QFont& font) {
    QFont f = font;
    int currentIndex = cbSize->currentIndex();
    if (currentIndex!=-1) {
        f.setPointSize(cbSize->itemData(currentIndex).toInt());
    }
    setFont(f);
    emit valueChanged(this->font);
}

QFont RFontChooserWidget::getFont() const {
    return font;
}

void RFontChooserWidget::setFont(const QFont &font) {
    this->font = font;
    cbFont->blockSignals(true);
    cbFont->setCurrentFont(font);
    cbFont->blockSignals(false);
    updateSizeCombo();
    lbSampleText->setFont(font);
}

QString RFontChooserWidget::getLabel() const {
    return lbLabel->text();
}

void RFontChooserWidget::setLabel(const QString& l) {
    lbLabel->setText(l);
}

void RFontChooserWidget::sizeChanged(int index) {
    if (cbFont == NULL || cbSize == NULL || index < 0) {
        return;
    }
    if (!cbSize->itemData(index).isValid()) {
        qWarning() <<
                QString("RFontChooserWidget::sizeChanged: invalid item data at index %1")
                .arg(index);
        return;
    }

    int size = cbSize->itemData(index).toInt();
    setSize(size);
    emit valueChanged(this->font);
}

int RFontChooserWidget::getSize() const {
    return font.pointSize();
}

void RFontChooserWidget::setSize(int size) {
    if (size <= 0) {
        qWarning() <<
                QString("RFontChooserWidget::setSize: size <= 0 (size = %1)").arg(size);
        return;
    }
    this->font.setPointSize(size);
    lbSampleText->setFont(font);
}

void RFontChooserWidget::resizeEvent(QResizeEvent* event) {
    Q_UNUSED(event)

    lbSampleText->setMaximumWidth(width());
}
