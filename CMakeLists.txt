set (CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.1.2)
cmake_policy(SET CMP0015 NEW) # Link Directory Pathing
set(CMAKE_DEBUG_POSTFIX _d)

project(xmscore)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CONAN_INCLUDE_DIRS})
link_directories(${CONAN_LIB_DIRS})

set(xmscore_sources
  xmscore/math/math.cpp
  xmscore/misc/DynBitset.cpp
  xmscore/misc/Observer.cpp
  xmscore/misc/Progress.cpp
  xmscore/misc/Singleton.cpp
  xmscore/misc/StringUtil.cpp
  xmscore/misc/XmError.cpp
  xmscore/misc/XmLog.cpp
  xmscore/points/functors.cpp
  xmscore/points/pt.cpp
  xmscore/stl/vector.cpp
)

set(xmscore_headers
  xmscore/math/math.h
  xmscore/misc/base_macros.h
  xmscore/misc/boost_defines.h
  xmscore/misc/carray.h
  xmscore/misc/color_defines.h
  xmscore/misc/DynBitset.h
  xmscore/misc/environment.h
  xmscore/misc/Observer.h
  xmscore/misc/Progress.h
  xmscore/misc/Singleton.h
  xmscore/misc/StringUtil.h
  xmscore/misc/XmConst.h
  xmscore/misc/XmError.h
  xmscore/misc/XmLog.h
  xmscore/misc/xmstype.h
  xmscore/points/functors.h
  xmscore/points/pt.h
  xmscore/points/ptsfwd.h
  xmscore/stl/deque.h
  xmscore/stl/hash.h
  xmscore/stl/list.h
  xmscore/stl/map.h
  xmscore/stl/set.h
  xmscore/stl/utility.h
  xmscore/stl/vector.h
)

add_definitions(-DCXX_TEST -DCXXTEST4)

list(APPEND xmscore_headers
    xmscore/math/math.t.h
    xmscore/misc/Observer.t.h
    xmscore/misc/Progress.t.h
    xmscore/misc/StringUtil.t.h
    xmscore/misc/XmError.t.h
    xmscore/misc/XmLog.t.h
    xmscore/points/functors.t.h
    xmscore/points/pt.t.h
    xmscore/testing/TestTools.h
)

list(APPEND xmscore_sources
    xmscore/testing/TestTools.cpp
)

add_custom_command(
    OUTPUT runner.cpp
    COMMAND ${CONAN_BIN_DIRS_CXXTEST}/cxxtestgen --error-printer --root -o runner.cpp ../xmscore/**/*.t.h
)
add_executable(runner runner.cpp)
target_link_libraries(runner ${PROJECT_NAME})

enable_testing()
add_test(unit_tests bin/runner)


add_library(${PROJECT_NAME} STATIC
  ${xmscore_sources} ${xmscore_headers})
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/>
    ${Boost_INCLUDE_DIR})
find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME}
  ${CMAKE_THREAD_LIBS_INIT}
)

install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
foreach (header IN LISTS xmscore_headers)
  get_filename_component(subdir "${header}" DIRECTORY)
  install(
    FILES "${header}"
    DESTINATION "include/xmscore/${subdir}"
  )
endforeach ()

