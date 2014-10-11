#
#
#
#
set(PROJECT_NAME "UDevDemo")

cmake_minimum_required(VERSION 2.8)
project(${PROJECT_NAME})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(UDev REQUIRED)

set(UDDEMO_EXE "udev_demo")
set(UDDEMO_INCLUDE "${PROJECT_SOURCE_DIR}/include")
set(UDDEMO_SRC "${PROJECT_SOURCE_DIR}/src")

# Uncomment to make makefiles verbose
# set(CMAKE_VERBOSE_MAKEFILE ON)

# gcc flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG -O3")

# Source Code
add_subdirectory(${UDDEMO_SRC})
include_directories(${UDDEMO_INCLUDE})

include_directories(${udev_INCLUDE_DIR})

# Executable
add_executable(${UDDEMO_EXE} ${SOURCE_FILES})

target_link_libraries(${UDDEMO_EXE} ${udev_LIBRARY})
