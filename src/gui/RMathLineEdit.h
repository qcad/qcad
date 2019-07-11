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

#ifndef RMATHLINEEDIT_H_
#define RMATHLINEEDIT_H_

#include "gui_global.h"

#include <QMetaType>
#include <QLineEdit>

#include "RMath.h"

/**
 * \scriptable
 * \ingroup gui
 */
class QCADGUI_EXPORT RMathLineEdit: public QLineEdit {

Q_OBJECT

// keep extra ';' in place for the benefit of ecmagenerator:
Q_PROPERTY(bool angle READ isAngle WRITE setAngle);
Q_PROPERTY(bool integer READ isInteger WRITE setInteger);
//Q_PROPERTY(double defaultValue READ getDefaultValue WRITE setDefaultValue);
//Q_PROPERTY(int defaultUnit READ getDefaultUnit WRITE setDefaultUnit);
//Q_PROPERTY(RS::Unit defaultUnit READ getDefaultUnit WRITE setDefaultUnit);
//Q_ENUMS(RS::Unit);

public:
    RMathLineEdit(QWidget* parent = NULL);

    bool isAngle() const {
       return angle;
    }
    void setAngle(bool on) {
       angle = on;
    }
    bool isInteger() const {
        return integer;
    }
    void setInteger(bool on) {
        integer = on;
    }

    void setValue(double v, int precision=6);
    double getValue();
    QString getError();
    void clearError();

    bool isValid() {
        return !RMath::isNaN(value);
    }

    bool isSane() {
        return RMath::isSane(value);
    }

    void setToolTip(const QString& toolTip);

    QColor getNormalTextColor() const;
    void setTextColor(bool error);

    /*
    double getDefaultValue() {
        return defaultValue;
    }
    void setDefaultValue(double v) {
        defaultValue = v;
    }
    */

    //void setDefaultUnit(int defaultUnit);
    //int getDefaultUnit();

protected:
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);
//    virtual bool eventFilter(QObject* obj, QEvent* event);

public slots:
    void slotTextChanged(const QString& text);
    void slotTextEdited(const QString& text);

signals:
    void valueChanged(double value, const QString& error);
    void upKeyPressed();
    void downKeyPressed();
    void enterKeyPressed();

private:
    QPalette oriPalette;
    bool angle;
    bool integer;
    double value;
    //RS::Unit defaultUnit;
    QString error;
    QString originalToolTip;
    bool noEmit;
    bool noResultInToolTip;
    //double defaultValue;
};

Q_DECLARE_METATYPE(RMathLineEdit*)

#endif
