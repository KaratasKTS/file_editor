#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H
#include <QDialog>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileDialog>
#include <fstream>
#include <execution>
#include <QImage>
#include <QPainter>
#include <QPdfWriter>


struct user_inputs_file_editor {

 QStringList user_input{};

 std::vector<std::string> user_input_vec{};

 std::array<std::string, 2> find_replace{"",""};

 std::string export_location{};

};

enum extention_flags{

    jpeg,
    png,
    webp,

};

namespace Ui {

class SecondWindow;

}

class SecondWindow : public QDialog
{

    Q_OBJECT

public:

    explicit SecondWindow(QWidget *parent = nullptr , bool mode = false  );

    user_inputs_file_editor file_editor_variables;

    bool m_programMode;

    void start_program(bool& mode);

    void add_refreshList();

    Ui::SecondWindow * ui;

    QStatusBar * statusBar;

    void setStackedWidget(const bool& mode);

    int file_validator();

    int inputValidation(const std::array<std::string,2>& inputs) ;

    ~SecondWindow();

private:

    void setUpConnections();

    void vectorize(const QStringList &list);

    static std::string getFileName(const std::string& url);


    void file_editor();

    void get_inputs();

    void add_file();

    void img_editor();

    void img_converter(const std::string& inputImgy);

    void text_converter(const std::string& str, const std::array<std::string, 2> &searchValue);

    void text_editor();

    void set_extentions();

    void clean_up_variables();


    std::array<std::string, 9> Extensions;



private slots :

    void getExportLocation();

    void on_exportfolder_clicked();

    void on_convert_clicked();

    void cleanUpSelections();

    void on_addfiles_clicked();
};

#endif // SECONDWINDOW_H
