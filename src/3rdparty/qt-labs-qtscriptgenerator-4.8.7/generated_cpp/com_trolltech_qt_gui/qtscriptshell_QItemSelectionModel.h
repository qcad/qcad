#ifndef QTSCRIPTSHELL_QITEMSELECTIONMODEL_H
#define QTSCRIPTSHELL_QITEMSELECTIONMODEL_H

#include <qitemselectionmodel.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QItemSelectionModel : public QItemSelectionModel
{
public:
    QtScriptShell_QItemSelectionModel(QAbstractItemModel*  model);
    QtScriptShell_QItemSelectionModel(QAbstractItemModel*  model, QObject*  parent);
    ~QtScriptShell_QItemSelectionModel();

    void childEvent(QChildEvent*  arg__1);
    void clear();
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void reset();
    void select(const QItemSelection&  selection, QItemSelectionModel::SelectionFlags  command);
    void select(const QModelIndex&  index, QItemSelectionModel::SelectionFlags  command);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QITEMSELECTIONMODEL_H
