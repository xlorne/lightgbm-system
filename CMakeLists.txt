cmake_minimum_required(VERSION 3.14)
project(LoginSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_party/LightGBM)

# 创建可执行目标
add_executable(lightgbm-system
        src/main.cpp
        src/LightGBMWrapper.cpp
)

# 指定头文件搜索路径（仅对这个 target 生效）
include_directories(
        ${PROJECT_SOURCE_DIR}/third_party/LightGBM/include
        ${PROJECT_SOURCE_DIR}/include
)

find_package(fmt REQUIRED)

target_link_libraries(lightgbm-system PRIVATE
        fmt::fmt
        _lightgbm
)