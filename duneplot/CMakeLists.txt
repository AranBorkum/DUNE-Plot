# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(DAQWork)
# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net XMLIO)
#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(DUNE-Plot SHARED Neutron.cxx)
target_link_libraries(DUNE-Plot ${ROOT_LIBRARIES})

#link_directories(build)

add_executable(Neutron Neutron.cxx)
target_link_libraries(Neutron DUNE-Plot)

add_executable(MultiPrim MultiPrim.cxx)
target_link_libraries(MultiPrim DUNE-Plot)

add_executable(GEANTCutOff GEANTCutOff.cxx)
target_link_libraries(GEANTCutOff DUNE-Plot)

add_executable(quick quick.cxx)
target_link_libraries(quick DUNE-Plot)