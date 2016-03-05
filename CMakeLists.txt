cmake_minimum_required(VERSION 3.3)
project(dodec_c_producer)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Includes.h Serial.cpp Serial.h LED.cpp LED.h Util.cpp Util.h Globals.cpp Globals.h)
add_executable(dodec_c_producer ${SOURCE_FILES})