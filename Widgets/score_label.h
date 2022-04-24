#pragma once

#include "number_label.h"

class ScoreLabel : public NumberLabel {
 public:
  ScoreLabel(const QString& label, int number);

 protected:
  void contextMenuEvent(QContextMenuEvent* ev) override;
};


