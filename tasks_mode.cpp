#include "tasks_mode.h"

QString TasksMode::kPickAnOptionString = "Выбери вариант";
QString TasksMode::kInputAnswerString = "Введи ответ";
QString TasksMode::kAudioString = "Аудио";
QString TasksMode::kMixedString = "Смешанное";
QString TasksMode::kUnsetString = "Unset";

TasksMode::TasksMode(QString value) {
  if (value == kPickAnOptionString) {
    this->value_ = Value::kPickAnOption;
  } else if (value == kInputAnswerString) {
    this->value_ = Value::kInputAnswer;
  } else if (value == kAudioString) {
    this->value_ = Value::kAudio;
  } else if (value == kMixedString) {
    this->value_ = Value::kMixed;
  } else {
    throw std::invalid_argument(
        "Task mode is incorrect(\"" + value.toStdString() + "\")");
  }
}

TasksMode::TasksMode(enum TasksMode::Value value) : value_(value) {}

TasksMode::TasksMode() : value_(TasksMode::kUnset) {}

enum TasksMode::Value TasksMode::Value() {
  return value_;
}

QString TasksMode::ToString() {
  if (value_ == kPickAnOption) {
    return kPickAnOptionString;
  } else if (value_ == kInputAnswer) {
    return kInputAnswerString;
  } else if (value_ == kAudio) {
    return kAudioString;
  } else if (value_ == kMixed) {
    return kMixedString;
  } else if (value_ == kUnset) {
    return kUnsetString;
  }
  throw std::runtime_error("unknown member of TaskMode enum");
}

bool TasksMode::operator==(enum TasksMode::Value value) {
  return value_ == value;
}

bool TasksMode::operator!=(enum TasksMode::Value value) {
  return value_ == value;
}

bool TasksMode::operator==(TasksMode tasks_mode) {
  return value_ == tasks_mode.value_;
}

bool TasksMode::operator!=(TasksMode tasks_mode) {
  return value_ != tasks_mode.value_;
}
