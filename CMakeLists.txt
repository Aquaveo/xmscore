cmake_minimum_required(VERSION 3.1.2)
cmake_policy(SET CMP0015 NEW) # Link Directory Pathing
set(CMAKE_DEBUG_POSTFIX _d)

if (APPLE OR WIN32)
    # Target C++17 on MacOS and Windows. If building with version of Visual Studio without
    # support, has no effect.
    set(CMAKE_CXX_STANDARD 17)
else()
    set(CMAKE_CXX_STANDARD 11)
endif()


project(xmscorelib C CXX)

if (APPLE)
  set(CMAKE_POSITION_INDEPENDENT_CODE False)
else()
  set(CMAKE_POSITION_INDEPENDENT_CODE True)
endif()

set(BUILD_TESTING NO CACHE BOOL "Enable/Disable testing")
set(IS_PYTHON_BUILD NO CACHE BOOL "Enable/Disable PYTHON")
set(IS_CONDA_BUILD NO CACHE BOOL "Set this if you want to make a conda package.")
set(XMS_BUILD NO CACHE BOOL "Set this if you want to use this package with XMS.")
if(DEFINED ENV{PYTHON_TARGET_VERSION})
    set(ENV_PYTHON_TARGET_VERSION $ENV{PTYHON_TARGET_VERSION} STRING)
else()
    set(ENV_PYTHON_TARGET_VERSION 3.6 STRING)
endif()
set(PYTHON_TARGET_VERSION ${ENV_PYTHON_TARGET_VERSION} CACHE STRING "Version of python to link to for python wrapping.")
set(IS_PYTHON_BUILD NO CACHE BOOL "Set this if you want to build the python bindings.")
set(XMS_TEST_PATH ${PROJECT_SOURCE_DIR}/test_files/ CACHE PATH "Path to test files for testing")
set(XMS_VERSION "99.99.99" CACHE STRING "Library Version")

if(IS_PYTHON_BUILD AND BUILD_TESTING)
  message(FATAL_ERROR "Cannot build python module when testing is enabled")
endif()

add_definitions(-DXMS_VERSION=\"${XMS_VERSION}\")

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

if(WIN32)
  string(COMPARE EQUAL "${CONAN_SETTINGS_COMPILER_RUNTIME}" "MT" USES_MT)
  if(NOT USES_MT)
    string(COMPARE EQUAL "${CONAN_SETTINGS_COMPILER_RUNTIME}" "MTd" USES_MT)
  endif()

  if(USES_MT)
    add_definitions(/Zc:wchar_t)  # Treat wchar_t as built-in type
  else()
    add_definitions(/Zc:wchar_t-)  # Treat wchar_t as built-in type
  endif()

  if(XMS_BUILD)
      add_definitions(/D _WIN32_WINNT=0x0501)  # Windows XP and higher
  else(NOT XMS_BUILD)
      add_definitions(/D BOOST_ALL_NO_LIB)
  endif()

  if(USES_MT)
    set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
    foreach(CompilerFlag ${CompilerFlags})
      string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
  endif()
endif()

message(STATUS "External Include Dirs: ${EXT_INCLUDE_DIRS}")
message(STATUS "External Lib Dirs: ${EXT_LIB_DIRS}")
message(STATUS "Extneral Libs: ${EXT_LIBS}")

if(IS_PYTHON_BUILD)

  # Pybind11 module
  if(IS_CONDA_BUILD)
      include("${CONDA_PREFIX}/share/cmake/pybind11/pybind11Targets.cmake")
      include("${CONDA_PREFIX}/share/cmake/pybind11/FindPythonLibsNew.cmake")
      include("${CONDA_PREFIX}/share/cmake/pybind11/pybind11Config.cmake")
      include("${CONDA_PREFIX}/share/cmake/pybind11/pybind11ConfigVersion.cmake")
      include("${CONDA_PREFIX}/share/cmake/pybind11/pybind11Tools.cmake")
  else()
      include("${CONAN_PYBIND11_ROOT}/share/cmake/pybind11/pybind11Targets.cmake")
      include("${CONAN_PYBIND11_ROOT}/share/cmake/pybind11/FindPythonLibsNew.cmake")
      include("${CONAN_PYBIND11_ROOT}/share/cmake/pybind11/pybind11Config.cmake")
      include("${CONAN_PYBIND11_ROOT}/share/cmake/pybind11/pybind11ConfigVersion.cmake")
      include("${CONAN_PYBIND11_ROOT}/share/cmake/pybind11/pybind11Tools.cmake")
  endif()

  list(APPEND EXT_INCLUDE_DIRS
    ${pybind11_INCLUDE_DIR}
  )

  find_package(PythonLibsNew ${PYTHON_TARGET_VERSION} EXACT REQUIRED)

  # Have to add this after conda because it doesn't get the path for pybind if we don't.
  list(APPEND EXT_INCLUDE_DIRS
    ${PYTHON_INCLUDE_DIRS}
  )
endif()

message("External Lib Includes: ${EXT_INCLUDE_DIRS}")
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${EXT_INCLUDE_DIRS})
link_directories(${EXT_LIB_DIRS})

