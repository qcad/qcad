#ifndef RFLOWLAYOUT_H
#define RFLOWLAYOUT_H

#include <QLayout>
#include <QRect>
#include <QStyle>

class RFlowLayout : public QLayout {
public:
    explicit RFlowLayout(QWidget* parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);
    explicit RFlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);
    ~RFlowLayout();

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
    int indexOf(QWidget* widget) const {
        return QLayout::indexOf(widget);
    }

private:
    int doLayout(const QRect& rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

    QList<QLayoutItem*> itemList;
    int hSpace;
    int vSpace;
};

#endif
