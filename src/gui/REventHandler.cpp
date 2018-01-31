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
#include <QLabel>
#include <QMimeData>
#include <QPainter>
#include <QScrollBar>
#include <QUrl>
#include <QWidget>

#include "REventHandler.h"
#include "RDocumentInterface.h"
#include "RGraphicsView.h"
#include "RRulerQt.h"
#include "RMainWindowQt.h"
#include "RSnapRestriction.h"
#include "RSnap.h"
#include "RUnit.h"

/**
 * Event handler for scroll, drag and drop, snap info.
 */
REventHandler::REventHandler(QWidget* widget, RDocumentInterface* di)
    : widget(widget),
    documentInterface(di),
    hsb(NULL),
    vsb(NULL),
    graphicsView(NULL),
    hruler(NULL),
    vruler(NULL) {

    if (widget!=NULL) {
        hsb = widget->findChild<QScrollBar*>("HorizontalScrollBar");
        vsb = widget->findChild<QScrollBar*>("VerticalScrollBar");
        QWidget* gv = widget->findChild<QWidget*>("GraphicsView");
        graphicsView = dynamic_cast<RGraphicsView*>(gv);
        hruler = widget->findChild<RRulerQt*>("HorizontalRuler");
        vruler = widget->findChild<RRulerQt*>("VerticalRuler");
    }
}

bool REventHandler::isUrl(const QString& urlString) {
    QUrl url(urlString);
    QString scheme = url.scheme();
    return scheme=="file" || scheme=="http" || scheme=="https" || scheme=="ftp";
}

QList<QUrl> REventHandler::getUrlsFromMimeData(QMimeData* mimeData) {
    if (mimeData==NULL) {
        return QList<QUrl>();
    }

    QList<QUrl> urls;

    if (mimeData->hasFormat("text/uri-list")) {
        urls = mimeData->urls();
    }

    else if (mimeData->hasFormat("text/plain")) {
        QString text = mimeData->text();
        QUrl url(text);
        if (!url.isValid()) {
            return urls;
        }
        if (!isUrl(url.toString())) {
            return urls;
        }
        urls.append(url);
    }

    return urls;
}

void REventHandler::dragEnter(QDragEnterEvent* event) {
    event->acceptProposedAction();
}

/**
 * Handles drop into the drawing area
 * \param event QDropEvent
 */
/*
REventHandler::drop(QDropEvent* event) {
    RMainWindowQt* appWin = RMainWindowQt::getMainWindow();

    const QMimeData* mimeData = event->mimeData();
    QList<QUrl> urls = getUrlsFromMimeData(mimeData);

    if (urls.isEmpty()) {
        appWin->handleUserWarning(tr("Dropped data not supported"));
        event->acceptProposedAction();
        return;
    }

    if (appWin!=NULL) {
        appWin->raise();
        appWin->setFocus(Qt::OtherFocusReason);
    }

    RGuiAction* action;
    if (urls[0].isLocalFile()) {
        QString file = urls[0].toLocalFile();
        appWin->handleUserMessage(tr("Importing file: ") + file);
        if (QFileInfo(file).isFile()) {
            //include("scripts/Block/InsertScriptItem/InsertScriptItem.js");
            if (InsertScriptItem.isScriptFile(file)) {
                action = RGuiAction.getByScriptFile("scripts/Block/InsertScriptItem/InsertScriptItem.js");
            } else {
                action = RGuiAction.getByScriptFile("scripts/Block/InsertBlockItem/InsertBlockItem.js");
            }
        }
    }
    else {
        EAction.handleUserMessage(tr("Importing URL: ") + urls[0].toString());
        action = RGuiAction.getByScriptFile("scripts/Block/InsertBlockItem/InsertBlockItem.js");
    }

    if (isNull(action)) {
        event.acceptProposedAction();
        return;
    }

    action.setData(urls[0]);
    action.slotTrigger();
    event.accept();
};
*/

void REventHandler::updateTextLabel(QPainter* painter, const RTextLabel& textLabel) {
    drawInfoLabel(painter, textLabel);
}

