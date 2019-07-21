cmake_minimum_required(VERSION 3.12)
project(noise_maker C)
set(THREADS_PREFER_PTHREAD_FLAG ON)


find_package(OpenGL)
find_package(Threads REQUIRED)
include_directories(./src)
# apparently ${SDL_LIBRARIES} contains terminating whitespace
# so we need this policy to deactivate the error
# see https://cmake.org/cmake/help/v3.0/policy/CMP0004.html and
# https://cmake.org/cmake/help/v3.0/command/cmake_policy.html
cmake_policy(SET CMP0004 OLD)

set(CMAKE_C_STANDARD 11)

set(SOURCES  src/renderer.h src/renderer.c src/logging.h src/logging.c src/input.h src/input.c src/program.h src/program.c src/audio.h src/audio.c src/note.h src/note.c src/vec.h src/instrument.h src/instrument.c src/data_structure/double_pair.h src/data_structure/int64_t_pair.h src/sound_drawing_canvas.h src/vec.c src/box.h src/box.c test/test_box.h)
add_executable(noise_maker src/main.c ${SOURCES} src/constants.h)
target_link_libraries(noise_maker SDL2)
target_link_libraries(noise_maker SDL2_ttf)
target_link_libraries(noise_maker ${OPENGL_gl_LIBRARY})
target_link_libraries(noise_maker m) # C standard maths library
target_link_libraries(noise_maker portaudio)
target_link_libraries(noise_maker Threads::Threads)

add_executable(noise_maker_tests test/main.c ${SOURCES} test/test_box.h)
target_link_libraries(noise_maker_tests SDL2)
target_link_libraries(noise_maker_tests ${OPENGL_gl_LIBRARY})
target_link_libraries(noise_maker_tests m) # C standard maths library
target_link_libraries(noise_maker_tests portaudio)
target_link_libraries(noise_maker_tests Threads::Threads)