cmake_minimum_required(VERSION 3.12)
project(noise_maker C)
set(THREADS_PREFER_PTHREAD_FLAG ON)


find_package(OpenGL)
find_package(Threads REQUIRED)
include_directories(.)
# apparently ${SDL_LIBRARIES} contains terminating whitespace
# so we need this policy to deactivate the error
# see https://cmake.org/cmake/help/v3.0/policy/CMP0004.html and
# https://cmake.org/cmake/help/v3.0/command/cmake_policy.html
cmake_policy(SET CMP0004 OLD)

set(CMAKE_C_STANDARD 11)

add_executable(noise_maker main.c renderer.h renderer.c logging.h logging.c input.h input.c program.h program.c audio.h audio.c note.h note.c vec2f.h instrument.h instrument.c data_structure/double_pair.h data_structure/int64_t_pair.h)
target_link_libraries(noise_maker SDL2)
target_link_libraries(noise_maker ${OPENGL_gl_LIBRARY})
target_link_libraries(noise_maker m) # C standard maths library
target_link_libraries(noise_maker portaudio)
target_link_libraries(noise_maker Threads::Threads)