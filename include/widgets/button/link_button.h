#ifndef LINK_BUTTON_H
#define LINK_BUTTON_H

#include "./../../global.h"
#include "./button.h"     

/* default values  */
#define DEFAULT_LINK_BUTTON_DIMENSIONS \
    {                                   \
        .height = 0,                    \
        .width = 0                      \
    }

#define DEFAULT_LINK_BUTTON_MARGIN \
    {                               \
        .bottom = 0,                \
        .top = 0,                   \
        .start = 0,                 \
        .end = 0                    \
    }

#define DEFAULT_LINK_BUTTON                           \
    {                                                 \
        .uri = "\0",                                  \
        .label = "\0",                                \
        .tooltip = "\0",                              \
        .is_visited = FALSE,                          \
        .dimensions = DEFAULT_LINK_BUTTON_DIMENSIONS, \
        .bg_color = "\0",                             \
        .text_color = "\0"                            \
    }

/* Struct definition */
typedef struct
{
    gchar uri[MAX_URI_SIZE];
    gchar label[MAX_BUTTON_LABEL_SIZE];
    gchar tooltip[MAX_TOOLTIP_SIZE];
    gboolean is_visited;
    Dimensions dimensions;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];
} LinkButtonConfig;



/**
 * @brief Initializes a LinkButtonConfig struct with given values.
 * @param uri The URI to associate with the link button.
 * @param label The label text to display on the button.
 * @return Pointer to the newly allocated and initialized LinkButtonConfig.
 */
LinkButtonConfig *init_link_button_config(const gchar *uri, const gchar *label);

/**
 * @brief Creates a GtkWidget for a link button using a LinkButtonConfig.
 * @param config The configuration for the link button.
 * @return Pointer to the newly created GtkWidget representing the link button.
 */
GtkWidget *create_link_button(LinkButtonConfig config);

// /**
//  * @brief Updates an existing link button widget with new properties.
//  * @param button The GtkWidget representing the link button to update.
//  * @param config The new configuration for the link button.
//  */
// void update_link_button(GtkWidget *button, LinkButtonConfig config);

// /**
//  * @brief Frees resources associated with a link button configuration.
//  * @param config The LinkButtonConfig to free.
//  */
// void free_link_button_config(LinkButtonConfig *config);

#endif // LINK_BUTTON_H