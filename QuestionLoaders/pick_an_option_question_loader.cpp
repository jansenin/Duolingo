#include "pick_an_option_question_loader.h"

#include <algorithm>

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QRandomGenerator>

using POQL = PickAnOptionQuestionLoader;

std::vector<POQL::Question> POQL::questions_;

void POQL::LoadQuestions() {
  questions_.clear();

  QFile questions_file(":/Resources/Questions/pick_an_option_questions.json");
  questions_file.open(QFile::ReadOnly | QIODevice::Text);
  QByteArray bytes = questions_file.readAll();
  QJsonDocument document = QJsonDocument::fromJson(bytes);
  QJsonArray questions = document["questions"].toArray();

  questions_.reserve(questions.size());
  for (int i = 0 ; i < questions.size() ; ++i) {
    QJsonObject question = questions.at(i).toObject();

    QString question_text = question["text"].toString();
    QJsonArray answers_json = question["answers"].toArray();
    int correct_answer_index = question["correctAnswerIndex"].toInt();

    std::vector<QString> answers;
    for (int j = 0 ; j < answers_json.size() ; ++j) {
      answers.push_back(answers_json[j].toString());
    }

    questions_.emplace_back(
        question_text,
        answers,
        correct_answer_index);
  }
}

const std::vector<POQL::Question>& POQL::GetQuestions() {
  return questions_;
}

std::vector<const POQL::Question*> POQL::GetNQuestions(int n) {
  if (n > questions_.size()) {
    throw std::invalid_argument(
        "there is no " +
        std::to_string(n) +
        " questions, only " +
        std::to_string(questions_.size()) +
        " are available");
  }
  std::vector<int> indexes;
  indexes.reserve(n);
  for (int i = 0 ; i < n ; ++i) {
    int index = QRandomGenerator::global()->bounded(0, n);
    while (std::count(indexes.begin(), indexes.end(), index) > 0) {
      index = QRandomGenerator::global()->bounded(0, n);
    }
    indexes.push_back(index);
  }

  std::vector<const Question*> result;
  result.reserve(n);
  for (int i : indexes) {
    result.push_back(&questions_[i]);
  }

  return result;
}

POQL::Question::Question(
    QString  question_text,
    std::vector<QString>  answers,
    int correct_answer_index)
    : question_text(std::move(question_text))
    , answers(std::move(answers))
    , correct_answer_index(correct_answer_index) {}
