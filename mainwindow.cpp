#include "mainwindow.h"
// #include "./ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      // ui(new Ui::MainWindow)

{
    // ui->setupUi(this);
    // setupUI();

}

MainWindow::~MainWindow()
{
    // delete ui;
}



void MainWindow::setupUI()
{
    // 设置主窗口
    setWindowTitle("2048面向世界");
    resize(600, 700);

}

