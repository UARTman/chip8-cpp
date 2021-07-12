add_library(core common.h CPU.cpp CPU.h Instructions.cpp Screen.cpp Screen.h Sprites.cpp)
target_link_libraries(core)