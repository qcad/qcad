/**
 * Copyright (c) 2011-2024 by Andrew Mustun. All rights reserved.
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

#ifndef RCOMBOBOX_H_
#define RCOMBOBOX_H_

#include "gui_global.h"

#include <QComboBox>
#include <QKeyEvent>

/**
 * Combo box which triggerd signal returnPressed if return is pressed while box has keyboard focus.
 * \scriptable
 * \ingroup gui
 */
class QCADGUI_EXPORT RComboBox: public QComboBox {

Q_OBJECT

public:
    RComboBox(QWidget* parent = 0);

protected:
    void keyPressEvent(QKeyEvent* event);

signals:
    void returnPressed();
};

Q_DECLARE_METATYPE(RComboBox*)

#endif /* RCOMBOBOX_H_ */
