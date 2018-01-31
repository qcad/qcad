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
#include <QDebug>

#include "RWidget.h"


/**
 * Default Constructor.
 */
RWidget::RWidget(QWidget* parent) :
    QWidget(parent) {
}

/**
 * Destructor
 */
RWidget::~RWidget() {
}

void RWidget::removeAction(QAction* action) {
    QWidget::removeAction(action);
}

void RWidget::addAction(QAction* action) {
    QWidget::addAction(action);
    //emit actionAdded(action);
}

void RWidget::insertAction(QAction* before, QAction* action) {
    QWidget::insertAction(before, action);
    //emit actionAdded(action);
}
