cmake_minimum_required(VERSION 3.23)
project(Projet_C C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)
###### SDL ############
set(SDL2_PATH "C:/C_libraries/SDL2-devel-2.28.5-mingw/x86_64-w64-mingw32")
###### SDL MIXER #######
set(SDL_MIXER_LIBRARY "C:/C_libraries/SDL2_mixer-2.6.3/x86_64-w64-mingw32/lib/libSDL2_mixer.dll.a")
set(SDL_MIXER_INCLUDE_DIR "C:/C_libraries/SDL2_mixer-2.6.3/x86_64-w64-mingw32/include")
######## SDL TTF ########
set(SDL_TTF_INCLUDE_DIR "C:/C_libraries/SDL2_ttf-2.20.2/x86_64-w64-mingw32/include")
set(SDL_TTF_LIBRARY "C:/C_libraries/SDL2_ttf-2.20.2/x86_64-w64-mingw32/lib/libSDL2_ttf.dll.a")

# Ajout du dossier de la bibliothèque SDL_ttf

find_package(SDL2 REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)


include_directories(${SDL2_INCLUDE_DIR}
        ${SDLTTF_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIRS}
        (${SDL2_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIRS})

)
add_executable(Projet_C main.c)
target_link_libraries(Projet_C
        ${SDL2_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL_TTF_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL_TTF_LIBRARY} ${SDL2_MIXER_LIBRARIES})