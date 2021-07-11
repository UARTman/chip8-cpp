cmake_minimum_required(VERSION 3.19)
project(chip8)

set(CMAKE_CXX_STANDARD 14)

# Checkout git submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# If imgui-sfml doesn't check out, something went wrong
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/imgui-sfml/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

set(BUILD_SHARED_LIBS TRUE)

find_package(SFML 2.5 COMPONENTS graphics audio system REQUIRED)

# Initialize imgui-sfml
set(IMGUI_DIR "../imgui")
add_subdirectory(imgui-sfml)

set(SFML_LIBS sfml-graphics sfml-window sfml-system)

add_executable(chip8 main.cpp)

function(TARGET_COMMON_STEPS TARGET)
    target_link_libraries(${TARGET} PRIVATE ${SFML_LIBS})
    target_compile_features(${TARGET} PRIVATE cxx_std_17)
    target_link_libraries(${TARGET} PRIVATE ImGui-SFML::ImGui-SFML)
endfunction()

TARGET_COMMON_STEPS(chip8)
