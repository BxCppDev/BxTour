#-----------------------------------------------------------------------
# Enforce an out-of-source build.
#
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(STATUS "BxTour requires an out-of-source build.")
  message(STATUS "Please remove these files from ${CMAKE_BINARY_DIR} first:")
  message(STATUS "  CMakeCache.txt")
  message(STATUS "  CMakeFiles")
  message(STATUS "Once these files are removed, create a separate directory")
  message(STATUS "and run CMake from there, pointing it to:")
  message(STATUS "  ${CMAKE_SOURCE_DIR}")
  message(FATAL_ERROR "in-source build detected")
endif()

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(BxTour)

# The version number.
set(BxTour_VERSION_MAJOR 1)
set(BxTour_VERSION_MINOR 0)
set(BxTour_VERSION_STRING "${BxTour_VERSION_MAJOR}.${BxTour_VERSION_MINOR}")

find_package(Bayeux REQUIRED NO_MODULE)
if (BAYEUX_WITH_QT_GUI)
  find_package(Qt5Core    ${BAYEUX_QT5_VERSION} REQUIRED)
  find_package(Qt5Gui     ${BAYEUX_QT5_VERSION} REQUIRED)
  find_package(Qt5Widgets ${BAYEUX_QT5_VERSION} REQUIRED)
  find_package(Qt5Svg     ${BAYEUX_QT5_VERSION} REQUIRED)
endif()

set(bxtour_PROGS
  bxtour000.cxx
  bxtour001.cxx
  bxtour002.cxx
  bxtour003.cxx
  )

foreach(_bxtour_prog IN LISTS bxtour_PROGS)
  get_filename_component(_bxtour_exe ${_bxtour_prog} NAME_WE)
  add_executable(${_bxtour_exe} programs/${_bxtour_prog})
  target_link_libraries(${_bxtour_exe} Bayeux::Bayeux)
  set_target_properties(${_bxtour_exe} PROPERTIES INSTALL_RPATH_USE_LINK_PATH 1)
  install(TARGETS ${_bxtour_exe} DESTINATION bin)
  install(FILES programs/${_bxtour_prog} DESTINATION share/BxTour-${BxTour_VERSION_STRING}/examples/)
endforeach()

# - end