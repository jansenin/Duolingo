#include "task_widget.h"

#include "model.h"

TaskWidget::TaskWidget(int tasks_count, QWidget* parent)
  : QWidget(parent)
  , layout_(new QVBoxLayout())
  , answer_button_(new QPushButton("Проверить"))
  , question_text(new QLabel())
  , progress_bar_(new QProgressBar())
  , finish_button_(new QPushButton("Завершить"))
  , tasks_left_(tasks_count)
  , is_answer_revealed(false) {
  setLayout(layout_);
  progress_bar_->setRange(0, tasks_count);
  progress_bar_->setValue(0);

  connect(finish_button_, &QPushButton::clicked, []() {
    Model::Instance()->SetPageId(Model::PageId::kMainPage);
  });
}

int TaskWidget::TasksLeft() const {
  return tasks_left_;
}

bool TaskWidget::IsAnswerRevealed() const {
  return is_answer_revealed;
}

void TaskWidget::SetTasksLeft(int tasks_left) {
  tasks_left_ = tasks_left;
  progress_bar_->setValue(progress_bar_->maximum() - tasks_left - 1);
}
