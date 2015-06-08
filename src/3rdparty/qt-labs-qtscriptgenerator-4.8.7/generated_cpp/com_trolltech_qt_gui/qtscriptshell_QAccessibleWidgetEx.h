#ifndef QTSCRIPTSHELL_QACCESSIBLEWIDGETEX_H
#define QTSCRIPTSHELL_QACCESSIBLEWIDGETEX_H

#include <qaccessiblewidget.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAccessibleWidgetEx : public QAccessibleWidgetEx
{
public:
    QtScriptShell_QAccessibleWidgetEx(QWidget*  o, QAccessible::Role  r = QAccessible::Client, const QString&  name = QString());
    ~QtScriptShell_QAccessibleWidgetEx();

    QString  actionText(int  action, QAccessible::Text  t, int  child) const;
    int  childAt(int  x, int  y) const;
    int  childCount() const;
    bool  doAction(int  action, int  child, const QList<QVariant >&  params);
    int  indexOfChild(const QAccessibleInterface*  child) const;
    QVariant  invokeMethodEx(QAccessible::Method  method, int  child, const QList<QVariant >&  params);
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
    QVariant  virtual_hook(const QVariant&  data);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QACCESSIBLEWIDGETEX_H
