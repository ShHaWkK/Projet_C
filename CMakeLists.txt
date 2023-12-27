cmake_minimum_required(VERSION 3.23)
project(${PROJECT_NAME} C)

set(CMAKE_C_STANDARD 11)

### SDL , SDL Mixer, SDL_ttf ##
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)
set(SDL2_PATH "C:/C_libraries/SDL2-2.28.5/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "C:/C_libraries/SDL2_ttf-2.20.2/x86_64-w64-mingw32")
set(SDL2_TTF_INCLUDE_DIR "C:/C_libraries/SDL2_ttf-2.20.2/x86_64-w64-mingw32/include")
set(SDL2_TTF_LIBRARY "C:/C_libraries/SDL2_ttf-2.20.2/x86_64-w64-mingw32/lib/libSDL2_ttf.dll.a")
set(SDL2_MIXER_PATH "C:/C_libraries/SDL2_mixer-2.6.3/x86_64-w64-mingw32")
set(SDL2_MIXER_INCLUDE_DIR "C:/C_libraries/SDL2_mixer-2.6.3/x86_64-w64-mingw32/include")
set(SDL2_MIXER_LIBRARIES "C:/C_libraries/SDL2_mixer-2.6.3/x86_64-w64-mingw32/lib/libSDL2_mixer.dll.a")

### Find Packages ##
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

### Include directories ###
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIRS} )


file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
add_executable(${PROJECT_NAME}
        src/main.c
        src/game.c
        src/ui.c
        src/character.c
        src/game.h
        src/ui.h
        src/character.h
        src/include.h
        assets/
        )
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARIES} )