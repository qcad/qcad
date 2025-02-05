#include <QDebug>
#include <QFileInfo>
#include <QSizePolicy>
#include <QToolButton>

#include "RCadToolBar.h"
#include "RCadToolBarPanel.h"
#include "RGuiAction.h"
#include "RSettings.h"
#include "RColumnLayout.h"

RCadToolBarPanel::RCadToolBarPanel(RCadToolBar* parent, bool hasBackButton) : RWidget(parent) {

    // init column layout:
    columnLayout = new RColumnLayout(this, parent, RSettings::getIntValue("CadToolBar/IconSize", 32) * 1.25);
    setLayout(columnLayout);

    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    backMenuName = "MainToolsPanel";

    if (hasBackButton) {
        RGuiAction* backAction = new RGuiAction(tr("Back"), this);
        backAction->setObjectName("Back");
        backAction->setCheckable(false);
        QString backIconFile = "scripts/Widgets/CadToolBar/Back.svg";
        if (QFileInfo(backIconFile).exists()) {
            backAction->setIcon(backIconFile);
        }
        else {
            backAction->setIcon(QString(":") + backIconFile);
        }
        addAction(backAction);
        connect(backAction, SIGNAL(triggered()), parent, SLOT(back()));
    }
}

QString RCadToolBarPanel::getButtonName(QAction* action) const {
    QString buttonName = action->objectName();
    if (buttonName.endsWith("Action")) {
        buttonName = buttonName.left(buttonName.length() - QString("Action").length());
    }
    buttonName += "Button";
    return buttonName;
};

void RCadToolBarPanel::removeAction(QAction* action) {
    RWidget::removeAction(action);

    QString buttonName = getButtonName(action);
    QWidget* w = findChild<QWidget*>(buttonName);
    if (w!=NULL) {
        w->setVisible(false);
    }
};

void RCadToolBarPanel::insertAction(QAction* before, QAction* action) {
    addAction(action);
    QWidget::insertAction(before, action);
};

void RCadToolBarPanel::addAction(QAction* action) {
    RGuiAction* ga = dynamic_cast<RGuiAction*>(action);
    if (ga==NULL) {
        qWarning() << "RCadToolBarPanel::addAction: trying to add QAction that is not a RGuiAction";
        return;
    }

    QString buttonName = getButtonName(action);

    // check if button already exists for this action:
    QToolButton* button = findChild<QToolButton*>(buttonName);
    if (button==NULL) {
        button = new QToolButton(this);
    }
    button->setVisible(true);
    button->setDefaultAction(action);
    button->setObjectName(buttonName);
    int s = RSettings::getIntValue("CadToolBar/IconSize", 32);
    button->setIconSize(QSize(s, s));

    button->setProperty("GroupSortOrder", RColumnLayout::getGroupSortOrder(action, objectName()));
    button->setProperty("SortOrder", RColumnLayout::getSortOrder(action, objectName()));

    if (button->objectName()=="BackButton") {
        button->setToolTip(tr("Back"));
        button->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
    }

    columnLayout->addWidget(button);
    RWidget::addAction(action);
};
