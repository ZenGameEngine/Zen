project(
  Zenith
  VERSION 0.1.0
  DESCRIPTION "A 2D game engine editor")

# ##############################################################################
# ###### Main Program Exec #####################################################
# ##############################################################################

add_executable(Zenith src/Zenith.cpp
                      src/GameLayer.cpp
                      src/Player.cpp
                      src/QuadBuilder.cpp
                      src/Obstacle.cpp)
target_link_directories(Zenith PRIVATE src)
target_link_libraries(Zenith PRIVATE ZenEngine imgui)
set_target_properties(Zenith PROPERTIES OUTPUT_NAME "Zenith")

set(RUN_DIR ${CMAKE_BINARY_DIR}/editor)
set(RUN_DATA_DIR ${RUN_DIR}/data)

file(MAKE_DIRECTORY "${RUN_DIR}")
execute_process(COMMAND ${CMAKE_COMMAND} -E rm -rf "${RUN_DATA_DIR}")
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
                        "${CMAKE_SOURCE_DIR}/editor/data" "${RUN_DATA_DIR}")

target_include_directories(Zenith PUBLIC "${RUN_DATA_DIR}")
