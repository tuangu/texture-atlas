cmake_minimum_required(VERSION 3.14)

project(texture-atlas CXX)

# Set warning level
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options(/Wa)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Add dependencies
add_subdirectory(dlib dlib_build)
add_subdirectory(Catch2)

# Build the library
add_library(${PROJECT_NAME} src/png_image.cpp
                            src/point.cpp
                            src/rect.cpp
                            src/texture.cpp
                            src/file_loader.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} dlib::dlib)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_link_libraries(${PROJECT_NAME} c++fs)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_link_libraries(${PROJECT_NAME} stdc++fs)
endif()

# Binary
add_executable(texture-atlas-bin main.cpp)
target_link_libraries(texture-atlas-bin ${PROJECT_NAME})
target_compile_features(texture-atlas-bin PRIVATE cxx_std_17)

# Test binary
add_executable(texture-atlas-tests test/test_main.cpp
                            test/test_point.cpp
                            test/test_rect.cpp
                            test/test_png_image.cpp
                            test/test_texture.cpp
                            test/test_file_loader.cpp
)
target_link_libraries(texture-atlas-tests Catch2::Catch2)
target_link_libraries(texture-atlas-tests ${PROJECT_NAME})
target_compile_features(texture-atlas-tests PRIVATE cxx_std_17)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_link_libraries(texture-atlas-tests c++fs)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_link_libraries(texture-atlas-tests stdc++fs)
endif()