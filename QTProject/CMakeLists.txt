# CMakeList.txt : CMake project for QTProject, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (QTProject "QTProject.cpp" "QTProject.h" "ChessGame.cpp" "ChessGame.h" "Chessboard.cpp" "Chessboard.h" "Pieces.cpp" "Pieces.h")

# find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

#target_link_libraries(QTProject
#	Qt6::Widgets
#	Qt6::Gui
#	Qt6::Core
#)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET QTProject PROPERTY CXX_STANDARD 20)
endif()

set(CMAKE_CXX_STANDARD 17)


target_compile_options(QTProject PUBLIC "/Zc:__cplusplus")

# TODO: Add tests and install targets if needed.
#include_directories(QTProject "C:/ProgrammingTools/QT/6.6.0/msvc2019_64/include")

