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

# Found with "nix eval --raw nixpkgs<target>"
set(LIBS
  ncursesw
  openal
  avcodec
  avformat
  avutil
  swresample
)

find_library(NCURSES_LIB ncursesw)
target_link_libraries(${EXECUTABLE_NAME} ${NCURSES_LIB})
find_path(NCURSES_INC ncurses.h)

find_library(OPENAL_LIB openal)
target_link_libraries(${EXECUTABLE_NAME} ${OPENAL_LIB})
find_path(OPENAL_INC AL/al.h)

find_library(AVCODEC_LIB avcodec)
target_link_libraries(${EXECUTABLE_NAME} ${AVCODEC_LIB})
find_path(AVCODEC_INC libavcodec/avcodec.h)

find_library(AVFORMAT_LIB avformat)
target_link_libraries(${EXECUTABLE_NAME} ${AVFORMAT_LIB})
find_path(AVFORMAT_INC libavformat/avformat.h)

find_library(AVUTIL_LIB avutil)
target_link_libraries(${EXECUTABLE_NAME} ${AVUTIL_LIB})
find_path(AVUTIL_INC libavutil/avutil.h)

find_library(SWRESAMPLE_LIB swresample)
target_link_libraries(${EXECUTABLE_NAME} ${SWRESAMPLE_LIB})
find_path(SWRESAMPLE_INC libswresample/swresample.h)

target_include_directories(${EXECUTABLE_NAME} PRIVATE 
  "${CMAKE_SOURCE_DIR}/include"
  ${NCURSES_INC}
  ${OPENAL_INC}
  ${AVCODEC_INC}
  ${AVFORMAT_INC}
  ${AVUTIL_INC}
  ${SWRESAMPLE_INC}
)

install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION bin)

