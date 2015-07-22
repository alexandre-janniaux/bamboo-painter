CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(BambooPainter)

FIND_PACKAGE(SFML COMPONENTS audio graphics window system REQUIRED)

SET(
    SRCS
    src/main.cpp
    src/GameScreenState.cpp
)

ADD_EXECUTABLE(
    BambooPainter
    ${SRCS}
)

ADD_DEFINITIONS(
    --std=c++11
)

TARGET_LINK_LIBRARIES(
    BambooPainter
    ${SFML_AUDIO_LIBRARY}
    ${SFML_GRAPHICS_LIBRARY}
    ${SFML_WINDOW_LIBRARY}
    ${SFML_SYSTEM_LIBRARY}
)
