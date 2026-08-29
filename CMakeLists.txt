cmake_minimum_required(VERSION 3.16)
project(Smarthome LANGUAGES CXX)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
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
)

add_executable(Smarthome
  main.cpp
  ${SMARTHOME_SOURCES}
)
target_link_libraries(Smarthome Qt${QT_VERSION_MAJOR}::Core Threads::Threads)

# vraag 44 (Object Georiënteerde Project - Aanvullend): test-driven development
# Apart build-doel, hergebruikt dezelfde klassen als het hoofdprogramma
# maar met tests.cpp i.p.v. main.cpp -- kan onafhankelijk gebouwd en
# uitgevoerd worden (in Qt Creator: kies "SmarthomeTests" als actief
# build-doel via de Kit-selector onderaan links).
add_executable(SmarthomeTests
  tests.cpp
  ${SMARTHOME_SOURCES}
)
target_link_libraries(SmarthomeTests Qt${QT_VERSION_MAJOR}::Core Threads::Threads)

include(GNUInstallDirs)
install(TARGETS Smarthome
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
