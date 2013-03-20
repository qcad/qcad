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
#include "RCustomWidgets.h"

#include "RTextEditPlugin.h"
#include "RCommandLinePlugin.h"
//#include "RHeaderDialogPlugin.h"
#include "RGraphicsViewGlPlugin.h"
//#include "RGraphicsViewGl3dPlugin.h"
#include "RGraphicsViewQtPlugin.h"
//#include "RGraphicsViewQVPlugin.h"
#include "RMathLineEditPlugin.h"
#include "RMdiChildQtPlugin.h"
#include "RColorComboPlugin.h"
#include "RLineweightComboPlugin.h"
#include "RLinetypeComboPlugin.h"
#include "RRulerQtPlugin.h"
#include "RFontChooserWidgetPlugin.h"
#include "RWebViewPlugin.h"
#include "RShortcutLineEditPlugin.h"
#include "RCharacterWidgetPlugin.h"
#include "RListViewPlugin.h"

#include <QWebView>

RCustomWidgets::RCustomWidgets(QObject *parent) :
    QObject(parent) {
    widgets.append(new RTextEditPlugin(this));
    widgets.append(new RCommandLinePlugin(this));
    widgets.append(new RGraphicsViewGlPlugin(this));
    //widgets.append(new RGraphicsViewGl3dPlugin(this));
    widgets.append(new RGraphicsViewQtPlugin(this));
    //widgets.append(new RHeaderDialogPlugin(this));
    //widgets.append(new RGraphicsViewQVPlugin(this));
    widgets.append(new RMathLineEditPlugin(this));
    widgets.append(new RMdiChildQtPlugin(this));
    widgets.append(new RColorComboPlugin(this));
    widgets.append(new RLineweightComboPlugin(this));
    widgets.append(new RLinetypeComboPlugin(this));
    widgets.append(new RRulerQtPlugin(this));
    widgets.append(new RFontChooserWidgetPlugin(this));
    widgets.append(new RWebViewPlugin(this));
    widgets.append(new RShortcutLineEditPlugin(this));
    widgets.append(new RCharacterWidgetPlugin(this));
    widgets.append(new RListViewPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> RCustomWidgets::customWidgets() const {
    return widgets;
}

Q_EXPORT_PLUGIN2(customwidgetsplugin, RCustomWidgets)
