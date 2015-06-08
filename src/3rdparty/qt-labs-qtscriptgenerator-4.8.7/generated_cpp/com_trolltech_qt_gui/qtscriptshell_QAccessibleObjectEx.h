#ifndef QTSCRIPTSHELL_QACCESSIBLEOBJECTEX_H
#define QTSCRIPTSHELL_QACCESSIBLEOBJECTEX_H

#include <qaccessibleobject.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAccessibleObjectEx : public QAccessibleObjectEx
{
public:
    QtScriptShell_QAccessibleObjectEx(QObject*  object);
    ~QtScriptShell_QAccessibleObjectEx();

    QString  actionText(int  action, QAccessible::Text  t, int  child) const;
    int  childAt(int  x, int  y) const;
    int  childCount() const;
    bool  doAction(int  action, int  child, const QList<QVariant >&  params);
    int  indexOfChild(const QAccessibleInterface*  arg__1) const;
    QVariant  invokeMethodEx(QAccessible::Method  method, int  child, const QList<QVariant >&  params);
    bool  isValid() const;
    int  navigate(QAccessible::RelationFlag  relation, int  index, QAccessibleInterface**  iface) const;
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

#endif // QTSCRIPTSHELL_QACCESSIBLEOBJECTEX_H
