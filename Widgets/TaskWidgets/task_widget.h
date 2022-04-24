#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QLabel>
#include <QProgressBar>

class TaskWidget : public QWidget {
  Q_OBJECT
 public:
  explicit TaskWidget(int tasks_count, QWidget* parent = nullptr);

  virtual void NextQuestion() = 0;
  virtual void ShowCorrectAnswer() = 0;
  bool IsAnswerRevealed() const;

  [[nodiscard]] int TasksLeft() const;
  void SetTasksLeft(int tasks_left);

 signals:

  void AnsweredCorrectly();
  void AnsweredIncorrectly();
  void NextTaskClicked();

 protected:
  QVBoxLayout* layout_;
  QPushButton* answer_button_;
  QLabel* question_text;
  QProgressBar* progress_bar_;
  QPushButton* finish_button_;
  bool is_answer_revealed;

 private:
  int tasks_left_;
};
