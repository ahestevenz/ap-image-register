cmake_minimum_required(VERSION 2.6)
project(apimageregister)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(apImageRegister_SRCS apImageRegister.cpp main.cpp)

qt4_automoc(${apImageRegister_SRCS})
add_executable(imregister ${apImageRegister_SRCS})
target_link_libraries(imregister ${QT_QTCORE_LIBRARY})

install(TARGETS imregister RUNTIME DESTINATION bin)
