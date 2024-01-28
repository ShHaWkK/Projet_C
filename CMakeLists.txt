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

set(SDL2_IMAGE_PATH "C:/C_libraries/SDL2_image-2.8.2/x86_64-w64-mingw32")
set(SDL2_IMAGE_INCLUDE_DIR "C:/C_libraries/SDL2_image-2.8.2/x86_64-w64-mingw32/include")
set(SDL2_IMAGE_LIBRARY "C:/C_libraries/SDL2_image-2.8.2/x86_64-w64-mingw32/lib/libSDL2_image.dll.a")
#link_directories(/"")
include_directories(C:/C_libraries/sqlite-dll-win-x64-3440200)
link_directories(C:/C_libraries/sqlite-dll-win-x64-3440200)
### Find Packages ##
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

### Include directories ###
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR} )


file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
add_executable(${PROJECT_NAME}
        src/main.c
        src/game.c
        src/ui.c
        src/Log.c
        src/survivor.c
        src/audio.c
        src/database.c
        src/text_input.c
        src/colision.c
        src/playerControlleur.c
        src/map.c
        src/save.c
        src/buildMenu.c
        src/trailer.c
        src/logo.c
        src/buildMenu.c
        #.h
        include/buildMenu.h
        include/game.h
        include/ui.h
        include/audio.h
        include/survivor.h
        include/include.h
        include/database.h
        include/Log.h
        include/text_input.h
        include/trailer.h
        include/logo.h
        include/playerControlleur.h
        include/map.h
        include/colision.h
        assets/
        survivor_colony.db
         )
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARIES} ${SDL2_IMAGE_LIBRARY} sqlite3 )