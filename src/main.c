#include "../include/game.h"
#include "../include/Log.h"

int main(int argc, char* argv[]) {
    Log_Init("game.log");
    //load_configuration("config.ini");
    //initialize_database();
    Game_Init();
    Game_Run();
    Game_Shutdown();

    return 0;
}
