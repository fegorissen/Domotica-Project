cmake_minimum_required(VERSION 3.16)

project(Smarthome LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(Smarthome
  main.cpp
  Light.h
  Light.cpp
  Device.cpp
  Device.h
  Thermostat.h
  Thermostat.cpp
  Room.h
  Room.cpp
  Doorlock.cpp
  Doorlock.h
  Camera.h
  Camera.cpp

)
target_link_libraries(Smarthome Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS Smarthome
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
