#pragma once

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QMenu>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include "number_label.h"

class MainPage : public QWidget {
  Q_OBJECT
 public:
  explicit MainPage(QWidget* parent = nullptr);

 private:
  QComboBox* mode_selector_;
  QPushButton* close_button_;
  QVBoxLayout* main_layout_;
  QPushButton* go_button_;
};
