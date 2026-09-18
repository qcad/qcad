/**
 * Copyright (c) 2011-2026 by Andrew Mustun. All rights reserved.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

#include "RAccessibleFlatTree.h"

#include <QAbstractItemModel>
#include <QAccessible>
#include <QAccessibleWidget>
#include <QHeaderView>
#include <QHash>
#include <QList>
#include <QPointer>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>
#include <QWindow>

namespace {

/**
 * \internal
 * Accessible interface of a single item of a flattened tree.
 *
 * Reported as a list item, which the Cocoa plugin maps to AXStaticText.
 * The item text is returned as the name of the interface, which is what
 * a screen reader reads as the value of that static text.
 */
class RAccessibleFlatTreeItem : public QAccessibleInterface {
public:
    RAccessibleFlatTreeItem(QTreeWidget* tree, QTreeWidgetItem* item, int column)
        : tree(tree),
          item(item),
          column(column) {
    }

    bool isValid() const override {
        return !tree.isNull() && item != NULL;
    }

    QObject* object() const override {
        // an item is not a QObject (same as Qt's own table cells):
        return NULL;
    }

    QWindow* window() const override {
        if (tree.isNull()) {
            return NULL;
        }
        QWidget* w = tree->window();
        return w != NULL ? w->windowHandle() : NULL;
    }

    QAccessibleInterface* parent() const override {
        if (tree.isNull()) {
            return NULL;
        }
        return QAccessible::queryAccessibleInterface(tree.data());
    }

    QAccessibleInterface* child(int index) const override {
        Q_UNUSED(index)
        return NULL;
    }

    int childCount() const override {
        return 0;
    }

    int indexOfChild(const QAccessibleInterface* iface) const override {
        Q_UNUSED(iface)
        return -1;
    }

    QAccessibleInterface* childAt(int x, int y) const override {
        Q_UNUSED(x)
        Q_UNUSED(y)
        return NULL;
    }

    QString text(QAccessible::Text t) const override {
        if (!isValid()) {
            return QString();
        }

        switch (t) {
        case QAccessible::Name: {
            const QString explicitText = item->data(column, Qt::AccessibleTextRole).toString();
            return explicitText.isEmpty() ? item->text(column) : explicitText;
        }
        case QAccessible::Description: {
            const QString description = item->data(column, Qt::AccessibleDescriptionRole).toString();
            // the name is already read as the value of the item: do not let
            // the same text be announced a second time as its label:
            if (description == text(QAccessible::Name)) {
                return QString();
            }
            return description;
        }
        default:
            return QString();
        }
    }

    void setText(QAccessible::Text t, const QString& text) override {
        Q_UNUSED(t)
        Q_UNUSED(text)
    }

    /**
     * \return The rectangle of the whole row: one item is reported as one
     * element, independently of the column its text is read from.
     */
    QRect rect() const override {
        if (!isValid()) {
            return QRect();
        }
        QRect r = tree->visualItemRect(item);
        if (r.isNull()) {
            return QRect();
        }
        r.setX(0);
        r.setWidth(tree->viewport()->width());
        r.translate(tree->viewport()->mapToGlobal(QPoint(0, 0)));
        return r;
    }

    QAccessible::Role role() const override {
        // static text rather than list item: both are mapped to
        // NSAccessibilityStaticTextRole by the Cocoa plugin, but only
        // static text is covered by QCocoaAccessible::hasValueAttribute(),
        // so only static text gets an AXValue - which is the text a screen
        // reader reads for such an element:
        return QAccessible::StaticText;
    }

    QAccessible::State state() const override {
        QAccessible::State s;
        if (!isValid()) {
            s.invalid = true;
            return s;
        }
        s.focusable = true;
        s.selectable = true;
        s.selected = item->isSelected();
        s.focused = (tree->currentItem() == item && tree->hasFocus());
        s.invisible = item->isHidden();
        if (!(item->flags() & Qt::ItemIsEnabled)) {
            s.disabled = true;
        }
        if (item->childCount() > 0) {
            s.expandable = true;
            s.expanded = item->isExpanded();
        }
        return s;
    }

