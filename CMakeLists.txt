cmake_minimum_required(VERSION 2.6)
project(apimageregister)
find_package(OpenCV)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${OpenCV_INCLUDE_DIRS})

set(apImageRegister_SRCS apImageRegister.cpp main.cpp)
set(CMAKE_CXX_FLAGS "-std=gnu++0x")

add_executable(imregister ${apImageRegister_SRCS})

target_link_libraries(imregister ${OpenCV_LIBS})

install(TARGETS imregister RUNTIME DESTINATION bin)
