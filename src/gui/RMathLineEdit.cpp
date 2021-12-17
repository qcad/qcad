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
#include <QColor>
#include <QComboBox>
#include <QKeyEvent>
#include <QLabel>
#include <QPalette>
#include <QTimer>
#include <QToolTip>

#include "RDocument.h"
#include "RMainWindowQt.h"
#include "RMath.h"
#include "RMathLineEdit.h"
#include "RUnit.h"

RMathLineEdit::RMathLineEdit(QWidget* parent) :
    QLineEdit(parent),
    angle(false),
    integer(false),
    value(0.0),
    noEmit(false),
    noResultInToolTip(false) {

    oriPalette = palette();

    slotTextChanged(text());
    originalToolTip = QString();
    QLineEdit::setToolTip("");

    connect(this, SIGNAL(textChanged(QString)), this, SLOT(slotTextChanged(QString)));
    connect(this, SIGNAL(textEdited(QString)), this, SLOT(slotTextEdited(QString)));
}

//int RMathLineEdit::getDefaultUnit() {
//    return (int)defaultUnit;
//}

//void RMathLineEdit::setDefaultUnit(int defaultUnit) {
//    this->defaultUnit = (RS::Unit)defaultUnit;
//}

void RMathLineEdit::slotTextChanged(const QString& text) {
    if (originalToolTip.isNull()) {
        // save original tooltip, typically set in designer:
        originalToolTip = toolTip();
        if (originalToolTip.isNull()) {
            originalToolTip = "";
        }
    }

    bool hasError = false;
    bool hasFormula = false;

    // most common case (double value):
    if (QRegExp("^[+-]?\\d*\\.?\\d+$").exactMatch(text)) {
        value = text.toDouble();
        hasError = false;
        hasFormula = false;
    }

    // advanced cases (formulas, variables, functions, etc.):
    else {
        RDocument* doc = NULL;
        RMainWindow* appWin = RMainWindow::getMainWindow();
        if (appWin!=NULL) {
            doc = appWin->getDocument();
        }

        if (doc!=NULL) {
            // this calls RMath::eval, so it's OK to call RMath::hasError after:
            value = doc->eval(text);
        }
        else {
            value = RMath::eval(text);
        }
        hasError = RMath::hasError();
        hasFormula = true;
    }

    if (hasError) {
        error = RMath::getError();
        //res = defaultValue;
        // special case: don't report an error for text between *
        // (e.g. *VARIES* in property editor)
        if (!(text.startsWith('*') && text.endsWith('*'))) {
            setToolTip(error);
        }
    }
    else {
        error = "";
        QString str;
        //str.sprintf("%.6g%s",value,(const char*)RUnit::unitToSymbol(defaultUnit).toUtf8());
        str.sprintf("%.6g",value);
        setToolTip(str);
    }

    if (isEnabled()) {
        setTextColor(hasError);
    }
    else {
        // update text color of line edit / math line combo:
        setTextColor(false);
        setPalette(oriPalette);
    }

    if (!RMath::isNaN(value) && isAngle()) {
        value = RMath::deg2rad(value);
    }

    /*if (parentWidget()!=NULL && isVisible()) {
        QPoint tPos = parentWidget()->mapToGlobal(pos());
        tPos+=QPoint(0, height());
        QToolTip::showText(tPos, toolTip(), this);

        // TODO: improved tool tip for result display:
//        if (resultTip==NULL) {
//            resultTip = new QLabel(toolTip(), RMainWindowQt::getMainWindow());
//            resultTip->resize(resultTip->sizeHint());
//            resultTip->move(tPos);
//            QPalette lp = resultTip->palette();
//    //        if (RMath::hasError()) {
//    //            lp.setColor(QPalette::Text, Qt::red);
//    //        }
//    //        else {
//    //            lp.setColor(QPalette::Text, Qt::black);
//    //        }
//            lp.setColor(QPalette::Window, Qt::yellow);
//            resultTip->setPalette(lp);
//        }

//        resultTip->show();
//        QTimer::singleShot(2000, resultTip, "hide");
    }*/

    // look up equal sign label and result label to update:
    if (!objectName().isEmpty()) {
        QWidget* parent = parentWidget();
        if (parent!=NULL) {
            QLabel* lEqual = parent->findChild<QLabel*>(objectName() + "Equal");
            if (lEqual!=NULL) {
                lEqual->setVisible(hasFormula);
            }
            QLabel* lResult = parent->findChild<QLabel*>(objectName() + "Result");
            if (lResult!=NULL) {
                double displayedValue = value;
                if (isAngle()) {
                    displayedValue = RMath::rad2deg(displayedValue);
                }
                lResult->setVisible(hasFormula);
                QString l;
                if (RMath::isNormal(displayedValue)) {
                    l.sprintf("%.3g", displayedValue);
                }
                else {
                    l = tr("Invalid");
                }
                lResult->setText(l);
                setToolTip("");
                noResultInToolTip = true;
            }
        }
    }

    if (!noEmit) {
        emit valueChanged(value, error);
    }
}

