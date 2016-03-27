cmake_minimum_required(VERSION 3.1)

find_package(Git REQUIRED)

# update from external git
file(REMOVE_RECURSE "tmp")
file(REMOVE_RECURSE "src/wakaama")
execute_process(COMMAND ${GIT_EXECUTABLE} clone https://github.com/eclipse/wakaama.git tmp)
file(GLOB_RECURSE WAKAAMA_FILES "tmp/core/*")
file(COPY tmp/core DESTINATION src/)
file(RENAME src/core src/wakaama)
file(REMOVE_RECURSE "tmp")

execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
    WORKING_DIRECTORY ${ROOT_SOURCE_PATH}
    RESULT_VARIABLE CMD_RESULT
    OUTPUT_VARIABLE DESCRIBE_REVISION
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

if(NOT DEFINED CMD_RESULT)
    message(WARNING "GIT executable not found. Make your PATH environment variable point to git")
    return()
endif()

execute_process(
    COMMAND ${GIT_EXECUTABLE} remote remove oo
    WORKING_DIRECTORY ${ROOT_SOURCE_PATH}
    RESULT_VARIABLE CMD_RESULT
    OUTPUT_VARIABLE DESCRIBE_REVISION
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
