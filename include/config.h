#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    int volume; // Volume du jeu
    int resolution[2]; // Largeur et hauteur pour la résolution
    int pleinEcran; // 1 pour plein écran, 0 sinon
    char toucheAction; // Touche pour une action spécifique
    // Autres touches...
} ConfigurationsJeu;

void ChargerConfigurations(ConfigurationsJeu* config);
void SauvegarderConfigurations(const ConfigurationsJeu* config);
void ModifierVolume(ConfigurationsJeu* config, int volume);
void ModifierResolution(ConfigurationsJeu* config, int largeur, int hauteur);
void ActiverPleinEcran(ConfigurationsJeu* config, int activer);
void ConfigurerToucheAction(ConfigurationsJeu* config, char touche);

#endif // CONFIG_H
