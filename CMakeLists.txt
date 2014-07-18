cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++98 -Wall -Werror ${CMAKE_CXX_FLAGS}")

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_library(foo
  msg.cc
  msg_hdr.cc
  printers.cpp
)

add_executable(main
  main.cpp
)

target_link_libraries(main foo)
