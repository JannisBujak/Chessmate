# CMakeList.txt : CMake project for Chessmate, include source and define
# project specific logic here.
#

# Add source to this project's executable.
file(GLOB CPP . *.cpp)
file(GLOB HPP . *.h)

add_executable (Chessmate ${HPP} ${CPP})

set_target_properties(Chessmate PROPERTIES AUTOMOC TRUE)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

target_link_libraries(Chessmate
	Qt6::Widgets
	Qt6::Gui
	Qt6::Core
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Chessmate PROPERTY CXX_STANDARD 20)
endif()

set(CMAKE_CXX_STANDARD 20)


if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")
else(MSVC)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
endif(MSVC) 


# TODO: Add tests and install targets if needed.
include_directories(Chessmate "$ENV{QTDIR}/include")
