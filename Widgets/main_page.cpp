#include "main_page.h"

#include "tasks_mode.h"
#include "model.h"

MainPage::MainPage(QWidget* parent)
  : QWidget(parent)
  , mode_selector_(new QComboBox())
  , close_button_(new QPushButton("Выйти"))
  , main_layout_(new QVBoxLayout())
  , go_button_(new QPushButton("Вперёд!")) {
  using TM = TasksMode;
  using TMValue = enum TasksMode::Value;

  mode_selector_->addItem(TM::kPickAnOptionString);
  mode_selector_->addItem(TM::kInputAnswerString);
  mode_selector_->addItem(TM::kAudioString);
  mode_selector_->addItem(TM::kMixedString);

  connect(close_button_, &QPushButton::clicked, [this](){window()->close();});
  connect(
      go_button_,
      &QPushButton::clicked,
      []() { Model::Instance()->SetPageId(Model::kTaskPage); });
  connect(mode_selector_, &QComboBox::currentIndexChanged, [this](){
    Model::Instance()->SetTasksMode(
        TM(mode_selector_->currentText()));
  });

  main_layout_->addWidget(mode_selector_);
  main_layout_->addWidget(go_button_);
  main_layout_->addWidget(close_button_);

  mode_selector_->setCurrentIndex(0);
  Model::Instance()->SetTasksMode(TM(mode_selector_->currentText()));

  setLayout(main_layout_);
}
