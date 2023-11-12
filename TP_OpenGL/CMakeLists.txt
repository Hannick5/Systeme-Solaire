cmake_minimum_required(VERSION 3.5)

project(TP_OpenGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TP_OpenGL pointlight.h pointlight.cpp ambientlight.h ambientlight.cpp navigationcontrols.h navigationcontrols.cpp main.cpp camera.h camera.cpp controls.h controls.cpp object.cpp object.h renderer.cpp renderer.h texture.cpp texture.h uvbuffer.cpp uvbuffer.h vertexarray.cpp  vertexarray.h vertexbuffer.cpp vertexbuffer.h shader.cpp shader.h stb_image/stb_image.cpp stb_image/stb_image.h)

target_link_libraries(TP_OpenGL glfw GLEW libGLEW.so libGLU.so libGL.so)
