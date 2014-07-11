#ifndef QTSCRIPTSHELL_QACCESSIBLEINTERFACE_H
#define QTSCRIPTSHELL_QACCESSIBLEINTERFACE_H

#include <qaccessible.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAccessibleInterface : public QAccessibleInterface
{
public:
    QtScriptShell_QAccessibleInterface();
    ~QtScriptShell_QAccessibleInterface();

    QString  actionText(int  action, QAccessible::Text  t, int  child) const;
    int  childAt(int  x, int  y) const;
    int  childCount() const;
    bool  doAction(int  action, int  child, const QList<QVariant >&  params = QVariantList());
    int  indexOfChild(const QAccessibleInterface*  arg__1) const;
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

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QACCESSIBLEINTERFACE_H
