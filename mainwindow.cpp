#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "huffmanCompressorHeader.h"
#include "minify.h"
#include "parsing_xml.h"
#include "indentaion.h"
#include "xmljson.h"
#include "form_tree.h"
#include "xml_validator.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // Opens a dialog that allows you to select a file to open
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    // An object for reading and writing files
    QFile file(fileName);

    // Store the currentFile name
    //currentFile = fileName;

    // Try to open the file as a read only file if possible or display a
    // warning dialog box
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    // Set the title for the window to the file name
    //setWindowTitle(fileName);

    // Interface for reading text
    QTextStream in(&file);

    // Copy text in the string
    QString text = in.readAll();

    // Put the text in the textEdit widget
    ui->textBrowser->setText(text);
    ui->label_2->setText(fileName);
    ui->textBrowser->setLineWrapColumnOrWidth(QTextEdit::NoWrap);

    // Close the file
    file.close();

    string current_locale_text = fileName.toLocal8Bit().constData();

    huffman h(current_locale_text, "output-compressed.txt");
    h.compressor_driver();


    // Opens a dialog that allows you to select a file to open
    //QString fileName1 = QFileDialog::getOpenFileName(this, "Open the file");

    // An object for reading and writing files
    QFile file1("output-compressed.txt");

    // Store the currentFile name
    //currentFile = fileName;

    // Try to open the file as a read only file if possible or display a
    // warning dialog box
    if (!file1.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file1.errorString());
        return;
    }

    // Set the title for the window to the file name
    //setWindowTitle("output.txt");

    // Interface for reading text
    QTextStream in1(&file1);

    // Copy text in the string
    QString text1 = in1.readAll();

    // Put the text in the textEdit widget
    ui->textBrowser_2->setText(text1);
    ui->label_3->setText("output-compressed.txt");
    ui->textBrowser_2->setLineWrapColumnOrWidth(QTextEdit::NoWrap);
    QMessageBox::information(this, tr("Notice"), tr("File was saved as output-compressed.txt"));

    // Close the file
    file1.close();
}


void MainWindow::on_pushButton_2_clicked()
{
    // Opens a dialog that allows you to select a file to open
    //QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    // An object for reading and writing files
    QFile file("output-compressed.txt");

    // Store the currentFile name
    //currentFile = fileName;

    // Try to open the file as a read only file if possible or display a
    // warning dialog box
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    // Set the title for the window to the file name
    //setWindowTitle("output.txt");

    // Interface for reading text
    QTextStream in(&file);

    // Copy text in the string
    QString text = in.readAll();

    // Put the text in the textEdit widget
    ui->textBrowser->setText(text);
    ui->label_2->setText("output-compressed.txt");
    ui->textBrowser->setLineWrapColumnOrWidth(QTextEdit::NoWrap);

    // Close the file
    file.close();

    //string current_locale_text = file.toLocal8Bit().constData();



    huffman h("output-compressed.txt", "orignial.txt");
    h.decompressor_driver();
    //       h.recreate_huffman_tree();
    //       h.save_decode();



    // Opens a dialog that allows you to select a file to open
    //QString fileName1 = QFileDialog::getOpenFileName(this, "Open the file");

    // An object for reading and writing files
    QFile file1("orignial.txt");

    // Store the currentFile name
    //currentFile = fileName;

    // Try to open the file as a read only file if possible or display a
    // warning dialog box
    if (!file1.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file1.errorString());
        return;
    }

    // Set the title for the window to the file name
    //setWindowTitle("orignial.txt");

    // Interface for reading text
    QTextStream in1(&file1);

    // Copy text in the string
    QString text1 = in1.readAll();

    // Put the text in the textEdit widget
    ui->textBrowser_2->setText(text1);
    ui->label_3->setText("orignial.txt");
    ui->textBrowser_2->setLineWrapColumnOrWidth(QTextEdit::NoWrap);

    QMessageBox::information(this, tr("Notice"), tr("File was saved as orignial.txt"));

    // Close the file
    file1.close();
}


