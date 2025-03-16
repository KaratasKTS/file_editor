#include "../hpp/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    setUpConnections();

    ui->label_2->setOpenExternalLinks(true);
}


// this opens the second window in the specified mode
// either file editor or image editor
void MainWindow::start_second_window(bool mode)
{
    if( !secWindow ) {

        this->secWindow = new SecondWindow(this, mode);

        secWindow->exec();
    }
    else {

        delete secWindow;

        secWindow = nullptr;

        this->secWindow = new SecondWindow(this, mode);

        secWindow->exec();
    }
}


void MainWindow::setUpConnections()
{
    connect(ui->loadfiles, &QPushButton::clicked, this , [this]{

         this->start_second_window(0);

    });

    connect(ui->loadimages2,&QPushButton::clicked, this , [this]{

        this->start_second_window(1);

    });
}


MainWindow::~MainWindow()
{
    delete ui;
}

