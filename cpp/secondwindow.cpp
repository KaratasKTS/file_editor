#include "../hpp/secondwindow.h"
#include <QFileDialog>
#include "ui/ui_secondwindow.h"
#include "ui_secondwindow.h"
#include <QStringList>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>


SecondWindow::SecondWindow( QWidget *parent , bool mode )
    : QDialog(parent),
    ui(new Ui::SecondWindow),

    m_programMode(mode)



 {
    ui->setupUi(this);

    this->cleanUpSelections();

    this->setUpConnections();

    this->setStackedWidget(m_programMode);

    this->start_program(m_programMode);

    this->set_extentions();
 }


void SecondWindow::start_program( bool& mode )
{
    this->add_file();

}



std::string SecondWindow::getFileName( const std::string& url )
{
    std::filesystem::path filepath(url);

    auto filename = filepath.filename();

    return filename.string();

}


// checks both file inputs and word inputs for the text editor if
// invalid prompts the user to add valid data and removes the unsupported types
int SecondWindow::inputValidation( const std::array<std::string, 2> &inputs )
{

        if( inputs.at(0) == "" || inputs.at(1) == "" )

        {
            QMessageBox msg;

            msg.setWindowTitle("File editor");

            msg.resize(250, 400);

            msg.setText( "please set valid Find and Replace values and try again" );

            if ( msg.exec())
            {

                return 0;

            }
        }

        else if ( file_editor_variables.user_input_vec.empty() )

        {
            QMessageBox msg;

            msg.setWindowTitle("File editor");

            msg.resize(250, 400);

            msg.setText( "No files are selected" );

            if ( msg.exec())
            {

                return 0 ;

            }
            else
            {

                return 1;

            }

        }
        else if ( file_editor_variables.export_location == "" )
        {
            QMessageBox msg;

            msg.setWindowTitle("File editor");

            msg.resize(250, 400);

            msg.setText( "Please set Export location" );

            if ( msg.exec())
            {

                return 0 ;

            }
        }

        if ( !file_validator() )
        {

            return 0;

        }

        return 1;

}

//opens a specified file and replaces a word specified by the user
// i am using std algos
void SecondWindow::text_converter( const std::string& str, const std::array<std::string, 2>& searchValues )

{
        auto start = std::chrono::high_resolution_clock::now();

        std::ifstream file ( str );

        std::string outfilename{ file_editor_variables.export_location + "/" + getFileName (str ) };

        std::ofstream outFile( outfilename );

        std::filesystem::path filePath(str);

        std::string filepathstr = filePath.parent_path().u8string();

        std::string line{};

        if ( file.is_open() && outFile.is_open() )
        {
            while ( std::getline(file, line) )
            {

                size_t pos{0};

                if ( (pos = line.find( searchValues.at(0), pos ) ) != std::string::npos )
                {

                    line.replace( pos, searchValues.at(0).size(), searchValues.at(1) );

                    pos += searchValues.at(1).size();

                }

                outFile << line << "\n";

            }

            file.close();

            outFile.close();

        }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start ;

    std::stringstream ss;

    ss<<duration.count();

    std::string successMessage = "Your files have been edited - " + std::string("Exec time: ")+ss.str();

    this ->statusBar->showMessage(successMessage.c_str(), 5000);




}


//parallel execution of text editing function
void SecondWindow::text_editor()
{

      std::for_each(std::execution::par,

            file_editor_variables.user_input_vec.begin(),

            file_editor_variables.user_input_vec.end(),

                [&]( auto& element )
                {

                    this->text_converter(element,file_editor_variables.find_replace);

                });

}




void SecondWindow::get_inputs()
{

    file_editor_variables.find_replace = {};

    file_editor_variables.find_replace.at(0) = ui->find->text().toStdString();

    file_editor_variables.find_replace.at(1) = ui->replace->text().toStdString();

}


//executes the convertion based on the program mode either text or img
void SecondWindow::file_editor()
{

    this -> get_inputs();

        if ( inputValidation(file_editor_variables.find_replace ) )
        {

            if( !file_validator() )

                return;

            if ( !m_programMode )
            {

              this->text_editor();

            }
            else
            {

               this->img_editor();

            }


        }

}




//refreshes the list widget ui
void SecondWindow::add_refreshList()
{
    auto listWidget =  ui->listWidget;

    listWidget->clear();

    for ( const auto& item : file_editor_variables.user_input )
    {

        listWidget->addItem(item);

    }
}


void SecondWindow::setStackedWidget( const bool &mode )
{
    this-> ui->stackedWidget->setCurrentIndex(mode);

}


SecondWindow::~SecondWindow()
{

    delete ui;

    delete statusBar;
}



void SecondWindow::cleanUpSelections()
{

    file_editor_variables.user_input = {};

    file_editor_variables.user_input_vec = {};

    ui->listWidget->clear();

}

