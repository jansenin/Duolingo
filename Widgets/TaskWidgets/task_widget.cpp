#include "task_widget.h"

TaskWidget::TaskWidget(int tasks_count, QWidget* parent)
  : QWidget(parent)
  , layout_(new QVBoxLayout())
  , answer_button_(new QPushButton("Проверить"))
  , question_text(new QLabel())
  , tasks_left_(tasks_count)
  , is_answer_revealed(false) {
  setLayout(layout_);
}

int TaskWidget::TasksLeft() const {
  return tasks_left_;
}

bool TaskWidget::IsAnswerRevealed() const {
  return is_answer_revealed;
}
