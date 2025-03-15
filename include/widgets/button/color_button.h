#ifndef COLOR_BUTTON_H
#define COLOR_BUTTON_H

#include "./../../global.h"

/* Max size of element */
#define MAX_COLOR_BUTTON_LABEL_SIZE 50

/*  default values */
#define DEFAULT_COLOR_BUTTON_DIMENSIONS \
    {                                   \
        .height = 0,                    \
        .width = 0}

#define DEFAULT_COLOR_BUTTON_ICON_DIMENSIONS \
    {                                        \
        .height = 0,                         \
        .width = 0}

#define DEFAULT_COLOR_BUTTON_MARGINS \
    {                                \
        .bottom = 0,                 \
        .top = 0,                    \
        .start = 0,                  \
        .end = 0}

#define DEFAULT_COLOR_BUTTON                           \
    {                                                  \
        .is_sensitive = TRUE,                          \
        .is_visible = TRUE,                            \
        .tooltip = "\0",                               \
        .dimensions = DEFAULT_COLOR_BUTTON_DIMENSIONS, \
        .margins = DEFAULT_COLOR_BUTTON_MARGINS,       \
        .hexpand = FALSE,                              \
        .vexpand = FALSE,                              \
        .halign = GTK_ALIGN_FILL,                      \
        .valign = GTK_ALIGN_FILL,                      \
    }

typedef struct
{
    /* Basic properties */
    gboolean is_sensitive;           // Whether the button is clickable or not
    gboolean is_visible;             // Whether the button is visible or hidden
    gchar tooltip[MAX_TOOLTIP_SIZE]; // Tooltip text shown when hovering over the button

    /* Dimensions and placement */
    Dimensions dimensions; // dimensions of the button
    Margins margins;       // margin of the button
    gboolean hexpand;
    gboolean vexpand;
    GtkAlign halign;
    GtkAlign valign;
} ColorButtonConfig;

ViewConfig *init_color_button_config(FILE *index, ColorButtonConfig *color_button_config);

// ViewConfig *init_color_button_config(FILE *index, ColorButtonConfig *color_button_config);

/**
 * @brief create coordinate button widget with default
 * @param[in] coor_button coordinate button structure root_view for signals
 * @return[ou] GtkWidget pointer to new coordinate button widget
 */
GtkWidget *create_color_button(ColorButtonConfig color_button);

ColorButtonConfig *read_color_button_config_from_dialog();

ColorButtonConfig *read_color_button_config_from_widget(GtkWidget *widget);

gchar *write_color_button_property(FILE *output_file, View *view, int tabs_number);

#endif