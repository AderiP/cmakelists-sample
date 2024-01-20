cmake_minimum_required(VERSION 3.27)
project(cmakelists_sample)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cpp
        src/test.cpp src/test.hpp)

add_library(my_lib STATIC lib/my-lib/my_lib.hpp lib/my-lib/my_lib.cpp)
target_include_directories(my_lib PUBLIC lib)
target_link_libraries(${PROJECT_NAME} PRIVATE my_lib)

# yaml-cpp の設定
set(yaml-cpp_DIR "${CMAKE_SOURCE_DIR}/oss/yaml-cpp_x64-windows/share/yaml-cpp")
find_package(yaml-cpp REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${YAML_CPP_LIBRARIES})

# yaml-cpp の DLL ファイルをコピー
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/OSS/yaml-cpp_x64-windows/debug/bin/yaml-cppd.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/OSS/yaml-cpp_x64-windows/bin/yaml-cpp.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

# OpenCV の設定
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/oss/opencv-4.5.4/build")
find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

# OpenCV の DLL ファイルをコピー
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${OpenCV_DIR}/x64/vc15/bin/opencv_world454d.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${OpenCV_DIR}/x64/vc15/bin/opencv_world454.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

configure_file(config.yaml config.yaml COPYONLY)