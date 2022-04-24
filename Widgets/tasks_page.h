#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "tasks_mode.h"
#include "TaskWidgets/task_widget.h"
#include <Widgets/number_label.h>

class TasksPage : public QWidget {
 public:
  TasksPage();
  TasksPage(const TasksMode& tasks_mode, int attempts, int tasks_count);

  void Reset(const TasksMode& tasks_mode, int attempts, int tasks_count);
  void SetAttemptsLeft(int attempts);

 private:
  TaskWidget* GenerateNewTaskWidget(int tasks_count);
  void ConnectCurrentTaskWidget();

  QVBoxLayout* layout_;
  TaskWidget* current_task_;
  TasksMode tasks_mode_;
  int attempts_left_;
  NumberLabel* attempts_label_;
};
