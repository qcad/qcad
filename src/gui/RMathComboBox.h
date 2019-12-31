/**
 * Copyright (c) 2011-2019 by Andrew Mustun. All rights reserved.
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

#ifndef RMATHCOMBOBOX_H_
#define RMATHCOMBOBOX_H_

#include "gui_global.h"

#include <QMetaType>
#include <QComboBox>

#include "RMath.h"
#include "RMathLineEdit.h"

/**
 * \scriptable
 * \ingroup gui
 */
class QCADGUI_EXPORT RMathComboBox: public QComboBox {

Q_OBJECT

// keep extra ';' in place for the benefit of ecmagenerator:
Q_PROPERTY(bool angle READ isAngle WRITE setAngle)
Q_PROPERTY(bool integer READ isInteger WRITE setInteger)

public:
    RMathComboBox(QWidget* parent = NULL);

    RMathLineEdit* getMathLineEdit() const {
        QLineEdit* le = lineEdit();
        RMathLineEdit* me = dynamic_cast<RMathLineEdit*>(le);
        Q_ASSERT(me!=NULL);
        return me;
    }

    bool isAngle() const {
        return getMathLineEdit()->isAngle();
    }
    void setAngle(bool on) {
        getMathLineEdit()->setAngle(on);
    }
    bool isInteger() const {
        return getMathLineEdit()->isInteger();
    }
    void setInteger(bool on) {
        getMathLineEdit()->setInteger(on);
    }

    void setValue(double v, int precision=6) {
        getMathLineEdit()->setValue(v, precision);
    }
    double getValue() {
        return getMathLineEdit()->getValue();
    }
    QString getError() {
        return getMathLineEdit()->getError();
    }
    void clearError() {
        getMathLineEdit()->clearError();
    }

    bool isValid() {
        return getMathLineEdit()->isValid();
    }

    bool isSane() {
        return getMathLineEdit()->isSane();
    }

public slots:
    void slotTextChanged(const QString& text) {
        getMathLineEdit()->slotTextChanged(text);
    }
    void slotValueChanged(double value, const QString& error) {
        // forward signal from RMathLineEdit:
        emit valueChanged(value, error);
    }

signals:
    void valueChanged(double value, const QString& error);
};

Q_DECLARE_METATYPE(RMathComboBox*)

#endif
