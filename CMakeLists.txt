cmake_minimum_required(VERSION 3.3)
project(dodec_c_producer)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Includes.h Globals.cpp Globals.h LED.cpp LED.h Group.cpp Group.h Board.cpp Board.h Dodec.cpp Dodec.h Serial.cpp Serial.h Util.cpp Util.h PatternFlags.cpp PatternFlags.h PatternManager.cpp PatternManager.h)
add_executable(dodec_c_producer ${SOURCE_FILES})