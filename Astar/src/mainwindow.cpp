#include "./ui_mainwindow.h"
#include "mainwindow.hpp"

mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mainwindow), startPoint(-1, -1),
      endPoint(-1, -1) {
  ui->setupUi(this);
  QIcon icon(":/image/images/astar.png");
  setWindowIcon(icon);
}

mainwindow::~mainwindow() { delete ui; }

void mainwindow::initializeMap(int rows, int cols) {
  map = QVector<QVector<int>>(rows, QVector<int>(cols, 0));
  drawGrid(rows, cols);
}

void mainwindow::drawGrid(int rows, int cols) {
  QLayoutItem *item;
  while ((item = ui->astar_layout->takeAt(0)) != nullptr) {
    delete item->widget();
    delete item;
  }

  ui->astar_layout->setSpacing(0);
  ui->astar_layout->setContentsMargins(0, 0, 0, 0);

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      QPushButton *cell = new QPushButton("");
      cell->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      cell->setStyleSheet(
          "background-color: white; border: 0.5px solid black;");

      connect(cell, &QPushButton::clicked, [this, r, c, cell]() {
        if (!isSetStart && !isSetEnd) {
          if (map[r][c] == 2 || map[r][c] == 3) {
            map[r][c] = 0;
            cell->setStyleSheet(
                "background-color: white; border: 0.5px solid black;");
          } else if (map[r][c] == 1) {
            map[r][c] = 0;
            cell->setStyleSheet(
                "background-color: white; border: 0.5px solid black;");
          }
          map[r][c] = 1;
          cell->setStyleSheet(
              "background-color: black; border: 0.5px solid black;");
        } else if (isSetStart && !isSetEnd) {
          replacePoint(2, r, c, "green");
          startPoint = QPoint(r, c);
          isSetStart = false;
        } else if (!isSetStart && isSetEnd) {
          replacePoint(3, r, c, "red");
          endPoint = QPoint(r, c);
          isSetEnd = false;
        }
      });

      ui->astar_layout->addWidget(cell, r, c);
    }
  }
}

void mainwindow::replacePoint(int pointType, int newRow, int newCol,
                              const QString &color) {
  for (int r = 0; r < map.size(); ++r) {
    for (int c = 0; c < map[r].size(); ++c) {
      if (map[r][c] == pointType) {
        map[r][c] = 0;
        QPushButton *cell = qobject_cast<QPushButton *>(
            ui->astar_layout->itemAtPosition(r, c)->widget());
        if (cell) {
          cell->setStyleSheet(
              "background-color: white; border: 0.5px solid black;");
        }
      }
    }
  }
  map[newRow][newCol] = pointType;
  QPushButton *cell = qobject_cast<QPushButton *>(
      ui->astar_layout->itemAtPosition(newRow, newCol)->widget());
  if (cell) {
    cell->setStyleSheet(
        QString("background-color: %1; border: 0.5px solid black;").arg(color));
  }
}

void mainwindow::findPath() {
  if (startPoint.x() == -1 || startPoint.y() == -1 || endPoint.x() == -1 ||
      endPoint.y() == -1) {
    QMessageBox::warning(this, "Error", "Start and end points must be set!");
    return;
  }

  Astar astar;
  Astar::Grid grid(map.size(), std::vector<int>(map[0].size(), 0));

  for (int r = 0; r < map.size(); ++r) {
    for (int c = 0; c < map[r].size(); ++c) {
      if (map[r][c] == 2) {
        grid[r][c] = 0;
      } else if (map[r][c] == 3) {
        grid[r][c] = 0;
      } else {
        grid[r][c] = map[r][c];
      }
    }
  }

  auto path = astar.findPath(grid, {startPoint.x(), startPoint.y()},
                             {endPoint.x(), endPoint.y()});

  if (path.empty()) {
    QMessageBox::information(this, "No Path",
                             "No path found between start and end points.");
    return;
  }

  for (const auto &p : path) {
    QPushButton *cell = qobject_cast<QPushButton *>(
        ui->astar_layout->itemAtPosition(p.first, p.second)->widget());
    if (cell && !(p.first == startPoint.x() && p.second == startPoint.y()) &&
        !(p.first == endPoint.x() && p.second == endPoint.y())) {
      cell->setStyleSheet("background-color: blue; border: 0.5px solid black;");
    }
  }
}

void mainwindow::on_generate_clicked() {
  initializeMap(ui->row->value(), ui->col->value());
  ui->set_start->setEnabled(true);
  ui->set_end->setEnabled(true);
  ui->astar_start->setEnabled(true);
}

void mainwindow::on_set_start_clicked() {
  isSetStart = true;
  isSetEnd = false;
}

void mainwindow::on_set_end_clicked() {
  isSetStart = false;
  isSetEnd = true;
}

void mainwindow::on_astar_start_clicked() { findPath(); }

void mainwindow::on_reset_clicked() {
  startPoint = QPoint(-1, -1);
  endPoint = QPoint(-1, -1);
  isSetStart = false;
  isSetEnd = false;
  ui->set_start->setEnabled(false);
  ui->set_end->setEnabled(false);
  ui->astar_start->setEnabled(false);
  map.clear();
  QLayoutItem *item;
  while ((item = ui->astar_layout->takeAt(0)) != nullptr) {
    delete item->widget();
    delete item;
  }
}
