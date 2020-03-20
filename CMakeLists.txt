cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(test VERSION 0.1.0 LANGUAGES C CXX)

# Version
set(PROJECT_VENDOR "Company")
configure_file(res/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/version.h LF)

# Sources
file(GLOB_RECURSE sources src/*.[hc]pp)

# Executable
add_executable(${PROJECT_NAME} ${sources} src/main.manifest src/main.rc)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src src)
set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)


# Precompiled Headers
target_precompile_headers(${PROJECT_NAME} PRIVATE src/main.hpp)
source_group(TREE ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir PREFIX res FILES
  ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir/cmake_pch.hxx
  ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir/cmake_pch.cxx)

# Dependencies
find_package(OpenCV CONFIG REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

# Install
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)

install(CODE [[
  file(GLOB libraries ${CMAKE_BINARY_DIR}/*.dll)
  file(INSTALL ${libraries} DESTINATION ${CMAKE_INSTALL_PREFIX})
]])

# Visual Studio
if(_CMAKE_USER_CXX_COMPILER_PATH)
  configure_file(res/config/launch.vs.json.in ${CMAKE_SOURCE_DIR}/.vs/launch.vs.json @ONLY LF)
endif()