void REventHandler::drawInfoLabel(QPainter* painter, const RTextLabel& textLabel) {
    RVector pos = textLabel.getPosition();
    QString text = textLabel.getText();

    RVector p = graphicsView->mapToView(pos);
    // info labels might have individual colors in future
    //var color = RSettings.getColor("GraphicsViewColors/TextLabelColor", new RColor(249,198,31));
    RColor color = RSettings::getColor("GraphicsViewColors/MeasurementToolsColor", RColor(155,220,112));
    painter->setPen(color);

    if (!text.isEmpty()) {
        QFont font = RSettings::getInfoLabelFont();
        font.setPointSizeF(font.pointSizeF()*graphicsView->getDevicePixelRatio());
        QFontMetrics fm(font);
        int w = fm.width(text)+10;
        int h = fm.height()+10;
        //fm.destroy();
        painter->setFont(font);
        painter->drawText(p.x - w - 15, p.y + h + 5, w, h, Qt::AlignHCenter | Qt::AlignVCenter, text, NULL);
    }
}

/**
 * Called on every repaint of a view to update snap related information.
 * \param painter QPainter for the view in screen coordinates.
 * \param snap Current snap.
 */
void REventHandler::updateSnapInfo(QPainter* painter, RSnap* snap, RSnapRestriction* restriction) {
    if (snap==NULL) {
        return;
    }

    RVector pos = snap->getLastSnap();
    if (!pos.isValid()) {
        return;
    }
    RVector posRestriction = RVector::invalid;
    if (restriction!=NULL) {
        posRestriction = restriction->getLastSnap();
    }

    QString text = "";
    switch (snap->getStatus()) {
//    case RSnap::Free:
//        text = tr("Free");
//        break;
    case RSnap::Grid:
        text = tr("Grid");
        break;
    case RSnap::Endpoint:
        text = tr("End");
        break;
    case RSnap::OnEntity:
        text = tr("On Entity");
        break;
    case RSnap::Perpendicular:
        text = tr("Perpendicular");
        break;
    case RSnap::Tangential:
        text = tr("Tangential");
        break;
    case RSnap::Center:
        text = tr("Center");
        break;
    case RSnap::Middle:
        text = tr("Middle");
        break;
    case RSnap::Intersection:
        text = tr("Intersection");
        break;
    case RSnap::Reference:
        text = tr("Reference");
        break;
    default:
        break;
    }

    drawSnapLabel(painter, pos, posRestriction, text);
}

void REventHandler::drawSnapLabel(QPainter* painter, const RVector& pos, const RVector& posRestriction, const QString& text) {
    RVector p = graphicsView->mapToView(pos);
    RVector pr = RVector::invalid;
    if (posRestriction.isValid()) {
        pr = graphicsView->mapToView(posRestriction);
    }
    RColor color = RSettings::getColor("GraphicsViewColors/TextLabelColor", RColor(249,198,31));
    painter->setPen(color);

    QFont font = RSettings::getSnapLabelFont();
    font.setPointSizeF(font.pointSizeF()*graphicsView->getDevicePixelRatio());
    QFontMetrics fm(font);
    painter->setFont(font);

    int offset = 5 * graphicsView->getDevicePixelRatio();

    if (!text.isEmpty()) {
        painter->drawText(
            p.x + offset, p.y + offset,
            fm.width(text)+10, fm.height()+10,
            Qt::AlignHCenter | Qt::AlignVCenter,
            text, NULL);
    }

    painter->drawEllipse(p.x-offset, p.y-offset, offset*2, offset*2);

    // restriction position:
    if (pr.isSane()) {
        painter->drawLine(pr.x, pr.y-offset, pr.x+offset, pr.y);
        painter->drawLine(pr.x+offset, pr.y, pr.x, pr.y+offset);
        painter->drawLine(pr.x, pr.y+offset, pr.x-offset, pr.y);
        painter->drawLine(pr.x-offset, pr.y, pr.x, pr.y-offset);
    }

    // display distance/angle:
    int display = RSettings::getIntValue("DisplaySettings/DisplayDistanceAngle", 0);
    if (display == 0) {
        return;
    }

    RDocumentInterface* di = graphicsView->getDocumentInterface();
    RDocument* doc = graphicsView->getDocument();

    RVector relativeZero = di->getRelativeZero();

    double dist, angle;
    if (posRestriction.isSane()) {
        dist = relativeZero.getDistanceTo(posRestriction);
        angle = relativeZero.getAngleTo(posRestriction);
    } else {
        dist = relativeZero.getDistanceTo(pos);
        angle = relativeZero.getAngleTo(pos);
    }

    int lp = doc->getLinearPrecision();
    QString distStr = RUnit::doubleToString(dist, lp);

    angle = RMath::rad2deg(angle);
    int ap = doc->getAnglePrecision();
    QString angStr = RUnit::doubleToString(angle, ap);

    QString sep = RSettings::getStringValue("Input/PolarCoordinateSeparator", "<");

    color = RSettings::getColor("GraphicsViewColors/MeasurementToolsColor", RColor(155,220,112));
    painter->setPen(color);
    QString displayText;
    switch (display) {
    case 0:
        displayText = "";
        break;
    case 1:
        displayText = distStr + sep + angStr + QChar(0x00b0);
        break;
    case 2:
        displayText = distStr;
        break;
    case 3:
        displayText = angStr + QChar(0x00b0);
        break;
    default:
        displayText = "";
    }

    if (!displayText.isEmpty()) {
        painter->drawText(
                    p.x + offset, p.y - 3*offset - fm.height(),
                    fm.width(displayText)+10, fm.height()+10,
                    Qt::AlignHCenter | Qt::AlignVCenter,
                    displayText, NULL);
    }
}

