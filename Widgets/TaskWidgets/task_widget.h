#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QLabel>

class TaskWidget : public QWidget {
  Q_OBJECT
 public:
  explicit TaskWidget(int tasks_count, QWidget* parent = nullptr);

  virtual void NextQuestion() = 0;
  virtual void ShowCorrectAnswer() = 0;
  bool IsAnswerRevealed() const;

  [[nodiscard]] int TasksLeft() const;

 signals:

  void AnsweredCorrectly();
  void AnsweredIncorrectly();

 protected:
  QVBoxLayout* layout_;
  QPushButton* answer_button_;
  QLabel* question_text;
  int tasks_left_;
  bool is_answer_revealed;
};
