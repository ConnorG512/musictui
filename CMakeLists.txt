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

target_include_directories(${EXECUTABLE_NAME} PRIVATE 
  "${CMAKE_SOURCE_DIR}/include"
)

set(LIBS
  ncursesw
  openal
  avcodec
  avformat
  avutil
  swresample
)

foreach(lib IN LISTS LIBS)
  message("Adding library ${lib}")
  find_library(FOUND_LIB ${lib})
  target_link_libraries(${EXECUTABLE_NAME} PRIVATE
    ${FOUND_LIB}
  )
endforeach()

set (INC_PATHS
  ncurses.h
  AL/al.h
  libavcodec/avcodec.h
  libavformat/avformat.h
  libavutil/avutil.h
  libswresample/swresample.h
)

foreach(inc IN LISTS INC_PATHS)
  message("Finding include: ${inc}")
  find_path(INC_RESULT ${inc})
  if(NOT INC_RESULT)
    message(FATAL_ERROR "${inc} could not be found!")
  endif()
  target_include_directories(${EXECUTABLE_NAME} PRIVATE
    ${inc}
  )
endforeach()


install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION bin)