// gets user input, passes the file addresses to the ui
// and stores them to the user input variables in second
// window file_editor_variables
void SecondWindow::add_file()
{
    QFileDialog dialog;

    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())

    {

        auto list = dialog.selectedFiles();

        for (const auto& it : list )
        {

           file_editor_variables.user_input.push_back(it);

        }

        vectorize(file_editor_variables.user_input);

        add_refreshList();

    }
}

//parallel execution of image convertion function
void SecondWindow::img_editor()
{
    std::for_each(std::execution::par, file_editor_variables.user_input_vec.begin(),

        file_editor_variables.user_input_vec.end(), [this](const auto& img){

        this->img_converter(img);

    });

}

//here i am using opencv for converting file formats (i didnt realize qt had that build it)
//but for the pdf painting i am using the qt pdfwriter
void SecondWindow::img_converter( const std::string& inputImgy )
{
    auto start = std::chrono::high_resolution_clock::now();

    cv::Mat input = cv::imread( inputImgy );

    if ( input.empty() )
    {
        this->statusBar->showMessage("cant read image", 5000);

        return;
    }

    std::filesystem::path inputpath( inputImgy );

    const QString extention = ui->comboBox->currentData().toString();

    const std::filesystem::path new_out_name = inputpath.replace_extension( extention.toStdString() );

    const std::string outfile = file_editor_variables.export_location+ "/" + new_out_name.filename().u8string();

    if(extention != "pdf"){

    cv::imwrite( outfile, input );

    }
    else
    {
        QImage image( QString::fromStdString ( inputImgy ) );

        if (image.isNull()) {

            qWarning() << "Failed to load image:" << QString::fromStdString( inputImgy );

            return;
        }

        QPdfWriter pdfwriter(QString::fromStdString( outfile ));

        QPainter painter( &pdfwriter );

        painter.drawImage(0, 0, image);

        painter.end();

    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start ;

    std::stringstream ss;

    ss<<duration.count();

    std::string successMessage = "Your files have been edited - " + std::string("Exec time: ")+ss.str();

    this ->statusBar->showMessage(successMessage.c_str(), 5000);


}

void SecondWindow::set_extentions()
{

    ui->comboBox->addItem("jpg","jpg");

    ui->comboBox->addItem("webp","webp");

    ui->comboBox->addItem("png","png");

    ui->comboBox->addItem("pdf","pdf");

    ui->comboBox->addItem("bmp","bmp");

    ui->comboBox->addItem("tiff","tiff");

    Extensions = {".jpg",".webp", ".png" , ".pdf", ".bmp", ".tiff",".exe",".dll", ".lib"};

}


void SecondWindow::clean_up_variables()
{
    file_editor_variables.export_location = {};

    file_editor_variables.find_replace = { "",""};

    file_editor_variables.user_input = {};

    file_editor_variables.user_input_vec = {};

}


int  SecondWindow::file_validator()
{
    for(auto it = file_editor_variables.user_input_vec.begin(); it != file_editor_variables.user_input_vec.end(); )
    {
        std::filesystem::path path(*it);

        std::string item_extension= path.extension().u8string();

        size_t index = 0;

        if(!m_programMode)
        {
            for(const std::string& item : Extensions)
            {

            if(item_extension == item){

            QMessageBox msg;

            msg.setText("Unsupported file type");

            msg.resize(250,400);

            msg.exec();

            it = file_editor_variables.user_input_vec.erase(it);

            file_editor_variables.user_input.removeAt(index);

            ++index;

            this->statusBar->showMessage("File Cleaned, try again", 5000);

            this->add_refreshList();

            return 0;

            }
        }
    }

        return 1;

  }

    return 1;

}


void SecondWindow::getExportLocation()
{
    QFileDialog dialog;

    dialog.setFileMode(QFileDialog::Directory);

    if ( dialog.exec() )
    {
        auto dirUrl = dialog.selectedFiles();

        for ( const auto & item : dirUrl )
         {

            file_editor_variables.export_location = item.toStdString();

            QString message =  file_editor_variables.export_location.c_str();

            this ->statusBar ->  showMessage("Export location is set to " + message , 5000);

        }
    }
}


// stores the qstringlist inputs to a std::vector
void SecondWindow::vectorize(const QStringList &list)
{
    file_editor_variables.user_input_vec= {};

    for ( const auto &item : list )
    {

        file_editor_variables.user_input_vec.push_back( item.toStdString() );

    }

}


void SecondWindow::setUpConnections()
{


    connect(ui->cleanup, &QPushButton::clicked, this, &SecondWindow::cleanUpSelections);

    statusBar = new QStatusBar();

    ui->statuscontainer ->addWidget(statusBar);


}


void SecondWindow::on_exportfolder_clicked()
{

    getExportLocation();

}


void SecondWindow::on_convert_clicked()
{

    if ( this->m_programMode ){

    img_editor();

    }
    else
    {

    file_editor();

    }
}


void SecondWindow::on_addfiles_clicked()
{
    this->add_file();
}

