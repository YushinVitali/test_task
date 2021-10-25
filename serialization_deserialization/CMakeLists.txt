cmake_minimum_required(VERSION 3.5)

project(serialization_deserialization LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR   ON)
set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -std=c++14 -Wall -Werror")

set(CMAKE_SOURCE_DIR               ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)


set(COMMON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/common)


add_executable(serialization_deserialization)


file(GLOB SOURCE_EXE ${CMAKE_SOURCE_DIR}/*.cpp)

target_sources(${PROJECT_NAME}
	PUBLIC ${SOURCE_EXE}
	PUBLIC ${COMMON_SOURCE})

target_include_directories(serialization_deserialization
	PUBLIC ${CMAKE_SOURCE_DIR}
	PUBLIC ${COMMON_DIR})
