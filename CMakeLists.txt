CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(BambooPainter)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})


FIND_PACKAGE(SFML COMPONENTS audio graphics window system REQUIRED)

SET(
    SRCS
    src/main.cpp
    src/Level.cpp
    src/GameScreenState.cpp
)

ADD_EXECUTABLE(
    BambooPainter
    ${SRCS}
)

ADD_DEFINITIONS(
    --std=c++11
)

INCLUDE_DIRECTORIES(
    ${SFML_INCLUDE_DIR}
)

TARGET_LINK_LIBRARIES(
    BambooPainter
    ${SFML_AUDIO_LIBRARY}
    ${SFML_GRAPHICS_LIBRARY}
    ${SFML_WINDOW_LIBRARY}
    ${SFML_SYSTEM_LIBRARY}
)
