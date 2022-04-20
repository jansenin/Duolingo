#include "number_label.h"

#include <utility>
#include <iostream>

NumberLabel::NumberLabel(QString label, int number)
  : label_(std::move(label))
  , number_(number) {
  setText(label_ + QString::number(number_));
}

void NumberLabel::SetLabel(const QString& label) {
  label_ = label;
  setText(label_ + QString::number(number_));
}

void NumberLabel::SetNumber(int number) {
  number_ = number;
  setText(label_ + QString::number(number_));
}
