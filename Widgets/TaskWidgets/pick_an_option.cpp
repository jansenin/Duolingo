#include "pick_an_option.h"

#include <vector>

PickAnOption::PickAnOption(int tasks_count, QWidget* parent)
  : TaskWidget(tasks_count, parent)
  , questions_(PickAnOptionQuestionLoader::GetNQuestions(tasks_count))
  , radio_buttons_layout(new QVBoxLayout())
  , question_index_(-1) {
  QHBoxLayout* h_layout1 = new QHBoxLayout;
  h_layout1->setAlignment(Qt::AlignCenter);
  h_layout1->addLayout(radio_buttons_layout);

  QHBoxLayout* h_layout2 = new QHBoxLayout;
  h_layout2->setAlignment(Qt::AlignCenter);
  h_layout2->addWidget(question_text);

  layout_->addWidget(finish_button_);
  layout_->addLayout(h_layout2);
  layout_->addLayout(h_layout1);
  layout_->addWidget(answer_button_);
  layout_->addWidget(progress_bar_);

  NextQuestion();

  connect(answer_button_, &QPushButton::clicked, [this](){
    if (is_answer_revealed) {
      emit NextTaskClicked();
      return;
    }

    const PickAnOptionQuestionLoader::Question* question =
        questions_[question_index_];
    const QString correct_answer =
        question->answers[question->correct_answer_index];

    for (QRadioButton* radio_button : radio_buttons_) {
      bool is_incorrect =
          radio_button->isChecked() &&
          radio_button->text() != correct_answer;
      is_incorrect |=
          !radio_button->isChecked() &&
          radio_button->text() == correct_answer;

      if (is_incorrect) {
        emit AnsweredIncorrectly();
        return;
      }
    }

    emit AnsweredCorrectly();
  });
}

void PickAnOption::NextQuestion() {
  for (QRadioButton* radio_button : radio_buttons_) {
    radio_button->deleteLater();
  }
  radio_buttons_.clear();
  question_index_++;
  SetTasksLeft(TasksLeft() - 1);
  for (int i = 0 ; i < questions_[question_index_]->answers.size() ; ++i) {
    QRadioButton* radio_button = new QRadioButton();
    radio_button->setText(questions_[question_index_]->answers[i]);
    radio_buttons_.push_back(radio_button);

    radio_buttons_layout->addWidget(radio_button);
  }

  question_text->setText(questions_[question_index_]->question_text);
  is_answer_revealed = false;
  answer_button_->setText("??????????????????");
}

void PickAnOption::ShowCorrectAnswer() {
  const std::vector<QString>& answers =
      questions_[question_index_]->answers;
  int correct_index = questions_[question_index_]->correct_answer_index;

  for (QRadioButton* radio_button : radio_buttons_) {
    if (radio_button->text() == answers[correct_index]) {
      radio_button->setStyleSheet("color: green");
    } else {
      if (radio_button->isChecked()) {
        radio_button->setStyleSheet("color: red");
      }
    }
  }
  is_answer_revealed = true;
  answer_button_->setText("????????????");
}
