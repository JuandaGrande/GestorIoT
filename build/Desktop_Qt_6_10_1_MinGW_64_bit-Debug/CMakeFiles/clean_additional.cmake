# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Gestor_IoT_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Gestor_IoT_autogen.dir\\ParseCache.txt"
  "Gestor_IoT_autogen"
  )
endif()
