cmake_minimum_required(VERSION 3.16)
project(PokerGame VERSION 1.0)

#Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQURED ON)

# Include headers from include/
include_directories(include)

# Collect all .cpp files in src/
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Set SFML
set(SFML_DIR "C:/Users/jovia/sfml/SFML-3.0.0/lib/cmake/SFML")

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Create executable and link SFML
add_executable(PokerGame ${SOURCES})

# Link SFML libraries
target_link_libraries(PokerGame sfml-graphics sfml-window sfml-system)