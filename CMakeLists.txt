cmake_minimum_required(VERSION 3.28)
project(MusicTUI CXX)

set(EXECUTABLE_NAME musictui)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
  src/main.cpp
)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

target_compile_options(${EXECUTABLE_NAME} PRIVATE -fsanitize=address,undefined -ggdb)
target_link_options(${EXECUTABLE_NAME} PRIVATE -fsanitize=address,undefined)

# Ncurses
# Library
find_library(NCURSES_LIBRARY ncursesw)
target_link_libraries( ${EXECUTABLE_NAME} PRIVATE 
  ${NCURSES_LIBRARY}
)
# Headers
find_path(NCURSES_INCLUDE ncurses.h)
if(NOT NCURSES_INCLUDE)
    message(FATAL_ERROR "ncurses headers not found!")
endif()

target_include_directories(${EXECUTABLE_NAME} PRIVATE 
  "${CMAKE_SOURCE_DIR}/include"
  ${NCURSES_INCLUDE}
)

install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION bin)
