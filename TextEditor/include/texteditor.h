#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Editor;
}
QT_END_NAMESPACE

class Editor : public QMainWindow
{
  Q_OBJECT

public:
  Editor(QWidget* parent = nullptr);
  ~Editor();

private slots:
  void on_open_clicked();
  void on_close_clicked();
  void on_save_clicked();
  void on_saveas_clicked();

private:
  Ui::Editor* ui;
  QString file_path;

  QString openFile();
  QString openFolder();
  void editFile(QString path);
};
#endif  // TEXTEDITOR_H
