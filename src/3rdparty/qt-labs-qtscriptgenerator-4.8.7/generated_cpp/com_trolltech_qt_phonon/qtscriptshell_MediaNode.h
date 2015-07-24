#ifndef QTSCRIPTSHELL_MEDIANODE_H
#define QTSCRIPTSHELL_MEDIANODE_H

#include <medianode.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_MediaNode : public Phonon::MediaNode
{
public:
    ~QtScriptShell_MediaNode();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_MEDIANODE_H
