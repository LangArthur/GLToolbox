cmake_minimum_required(VERSION 3.14)
project(GLToolBox-test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)


include(FetchContent)
# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG        45ce5ddd197d5c58f50fdd3296a5131c894e5527 # release-3.3.7
)
FetchContent_MakeAvailable(glfw)

# GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG        bf71a834948186f4097caa076cd2663c69a10e1e # 0.9.9.8
)
FetchContent_MakeAvailable(glm)

message("Fetching Google test")
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test_shader.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${OPENGL_LIBRARIES}
  ${GLEW_INCLUDE_DIRS}
  ${GLUT_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  GTest::gtest_main
  ${OPENGL_INCLUDE_DIRS}
  ${GLEW_LIBRARIES}
  ${GLUT_LIBRARIES}
  GLToolBox
  glm::glm
  glfw
)

include(GoogleTest)
# gtest_discover_tests(${PROJECT_NAME})
