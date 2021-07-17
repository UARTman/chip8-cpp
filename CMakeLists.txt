cmake_minimum_required(VERSION 3.19)
project(chip8)

set(CMAKE_CXX_STANDARD 14)
if( MINGW )
    message( STATUS "    Installing system-libraries: MinGW DLLs." )
    get_filename_component( Mingw_Path ${CMAKE_CXX_COMPILER} PATH )
    file(GLOB CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS  ${Mingw_Path}/*.dll)
#    set( CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS ${Mingw_Path}/libgcc_s_dw2-1.dll ${Mingw_Path}/libstdc++-6.dll )
endif( MINGW )
include( InstallRequiredSystemLibraries )

include("${PROJECT_SOURCE_DIR}/cmake/GitCheckout.cmake")

find_package(SFML 2.5 COMPONENTS graphics audio system REQUIRED)
set(SFML_LIBS sfml-graphics sfml-window sfml-system sfml-audio)

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


install(TARGETS chip8 core implementation DESTINATION bin)
file(GLOB SFML_DLLS "${SFML_DIR}/lib/*.dll")
message(SFML_DLLS)
install(FILES ${SFML_DLLS} DESTINATION bin)
if( CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS )
    install( PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION bin COMPONENT System )
endif( CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS )
#install(SCRIPT "cmake/bundle.cmake")