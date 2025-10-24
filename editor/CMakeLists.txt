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
                      src/Obstacle.cpp
                      src/DemoSwitcher.cpp)
target_link_directories(Zenith PRIVATE src)
target_link_libraries(Zenith PRIVATE ZenEngine imgui)
set_target_properties(Zenith PROPERTIES OUTPUT_NAME "Zenith")

set(RUN_DIR ${CMAKE_BINARY_DIR}/editor)
set(RUN_DATA_DIR ${RUN_DIR}/data)

if(UNIX AND NOT APPLE)
  file(MAKE_DIRECTORY "${RUN_DIR}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E rm -rf "${RUN_DATA_DIR}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
                        "${CMAKE_SOURCE_DIR}/editor/data" "${RUN_DATA_DIR}")

  target_include_directories(Zenith PUBLIC "${RUN_DATA_DIR}")
endif()

if (WIN32)
    set(DATA_SRC_DIR "${CMAKE_SOURCE_DIR}/editor/data")
    set(TARGET_DIR $<TARGET_FILE_DIR:Zenith>)
    set(DATA_DST_DIR "${TARGET_DIR}/data")

    add_custom_command(
        TARGET Zenith PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${DATA_DST_DIR}")

    add_custom_command(
        TARGET Zenith POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${DATA_SRC_DIR}" "${DATA_DST_DIR}"
        COMMENT "Copying editor data files to ${DATA_DST_DIR}")
endif()

# CPACK STUFF
install(TARGETS Zenith
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

if(WIN32)
  install(FILES "$<TARGET_FILE:SDL3::SDL3>" DESTINATION bin)
endif()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/editor/data DESTINATION bin)

set(CPACK_PACKAGE_NAME "Zen")
set(CPACK_PACKAGE_VENDOR "Zen")
set(CPACK_PACKAGE_VERSION "0.3.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Zen 2D Game Engine Demo")
set(CPACK_RESOURCE_FILE_README  "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")

if(WIN32)
  set(CPACK_GENERATOR "ZIP;NSIS")
  set(CPACK_NSIS_DISPLAY_NAME "Zen")
  set(CPACK_NSIS_PACKAGE_NAME "Zen")
  set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
  set(CPACK_PACKAGE_INSTALL_DIRECTORY "Zen")
else()
  set(CPACK_GENERATOR "TGZ;TXZ;ZIP")
endif()


set(CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

include(CPack)