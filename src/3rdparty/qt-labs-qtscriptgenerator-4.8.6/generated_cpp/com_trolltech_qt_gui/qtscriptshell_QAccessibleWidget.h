#ifndef QTSCRIPTSHELL_QACCESSIBLEWIDGET_H
#define QTSCRIPTSHELL_QACCESSIBLEWIDGET_H

#include <qaccessiblewidget.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAccessibleWidget : public QAccessibleWidget
{
public:
    QtScriptShell_QAccessibleWidget(QWidget*  o, QAccessible::Role  r = QAccessible::Client, const QString&  name = QString());
    ~QtScriptShell_QAccessibleWidget();

    QString  actionText(int  action, QAccessible::Text  t, int  child) const;
    int  childAt(int  x, int  y) const;
    int  childCount() const;
    bool  doAction(int  action, int  child, const QList<QVariant >&  params);
    int  indexOfChild(const QAccessibleInterface*  child) const;
    bool  isValid() const;
    int  navigate(QAccessible::RelationFlag  rel, int  entry, QAccessibleInterface**  target) const;
    QObject*  object() const;
    QRect  rect(int  child) const;
    QAccessible::Relation  relationTo(int  child, const QAccessibleInterface*  other, int  otherChild) const;
    QAccessible::Role  role(int  child) const;
    void setText(QAccessible::Text  t, int  child, const QString&  text);
    QAccessible::State  state(int  child) const;
    QString  text(QAccessible::Text  t, int  child) const;
    int  userActionCount(int  child) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QACCESSIBLEWIDGET_H