/**
 * Called whenever the current viewport changed through panning or
 * zooming. Updates the scroll bars, rulers, etc.
 */
void REventHandler::viewportChanged() {
    if (hsb==NULL || vsb==NULL) {
        return;
    }

    hsb->blockSignals(true);
    vsb->blockSignals(true);

    RDocument& document = documentInterface->getDocument();

    RBox box = document.getBoundingBox(true, true);
    double min = box.getMinimum().x * graphicsView->getFactor() - 800;
    double max = box.getMaximum().x * graphicsView->getFactor() - graphicsView->getWidth() + 800;
    hsb->setRange(min, max);
    hsb->setPageStep(graphicsView->getWidth());
    hsb->setValue(-graphicsView->getOffset().x * graphicsView->getFactor());

    min = graphicsView->getHeight() - box.getMaximum().y * graphicsView->getFactor() - 800;
    max = 800 - box.getMinimum().y * graphicsView->getFactor();
    vsb->setRange(min, max);
    vsb->setPageStep(graphicsView->getHeight());
    vsb->setValue(graphicsView->getOffset().y * graphicsView->getFactor());

    hsb->blockSignals(false);
    vsb->blockSignals(false);

    // rulers
    if (hruler!=NULL) {
        hruler->updateViewport();
    }
    if (vruler!=NULL) {
        vruler->updateViewport();
    }

    // grid info label
    QLabel* infoLabel = widget->findChild<QLabel*>("InfoLabel");
    RGrid* grid = graphicsView->getGrid();
    if (grid!=NULL) {
        infoLabel->setText(grid->getInfoText());
    }
}

void REventHandler::horizontalScrolled(double pos) {
    bool blocked = graphicsView->getSignalsBlocked();
    graphicsView->setSignalsBlocked(true);
    RVector off = graphicsView->getOffset();
    off.x = -(pos / graphicsView->getFactor());
    graphicsView->setOffset(off);
    graphicsView->setSignalsBlocked(blocked);
    if (hruler!=NULL) {
        hruler->updateViewport();
    }
}

void REventHandler::verticalScrolled(double pos) {
    bool blocked = graphicsView->getSignalsBlocked();
    graphicsView->setSignalsBlocked(true);
    RVector off = graphicsView->getOffset();
    off.y = pos / graphicsView->getFactor();
    graphicsView->setOffset(off);
    graphicsView->setSignalsBlocked(blocked);
    if (vruler!=NULL) {
        vruler->updateViewport();
    }
}
