#ifndef TOGGLE_BUTTON_H
#define TOGGLE_BUTTON_H

#include "./../../global.h"
#include "./../../../include/widgets/button/button.h"

/* Valeurs par défaut */
#define DEFAULT_TOGGLE_BUTTON_DIMENSIONS \
    {                                    \
        .height = 0,                     \
        .width = 0                        \
    }

#define DEFAULT_TOGGLE_BUTTON_MARGINS \
    {                                 \
        .bottom = 0,                  \
        .top = 0,                     \
        .start = 0,                   \
        .end = 0                       \
    }

#define DEFAULT_TOGGLE_BUTTON                           \
    {                                                   \
        .label = "",                                    \
        .tooltip = "",                                  \
        .is_mnemonic = FALSE,                           \
        .is_active = FALSE,                             \
        .is_visible = FALSE,                            \
        .mode = TRUE,                                   \
        .is_inconsistent = FALSE,                       \
        .hexpand = FALSE,                                  \
        .vexpand = FALSE,                                  \
        .halign = GTK_ALIGN_FILL,                          \
        .valign = GTK_ALIGN_FILL,                          \
        .dimensions = DEFAULT_TOGGLE_BUTTON_DIMENSIONS, \
        .margins = DEFAULT_TOGGLE_BUTTON_MARGINS,       \
        .bg_color = "",                                 \
        .text_color = ""                                \
    }

/* Structure de configuration du Toggle Button */
typedef struct
{
    gchar label[MAX_BUTTON_LABEL_SIZE];
    gchar tooltip[MAX_TOOLTIP_SIZE];
    gboolean is_mnemonic;   // Utilisation des mnemonics dans le label
    gboolean is_active;     // Détermine si le bouton est activé/désactivé
    gboolean is_visible;    // Détermine si le bouton est affiché
    gboolean mode;          // Affichage du bouton avec/sans indicateur
    gboolean is_inconsistent; // État intermédiaire du bouton
    gboolean hexpand;
    gboolean vexpand;
    GtkAlign halign;
    GtkAlign valign;
    Dimensions dimensions;
    Margins margins;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} ToggleButtonConfig;

/* Fonction d'initialisation */
ViewConfig *init_toggle_button_config(FILE *index, ToggleButtonConfig *toggle_button_config);

/* Fonction de création */
GtkWidget *create_toggle_button(ToggleButtonConfig toggle_button_config);

/* Fonction pour appliquer les styles CSS dynamiques */
void apply_toggle_button_css(GtkWidget *toggle_button, const gchar *bg_color, const gchar *text_color);

/* Connexion des signaux */
void connect_toggle_button_signal(GtkWidget *toggle_button);

/* Fonctions pour manipuler l'état du ToggleButton */
void set_toggle_button_active(GtkWidget *toggle_button, gboolean is_active);
gboolean get_toggle_button_active(GtkWidget *toggle_button);

void set_toggle_button_mode(GtkWidget *toggle_button, gboolean mode);
gboolean get_toggle_button_mode(GtkWidget *toggle_button);

void set_toggle_button_inconsistent(GtkWidget *toggle_button, gboolean is_inconsistent);
gboolean get_toggle_button_inconsistent(GtkWidget *toggle_button);

#endif
