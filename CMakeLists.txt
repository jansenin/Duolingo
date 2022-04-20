cmake_minimum_required(VERSION 3.20)
project(laba5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(Laba5
        resources.qrc
        main.cpp
        main_window.cpp
        Widgets/main_page.cpp
        model.cpp
        tasks_mode.cpp Widgets/number_label.cpp Widgets/number_label.h Widgets/TaskWidgets/pick_an_option.cpp Widgets/TaskWidgets/pick_an_option.h Widgets/tasks_page.cpp Widgets/tasks_page.h Widgets/TaskWidgets/task_widget.cpp Widgets/TaskWidgets/task_widget.h QuestionLoaders/pick_an_option_question_loader.cpp QuestionLoaders/pick_an_option_question_loader.h)

target_link_libraries(Laba5 Qt::Core Qt::Gui Qt::Widgets)
