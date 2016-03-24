cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(keyence)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)

add_executable(AutoZero src_cpp/AutoZero.cpp)
add_executable(ChangeProgramNumber src_cpp/ChangeProgramNumber.cpp)
add_executable(GetMeasurementValues src_cpp/GetMeasurementValues.cpp)
add_executable(GetProfile src_cpp/GetProfile.cpp)
add_executable(Trigger src_cpp/Trigger.cpp)

# add c executables
add_executable(c_AutoZero src_c/LJV7_AutoZero.c)
add_executable(c_ChangeProgramNumber src_c/LJV7_ChangeProgramNumber.c)
add_executable(c_GetMeasurementValues src_c/LJV7_GetMeasurementValues.c)
add_executable(c_GetProfile src_c/LJV7_GetProfile.c)
add_executable(c_Trigger src_c/LJV7_Trigger.c)

file(GLOB cFiles ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/c_*)

#We copy the c executables over to the C_EXE Directory
file(COPY ${cFiles} DESTINATION ${PROJECT_SOURCE_DIR}/../C_EXE)	

#and then remove the C executables from the bin directory
file(TO_CMAKE_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/c_*" C_BIN)
file(REMOVE ${C_BIN})		

message(STATUS "C_BIN : " ${C_BIN})