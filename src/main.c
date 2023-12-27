#include "game.h"
#include "Log.h"

int main(int argc, char* argv[]) {
    Log_Init("game.log");
    Game_Init();

    Game_Run();

    Game_Shutdown();

    return 0;
}
