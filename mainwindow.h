#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:

private slots:

    void on_actionExit_triggered();
    void on_actionLoad_Object_triggered();
    void on_actionLoad_Texture_triggered();
    void on_actionAbout_triggered();


private:
    Ui::MainWindow *ui;
    QShortcut* up;
    QShortcut* down;
    QShortcut* left;
    QShortcut* right;
    QShortcut* forward;
    QShortcut* back;
};

#endif // MAINWINDOW_H
