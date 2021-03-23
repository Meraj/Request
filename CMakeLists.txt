cmake_minimum_required(VERSION 3.17)
project(Request)

set(CMAKE_CXX_STANDARD 20)

## CURL
add_definitions(-DCURL_STATICLIB)
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)


add_library(Request src/Request.cpp include/Request.h)

add_executable(RequestTest test/main.cpp include/Request.h src/Request.cpp)

## CURL
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
target_link_libraries(RequestTest ${CURL_LIBRARIES})