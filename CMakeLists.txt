# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("RushHour")

# Include sub-projects.
add_subdirectory ("RushHour")

target_compile_features(RushHour PRIVATE cxx_std_20)