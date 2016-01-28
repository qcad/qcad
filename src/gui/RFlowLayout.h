#ifndef RFLOWLAYOUT_H
#define RFLOWLAYOUT_H

#include "gui_global.h"

#include <QLayout>
#include <QMetaType>
#include <QRect>
#include <QStyle>

#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif

/**
 * Flow layout. Added actions are represented as QToolButtons.
 *
 * \ingroup gui
 * \scriptable
 * \generateScriptShell
 */
class QCADGUI_EXPORT RFlowLayout : public QLayout {
    Q_OBJECT

public:
    RFlowLayout(QWidget* parent, int margin = RDEFAULT_MIN1, int hSpacing = RDEFAULT_MIN1, int vSpacing = RDEFAULT_MIN1);
    RFlowLayout(int margin = RDEFAULT_MIN1, int hSpacing = RDEFAULT_MIN1, int vSpacing = RDEFAULT_MIN1);
    ~RFlowLayout();

    void setIconSize(const QSize& s);
    void setListViewMode(bool on);

    void addItem(QLayoutItem* item);
    int horizontalSpacing() const;
    int verticalSpacing() const;
    Qt::Orientations expandingDirections() const;
    bool hasHeightForWidth() const;
    int heightForWidth(int) const;
    int count() const;
    QLayoutItem* itemAt(int index) const;
    QSize minimumSize() const;
    void setGeometry(const QRect& rect);
    QSize sizeHint() const;
    QLayoutItem* takeAt(int index);

    void insertAction(int index, QAction* action);
    int indexOf(QAction* action) const;

    void invalidate() {
        QLayout::invalidate();
    }

    /**
     * \nonscriptable
     */
    int indexOf(QWidget* widget) const {
        return QLayout::indexOf(widget);
    }

private:
    int doLayout(const QRect& rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

    QList<QLayoutItem*> itemList;
    int hSpace;
    int vSpace;
    QSize iconSize;
    bool listViewMode;
};

Q_DECLARE_METATYPE(RFlowLayout*)

#endif
