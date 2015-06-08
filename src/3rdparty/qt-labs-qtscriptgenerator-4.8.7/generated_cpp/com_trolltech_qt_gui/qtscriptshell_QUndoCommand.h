#ifndef QTSCRIPTSHELL_QUNDOCOMMAND_H
#define QTSCRIPTSHELL_QUNDOCOMMAND_H

#include <qundostack.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QUndoCommand : public QUndoCommand
{
public:
    QtScriptShell_QUndoCommand(QUndoCommand*  parent = 0);
    QtScriptShell_QUndoCommand(const QString&  text, QUndoCommand*  parent = 0);
    ~QtScriptShell_QUndoCommand();

    int  id() const;
    bool  mergeWith(const QUndoCommand*  other);
    void redo();
    void undo();

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QUNDOCOMMAND_H
