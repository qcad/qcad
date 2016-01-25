#include <QAction>
#include <QEvent>
#include <QWidget>

#include "RFlowLayout.h"
#include "RSettings.h"
#include "RToolButton.h"

RFlowLayout::RFlowLayout(QWidget* parent, int margin, int hSpacing, int vSpacing)
    : QLayout(parent), hSpace(hSpacing), vSpace(vSpacing), iconSize(32,32), listViewMode(false) {
    setContentsMargins(margin, margin, margin, margin);
}

RFlowLayout::RFlowLayout(int margin, int hSpacing, int vSpacing)
    : hSpace(hSpacing), vSpace(vSpacing), iconSize(32,32), listViewMode(false) {
    setContentsMargins(margin, margin, margin, margin);
}

RFlowLayout::~RFlowLayout() {
    QLayoutItem* item;
    while ((item = takeAt(0))) {
        delete item;
    }
}

void RFlowLayout::setIconSize(const QSize& s) {
    iconSize = s;

    QWidget* parent = parentWidget();
    if (parent==NULL) {
        return;
    }
    QList<QToolButton*> buttons = parent->findChildren<QToolButton*>();
    for (int i=0; i<buttons.length(); i++) {
        QToolButton* tb = buttons[i];
        tb->setIconSize(iconSize);
    }
}

void RFlowLayout::setListViewMode(bool on) {
    listViewMode = on;

    QWidget* parent = parentWidget();
    if (parent==NULL) {
        return;
    }
    QList<QToolButton*> buttons = parent->findChildren<QToolButton*>();
    for (int i=0; i<buttons.length(); i++) {
        QToolButton* tb = buttons[i];
        if (listViewMode) {
            tb->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        }
        else {
            tb->setToolButtonStyle(Qt::ToolButtonIconOnly);
        }
    }
}

void RFlowLayout::addItem(QLayoutItem* item) {
    itemList.append(item);
}

int RFlowLayout::horizontalSpacing() const {
    if (hSpace >= 0) {
        return hSpace;
    } else {
        return smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
    }
}

int RFlowLayout::verticalSpacing() const {
    if (vSpace >= 0) {
        return vSpace;
    } else {
        return smartSpacing(QStyle::PM_LayoutVerticalSpacing);
    }
}

int RFlowLayout::count() const {
    return itemList.size();
}

QLayoutItem* RFlowLayout::itemAt(int index) const {
    return itemList.value(index);
}

QLayoutItem* RFlowLayout::takeAt(int index) {
    if (index >= 0 && index < itemList.size()) {
        return itemList.takeAt(index);
    }
    else {
        return 0;
    }
}

Qt::Orientations RFlowLayout::expandingDirections() const {
    return 0;
}

bool RFlowLayout::hasHeightForWidth() const {
    return true;
}

int RFlowLayout::heightForWidth(int width) const {
    int height = doLayout(QRect(0, 0, width, 0), true);
    return height;
}

void RFlowLayout::setGeometry(const QRect& rect) {
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

QSize RFlowLayout::sizeHint() const {
    return minimumSize();
}

QSize RFlowLayout::minimumSize() const {
    QSize size;
    QLayoutItem* item;
    foreach (item, itemList) {
        size = size.expandedTo(item->minimumSize());
    }

    size += QSize(2*margin(), 2*margin());
    return size;
}

int RFlowLayout::doLayout(const QRect& rect, bool testOnly) const {
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;

    QLayoutItem* item;
    foreach (item, itemList) {
        QWidget* wid = item->widget();
        QToolButton* tb = qobject_cast<QToolButton*>(wid);

        if (wid->isHidden()) {
            continue;
        }

        QAction* action = tb->defaultAction();
        if (action==NULL || !action->isVisible()) {
            continue;
        }

        int spaceX = horizontalSpacing();
        if (spaceX == -1) {
            spaceX = wid->style()->layoutSpacing(
                QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);
        }
        int spaceY = verticalSpacing();
        if (spaceY == -1) {
            spaceY = wid->style()->layoutSpacing(
                QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);
        }
        bool listModeItem = (tb!=NULL && tb->toolButtonStyle()==Qt::ToolButtonTextBesideIcon);
        if (listModeItem) {
            wid->setFixedWidth(effectiveRect.width());
        }
        else {
            wid->setFixedWidth(wid->height());
        }
        int nextX = x + item->sizeHint().width() + spaceX;
        if (nextX - spaceX > effectiveRect.right() && lineHeight > 0 || listModeItem) {
            x = effectiveRect.x();
            y = y + lineHeight + spaceY;
            nextX = x + item->sizeHint().width() + spaceX;
            lineHeight = 0;
        }

        if (!testOnly) {
            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));
        }

        x = nextX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
    }
    return y + lineHeight - rect.y() + bottom;
}

int RFlowLayout::smartSpacing(QStyle::PixelMetric pm) const {
    QObject* parent = this->parent();
    if (!parent) {
        return -1;
    } else if (parent->isWidgetType()) {
        QWidget* pw = static_cast<QWidget*>(parent);
        return pw->style()->pixelMetric(pm, 0, pw);
    } else {
        return static_cast<QLayout*>(parent)->spacing();
    }
}

void RFlowLayout::insertAction(int index, QAction* action) {
    index = qMax(0, index);
    index = qMin(itemList.count(), index);

    if (action->isSeparator()) {
        QWidget* w = new QWidget(parentWidget());
        w->addAction(action);
        w->hide();
        QWidgetItem* item = new QWidgetItem(w);
        //item->setGeometry(QRect(0,0,0,0));
        itemList.insert(index, item);
        invalidate();
        return;
    }

    RToolButton* button = new RToolButton(parentWidget());
    //int iconSize = RSettings::getIntValue("CadToolBar/IconSize", 32);
    button->setIconSize(iconSize);
    button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    button->setDefaultAction(action);
    itemList.insert(index, new QWidgetItem(button));
    invalidate();

//    QToolBarItem* item = createItem(action);
//    if (item) {
//        items.insert(index, item);
//        invalidate();
//    }
}

int RFlowLayout::indexOf(QAction* action) const {
    //qDebug() << "indexOf: " << action;
    for (int i = 0; i < itemList.count(); ++i) {
        QLayoutItem* item = itemList.at(i);
        QWidget* w = item->widget();
        QToolButton* b = qobject_cast<QToolButton*>(w);
        if (b!=NULL && b->defaultAction()==action) {
            return i;
        }
        if (w->actions().length()==1 && w->actions()[0]==action) {
            return i;
        }
    }
    return -1;
}
