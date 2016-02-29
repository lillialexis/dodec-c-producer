cmake_minimum_required(VERSION 3.3)
project(dodec_c_producer)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c Serial.h Serial.c Includes.h)
add_executable(dodec_c_producer ${SOURCE_FILES})