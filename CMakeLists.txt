cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_MODULE_PATH_BACK CMAKE_MODULE_PATH)
set(CMAKE_CXX_STANDARD_BACK ${CMAKE_CXX_STANDARD})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE_BACK CMAKE_POSITION_INDEPENDENT_CODE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(AnyonDeviceLibrary)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# =========================================
# Install variables
# =========================================
message(STATUS "**${PROJECT_NAME}** INSTALLING VARIABLES")
set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib")
set(INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include")
set(INSTALL_CMAKE_DIR "${CMAKE_INSTALL_PREFIX}/lib/CMake")
if(NOT CMAKE_BUILD_TYPE)
    set(msg "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used)")
    set(msg "${msg} Debug Release RelWithDebInfo MinSizeRel.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING ${msg} FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
include(importCMakeUtility.cmake)

# =========================================
# Internal dependecies
# =========================================
message(STATUS "**${PROJECT_NAME}** INSTALLING INTERNAL DEPENDENCIES")
set(USE_ANYON_PARTS_CONFIG "USE_ANYON_PARTS_CONFIG")
set(importedUrl "git@github.com:AnyonSystems/AnyonLayoutGenerator.git")
set(importedSha "stream_extractor")
set(importedPath "submodules/AnyonLayoutGenerator")
anyon_import_submodule(${importedUrl} ${importedSha} ${importedPath})
anyon_import_dependencies(AnyonLayoutGenerator)

# =========================================
# Unit testing dependecies
# =========================================
message(STATUS "**${PROJECT_NAME}** INSTALLING UNIT TESTING DEPENDENCIES")
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    find_package(GTest REQUIRED)
    if(GTEST_FOUND)
        include_directories(SYSTEM ${GTEST_INCLUDE_DIR})
        enable_testing()
    endif()
endif()
message(STATUS "**${PROJECT_NAME}** EXTERNAL DEPENDENCIES END HERE")

# =========================================
# Building Project
# =========================================
include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(src)
