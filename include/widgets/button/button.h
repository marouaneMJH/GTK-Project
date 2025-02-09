#ifndef BUTTON_H
#define BUTTON_H

// todo button icon
// todo button image
// todo background-color problem

#include "./../../global.h"

/* Max size of element */
#define MAX_BUTTON_LABEL_SIZE 50

/*  default values */
#define DEFAULT_BUTTON_DIMENSIONS \
    {                             \
        .height = 0,              \
        .width = 0}

#define DEFAULT_BUTTON_ICON_DIMENSIONS \
    {                                  \
        .height = 32,                  \
        .width = 32}

#define DEFAULT_BUTTON_MARGINS \
    {                          \
        .bottom = 0,           \
        .top = 0,              \
        .start = 0,            \
        .end = 0}

#define DEFAULT_BUTTON                                     \
    {                                                      \
        .label = "Click here",                             \
        .is_sensitive = TRUE,                              \
        .is_visible = TRUE,                                \
        .tooltip = "\0",                                   \
        .dimensions = DEFAULT_BUTTON_DIMENSIONS,           \
        .icon_dimensions = DEFAULT_BUTTON_ICON_DIMENSIONS, \
        .margins = DEFAULT_BUTTON_MARGINS,                 \
        .hexpand = FALSE,                                  \
        .vexpand = FALSE,                                  \
        .icon_path = "\0",                                 \
        .halign = GTK_ALIGN_CENTER,                        \
        .valign = GTK_ALIGN_CENTER,                        \
        .always_show_image = TRUE,                        \
        .focus_on_click = TRUE,                            \
        .use_underline = FALSE,                            \
        .use_stock = FALSE,                                \
        .icon_position = GTK_POS_LEFT,                     \
        .onclick = "\0",                                   \
        .bg_color = "\0",                                  \
        .color = "\0"}

typedef struct
{
    /* Basic properties */
    gchar label[MAX_BUTTON_LABEL_SIZE]; // The text displayed on the button
    gboolean is_sensitive;              // Whether the button is clickable or not
    gboolean is_visible;                // Whether the button is visible or hidden
    gchar tooltip[MAX_TOOLTIP_SIZE];    // Tooltip text shown when hovering over the button

    /* Dimensions and placement */
    Dimensions dimensions; // dimensions of the button
    Margins margins;       // margin of the button
    gboolean hexpand;      // If the button expands in its container (horizontal)
    gboolean vexpand;      // If the button expands in its container (vertical)

    gchar onclick[MAX_SIGNAL_NAME_SIZE]; // Path to the icon image file
    gchar icon_path[MAX_ICON_PATH_SIZE]; // Path to the icon image file
    Dimensions icon_dimensions;          // Dimensions of the icon image

    GtkAlign halign;               // Horizontal alignment of the button label
    GtkAlign valign;               // Vertical alignment of the button label
    gboolean always_show_image;    // Whether to always show the image
    gboolean use_underline;        // Whether to use underline in the button label
    GtkPositionType icon_position; // Whether to use underline in the button label

    /* Button appearance */
    gchar bg_color[MAX_COLOR_SIZE]; // Background color (e.g., "\0")
    gchar color[MAX_COLOR_SIZE];    // Text color (e.g., "#0000000")

    // @deprecated
    gboolean use_stock;      // Whether to use stock items for the button (deprecated)
    gboolean focus_on_click; // Whether the button grabs focus when clicked (deprecated)
    gfloat alignment_x;      // Horizontal alignment of the button label (deprecated)
    gfloat alignment_y;      // Vertical alignment of the button label (deprecated)

} ButtonConfig;

ViewConfig *init_button_config(FILE *index, ButtonConfig *button_config);

/**
 * @brief create button widget with default
 * @param[in] button button structure root_view for signals
 * @return[ou] GtkWidget pointer to new button widget
 */
GtkWidget *create_button(ButtonConfig button, View* root_view);

#endif