# Sources
set(xmscore_sources
  xmscore/dataio/daStreamIo.cpp
  xmscore/math/math.cpp
  xmscore/misc/DynBitset.cpp
  xmscore/misc/HeaderCheck.cpp
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
  xmscore/dataio/daStreamIo.h
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
  xmscore/stl/list.h
  xmscore/stl/map.h
  xmscore/stl/set.h
  xmscore/stl/utility.h
  xmscore/stl/vector.h
)

# Tests
if(BUILD_TESTING)
    add_definitions(-DXMS_TEST_PATH="${XMS_TEST_PATH}/")
    add_definitions(-DCXX_TEST -DCXXTEST4)

    list(APPEND xmscore_headers
        xmscore/dataio/daStreamIo.t.h
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
      include_directories(${CXXTEST_INCLUDE_DIRS})
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

if(IS_PYTHON_BUILD)
  list(APPEND xmscore_sources
    xmscore/python/misc/PyUtils.cpp
  )
  list(APPEND xmscore_headers
    xmscore/python/misc/PyUtils.h
  )
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

#Pybind11
if(IS_PYTHON_BUILD)

  # Pybind11 sources
  set(xmscore_py
    xmscore/python/xmscore_py.cpp
    # Misc
    xmscore/python/misc/misc_py.cpp
    xmscore/python/misc/PyUtils.cpp
    xmscore/python/misc/observer_py.cpp
  )

  set(xmscore_py_headers
    xmscore/python/misc/misc_py.h
    xmscore/python/misc/PyUtils.h
    xmscore/python/misc/PublicObserver.h
    xmscore/python/misc/PyObserver.h
  )

  message(STATUS "PYTHON_INCLUDE: ${PYTHON_INCLUDE_DIRS}")
  message(STATUS "PYTHON_LIBS: ${PYTHON_LIBRARIES}")

  pybind11_add_module(_xmscore
    ${xmscore_py} ${xmscore_py_headers}
  )
  target_include_directories(_xmscore
      PRIVATE
        ${EXT_INCLUDE_DIRS}
  )
  target_link_libraries(_xmscore
    PRIVATE
      ${EXT_LIBS}
      ${PROJECT_NAME}
  )
  set_target_properties(_xmscore PROPERTIES
    LINKER_LANGUAGE CXX
  )

  # Install recipe
  install(
      TARGETS _xmscore
      ARCHIVE DESTINATION "_package/xms/core"
      LIBRARY DESTINATION "_package/xms/core"
  )

  install(DIRECTORY "_package/" DESTINATION "_package"
           FILES_MATCHING PATTERN "*.py"
           PATTERN "_package/tests" EXCLUDE)
endif()

# Install recipe
install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib"
)
foreach (header IN LISTS xmscore_headers xmscore_py_headers)
  get_filename_component(subdir "${header}" DIRECTORY)
  install(
    FILES "${header}"
    DESTINATION "include/${subdir}"
  )
endforeach ()
