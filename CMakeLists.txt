cmake_minimum_required (VERSION 2.8)

project(SkyGL)

set(SRC_DIR "${CMAKE_SOURCE_DIR}")
set(BIN_DIR "${CMAKE_BINARY_DIR}/bin")
set(LIB_DIR "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${LIB_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${LIB_DIR}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SRC_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g")

# find the required packages
find_package(GLFW3 REQUIRED)
find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(ASSIMP REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED
    COMPONENTS
)

add_definitions(${OPENGL_DEFINITIONS})
include_directories(include
    ${GLFW3_INCLUDE_DIR}
    ${X11_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${ASSIMP_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)
set(DEPEND_LIBS
    ${GLFW3_LIBRARY}
    ${X11_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${Boost_LIBRARIES}
)

add_library(skygl STATIC
    src/window.cpp
)
set(SKYGL_LIBRARY skygl)

set(LIBS ${SKYGL_LIBRARY} ${DEPEND_LIBS})

add_subdirectory(tests)

