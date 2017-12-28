cmake_minimum_required(VERSION 3.9.4)
project(cake_log_forwarder)

set(CMAKE_CXX_STANDARD 17)

add_executable(cake_log_forwarder main.cpp src/listener_constants.h src/listener/syslog_listener.cpp src/listener/log_listener.h src/listener/log_listener.cpp src/listener_constants.cpp src/json.h src/parser/parser.cpp src/parser/parser.h)

target_link_libraries(cake_log_forwarder ${CMAKE_CURRENT_SOURCE_DIR}/lib/libfluent-bit.so)
