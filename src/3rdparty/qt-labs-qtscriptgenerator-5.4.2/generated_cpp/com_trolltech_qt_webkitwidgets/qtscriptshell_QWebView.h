#ifndef QTSCRIPTSHELL_QWEBVIEW_H
#define QTSCRIPTSHELL_QWEBVIEW_H

#include <qwebview.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QWebView : public QWebView
{
public:
    QtScriptShell_QWebView(QWidget*  parent = 0);
    ~QtScriptShell_QWebView();

    void changeEvent(QEvent*  arg__1);
    void contextMenuEvent(QContextMenuEvent*  arg__1);
    QWebView*  createWindow(QWebPage::WebWindowType  type);
    void dragEnterEvent(QDragEnterEvent*  arg__1);
    void dragLeaveEvent(QDragLeaveEvent*  arg__1);
    void dragMoveEvent(QDragMoveEvent*  arg__1);
    void dropEvent(QDropEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    void focusInEvent(QFocusEvent*  arg__1);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  arg__1);
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    void keyPressEvent(QKeyEvent*  arg__1);
    void keyReleaseEvent(QKeyEvent*  arg__1);
    void mouseDoubleClickEvent(QMouseEvent*  arg__1);
    void mouseMoveEvent(QMouseEvent*  arg__1);
    void mousePressEvent(QMouseEvent*  arg__1);
    void mouseReleaseEvent(QMouseEvent*  arg__1);
    void wheelEvent(QWheelEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QWEBVIEW_H
