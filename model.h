#pragma once

#include <QString>
#include <QObject>

#include "tasks_mode.h"

class Model : public QObject {
  Q_OBJECT

 public:
  enum PageId {
    kMainPage,
    kTaskPage
  };

  static Model* Instance();

  int Score();
  void SetScore(int score);

  [[nodiscard]] PageId GetPageId() const;
  void SetPageId(enum PageId page_id);

  [[nodiscard]] bool GetSound() const;
  void SetSound(bool sound);

  [[nodiscard]] const TasksMode& GetTasksMode() const;
  void SetTasksMode(const TasksMode& tasks_mode);

  virtual ~Model();

  signals:

  void PageIdChanged(int previous);
  void ScoreChanged(int previous);
  void SoundChanged();
  void TasksModeChanged(class TasksMode tasks_mode);

 private:
  static const QString kScoreSettingName;
  static const QString kSoundSettingName;

  static Model* instance_;

  Model();

  int score_;
  enum PageId page_id_;
  bool sound_;
  TasksMode tasks_mode_;
};
