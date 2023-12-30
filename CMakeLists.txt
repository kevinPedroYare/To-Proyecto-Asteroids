cmake_minimum_required(VERSION 3.12)
project(finalTO)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(main src/main.cpp src/main.cpp)

target_link_libraries(main PRIVATE sfml-graphics sfml-audio)

# Copiar archivos de recursos al directorio de compilación
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
