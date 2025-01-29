#ifndef CHECK_BUTTON_H
#define CHECK_BUTTON_H

#include "./../../global.h"
#include "./button.h"

/* default values  */

#define DEFAULT_CHECK_BUTTON_DIMENSIONS \
    {                                   \
        .width = 0,                     \
        .height = 0}

#define DEFAULT_CHECK_BUTTON_MARGIN \
    {                              \
        .bottom = 0,               \
        .top = 0,                  \
        .start = 0,                \
        .end = 0}

#define DEFAULT_CHECK_BUTTON                           \
    {                                                  \
        .label = "\0",                                 \
        .tooltip = "\0",                               \
        .is_active = FALSE,                            \
        .is_inconsistent = FALSE,                      \
        .use_underline = FALSE,                        \
        .dimensions = DEFAULT_CHECK_BUTTON_DIMENSIONS, \
        .margins = DEFAULT_CHECK_BUTTON_MARGIN, \
        .bg_color = "\0",                              \
        .text_color = "\0"}

/**
 * @brief Structure de configuration pour un bouton check.
 */
typedef struct
{
    gchar label[MAX_BUTTON_LABEL_SIZE];
    gchar tooltip[MAX_TOOLTIP_SIZE];
    gboolean is_active;
    gboolean is_inconsistent;
    gboolean use_underline;
    Dimensions dimensions;
    Margins margins;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];
} CheckButtonConfig;

/**
 * @brief Initialise une structure de configuration pour un bouton check.
 * @param label Le texte affiché sur le bouton.
 * @param is_active État initial actif ou inactif.
 * @return Un pointeur vers la configuration initialisée.
 */
ViewConfig *init_check_button_config(FILE *index, CheckButtonConfig *check_button_config);

/**
 * @brief Crée un nouveau bouton check basé sur une configuration.
 * @param check_button_config La configuration utilisée pour créer le bouton.
 * @return Un pointeur vers le GtkWidget représentant le bouton check.
 */
GtkWidget *create_check_button(CheckButtonConfig check_button_config);

#endif // CHECK_BUTTON_H