void RMathLineEdit::slotTextEdited(const QString& text) {
    noEmit = true;
    // make sure that value and error message are up to date:
    slotTextChanged(text);
    noEmit = false;

    if (parentWidget()!=NULL && isVisible() && !noResultInToolTip) {
        QPoint tPos = parentWidget()->mapToGlobal(pos());
        tPos+=QPoint(0, height());
        QToolTip::showText(tPos, toolTip(), this);

        // TODO: improved tool tip for result display:
        //        if (resultTip==NULL) {
        //            resultTip = new QLabel(toolTip(), RMainWindowQt::getMainWindow());
        //            resultTip->resize(resultTip->sizeHint());
        //            resultTip->move(tPos);
        //            QPalette lp = resultTip->palette();
        //    //        if (RMath::hasError()) {
        //    //            lp.setColor(QPalette::Text, Qt::red);
        //    //        }
        //    //        else {
        //    //            lp.setColor(QPalette::Text, Qt::black);
        //    //        }
        //            lp.setColor(QPalette::Window, Qt::yellow);
        //            resultTip->setPalette(lp);
        //        }

        //        resultTip->show();
        //        QTimer::singleShot(2000, resultTip, "hide");
    }
}

void RMathLineEdit::setValue(double v, int precision) {
    // update value (in rad for angles):
    value = v;

    // update text (in deg for angles):
    if (isAngle()) {
        v = RMath::rad2deg(v);
    }
    setText(QString("%1").arg(v, 0, 'g', precision));
    clearError();
}

double RMathLineEdit::getValue() {
    if (isInteger()) {
        return RMath::mround(value);
    }
    else {
        return value;
    }
}

QString RMathLineEdit::getError() {
    return error;
}

void RMathLineEdit::clearError() {
    error = "";
    QPalette p = palette();
    p.setColor(QPalette::Active, QPalette::Text, getNormalTextColor());
    setPalette(p);
}


void RMathLineEdit::setToolTip(const QString& toolTip) {
    if (originalToolTip.isEmpty() && error.isEmpty() && toolTip.isEmpty()) {
        QLineEdit::setToolTip("");
        return;
    }

    QString textCol = palette().toolTipText().color().name();
    if (RSettings::isDarkMode()) {
        textCol = "white";
    }

    QLineEdit::setToolTip(
        QString(
            "%1%2"
            "<span style=\""
                "color: %3; "
                "font-size: small; "
                "font-family: monospace"
            "\">%4</span>"
        )
        .arg(originalToolTip)
        .arg(originalToolTip.isEmpty() ? "" : "<br>")
        .arg(error.isEmpty() ? textCol : "red")
        .arg(toolTip)
    );
}

QColor RMathLineEdit::getNormalTextColor() const {
    return oriPalette.color(QPalette::Normal, QPalette::WindowText);
}

void RMathLineEdit::setTextColor(bool error) {
    QPalette p = palette();
    p.setColor(QPalette::Active, QPalette::Text, QColor(error ? Qt::red : getNormalTextColor()));
    setPalette(p);

    QWidget* parent = parentWidget();
    QComboBox* cb = dynamic_cast<QComboBox*>(parent);
    if (cb!=NULL) {
        cb->setPalette(p);
    }
}

void RMathLineEdit::keyPressEvent(QKeyEvent* event) {
    if (event->key()==Qt::Key_Up) {
        emit upKeyPressed();
    }
    else if (event->key()==Qt::Key_Down) {
        emit downKeyPressed();
    }
    else if (event->key()==Qt::Key_Enter || event->key()==Qt::Key_Return) {
        emit enterKeyPressed();
        QLineEdit::keyPressEvent(event);
    }
    else {
        QLineEdit::keyPressEvent(event);
    }
}

void RMathLineEdit::keyReleaseEvent(QKeyEvent* event) {
    QLineEdit::keyReleaseEvent(event);
}
