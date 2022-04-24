#pragma once

#include <QString>

class TasksMode {
 public:
  enum Value {
    kPickAnOption,
    kInputAnswer,
    kAudio,
    kMixed,
    kUnset
  };

  static QString kPickAnOptionString;
  static QString kInputAnswerString;
  static QString kAudioString;
  static QString kMixedString;
  static QString kUnsetString;

  TasksMode();
  explicit TasksMode(QString value);
  TasksMode(enum Value value);

  QString ToString();
  Value Value();

  bool operator==(enum Value value);
  bool operator!=(enum Value value);

  bool operator==(TasksMode tasks_mode);
  bool operator!=(TasksMode tasks_mode);

 private:
  enum Value value_;
};
