cmake_minimum_required(VERSION 3.2) # minimum version of Cmake required
project(MPAGSCipher VERSION 0.1.0) # project name/version decleration

set(CMAKE_VERBOSE_MAKEFILE ON) # turns on verbose mode so we can see what is happening as it builds

 # declare what executable to make and with what code
add_executable(mpags-cipher mpags-cipher.cpp 
    MPAGSCipher/TransformChar.cpp
    MPAGSCipher/ProcessCommandLine.cpp
    MPAGSCipher/RunCaesarCipher.cpp
    )

# we can directly set the version of c++ using
set(CMAKE_CXX_STANDARD 14)

# set file paths to allow the compiler to install our customn header files
target_include_directories(mpags-cipher PRIVATE MPAGSCipher)

# dont allow c++ compiler vendor extentions
set(CMAKE_CXX_EXTENSIONS OFF)

# declare flags for outr compiler (g++) to use
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic")

# here we are setting features that the compiler should implement when building mpags-cipher
# see https://cmake.org/cmake/help/v3.2/manual/cmake-compile-features.7.html for more
target_compile_features(mpags-cipher
    PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization
)
