# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\UI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\UI_autogen.dir\\ParseCache.txt"
  "UI_autogen"
  )
endif()