    QTreeWidgetItem* treeItem() const {
        return item;
    }

private:
    QPointer<QTreeWidget> tree;
    QTreeWidgetItem* item;
    int column;
};

/**
 * \internal
 * Accessible interface of a tree widget which is exposed as a flat list.
 */
class RAccessibleFlatTreeView : public QAccessibleWidget, public QAccessibleSelectionInterface {
public:
    explicit RAccessibleFlatTreeView(QTreeWidget* tree)
        : QAccessibleWidget(tree, QAccessible::List),
          watcher(new QObject()) {

        // items are cached by item pointer: the cache has to be dropped
        // before items are deleted, or a screen reader which still holds an
        // element would read a deleted item (the layer list and the block
        // list rebuild all their items whenever the drawing changes).
        // the watcher object owns the connections and is deleted with this
        // interface, so no callback can outlive it:
        QAbstractItemModel* model = tree->model();
        if (model != NULL) {
            QObject::connect(model, &QAbstractItemModel::modelAboutToBeReset,
                             watcher, [this]() { dropItemInterfaces(); });
            QObject::connect(model, &QAbstractItemModel::rowsAboutToBeRemoved,
                             watcher, [this]() { dropItemInterfaces(); });
            QObject::connect(model, &QAbstractItemModel::columnsAboutToBeRemoved,
                             watcher, [this]() { dropItemInterfaces(); });
            QObject::connect(model, &QAbstractItemModel::layoutAboutToBeChanged,
                             watcher, [this]() { dropItemInterfaces(); });
            QObject::connect(model, &QObject::destroyed,
                             watcher, [this]() { dropItemInterfaces(); });
        }
    }

    ~RAccessibleFlatTreeView() override {
        delete watcher;
        watcher = NULL;
        dropItemInterfaces();
    }

    void* interface_cast(QAccessible::InterfaceType t) override {
        if (t == QAccessible::SelectionInterface) {
            return static_cast<QAccessibleSelectionInterface*>(this);
        }
        return QAccessibleWidget::interface_cast(t);
    }

    int childCount() const override {
        return (getVisibleItems().size() + getHeaderOffset()) * getColumnCount();
    }

    /**
     * \return The interface of the item at the given child index, or NULL.
     *
     * Child indexes are cell indexes, as used by Qt's own item view
     * accessibility: the index space of QTreeViewPrivate::accessibleTree2Index
     * is kept identical, so that the child indexes of the focus and selection
     * events QTreeView sends refer to the same items here. Only the column
     * which holds the item text is exposed, so that an item shows up as one
     * element and not once per column.
     */
    QAccessibleInterface* child(int index) const override {
        if (index < 0) {
            return NULL;
        }
        const int columns = getColumnCount();
        if (index % columns != getAccessibleColumn()) {
            return NULL;
        }
        // Qt's item views count the header as the first row, even if it is
        // hidden. The header itself is not exposed:
        const int i = index / columns - getHeaderOffset();
        if (i < 0) {
            return NULL;
        }
        const QList<QTreeWidgetItem*> items = getVisibleItems();
        if (i >= items.size()) {
            return NULL;
        }
        return getItemInterface(items.at(i));
    }

    int indexOfChild(const QAccessibleInterface* iface) const override {
        const RAccessibleFlatTreeItem* itemIface =
                dynamic_cast<const RAccessibleFlatTreeItem*>(iface);
        if (itemIface == NULL) {
            return -1;
        }
        const int i = getVisibleItems().indexOf(itemIface->treeItem());
        if (i < 0) {
            return -1;
        }
        return (i + getHeaderOffset()) * getColumnCount() + getAccessibleColumn();
    }

