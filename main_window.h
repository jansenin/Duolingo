#pragma once

#include <QMainWindow>
#include <QStackedWidget>

#include "Widgets/main_page.h"
#include "model.h"
#include "Widgets/tasks_page.h"
#include "Widgets/score_label.h"

class MainWindow : public QMainWindow {
 public:
  explicit MainWindow(QWidget* parent = nullptr);

 protected:
  void closeEvent(QCloseEvent* event) override;

 private:
  void SetupMenu();
  void OnPageIdChanged(int previous);

  QStackedWidget* stacked_widget_;
  MainPage* main_page_;
  TasksPage* tasks_page_;

  ScoreLabel* score_label_;
};
