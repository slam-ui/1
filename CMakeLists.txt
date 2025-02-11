cmake_minimum_required(VERSION 3.15)
project(MyQtApp)

# Указываем, где искать модули CMake для Qt
set(QT_DIR "C:/Qt/6.8.2/mingw_64")

# Находим необходимые компоненты Qt
find_package(Qt6 REQUIRED PATHS ${QT_DIR} NO_DEFAULT_PATH COMPONENTS Core Gui Widgets)

# Добавляем исполняемый файл с использованием qt_add_executable
qt_add_executable(MyQtApp
        main.cpp
)

# Подключаем необходимые модули Qt к нашему проекту
target_link_libraries(MyQtApp PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

# Убедитесь, что moc-файлы генерируются автоматически
set_target_properties(MyQtApp PROPERTIES AUTOMOC TRUE)