#include "tasks_page.h"

#include "TaskWidgets/pick_an_option.h"
#include "model.h"

TasksPage::TasksPage()
  : QWidget()
  , layout_(new QVBoxLayout())
  , current_task_(nullptr) {
  setLayout(layout_);
}

TasksPage::TasksPage(
    const TasksMode& tasks_mode,
    int attempts,
    int tasks_count) : TasksPage() {
  tasks_mode_ = tasks_mode;
  attempts_left_ = attempts;

  current_task_ = GenerateNewTaskWidget(tasks_count);
  layout_->addWidget(current_task_);
  ConnectCurrentTaskWidget();
}

void TasksPage::ConnectCurrentTaskWidget() {
  connect(current_task_, &TaskWidget::AnsweredCorrectly, [this](){
    if (!current_task_->IsAnswerRevealed()) {
      current_task_->ShowCorrectAnswer();
      return;
    }
    if (current_task_->TasksLeft() <= 0) {
      Model::Instance()->SetScore(Model::Instance()->Score() + 1);
      Model::Instance()->SetPageId(Model::PageId::kMainPage);
    } else {
      current_task_->NextQuestion();
    }
  });
  connect(current_task_, &TaskWidget::AnsweredIncorrectly, [this](){
    if (!current_task_->IsAnswerRevealed()) {
      current_task_->ShowCorrectAnswer();
      return;
    }
    --attempts_left_;
    if (attempts_left_ < 0) {
      Model::Instance()->SetPageId(Model::PageId::kMainPage);
    }
  });
}

void TasksPage::Reset(
    const TasksMode& tasks_mode,
    int attempts,
    int tasks_count) {
  tasks_mode_ = tasks_mode;
  attempts_left_ = attempts;
  if (current_task_ != nullptr) {
    current_task_->deleteLater();
  }
  current_task_ = GenerateNewTaskWidget(tasks_count);
  layout_->addWidget(current_task_);
  ConnectCurrentTaskWidget();
}

TaskWidget* TasksPage::GenerateNewTaskWidget(int tasks_count) {
  using TM = TasksMode;
  using TMValue = enum TM::Value;

  if (tasks_mode_ == TMValue::kPickAnOption) {
    return new PickAnOption(tasks_count);
  } else if (tasks_mode_ == TMValue::kInputAnswer) {
    return nullptr;
  } else if (tasks_mode_ == TMValue::kAudio) {
    return nullptr;
  } else if (tasks_mode_ == TMValue::kMixed) {
    return nullptr;
  }
  return nullptr;
}
