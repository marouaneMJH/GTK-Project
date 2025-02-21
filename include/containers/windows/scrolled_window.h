#ifndef SCROLLED_WINDOW_H
#define SCROLLED_WINDOW_H

#include "../../global.h"

#define DEFAULT_SCROLLED_WINDOW_DIMENSIONS \
    {                                      \
        .height = 0,                       \
        .width = 0}

// Default Margins
#define DEFAULT_SCROLLED_WINDOW_MARGINS { \
    .bottom = 0,                          \
    .top = 0,                             \
    .start = 0,                           \
    .end = 0}

// Configuration par défaut pour la fenêtre à défilement
#define DEFAULT_SCROLLED_WINDOW                           \
    {                                                     \
        .h_adjustment = NULL,                             \
        .v_adjustment = NULL,                             \
        .h_policy = GTK_POLICY_AUTOMATIC,                 \
        .v_policy = GTK_POLICY_AUTOMATIC,                 \
        .hexpand = FALSE,                                 \
        .vexpand = FALSE,                                 \
        .halign = GTK_ALIGN_FILL,                         \
        .valign = GTK_ALIGN_FILL,                         \
        .dimensions = DEFAULT_SCROLLED_WINDOW_DIMENSIONS, \
        .bg_color = "\0",                                 \
        .text_color = "\0",                               \
        .margins = DEFAULT_SCROLLED_WINDOW_MARGINS}

// Structure de configuration pour la fenêtre à défilement
typedef struct
{
    GtkAdjustment *h_adjustment;
    GtkAdjustment *v_adjustment;
    GtkPolicyType h_policy;
    GtkPolicyType v_policy;

    gboolean hexpand;
    gboolean vexpand;

    GtkAlign halign;
    GtkAlign valign;

    // Margins
    Margins margins;
    Dimensions dimensions;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} ScrolledWindowConfig;

ViewConfig *init_scrolled_window_config(FILE *index, ScrolledWindowConfig *scrolled_window_config);

/**
 * @brief Crée une fenêtre à défilement en utilisant la configuration spécifiée.
 *
 * @param config Pointeur vers la structure ScrolledWindowConfig.
 * @return GtkWidget* Widget de type GtkScrolledWindow ou NULL en cas d'échec.
 */

GtkWidget *create_scrolled_window(ScrolledWindowConfig scrolled_window_config);

gchar *write_scrolled_window_property(FILE *output_file, View *view, int tabs_number);

#endif
