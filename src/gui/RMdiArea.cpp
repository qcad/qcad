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
#include "RMdiArea.h"

#include <QDebug>
#include <QTabBar>
#include <QToolButton>

/**
 * Default Constructor.
 */
RMdiArea::RMdiArea(QWidget* parent) :
    QMdiArea(parent) {

    //addTabButton = new QToolButton(this);
    //addTabButton->setFixedSize(20,20);
    //connect(addTabButton, SIGNAL(clicked()), this, SLOT());
}

/**
 * Destructor
 */
RMdiArea::~RMdiArea() {
}

void RMdiArea::resizeEvent(QResizeEvent* event) {
    QMdiArea::resizeEvent(event);

//    QTabBar* tabBar = findChild<QTabBar*>();
//    const QSize tabBarSizeHint = tabBar->sizeHint();
//    int s = tabBarSizeHint.height();
//    addTabButton->setFixedSize(s, s);
//    addTabButton->move(width()-s, 0);
}
