#pragma once

#include <QLabel>

class NumberLabel : public QLabel {
 public:
  explicit NumberLabel(QString label, int number);

  void SetLabel(const QString& label);
  void SetNumber(int number);

 private:
  QString label_;
  int number_;
};


