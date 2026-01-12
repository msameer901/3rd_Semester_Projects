# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BankSystem_autogen"
  "CMakeFiles\\BankSystem_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BankSystem_autogen.dir\\ParseCache.txt"
  )
endif()
