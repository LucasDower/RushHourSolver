# CMakeList.txt : CMake project for RushHour, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (RushHour "RushHour.cpp" "Board.cpp" "Board.h" "Util.h" "Piece.h" "Config.h" "Util.cpp" "Piece.cpp" "Config.cpp")

target_compile_features(RushHour PUBLIC cxx_std_20)

# TODO: Add tests and install targets if needed.
