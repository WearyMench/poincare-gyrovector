cmake_minimum_required(VERSION 3.12)
project(poincare_gyrovector VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(BUILD_PYTHON_BINDINGS "Build Python bindings" ON)
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTS "Build tests" OFF)

# Include directories
include_directories(include)

# Core library
add_library(poincare_gyrovector STATIC
    src/poincare.cpp
)

target_include_directories(poincare_gyrovector PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Python bindings
if(BUILD_PYTHON_BINDINGS)
    find_package(pybind11 QUIET)
    if(pybind11_FOUND)
        message(STATUS "Found pybind11: ${pybind11_VERSION}")
    else()
        message(STATUS "pybind11 not found. Fetching from GitHub...")
        include(FetchContent)
        FetchContent_Declare(
            pybind11
            GIT_REPOSITORY https://github.com/pybind/pybind11.git
            GIT_TAG v2.11.1
        )
        FetchContent_MakeAvailable(pybind11)
    endif()

    pybind11_add_module(poincare_gyrovector_py
        python/poincare_bindings.cpp
    )

    target_link_libraries(poincare_gyrovector_py PRIVATE
        poincare_gyrovector
    )

    # Set output directory for Python module
    set_target_properties(poincare_gyrovector_py PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python
    )
endif()

# Examples
if(BUILD_EXAMPLES)
    add_executable(example_cpp examples/example.cpp)
    target_link_libraries(example_cpp PRIVATE poincare_gyrovector)
endif()

# Installation
install(TARGETS poincare_gyrovector
    EXPORT poincare_gyrovectorTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT poincare_gyrovectorTargets
    FILE poincare_gyrovectorTargets.cmake
    NAMESPACE poincare_gyrovector::
    DESTINATION lib/cmake/poincare_gyrovector
)
