#include <QMainWindow>

class RDocumentInterface;

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow() {}

protected:
    virtual void showEvent(QShowEvent* event);

private:
    RDocumentInterface* documentInterface;
};
