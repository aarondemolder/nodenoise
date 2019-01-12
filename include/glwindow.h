#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QWidget>


class GLWidget;
class MainWindow;

class GLWindow : public QWidget
{
    Q_OBJECT

public:
    GLWindow(MainWindow *mw);

protected:
    void keyPressEvent(QKeyEvent *event) override;


private:

    GLWidget *glWidget;
    MainWindow *mainWindow;
};

#endif