    QAccessibleInterface* childAt(int x, int y) const override {
        QTreeWidget* tree = getTreeWidget();
        if (tree == NULL) {
            return NULL;
        }
        QTreeWidgetItem* item = tree->itemAt(tree->viewport()->mapFromGlobal(QPoint(x, y)));
        if (item == NULL) {
            return NULL;
        }
        return getItemInterface(item);
    }

    /**
     * \return The interface of the current item. This is what a screen
     * reader asks for when the keyboard focus is inside the tree.
     */
    QAccessibleInterface* focusChild() const override {
        QTreeWidget* tree = getTreeWidget();
        if (tree == NULL) {
            return NULL;
        }
        QTreeWidgetItem* current = tree->currentItem();
        if (current != NULL && !current->isHidden()) {
            return getItemInterface(current);
        }
        // no current item: the list itself is the focused element.
        // note that QAccessibleWidget::focusChild() must not be called here:
        // if the tree is its own focus widget but does not have the focus
        // (e.g. while the application is not active), it calls focusChild()
        // of the tree again, which would not terminate:
        return QAccessible::queryAccessibleInterface(tree);
    }

    // QAccessibleSelectionInterface:

    int selectedItemCount() const override {
        QTreeWidget* tree = getTreeWidget();
        return tree != NULL ? tree->selectedItems().size() : 0;
    }

    QList<QAccessibleInterface*> selectedItems() const override {
        QList<QAccessibleInterface*> ret;
        QTreeWidget* tree = getTreeWidget();
        if (tree == NULL) {
            return ret;
        }
        const QList<QTreeWidgetItem*> items = tree->selectedItems();
        for (int i = 0; i < items.size(); i++) {
            QAccessibleInterface* iface = getItemInterface(items.at(i));
            if (iface != NULL) {
                ret.append(iface);
            }
        }
        return ret;
    }

    bool isSelected(QAccessibleInterface* childItem) const override {
        QTreeWidgetItem* item = getTreeItem(childItem);
        return item != NULL && item->isSelected();
    }

    bool select(QAccessibleInterface* childItem) override {
        QTreeWidgetItem* item = getTreeItem(childItem);
        if (item == NULL) {
            return false;
        }
        QTreeWidget* tree = getTreeWidget();
        if (tree != NULL) {
            tree->setCurrentItem(item);
        }
        item->setSelected(true);
        return true;
    }

    bool unselect(QAccessibleInterface* childItem) override {
        QTreeWidgetItem* item = getTreeItem(childItem);
        if (item == NULL) {
            return false;
        }
        item->setSelected(false);
        return true;
    }

    bool selectAll() override {
        QTreeWidget* tree = getTreeWidget();
        if (tree == NULL) {
            return false;
        }
        if (tree->selectionMode() != QAbstractItemView::MultiSelection &&
            tree->selectionMode() != QAbstractItemView::ExtendedSelection) {
            return false;
        }
        tree->selectAll();
        return true;
    }

    bool clear() override {
        QTreeWidget* tree = getTreeWidget();
        if (tree == NULL) {
            return false;
        }
        tree->clearSelection();
        return true;
    }

private:
    QTreeWidget* getTreeWidget() const {
        return qobject_cast<QTreeWidget*>(object());
    }

    /**
     * \return 1 if the tree has a header (even a hidden one), as Qt's own
     * item view accessibility does, 0 otherwise.
     */
    int getHeaderOffset() const {
        QTreeWidget* tree = getTreeWidget();
        return (tree != NULL && tree->header() != NULL) ? 1 : 0;
    }

    /**
     * \return Number of columns of the tree, at least 1.
     */
    int getColumnCount() const {
        QTreeWidget* tree = getTreeWidget();
        if (tree == NULL) {
            return 1;
        }
        return qMax(1, tree->columnCount());
    }

