cmake_minimum_required(VERSION 3.12)

add_library(
    tca9534
    src/tca9534.h
    src/tca9534.c
)

target_include_directories(tca9534 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(tca9534 pico_stdlib hardware_gpio hardware_i2c)
