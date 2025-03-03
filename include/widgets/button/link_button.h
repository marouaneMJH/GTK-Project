#ifndef LINK_BUTTON_H
#define LINK_BUTTON_H

#include "./../../global.h"
#include "./button.h"

/* default values  */
#define DEFAULT_LINK_BUTTON_DIMENSIONS \
    {                                  \
        .height = 0,                   \
        .width = 0}

#define DEFAULT_LINK_BUTTON_MARGIN \
    {                              \
        .bottom = 0,               \
        .top = 0,                  \
        .start = 0,                \
        .end = 0}

#define DEFAULT_LINK_BUTTON                           \
    {                                                 \
        .uri = "\0",                                  \
        .label = "\0",                                \
        .tooltip = "\0",                              \
        .is_visited = FALSE,                          \
        .dimensions = DEFAULT_LINK_BUTTON_DIMENSIONS, \
        .margins = DEFAULT_LINK_BUTTON_MARGIN,        \
        .hexpand = FALSE,                       \
        .vexpand = FALSE,                       \
        .halign = GTK_ALIGN_FILL,               \
        .valign = GTK_ALIGN_FILL,               \
        .bg_color = "\0",                             \
        .text_color = "\0"}

/* Struct definition */
typedef struct
{
    gchar uri[MAX_URI_SIZE];
    gchar label[MAX_BUTTON_LABEL_SIZE];
    gchar tooltip[MAX_TOOLTIP_SIZE];
    gboolean is_visited;


    gboolean hexpand;
    gboolean vexpand;
    GtkAlign halign;
    GtkAlign valign;
    Dimensions dimensions;
    Margins margins;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];
} LinkButtonConfig;

/**
 * @brief Initializes a LinkButtonConfig struct with given values.
 * @param uri The URI to associate with the link button.
 * @param label The label text to display on the button.
 * @return Pointer to the newly allocated and initialized LinkButtonConfig.
 */
ViewConfig *init_link_button_config(FILE *index, LinkButtonConfig *link_button_config);

/**
 * @brief Creates a GtkWidget for a link button using a LinkButtonConfig.
 * @param config The configuration for the link button.
 * @return Pointer to the newly created GtkWidget representing the link button.
 */
GtkWidget *create_link_button(LinkButtonConfig config);

LinkButtonConfig *read_link_button_config_from_dialog();

gchar *write_link_button_property(FILE *output_file, View *view, int tabs_number);

#endif // LINK_BUTTON_H