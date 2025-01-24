cmake_minimum_required(VERSION 3.11.0)
cmake_policy(SET CMP0015 NEW) # Link Directory Pathing
cmake_policy(SET CMP0091 NEW)
set(CMAKE_DEBUG_POSTFIX _d)

project(xmscorelib C CXX)

set(BUILD_TESTING NO CACHE BOOL "Enable/Disable testing")
set(IS_CONDA_BUILD NO CACHE BOOL "Set this if you want to make a conda package.")
set(IS_EMSCRIPTEN_BUILD NO CACHE BOOL "Set this to build with emscripten using cmake.")
set(PYTHON_TARGET_VERSION 3.12 CACHE STRING "Version of python to link to for python wrapping.")
set(CONDA_PREFIX "" CACHE PATH "Path to the conda environment used to build.")
set(IS_PYTHON_BUILD NO CACHE BOOL "Set this if you want to build the python bindings.")
set(XMS_TEST_PATH ${PROJECT_SOURCE_DIR}/test_files/ CACHE PATH "Path to test files for testing")
set(XMS_VERSION "99.99.99" CACHE STRING "Library Version")

# Static library sources
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
    xmscore/time/TimeConversion.cpp
)

# Static library headers
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
    xmscore/time/TimeConversion.h
)

if (APPLE OR WIN32 OR IS_EMSCRIPTEN_BUILD)
    # Target C++17 on MacOS and Windows. If building with version of Visual Studio without
    # support, has no effect.
    set(CMAKE_CXX_STANDARD 17)
else ()
    set(CMAKE_CXX_STANDARD 11)
endif ()

if (APPLE)
    set(CMAKE_POSITION_INDEPENDENT_CODE False)
else ()
    set(CMAKE_POSITION_INDEPENDENT_CODE True)
endif ()

if (IS_PYTHON_BUILD AND BUILD_TESTING)
    message(FATAL_ERROR "Cannot build python module when testing is enabled")
endif ()

