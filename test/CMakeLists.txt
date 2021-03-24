cmake_minimum_required(VERSION 3.17)
project(RequestTest)

set(CMAKE_CXX_STANDARD 20)

## CURL
add_definitions(-DCURL_STATICLIB)
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

add_executable(RequestTest main.cpp ../include/Request.h ../src/Request.cpp)

## CURL
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})