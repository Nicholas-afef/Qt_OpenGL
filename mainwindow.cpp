#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    //setup some keyboard shortcuts to correspond to our button interactions
    up = new QShortcut(QKeySequence(Qt::Key_Up), this);
    QObject::connect(up, &QShortcut::activated, ui->openGLWidget, &MyGLWidget::moveUp);

    down = new QShortcut(QKeySequence(Qt::Key_Down), this);
    QObject::connect(down, &QShortcut::activated, ui->openGLWidget, &MyGLWidget::moveDown);

    left = new QShortcut(QKeySequence(Qt::Key_Left), this);
    QObject::connect(left, &QShortcut::activated, ui->openGLWidget, &MyGLWidget::moveLeft);

    right = new QShortcut(QKeySequence(Qt::Key_Right), this);
    QObject::connect(right, &QShortcut::activated, ui->openGLWidget, &MyGLWidget::moveRight);

    forward = new QShortcut(QKeySequence(Qt::Key_PageUp), this);
    QObject::connect(forward, &QShortcut::activated, ui->openGLWidget, &MyGLWidget::moveForward);

    back = new QShortcut(QKeySequence(Qt::Key_PageDown), this);
    QObject::connect(back, &QShortcut::activated, ui->openGLWidget, &MyGLWidget::moveBackward);

    QObject::connect(ui->comboBox, &QComboBox::currentIndexChanged, ui->openGLWidget, &MyGLWidget::setAxisOfRotation);
    QObject::connect(ui->spinBox, &QSpinBox::valueChanged, ui->openGLWidget, &MyGLWidget::rotateObject);
}

MainWindow::~MainWindow(){
    delete up;
    delete down;
    delete left;
    delete right;
    delete ui;
}


void MainWindow::on_actionExit_triggered(){
    QApplication::quit();
}

void MainWindow::on_actionLoad_Object_triggered(){
    QString root = QDir::currentPath();
    QFileDialog dialog;
    dialog.setNameFilter("objects(*.obj)");
    dialog.setDirectory(root);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QStringList file;
    try{
        if(dialog.exec()) file = dialog.selectedFiles();
        ui->openGLWidget->loadNewObject(file.first().toStdString());
    }
    catch(...){
        qDebug("No File Selected");
    }
}


void MainWindow::on_actionLoad_Texture_triggered(){
    QString root = QDir::currentPath();
    QFileDialog dialog;
    dialog.setNameFilter("Images(*.png *.xpm *.jpg *.bmp)");
    dialog.setDirectory(root);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QStringList file;
    try{
        if(dialog.exec()) file = dialog.selectedFiles();
        ui->openGLWidget->loadNewTexture(file.first().toStdString());
    }
    catch(...){
        qDebug("No File Selected");
    }
}


void MainWindow::on_actionAbout_triggered(){
    QMessageBox msg;
    msg.setWindowTitle("About Me");
    msg.setIcon(QMessageBox::Information);
    msg.setTextFormat(Qt::RichText);
    msg.setText("Title: OpenGL object viewer<br>Author: Nicholas Foster<br>Date Last Edited: 12/11/2021<br>Project: Fall 2021 WSU Human Computer Interaction Project<br> Github link: <a href='https://github.com/Nicholas-afef/Qt_OpenGL'>Source Code</a>");
    msg.setStandardButtons(QMessageBox::Ok);
    msg.exec();
}

