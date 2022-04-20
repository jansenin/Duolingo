#pragma once

#include "task_widget.h"
#include "QuestionLoaders/pick_an_option_question_loader.h"

class PickAnOption : public TaskWidget {
 public:
  PickAnOption(int tasks_count, QWidget* parent = nullptr);

  void NextQuestion() override;
  void ShowCorrectAnswer() override;

 private:
  std::vector<QRadioButton*> radio_buttons_;
  std::vector<const PickAnOptionQuestionLoader::Question*> questions_;
  QVBoxLayout* radio_buttons_layout;
  int question_index_;
};
