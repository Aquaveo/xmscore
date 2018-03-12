project(xmscore)

set(xmscore_sources
  src/math/math.cpp
  src/misc/Singleton.cpp
  src/misc/StringUtil.cpp
  src/misc/XmError.cpp
  src/misc/XmLog.cpp
  src/points/functors.cpp
  src/points/pt.cpp
  src/stl/vector.cpp
)

set(xmscore_headers
  src/math/math.h
  src/misc/ObjectCallback.h
  src/misc/Singleton.h
  src/misc/StringUtil.h
  src/misc/XmError.h
  src/misc/XmInt.h
  src/misc/XmLog.h
  src/misc/boost_defines.h
  src/misc/environment.h
  src/points/functors.h
  src/points/pt.h
  src/points/ptsfwd.h
  src/stl/deque.h
  src/stl/hash.h
  src/stl/list.h
  src/stl/map.h
  src/stl/set.h
  src/stl/string.h
  src/stl/utility.h
  src/stl/vector.h
)

if (BUILD_TESTING)
  add_definitions(-DCXX_TEST -DCXXTEST4)

  list(APPEND xmscore_sources
    src/math/math.t.h
    src/misc/StringUtil.t.h
    src/misc/XmError.t.h
    src/misc/XmLog.t.h
    src/points/functors.t.h
    src/points/pt.t.h
    src/testing/TestTools.cpp
    src/testing/TestTools.h
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
  EXPORT  Filigree-targets
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
