
cmake_minimum_required (VERSION 3.8)

project ("FinalProject")

# Add source to this project's executable.
add_executable (FinalProject "FinalProject.cpp" )

# TODO: Add tests and install targets if needed.

target_include_directories(FinalProject PUBLIC "./SFML-2.5.1/include" )
target_link_directories(FinalProject PUBLIC "./SFML-2.5.1/lib")

target_link_libraries(FinalProject PUBLIC "sfml-system-d" "sfml-audio-d" "sfml-window-d" "sfml-graphics-d")