void MainWindow::on_pushButton_3_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    //setWindowTitle(fileName);

    QTextStream in(&file);

    QString text = in.readAll();

    ui->textBrowser->setText(text);
    ui->label_2->setText(fileName);
    ui->textBrowser->setLineWrapColumnOrWidth(QTextEdit::NoWrap);

    file.close();

    string current_locale_text = fileName.toLocal8Bit().constData();

    parsing_xml(current_locale_text);
    indentation("output-cutter.txt", "output-indent.txt");
    QFile file1("output-indent.txt");

    if (!file1.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file1.errorString());
        return;
    }

    //setWindowTitle("output-indent.txt");

    QTextStream in1(&file1);

    QString text1 = in1.readAll();

    ui->textBrowser_2->setText(text1);
    ui->label_3->setText("output-indent.txt");
    ui->textBrowser_2->setLineWrapColumnOrWidth(QTextEdit::NoWrap);

    QMessageBox::information(this, tr("Notice"), tr("File was saved as output-indent.txt"));

    file1.close();
}


void MainWindow::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    //setWindowTitle(fileName);

    QTextStream in(&file);

    QString text = in.readAll();

    ui->textBrowser->setText(text);
    ui->label_2->setText(fileName);
    ui->textBrowser->setLineWrapColumnOrWidth(QTextEdit::NoWrap);

    file.close();

    string current_locale_text = fileName.toLocal8Bit().constData();

    parsing_xml(current_locale_text);
    minify("output-cutter.txt");
    QFile file1("output-minify.txt");

    if (!file1.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file1.errorString());
        return;
    }

    //setWindowTitle("output-minify.txt");

    QTextStream in1(&file1);

    QString text1 = in1.readAll();

    ui->textBrowser_2->setText(text1);
    ui->label_3->setText("output-minify.txt");
    ui->textBrowser_2->setLineWrapColumnOrWidth(QTextEdit::NoWrap);

    QMessageBox::information(this, tr("Notice"), tr("File was saved as output-minify.txt"));

    file1.close();
}


void MainWindow::on_pushButton_5_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    //setWindowTitle(fileName);

    QTextStream in(&file);

    QString text = in.readAll();

    ui->textBrowser->setText(text);
    ui->label_2->setText(fileName);
    ui->textBrowser->setLineWrapColumnOrWidth(QTextEdit::NoWrap);

    file.close();

    string current_locale_text = fileName.toLocal8Bit().constData();

    driverjson(current_locale_text);



    QFile file1("output-json.txt");

    if (!file1.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file1.errorString());
        return;
    }

    //setWindowTitle("json.txt");

    QTextStream in1(&file1);

    QString text1 = in1.readAll();

    ui->textBrowser_2->setText(text1);
    ui->label_3->setText("output-json.txt");
    ui->textBrowser_2->setLineWrapColumnOrWidth(QTextEdit::NoWrap);

    QMessageBox::information(this, tr("Notice"), tr("File was saved as output-json.txt"));

    file1.close();






}


void MainWindow::on_pushButton_6_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    //setWindowTitle(fileName);

    QTextStream in(&file);

    QString text = in.readAll();

    ui->textBrowser->setText(text);
    ui->label_2->setText(fileName);
    ui->textBrowser->setLineWrapColumnOrWidth(QTextEdit::NoWrap);

    file.close();

    string current_locale_text = fileName.toLocal8Bit().constData();



    xml_tree tree;
    form_tree(tree, current_locale_text);
    vector <int> error_line;
    int num_of_errors = 0;
    xml_validator(error_line, "output-cutter.txt", num_of_errors);
    indentation("output-validated.txt", "output-validated-indented.txt");



    QFile file1("output-validated-indented.txt");

    if (!file1.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file1.errorString());
        return;
    }


    //QMessageBox::information(this, tr("Error number") ,tr((num_of_errors)));
    //setWindowTitle("json.txt");

    QTextStream in1(&file1);

    QString text1 = in1.readAll();

    ui->textBrowser_2->setText(text1);
    ui->label_3->setText("output-validated-indented.txt");
    ui->textBrowser_2->setLineWrapColumnOrWidth(QTextEdit::NoWrap);

    QString status = QString("File was saved as output-validated-indented.txt\nAnd Found %1 Error(s) in the File.").arg(num_of_errors);
    QMessageBox::information(this, tr("Info"), status);
    //QMessageBox::information(this, tr("Notice"), tr("File was saved as output-validated-indented.txt\nAnd "));

    file1.close();
}

