#include <QApplication>
#include <QTranslator>
#include <QCloseEvent>
#include <QWidget>

#include "main_window.h"
#include "QuestionLoaders/pick_an_option_question_loader.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  QCoreApplication::setOrganizationName("MyOrganization");
  QCoreApplication::setApplicationName("Duolingo clone");

  PickAnOptionQuestionLoader::LoadQuestions();

  MainWindow main_window = MainWindow();
  main_window.show();

  return QApplication::exec();
}
