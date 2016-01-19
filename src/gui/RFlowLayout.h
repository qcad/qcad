#ifndef RFLOWLAYOUT_H
#define RFLOWLAYOUT_H

#include <QLayout>
#include <QRect>
#include <QStyle>
class RFlowLayout : public QLayout
{
public:
    explicit RFlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);
    explicit RFlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);
    ~RFlowLayout();

    void addItem(QLayoutItem *item) Q_DECL_OVERRIDE;
    int horizontalSpacing() const;
    int verticalSpacing() const;
    Qt::Orientations expandingDirections() const Q_DECL_OVERRIDE;
    bool hasHeightForWidth() const Q_DECL_OVERRIDE;
    int heightForWidth(int) const Q_DECL_OVERRIDE;
    int count() const Q_DECL_OVERRIDE;
    QLayoutItem *itemAt(int index) const Q_DECL_OVERRIDE;
    QSize minimumSize() const Q_DECL_OVERRIDE;
    void setGeometry(const QRect &rect) Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    QLayoutItem *takeAt(int index) Q_DECL_OVERRIDE;

    void insertAction(int index, QAction* action);
    int indexOf(QAction* action) const;
    int indexOf(QWidget* widget) const Q_DECL_OVERRIDE { return QLayout::indexOf(widget); }

private:
    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

    QList<QLayoutItem *> itemList;
    int m_hSpace;
    int m_vSpace;
};

#endif
