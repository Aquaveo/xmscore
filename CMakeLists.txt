set(CMAKE_CXX_STANDARD 11)
set(POSITION_INDEPENDENT_CODE True)
cmake_minimum_required(VERSION 3.1.2)
cmake_policy(SET CMP0015 NEW) # Link Directory Pathing
set(CMAKE_DEBUG_POSTFIX _d)

set(BUILD_TESTING NO CACHE BOOL "Enable/Disable testing")
set(IS_CONDA_BUILD NO CACHE BOOL "Set this if you want to make a conda package.")

project(xmscore C CXX)

if(WIN32)
    if(XMS_BUILD)
        add_definitions(/D _WIN32_WINNT=0x0501)  # Windows XP and higher
        add_definitions(/Zc:wchar_t-)  # Treat wchar_t as built-in type
    else(NOT XMS_BUILD)
        add_definitions(/D BOOST_ALL_NO_LIB)
    endif()
endif()

IF(IS_CONDA_BUILD)
  include(${CMAKE_CURRENT_LIST_DIR}/condabuildinfo.cmake)

ELSE() # If we are not using conda, we are using conan
  # C++11 Support

  # Conan setup
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS)
  set(EXT_INCLUDE_DIRS ${CONAN_INCLUDE_DIRS})
  set(EXT_LIB_DIRS ${CONAN_LIB_DIRS})
  set(EXT_LIBS ${CONAN_LIBS})
ENDIF(IS_CONDA_BUILD)

message("External Include Dirs: ${EXT_INCLUDE_DIRS}")
message("External Lib Dirs: ${EXT_LIB_DIRS}")
message("Extneral Libs: ${EXT_LIBS}")

include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${EXT_INCLUDE_DIRS})
link_directories(${EXT_LIB_DIRS})

# Sources
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

# Tests
if(BUILD_TESTING)
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

    find_package(CxxTest)
    if(CXXTEST_FOUND)
      include_directories(${CXXTEST_INCLUDE_DIR})
      enable_testing()

      set(CXXTEST_TESTGEN_ARGS --xunit-printer)
      file(GLOB_RECURSE test_headers ${CMAKE_CURRENT_LIST_DIR}/xmscore/*.t.h)
      CXXTEST_ADD_TEST(
        runner runner.cpp ${test_headers}
      )
      target_link_libraries(runner ${PROJECT_NAME})

      if(WIN32)
        set(RUNNERNAME "runner.exe")
      else()
        set(RUNNERNAME "runner")
      endif()
    endif()
endif()

# Static library
add_library(${PROJECT_NAME} STATIC
  ${xmscore_sources} ${xmscore_headers}
)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME}
  ${EXT_LIBS}
)
target_link_libraries(${PROJECT_NAME}
  ${CMAKE_THREAD_LIBS_INIT}
)
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} rt)
endif()

# Install recipe
install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib"
)
foreach (header IN LISTS xmscore_headers)
  get_filename_component(subdir "${header}" DIRECTORY)
  install(
    FILES "${header}"
    DESTINATION "include/${subdir}"
  )
endforeach ()

