#include "main_window.h"

#include <QMessageBox>
#include <QApplication>
#include <QCloseEvent>
#include <QMenuBar>

#include "model.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , stacked_widget_(new QStackedWidget())
    , main_page_(new MainPage())
    , tasks_page_(new TasksPage())
    , score_label_(
        new NumberLabel("Очки : ", Model::Instance()->Score())) {
  stacked_widget_->addWidget(main_page_);
  stacked_widget_->addWidget(tasks_page_);
  stacked_widget_->setCurrentWidget(main_page_);
  setCentralWidget(stacked_widget_);

  connect(
      Model::Instance(),
      &Model::PageIdChanged,
      this,
      &MainWindow::OnPageIdChanged);

  connect(
      Model::Instance(),
      &Model::ScoreChanged,
      score_label_,
      [this](){ score_label_->SetNumber(Model::Instance()->Score()); });

  menuBar()->setCornerWidget(score_label_);
  //menuBar()->layout()->addWidget(score_label_);

  SetupMenu();
}

void MainWindow::OnPageIdChanged(int previous) {
  if (Model::Instance()->GetPageId() == Model::PageId::kMainPage) {
    stacked_widget_->setCurrentWidget(main_page_);
  } else if (Model::Instance()->GetPageId() == Model::PageId::kTaskPage) {
    tasks_page_->Reset(Model::Instance()->GetTasksMode(), 1, 3);
    stacked_widget_->setCurrentWidget(tasks_page_);
  }
}

void MainWindow::closeEvent(QCloseEvent* event) {
  auto answer = QMessageBox::question(
      this,
      "Вы точно хотите выйти?",
      "Вы точно хотите выйти?");

  if (answer == QMessageBox::Yes) {
    event->accept();
    delete Model::Instance();
  } else if (answer == QMessageBox::No) {
    event->ignore();
  }
}

void MainWindow::SetupMenu() {
  //Меню:
  //  1)Возможность поменять сложность заданий (например, легкие и сложные).
  //  2)Возможность выключить/включить звук.
  //  3)Возможность сбросить текущие очки игрока. Такой же вариант должен
  //  появляться в контекстном меню при нажатии ПКМ на области, которая
  //  отображает текущие очки игрока (при нажатии на другую область приложения
  //  контекстное меню появляться не должно)
  //  4)Найстройки (сложность и наличие звука) должны сохраняться между
  //  запусками приложения.
  //

  auto* menu = menuBar()->addMenu("Меню");

  auto* change_sound = menu->addAction("Звук");
  change_sound->setCheckable(true);
  change_sound->setChecked(Model::Instance()->GetSound());

  connect(
      change_sound,
      &QAction::toggled,
      [](bool sound) { Model::Instance()->SetSound(sound); });

  auto* reset_score = menu->addAction("Сбросить очки");
  connect(
      reset_score,
      &QAction::triggered,
      [] { Model::Instance()->SetScore(0); });

  auto* close = menu->addAction("Выйти");
  connect(
      close,
      &QAction::triggered,
      [this] { this->close(); });
  close->setShortcut(QKeySequence::Close);
}
