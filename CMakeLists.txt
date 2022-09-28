cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)
project(GLToolBox)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

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

set(SRC_LIB
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/std_image.cpp
)

set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shader/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shader/ShaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Logger.cpp
)

add_library(${PROJECT_NAME}
    ${SRC}
    ${SRC_LIB}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    include/
    lib/
)

## Linking libraries to street
target_link_libraries(${PROJECT_NAME} PUBLIC
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  glm::glm
  glfw
)

# test file
add_executable(testExec
  main.cpp
)

target_include_directories(testExec PUBLIC
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    include/
)

target_link_libraries(testExec PUBLIC
  ${PROJECT_NAME}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  glm::glm
  glfw
)


add_subdirectory(tests)