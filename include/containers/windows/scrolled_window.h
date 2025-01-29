#ifndef SCROLLED_WINDOW_H
#define SCROLLED_WINDOW_H

#include "../../global.h"


// Configuration par défaut pour la fenêtre à défilement

#define DEFAULT_SCROLLED_WINDOW        \
    {                                  \
        .h_adjustment = NULL,          \
        .v_adjustment = NULL,          \
        .h_policy = GTK_POLICY_AUTOMATIC, \
        .v_policy = GTK_POLICY_AUTOMATIC, \
    }

// Structure de configuration pour la fenêtre à défilement
typedef struct
{
    GtkAdjustment *h_adjustment;
    GtkAdjustment *v_adjustment;
    GtkPolicyType h_policy;
    GtkPolicyType v_policy;
} ScrolledWindowConfig;

ViewConfig *init_scrolled_window_config(FILE *index, ScrolledWindowConfig *scrolled_window_config);

/**
 * @brief Crée une fenêtre à défilement en utilisant la configuration spécifiée.
 *
 * @param config Pointeur vers la structure ScrolledWindowConfig.
 * @return GtkWidget* Widget de type GtkScrolledWindow ou NULL en cas d'échec.
 */

GtkWidget *create_scrolled_window(ScrolledWindowConfig scrolled_window_config);

#endif
