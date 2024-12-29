#ifndef BUTTON_H
#define BUTTON_H

#include "./../../global.h"

/* Max size of element */
#define MAX_BUTTON_LABEL_SIZE 50
#define MAX_ICON_NAME_SIZE 100
#define MAX_BUTTON_TOOLTIP_SIZE 100

/*  default values */
#define DEFAULT_BUTTON_DIMENSIONS \
    {                             \
        .height = 0,              \
        .width = 0}

#define DEFAULT_BUTTON_MARGIN \
    {                         \
        .bottom = 0,          \
        .top = 0,             \
        .start = 0,           \
        .end = 0}

#define DEFAULT_BUTTON                           \
    {                                            \
        .label = "Click here",                   \
        .is_sensitive = TRUE,                    \
        .is_visible = TRUE,                      \
        .tooltip = "\0",                         \
        .dimensions = DEFAULT_BUTTON_DIMENSIONS, \
        .margin = DEFAULT_BUTTON_MARGIN,         \
        .expand = FALSE,                         \
        .bg_color = "#FFFFFF",                   \
        .text_color = "#333333"}

typedef struct
{
    /* Basic properties */
    gchar label[MAX_BUTTON_LABEL_SIZE];          // The text displayed on the button
    gboolean is_sensitive; // Whether the button is clickable or not
    gboolean is_visible;   // Whether the button is visible or hidden
    gchar tooltip[MAX_BUTTON_TOOLTIP_SIZE];        // Tooltip text shown when hovering over the button

    /* Dimensions and placement */
    Dimensions dimensions; // dimensions of the button
    Margin margin;         // margin of the button
    gboolean expand;       // If the button expands in its container

    /* Button appearance */
    gchar bg_color[MAX_COLOR_SIZE];   // Background color (e.g., "#FFFFFF")
    gchar text_color[MAX_COLOR_SIZE]; // Text color (e.g., "#0000000" )

} Button;

/**
 * @brief customize button structure
 * @param button structure field
 * @return[ou] pointer to new button structure
 */
Button edit_button(
    gchar *label,
    gboolean is_sensitive,
    gboolean is_visible,
    gchar *tooltip,
    Dimensions dimensions,
    Margin margin,
    gboolean expand,
    gchar *bg_color,
    gchar *text_color

);

/**
 * @brief create button widget with default
 * @param[in] button button structure
 * @return[ou] GtkWidget pointer to new button widget
 */
GtkWidget *create_button(Button button);

#endif