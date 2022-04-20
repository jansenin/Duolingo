#include "model.h"

#include <iostream>

#include <QSettings>

const QString Model::kScoreSettingName = "score";
const QString Model::kSoundSettingName = "sound";
Model* Model::instance_ = nullptr;

Model::Model() {
  bool has_score;
  int score = QSettings().value(kScoreSettingName).toInt(&has_score);
  score_ = has_score ? score : 0;
  score_ = 10;

  bool has_sound = !QSettings().value(kSoundSettingName).isNull();
  if (has_sound) {
    sound_ = QSettings().value(kSoundSettingName).toBool();
  }
}

Model::~Model() {
  QSettings settings;
  settings.setValue(kScoreSettingName, score_);
  settings.setValue(kSoundSettingName, sound_);
}

Model* Model::Instance() {
  if (instance_ == nullptr) {
    instance_ = new Model();
  }
  return instance_;
}

enum Model::PageId Model::GetPageId() const {
  return page_id_;
}

void Model::SetPageId(enum Model::PageId page_id) {
  std::cout << "Model:" << std::endl;
  std::cout << "\tIs main page : " << (page_id == kMainPage) << std::endl;
  std::cout << "\tIs tasks page : " << (page_id == kTaskPage) << std::endl;
  enum PageId previous = page_id_;
  page_id_ = page_id;
  if (previous != page_id) {
    emit PageIdChanged(previous);
  }
}

bool Model::GetSound() const {
  return sound_;
}

void Model::SetSound(bool sound) {
  bool previous = sound_;
  sound_ = sound;
  if (previous != sound) {
    emit SoundChanged();
  }
}

int Model::Score() {
  return score_;
}

void Model::SetScore(int score) {
  int previous = score_;
  score_ = score;
  if (previous != score) {
    emit ScoreChanged(previous);
  }
}

const TasksMode& Model::GetTasksMode() const {
  return tasks_mode_;
}

void Model::SetTasksMode(const class TasksMode& tasks_mode) {
  class TasksMode previous = tasks_mode_;
  tasks_mode_ = tasks_mode;
  if (previous != tasks_mode) {
    emit TasksModeChanged(previous);
  }
}
