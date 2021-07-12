set(IMFD ${PROJECT_SOURCE_DIR}/ImGuiFileDialog/ImGuiFileDialog.h ${PROJECT_SOURCE_DIR}/ImGuiFileDialog/ImGuiFileDialog.cpp ${PROJECT_SOURCE_DIR}/ImGuiFileDialog/ImGuiFileDialogConfig.h ${PROJECT_SOURCE_DIR}/ImGuiFileDialog/dirent/dirent.h)
add_library(implementation SFMLScreen.cpp SFMLScreen.h DebugCPU.cpp DebugCPU.h ${IMFD})
target_link_libraries(implementation PRIVATE core ${SFML_LIBS} ImGui-SFML::ImGui-SFML)
target_include_directories(implementation PRIVATE ${PROJECT_SOURCE_DIR})