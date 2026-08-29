cmake_minimum_required(VERSION 3.16)
project(Smarthome LANGUAGES CXX)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(Threads REQUIRED)

set(SMARTHOME_SOURCES
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
  MathUtils.h
  LogHistory.h
  LogHistory.cpp
  DeviceFactory.cpp
  DeviceFactory.h
  MotionSensor.h
  MotionSensor.cpp
  MotionMonitor.h
  DeviceNotFoundException.h
  SmartHomeWindow.h
  SmartHomeWindow.cpp
  Rule.h
  RuleEngine.h
  RuleEngine.cpp
  House.h
  House.cpp
)

add_executable(Smarthome
  main.cpp
  ${SMARTHOME_SOURCES}
)
target_link_libraries(Smarthome Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Threads::Threads)

# vraag 44 (Object Georiënteerde Project - Aanvullend): test-driven development
add_executable(SmarthomeTests
  tests.cpp
  ${SMARTHOME_SOURCES}
)
target_link_libraries(SmarthomeTests Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Threads::Threads)

include(GNUInstallDirs)
install(TARGETS Smarthome
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