    /**
     * \return Index of the column which holds the text of an item.
     */
    int getAccessibleColumn() const {
        QTreeWidget* tree = getTreeWidget();
        if (tree == NULL) {
            return 0;
        }
        bool ok = false;
        const int c = tree->property(RAccessibleFlatTree::columnPropertyName()).toInt(&ok);
        if (!ok || c < 0 || c >= getColumnCount()) {
            return 0;
        }
        return c;
    }

    static QTreeWidgetItem* getTreeItem(const QAccessibleInterface* iface) {
        const RAccessibleFlatTreeItem* itemIface =
                dynamic_cast<const RAccessibleFlatTreeItem*>(iface);
        return itemIface != NULL ? itemIface->treeItem() : NULL;
    }

    static void collectVisibleChildren(QTreeWidgetItem* parent, QList<QTreeWidgetItem*>& ret) {
        for (int i = 0; i < parent->childCount(); i++) {
            QTreeWidgetItem* item = parent->child(i);
            if (item->isHidden()) {
                continue;
            }
            ret.append(item);
            if (item->isExpanded()) {
                collectVisibleChildren(item, ret);
            }
        }
    }

    /**
     * \return All items which are currently displayed, in display order
     * (the same order as the view items of QTreeView).
     */
    QList<QTreeWidgetItem*> getVisibleItems() const {
        QList<QTreeWidgetItem*> ret;
        QTreeWidget* tree = getTreeWidget();
        if (tree == NULL) {
            return ret;
        }
        for (int i = 0; i < tree->topLevelItemCount(); i++) {
            QTreeWidgetItem* item = tree->topLevelItem(i);
            if (item->isHidden()) {
                continue;
            }
            ret.append(item);
            if (item->isExpanded()) {
                collectVisibleChildren(item, ret);
            }
        }
        return ret;
    }

    /**
     * \return The (cached) accessible interface of the given item. The
     * interfaces have to be stable: a screen reader identifies an element
     * by the interface it was given.
     */
    QAccessibleInterface* getItemInterface(QTreeWidgetItem* item) const {
        if (item == NULL) {
            return NULL;
        }
        QHash<QTreeWidgetItem*, QAccessible::Id>::const_iterator it = itemIds.constFind(item);
        if (it != itemIds.constEnd()) {
            QAccessibleInterface* cached = QAccessible::accessibleInterface(it.value());
            if (cached != NULL) {
                return cached;
            }
            itemIds.remove(item);
        }

        QAccessibleInterface* iface =
                new RAccessibleFlatTreeItem(getTreeWidget(), item, getAccessibleColumn());
        QAccessible::registerAccessibleInterface(iface);
        itemIds.insert(item, QAccessible::uniqueId(iface));
        return iface;
    }

    /**
     * Drops all cached item interfaces. Called before items are removed
     * from the tree, so that no interface can refer to a deleted item.
     */
    void dropItemInterfaces() const {
        QHash<QTreeWidgetItem*, QAccessible::Id>::const_iterator it;
        for (it = itemIds.constBegin(); it != itemIds.constEnd(); it++) {
            QAccessible::deleteAccessibleInterface(it.value());
        }
        itemIds.clear();
    }

    QObject* watcher;
    mutable QHash<QTreeWidgetItem*, QAccessible::Id> itemIds;
};

QAccessibleInterface* raccessibleFlatTreeFactory(const QString& classname, QObject* object) {
    Q_UNUSED(classname)

    QTreeWidget* tree = qobject_cast<QTreeWidget*>(object);
    if (tree == NULL) {
        return NULL;
    }
    if (!tree->property(RAccessibleFlatTree::propertyName()).toBool()) {
        return NULL;
    }
    return new RAccessibleFlatTreeView(tree);
}

} // namespace

bool RAccessibleFlatTree::installed = false;

void RAccessibleFlatTree::install() {
    if (installed) {
        return;
    }
    installed = true;
    // factories are queried last installed first, so this one is asked
    // before the default implementation of Qt:
    QAccessible::installFactory(raccessibleFlatTreeFactory);
}
