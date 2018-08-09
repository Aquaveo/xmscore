set(CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.1.2)
cmake_policy(SET CMP0015 NEW) # Link Directory Pathing
set(CMAKE_DEBUG_POSTFIX _d)

if (APPLE)  
  set(CMAKE_POSITION_INDEPENDENT_CODE False)
else()
  set(CMAKE_POSITION_INDEPENDENT_CODE True)
endif()

set(BUILD_TESTING NO CACHE BOOL "Enable/Disable testing")
set(IS_PYTHON_BUILD NO CACHE BOOL "Enable/Disable PYTHON")
set(IS_CONDA_BUILD NO CACHE BOOL "Set this if you want to make a conda package.")

if(IS_PYTHON_BUILD AND BUILD_TESTING)
  message(FATAL_ERROR "Cannot build python module when testing is enabled")
endif()


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

message(STATUS "External Include Dirs: ${EXT_INCLUDE_DIRS}")
message(STATUS "External Lib Dirs: ${EXT_LIB_DIRS}")
message(STATUS "Extneral Libs: ${EXT_LIBS}")

if(IS_PYTHON_BUILD)
  #set(PYTHON_LIBRARY ${PYTHON}/libs)
  #set(PYTHON_INCLUDE_DIR ${PYTHON}/include)
  find_package(PythonLibs REQUIRED)
  list(APPEND EXT_INCLUDE_DIRS
    ${PYTHON_INCLUDE_DIRS}
  )
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
endif()

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

  pybind11_add_module(xmscore_py
    ${xmscore_py} ${xmscore_py_headers}
  )
  target_include_directories(xmscore_py
      PRIVATE
        ${EXT_INCLUDE_DIRS}
  )
  target_link_libraries(xmscore_py
    PRIVATE
      ${EXT_LIBS}
      ${PROJECT_NAME}
  )
  set_target_properties(xmscore_py PROPERTIES
    LINKER_LANGUAGE CXX
  )

  execute_process(COMMAND python -c "import os; print('${PYTHON_SITE_PACKAGES}'.replace('${CONDA_PREFIX}' + os.sep, ''))" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES_TRIMMED OUTPUT_STRIP_TRAILING_WHITESPACE)

  # Install recipe
  install(
    TARGETS xmscore_py
    ARCHIVE DESTINATION ${PYTHON_SITE_PACKAGES_TRIMMED}
    LIBRARY DESTINATION ${PYTHON_SITE_PACKAGES_TRIMMED}
  )
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
