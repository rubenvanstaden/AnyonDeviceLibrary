find_program(GIT "git")
if(NOT GIT)
    set(msg "In order to install this project, CMake needs git.")
    set(msg "${msg} In order to install this project, CMake needs git.")
    message(FATAL_ERROR "${msg}")
endif()
message(STATUS "Including submodules. You might be ask to enter your Github credentials several times.")
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/submodules)
    execute_process(COMMAND mkdir submodules WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endif()
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/submodules/CMakeUtility/CMakeUtility.cmake)
    set(CMakeUtilityURL "git@github.com:AnyonSystems/CMakeUtility.git")
    execute_process(COMMAND ${GIT} clone ${CMakeUtilityURL} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/submodules)
    set(${PROJECT_NAME}_CMakeUtility_SHA "" CACHE INTERNAL "")
endif()
if((NOT ${PROJECT_NAME}_CMakeUtility_SHA STREQUAL "master") AND (NOT SKIP_SUBMODULES_UPDATE))
    set(${PROJECT_NAME}_CMakeUtility_SHA "master" CACHE INTERNAL "")
    execute_process(COMMAND ${GIT} checkout master WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/submodules/CMakeUtility)
    execute_process(COMMAND ${GIT} pull WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/submodules/CMakeUtility)
endif()
include(submodules/CMakeUtility/CMakeUtility.cmake)
set(CMAKE_MODULE_PATH_BACK CMAKE_MODULE_PATH)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/submodules/CMakeUtility/modules")
anyon_clear_global_variables()