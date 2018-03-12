project(xmscore)
cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0015 NEW) # Link Directory Pathing
set(CMAKE_DEBUG_POSTFIX _d)
include_directories(${CMAKE_CURRENT_LIST_DIR})


set(xmscore_sources
  xmscore/math/math.cpp
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
  xmscore/misc/Singleton.h
  xmscore/misc/StringUtil.h
  xmscore/misc/XmError.h
  xmscore/misc/XmLog.h
  xmscore/misc/boost_defines.h
  xmscore/misc/environment.h
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

if (BUILD_TESTING)
  add_definitions(-DCXX_TEST -DCXXTEST4)

  list(APPEND xmscore_sources
    xmscore/math/math.t.h
    xmscore/misc/StringUtil.t.h
    xmscore/misc/XmError.t.h
    xmscore/misc/XmLog.t.h
    xmscore/points/functors.t.h
    xmscore/points/pt.t.h
    xmscore/testing/TestTools.cpp
    xmscore/testing/TestTools.h
  )
endif ()

add_library(${PROJECT_NAME} STATIC
  ${xmscore_sources} ${xmscore_headers})
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/>
    ${Boost_INCLUDE_DIR})
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME}
  PUBLIC
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
