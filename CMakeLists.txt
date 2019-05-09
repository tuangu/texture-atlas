cmake_minimum_required(VERSION 3.14)

project(texture-atlas CXX)

file(GLOB SOURCES "src/*.cpp")
file(GLOB TEST_SOURCES "test/*.cpp")

# Set warning level
if (MSVC)
    add_compile_options(/Wa)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Add dependencies
add_subdirectory(dlib dlib_build)
add_subdirectory(Catch2)

# Main application
add_executable(${PROJECT_NAME} ${SOURCE} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} dlib::dlib)
target_link_libraries(${PROJECT_NAME} stdc++fs)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

# Tests
set(TEST_EXEC "tests")
add_executable(${TEST_EXEC} ${TEST_SOURCES} ${SOURCES})
target_include_directories(${TEST_EXEC} PRIVATE include)
target_link_libraries(${TEST_EXEC} Catch2::Catch2)
