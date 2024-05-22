cmake_minimum_required(VERSION 3.10)
project(cpp-webcrawler)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -rdynamic")

find_package(CURL REQUIRED)
find_package(LibXml2 REQUIRED)

include_directories(inc)

file(GLOB SOURCES "src/*.cpp")

# Webdriver++
add_subdirectory(webdriver++)
include_directories(webdriver++/include)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} webdriverxx ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CURL_INCLUDE_DIRS} ${LIBXML2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})