# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Smarthome_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Smarthome_autogen.dir\\ParseCache.txt"
  "Smarthome_autogen"
  )
endif()
