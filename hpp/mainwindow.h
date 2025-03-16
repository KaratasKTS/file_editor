#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include "./secondwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


private:

    SecondWindow * secWindow{nullptr};

    void start_second_window(bool mode);

    void setUpConnections();

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
