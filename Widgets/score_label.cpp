#include "score_label.h"

#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>

#include "model.h"

ScoreLabel::ScoreLabel(const QString& label, int number)
  : NumberLabel(label, number) {}

void ScoreLabel::contextMenuEvent(QContextMenuEvent* ev) {
  QMenu menu(this);
  QAction* reset = new QAction("Сбросить");
  menu.addAction(reset);
  connect(
      reset,
      &QAction::triggered,
      [] { Model::Instance()->SetScore(0); });

  menu.exec(ev->globalPos());
}
