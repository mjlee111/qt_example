#include "./ui_texteditor.h"
#include "texteditor.h"

Editor::Editor(QWidget* parent) : QMainWindow(parent), ui(new Ui::Editor)
{
  ui->setupUi(this);
  QIcon icon(":/image/images/texteditor.png");
  setWindowIcon(icon);
  ui->filename->setReadOnly(true);
  ui->filedata->setReadOnly(true);
  ui->save->setEnabled(false);
  ui->saveas->setEnabled(false);
}

Editor::~Editor()
{
  delete ui;
}

QString Editor::openFile()
{
  QString filter = "Text Files (*.txt);;C Files (*.c);;C++ Files (*.cpp)";

  QString fileName = QFileDialog::getOpenFileName(this, "Select a file", QDir::homePath(), filter);

  if (!fileName.isEmpty())
  {
    return fileName;
  }
  else
  {
    return QString();
  }
}

QString Editor::openFolder()
{
  QString folderPath =
      QFileDialog::getExistingDirectory(this, "Select a folder", QDir::homePath(), QFileDialog::ShowDirsOnly);

  if (!folderPath.isEmpty())
  {
    return folderPath;
  }
  else
  {
    return QString();
  }
}

void Editor::editFile(QString path)
{
  QFile file(path);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QMessageBox::warning(this, "Error", "Unable to open file: " + file.errorString());
    return;
  }

  QTextStream in(&file);
  QString fileContent = in.readAll();

  ui->filedata->setPlainText(fileContent);
  file.close();
}

void Editor::on_open_clicked()
{
  file_path = openFile();
  if (!file_path.isEmpty())
  {
    ui->filename->setText(file_path);
    ui->filedata->setReadOnly(false);
    editFile(file_path);
    ui->save->setEnabled(true);
    ui->saveas->setEnabled(true);
  }
  else
  {
    ui->filename->setText("No File Selected . . .");
    ui->filedata->setReadOnly(true);
    ui->filedata->clear();
    ui->save->setEnabled(false);
    ui->saveas->setEnabled(false);
    return;
  }
}

void Editor::on_close_clicked()
{
  ui->filename->setText("No File Selected . . .");
  ui->filedata->setReadOnly(true);
  ui->filedata->clear();
  ui->save->setEnabled(false);
  ui->saveas->setEnabled(false);
}

void Editor::on_save_clicked()
{
  if (!file_path.isEmpty())
  {
    QFile file(file_path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      QMessageBox::warning(this, "Error", "Unable to save file: " + file.errorString());
      return;
    }

    QTextStream out(&file);
    out << ui->filedata->toPlainText();
    file.close();

    QMessageBox::information(this, "Save", "File saved successfully.");
  }
  else
  {
    QMessageBox::warning(this, "Error", "No file is open for saving.");
  }
}

void Editor::on_saveas_clicked()
{
  QString savePath = QFileDialog::getSaveFileName(this, "Save As", QDir::homePath(),
                                                  "Text Files (*.txt);;C Files (*.c);;C++ Files (*.cpp)");

  if (!savePath.isEmpty())
  {
    QFile file(savePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      QMessageBox::warning(this, "Error", "Unable to save file: " + file.errorString());
      return;
    }

    QTextStream out(&file);
    out << ui->filedata->toPlainText();
    file.close();

    file_path = savePath;
    ui->filename->setText(file_path);

    QMessageBox::information(this, "Save As", "File saved successfully.");
  }
  else
  {
    QMessageBox::information(this, "Save As", "No file selected.");
  }
}
