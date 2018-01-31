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

#include "RDebug.h"
#include "RDocumentInterface.h"
#include "RGraphicsViewQt.h"
#include "RMainWindowQt.h"
#include "RMdiArea.h"
#include "RMdiChildQt.h"
#include "RRulerQt.h"
#include "RScriptHandler.h"
#include "RSingleApplication.h"


RDocumentInterface* RMdiChildQt::diLast = NULL;

/**
 * Creates a new MDI child window for interaction with the given document.
 * The MDI window takes ownership of the document.
 */
RMdiChildQt::RMdiChildQt(QWidget* parent) :
    QMdiSubWindow(parent), documentInterface(NULL), closeEventAccepted(false) {

    setAttribute(Qt::WA_DeleteOnClose);
    setFocusPolicy(Qt::WheelFocus);
}

RMdiChildQt::~RMdiChildQt() {
}

void RMdiChildQt::setDocumentInterface(RDocumentInterface* di) {
    Q_ASSERT(di!=NULL);

    documentInterface = di;

    if (documentInterface!=NULL) {
        RStorage& storage = documentInterface->getStorage();
        storage.addModifiedListener(this);
    }
}

RDocumentInterface* RMdiChildQt::getDocumentInterface() {
    if (documentInterface == NULL) {
//        qWarning() << "RMdiChildQt::getDocumentInterface(): "
//                "documentInterface is NULL";
        return NULL;
    }
    return documentInterface;
}

RDocument* RMdiChildQt::getDocument() {
    if (documentInterface == NULL) {
        //qWarning() << "RMdiChildQt::getDocument(): "
        //        "documentInterface is NULL";
        return NULL;
    }
    return &documentInterface->getDocument();
}

RGraphicsViewQt* RMdiChildQt::getLastKnownViewWithFocus() {
    RDocumentInterface* di = getDocumentInterface();
    if (di==NULL) {
        return NULL;
    }
    return dynamic_cast<RGraphicsViewQt*>(di->getLastKnownViewWithFocus());
}

void RMdiChildQt::closeEvent(QCloseEvent* closeEvent) {
    // ask before closing (document was modified):
    if (documentInterface != NULL) {
        emit closeRequested(this);
    }
    else {
        closeEvent->accept();
        return;
    }

    // close canceled:
    if (!closeEventAccepted) {
        closeEvent->ignore();
        return;
    }

    if (documentInterface != NULL) {

        if (diLast==documentInterface) {
            diLast = NULL;
        }

        // 20130510: leads to empty layer list, etc when
        // closing background tab
        //RMainWindowQt::getMainWindow()->notifyListeners(true);

        // make sure rulers don't try to access view anymore:
        QList<RRulerQt*> rulers = findChildren<RRulerQt*>();
        for (int i=0; i<rulers.size(); i++) {
            rulers.at(i)->setGraphicsView(NULL);
        }

        // give current action a chance to clean up:
        RAction* action = documentInterface->getCurrentAction();
        if (action!=NULL) {
            action->suspendEvent();
            action->terminate();
        }
        documentInterface->deleteTerminatedActions();

        emit closeAccepted(this);

        RDocumentInterface* di = documentInterface;
        documentInterface=NULL;
        delete di;
        di = NULL;
    }
    closeEvent->accept();

#ifndef Q_OS_WIN
    // part of the workaround for QMdiArea bug
    // with events filtering through all stacked windows:
    RMdiArea* mdiArea = RMainWindowQt::getMainWindow()->getMdiArea();
    QMdiSubWindow* child =  mdiArea->currentSubWindow();
    QList<QMdiSubWindow *> children = mdiArea->subWindowList(QMdiArea::ActivationHistoryOrder);
    int index = children.indexOf(child);
    int nextIndex = children.length()-2;
    nextIndex = nextIndex%children.length();
    if (nextIndex!=index) {
        children.at(nextIndex)->showMaximized();
        mdiArea->setActiveSubWindow(children.at(nextIndex));
    }
#endif
}

QSize RMdiChildQt::sizeHint() const {
    return QSize(640, 480);
}

void RMdiChildQt::updateModifiedListener(const RStorage* storage) {
    setWindowModified(storage->isModified());
    emit modifiedStatusChanged(this);
}

//RMdiChildQt* RMdiChildQt::getMdiChild(QWidget* w) {
//    QWidget* parent = w;
//    do {
//        parent = parent->parentWidget();
//        RMdiChildQt* mdiChild = qobject_cast<RMdiChildQt*>(parent);
//        if (mdiChild!=NULL) {
//            return mdiChild;
//        }
//    } while (parent!=NULL);

//    return NULL;
//}