add_definitions(-DXMS_VERSION=\"${XMS_VERSION}\")

if (IS_CONDA_BUILD)
    include(${CMAKE_CURRENT_LIST_DIR}/condabuildinfo.cmake)
elseif (IS_EMSCRIPTEN_BUILD)
    include(${CMAKE_CURRENT_LIST_DIR}/emscriptenbuildinfo.cmake)
else () # If we are not using conda or emscripten, we are using conan
    # Conan 2 setup
    find_package(Boost REQUIRED)
    find_package(ZLIB REQUIRED)
    list(APPEND EXT_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
    list(APPEND EXT_INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS})
    list(APPEND EXT_LIB_DIRS ${Boost_LIBRARY_DIRS})
    list(APPEND EXT_LIB_DIRS ${ZLIB_LIBRARY_DIRS})
    list(APPEND EXT_LIBS ${Boost_LIBRARIES})
    list(APPEND EXT_LIBS ${ZLIB_LIBRARIES})
endif ()

if (WIN32)
    string(COMPARE EQUAL "${CONAN_SETTINGS_COMPILER_RUNTIME}" "MT" USES_MT)
    if (NOT USES_MT)
        string(COMPARE EQUAL "${CONAN_SETTINGS_COMPILER_RUNTIME}" "MTd" USES_MT)
    endif ()

    if (USE_TYPEDEF_WCHAR_T)
        add_definitions(/Zc:wchar_t-)  # Treat wchar_t as a typedef
    endif ()

    add_definitions(/D BOOST_ALL_NO_LIB)

    if (USES_MT)
        set(CompilerFlags
                CMAKE_CXX_FLAGS
                CMAKE_CXX_FLAGS_DEBUG
                CMAKE_CXX_FLAGS_RELEASE
                CMAKE_C_FLAGS
                CMAKE_C_FLAGS_DEBUG
                CMAKE_C_FLAGS_RELEASE
        )
        foreach (CompilerFlag ${CompilerFlags})
            string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
        endforeach ()
    endif ()
endif ()

if (IS_PYTHON_BUILD)

    find_package(Python3 ${PYTHON_TARGET_VERSION} REQUIRED COMPONENTS Interpreter Development)
    find_package(pybind11 REQUIRED)
    list(APPEND EXT_INCLUDE_DIRS
            ${pybind11_INCLUDE_DIR}
    )

    # Have to add this after conda because it doesn't get the path for pybind if we don't.
    list(APPEND EXT_INCLUDE_DIRS
            ${Python3_INCLUDE_DIRS}
    )
    list(APPEND EXT_LIBS ${Python3_LIBRARIES})
    list(APPEND LIBRARY_DIRS ${Python3_LIBRARY_DIRS})
endif ()

if (BUILD_TESTING)
    message(STATUS "Adding test dependencies...")
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
         xmscore/time/TimeConversion.t.h
         xmscore/testing/TestTools.h
    )

    # Add source for testing build only
    list(APPEND xmscore_sources
         xmscore/testing/TestTools.cpp
    )

    find_package(cxxtest REQUIRED)
    list(APPEND EXT_INCLUDE_DIRS ${cxxtest_INCLUDE_DIRS})
    list(APPEND EXT_LIB_DIRS ${cxxtest_LIBRARY_DIRS})
    list(APPEND EXT_LIBS ${cxxtest_LIBRARIES})

    if (cxxtest_FOUND)
        include("FindCxxTest")
        include_directories(${CXXTEST_INCLUDE_DIR})
        enable_testing()

        set(cxxtest_TESTGEN_ARGS --xunit-printer --have-eh)
        file(GLOB_RECURSE test_headers ${CMAKE_CURRENT_LIST_DIR}/xmscore/*.t.h)
        message(STATUS "Prefix Path: ${CMAKE_PREFIX_PATH}")
        message(STATUS "Module Path: ${CMAKE_MODULE_PATH}")
        CXXTEST_ADD_TEST(
                runner runner.cpp ${test_headers}
        )
        target_link_libraries(runner ${PROJECT_NAME})

        if (WIN32)
            set(RUNNERNAME "runner.exe")
        else ()
            set(RUNNERNAME "runner")
        endif ()
    endif ()
endif ()


message(STATUS "External Include Dirs: ${EXT_INCLUDE_DIRS}")
message(STATUS "External Lib Dirs: ${EXT_LIB_DIRS}")
message(STATUS "Extneral Libs: ${EXT_LIBS}")


include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${EXT_INCLUDE_DIRS})
link_directories(${EXT_LIB_DIRS})

# Add source for Python library only
if (IS_PYTHON_BUILD)
    list(APPEND xmscore_sources
         xmscore/python/misc/PyUtils.cpp
    )
    list(APPEND xmscore_headers
         xmscore/python/misc/PyUtils.h
    )
endif ()

message("External Include Dirs: ${EXT_INCLUDE_DIRS}")
message("External Lib Dirs: ${EXT_LIB_DIRS}")
message("Extneral Libs: ${EXT_LIBS}")

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
if (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} rt)
endif ()


# Pybind11
if (IS_PYTHON_BUILD)
    # Pybind11 sources
    set(xmscore_py
        xmscore/python/xmscore_py.cpp
        # Misc
        xmscore/python/misc/detail/Listener.cpp
        xmscore/python/misc/detail/PublicProgressListener.cpp
        xmscore/python/misc/misc_py.cpp
        xmscore/python/misc/observer_py.cpp
        xmscore/python/misc/PyUtils.cpp
        xmscore/python/misc/progress_listener_py.cpp
        xmscore/python/time/time_py.cpp
        xmscore/python/time/TimeConversion_py.cpp
    )

    set(xmscore_py_headers
        xmscore/python/misc/detail/Listener.h
        xmscore/python/misc/misc_py.h
        xmscore/python/misc/PyUtils.h
        xmscore/python/misc/PublicObserver.h
        xmscore/python/misc/PublicProgressListener.h
        xmscore/python/misc/PyObserver.h
        xmscore/python/misc/PyProgressListener.h
        xmscore/python/time/time_py.h
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

    install(
            TARGETS _xmscore
            ARCHIVE DESTINATION "_package/xms/core"
            LIBRARY DESTINATION "_package/xms/core"
    )

    install(DIRECTORY "_package/" DESTINATION "_package"
            FILES_MATCHING PATTERN "*.py"
            PATTERN "_package/tests" EXCLUDE)
endif ()


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
