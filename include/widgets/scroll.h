#ifndef SCROLL_H
#define SCROLL_H

#include "./../global.h"

// Configuration par défaut pour la fenêtre à défilement

#define DEFAULT_SCROLLED_WINDOW_CONFIG                 \
    {                                                  \
        .h_adjustment = NULL,                          \
        .v_adjustment = NULL,                          \
        .h_policy = GTK_POLICY_ALWAYS,                 \
        .v_policy = GTK_POLICY_ALWAYS,                 \
        .content = NULL,                               \
        .window = NULL                                 \
    }


// Structure de configuration pour la fenêtre à défilement
typedef struct {
    GtkAdjustment *h_adjustment;
    GtkAdjustment *v_adjustment;
    GtkPolicyType h_policy;
    GtkPolicyType v_policy;
    GtkWidget *content;
    GtkWidget *window;
} ScrolledWindowConfig;


// Initialise une configuration de fenêtre à défilement
ScrolledWindowConfig *init_scrolled_window_config(void);


/**
 * @brief Crée une fenêtre à défilement en utilisant la configuration spécifiée.
 * 
 * @param config Pointeur vers la structure ScrolledWindowConfig.
 * @return GtkWidget* Widget de type GtkScrolledWindow ou NULL en cas d'échec.
 */

GtkWidget *create_scrolled_window(ScrolledWindowConfig  scrolled_window_config);

#endif // SCROLL_H
