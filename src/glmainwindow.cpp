#include "glmainwindow.h"
#include "glwindow.h"

MainWindow::MainWindow()
{
    setCentralWidget(new GLWindow(this));
}
