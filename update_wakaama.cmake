cmake_minimum_required(VERSION 3.1)

find_package(Git REQUIRED)

set(GH_REF "github.com/Openhab-Nodes/libWakaamaEmb.git")

# update from external git
file(REMOVE_RECURSE "tmp")
file(REMOVE_RECURSE "src/wakaama")
execute_process(COMMAND ${GIT_EXECUTABLE} clone https://github.com/eclipse/wakaama.git tmp --branch master --single-branch --depth 1)
set(REP "${CMAKE_CURRENT_LIST_DIR}/tmp")
execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD OUTPUT_VARIABLE DESCRIBE_REVISION WORKING_DIRECTORY "${REP}" )
file(GLOB_RECURSE WAKAAMA_FILES "tmp/core/*")
file(COPY tmp/core DESTINATION src/)
file(RENAME src/core src/wakaama)
file(REMOVE_RECURSE "tmp")

execute_process(COMMAND ${GIT_EXECUTABLE} add src/wakaama)
execute_process(COMMAND ${GIT_EXECUTABLE} commit --author="Wakaama Update <david.graeff@web.de>" -m "Update wakaama source to revision ${DESCRIBE_REVISION}")
execute_process(COMMAND ${GIT_EXECUTABLE} push "https://${GH_TOKEN}@${GH_REF}" master:master  )
