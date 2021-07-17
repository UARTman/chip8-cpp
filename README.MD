# CHIP-8 Emulator

This is a CHIP-8 emulator written in C++

## Running

Just start the executable. It comes pre-loaded with a demo ROM. 

## Building

## Linux

You'll need SFML and CMake. Clone this, making sure that you include submodules. Then build it with cmake.

Example:
```shell
git clone --recurse-submodules https://github.com/UARTman/chip8-cpp
cd chip8-cpp
mkdir build
cd build
cmake ..
make
```

## Windows

Building this on Windows is a complicated proccess. I suggest you don't. 
However, in the interest of showing off this project to my friends, I have added windows support.

Here's how it's done:


- Install MinGW-w64 toolchain (**not** MSVC!) and CMake. 
- Download and build SFML using this toolchain.
- Set CMake variable `SFML_DIR` to path to SFML you built
- Set install prefix somewhere where you have write permissions
- Build the project
- Using `mingw32-make install`, install the project into the install prefix
- The executable and all the dlls it needs are in the `bin` subdirectory of the install prefix.

## TODO
- [x] Keyboard support
- [x] Sound
- [x] Memory safety checks
- [ ] Graceful error handling
- [x] Screen architecture refactoring