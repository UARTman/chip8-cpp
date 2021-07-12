cmake_minimum_required(VERSION 3.19)
project(chip8)

set(CMAKE_CXX_STANDARD 14)

include("${PROJECT_SOURCE_DIR}/cmake/GitCheckout.cmake")

find_package(SFML 2.5 COMPONENTS graphics audio system REQUIRED)
set(SFML_LIBS sfml-graphics sfml-window sfml-system)

# Initialize imgui-sfml
set(BUILD_SHARED_LIBS TRUE)
set(IMGUI_DIR "../imgui")
add_subdirectory(imgui-sfml)


add_subdirectory(Core)
add_subdirectory(Implementation)

add_executable(chip8 main.cpp)
include_directories(${PROJECT_SOURCE_DIR})

function(TARGET_COMMON_STEPS TARGET)
    target_link_libraries(${TARGET} PRIVATE ${SFML_LIBS} ImGui-SFML::ImGui-SFML core implementation)
    target_compile_features(${TARGET} PRIVATE cxx_std_17)
endfunction()

TARGET_COMMON_STEPS(chip8)
