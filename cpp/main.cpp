#include "../hpp/mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QFont>

//Description
//this is just for setting some general
//styles that will apply to the whole application


void setFontstyles(QApplication &a);


void setIconStyle(QApplication &a);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    setFontstyles(a);

    setIconStyle(a);

    w.setWindowTitle("File editor");

    w.show();

    return a.exec();
}

void setFontstyles(QApplication &a )
{

    int fontId = QFontDatabase::addApplicationFont(":/new/prefix1/fonts/RedHatDisplay-VariableFont_wght.ttf");

    if(fontId == -1)
    {

        qDebug()<< "failed to load font ";

    }

    else
    {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

        QFont appFont(fontFamily);

        a.setFont(appFont);

        a.setStyleSheet("QPushButton { font-size: 12px; }");


    }
}

void setIconStyle(QApplication& a )
{

    QIcon icon(":/new/prefix1/icons/edit(1).png");

    a.setWindowIcon(icon);

}
