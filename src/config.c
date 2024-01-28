// config.c
#include "../include/config.h"
#include "../include/include.h"

void ChargerConfigurations(ConfigurationsJeu* config) {
    FILE *file = fopen("config.txt", "r");
    if (file == NULL) {
        printf("Fichier de configuration non trouvé. Utilisation des paramètres par défaut.\n");
        // Définir les valeurs par défaut
        config->volume = 50; // Volume par défaut
        config->resolution[0] = 800; // Largeur par défaut
        config->resolution[1] = 600; // Hauteur par défaut
        config->pleinEcran = 0; // Mode fenêtré par défaut
        config->toucheAction = 'A'; // Touche d'action par défaut
        return;
    }

    fscanf(file, "%d %d %d %d %c",
           &config->volume,
           &config->resolution[0],
           &config->resolution[1],
           &config->pleinEcran,
           &config->toucheAction);

    fclose(file);
}