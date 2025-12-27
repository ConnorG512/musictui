cmake_minimum_required(VERSION 3.28)
project(MusicTUI CXX)

set(EXECUTABLE_NAME musictui)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
  src/main.cpp
  src/track-instance.cpp
  src/playback-position.cpp
  src/audio/engine.cpp
  src/audio/volume.cpp
)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

target_compile_options(${EXECUTABLE_NAME} PRIVATE -fsanitize=address,undefined -ggdb)
target_link_options(${EXECUTABLE_NAME} PRIVATE -fsanitize=address,undefined)

# Found with "nix eval --raw nixpkgs<target>"
find_package(PkgConfig REQUIRED)
pkg_check_modules(NCURSES_PKG REQUIRED
  ncursesw
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MINIAUDIO_PKG REQUIRED
  miniaudio
)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
  ${NCURSES_PKG_LIBRARIES}
  ${MINIAUDIO_PKG_LIBRARIES}
)

target_include_directories(${EXECUTABLE_NAME} PRIVATE 
  "${CMAKE_SOURCE_DIR}/include"
  ${NCURSES_PKG_INCLUDE_DIRS}
  ${MINIAUDIO_PKG_INCLUDE_DIRS}
)

target_compile_options(${EXECUTABLE_NAME} PRIVATE 
  ${FFMPEG_CFLAGS_OTHER}
)

install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION bin)

