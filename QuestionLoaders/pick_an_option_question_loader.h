#pragma once

#include <vector>

#include <QString>

class PickAnOptionQuestionLoader {
 public:
  struct Question {
    Question(QString question_text,
             std::vector<QString> answers,
             int correct_answer_index);

    QString question_text;
    std::vector<QString> answers;
    int correct_answer_index;
  };

  static void LoadQuestions();
  static const std::vector<Question>& GetQuestions();
  static std::vector<const Question*> GetNQuestions(int n);

 private:
  static std::vector<Question> questions_;
};
