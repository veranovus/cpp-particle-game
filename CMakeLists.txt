cmake_minimum_required(VERSION 3.20)
project(particle_game)

set(CMAKE_CXX_STANDARD 14)
set(IMGUI_SOURCE_FILES src/vendor/imgui/imgui.cpp src/vendor/imgui/imgui_demo.cpp src/vendor/imgui/imgui_draw.cpp src/vendor/imgui/imgui_impl_glfw.cpp src/vendor/imgui/imgui_impl_opengl3.cpp src/vendor/imgui/imgui_tables.cpp src/vendor/imgui/imgui_widgets.cpp)

# Include directories for Other External Libraries
include_directories(src/vendor)
include_directories(src/vendor/imgui)

# Include directories for GLEW and GLFW
include_directories(/opt/homebrew/Cellar/glew/2.2.0_1/include)
include_directories(/opt/homebrew/Cellar/glfw/3.3.4/include)
link_directories(/opt/homebrew/Cellar/glew/2.2.0_1/lib)
link_directories(/opt/homebrew/Cellar/glfw/3.3.4/lib)

# We include our source files here
add_executable(particle_game main.cpp ${IMGUI_SOURCE_FILES})

# Link the necessary libraries
find_package(OpenGL REQUIRED)
target_link_libraries(particle_game PRIVATE OpenGL::GL)

find_package(glfw3 REQUIRED)
target_link_libraries(particle_game PRIVATE glfw.3.3)
find_package(GLEW REQUIRED)
target_link_libraries(particle_game PRIVATE GLEW)