cmake_minimum_required(VERSION 3.14)
project(TerminalReminders VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Descargar e incluir FTXUI automáticamente
include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v5.0.0 # O la versión más reciente
)
FetchContent_MakeAvailable(ftxui)

# Tu ejecutable (asumiendo que mantienes la separación de archivos que hablamos antes)
add_executable(reminders_app 
    main.cpp
    recordatorio.cpp
    gestor.cpp
)

# Enlazar con las librerías de FTXUI
target_link_libraries(reminders_app PRIVATE ftxui::screen ftxui::dom ftxui::component)
