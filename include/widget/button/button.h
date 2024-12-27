#ifndef BUTTON_H
#define BUTTON_H


// todo button icon
// todo button image
// todo background-color problem

#include "./../../global.h"

/* Max size of element */
#define MAX_BUTTON_LABEL 100
#define MAX_BUTTON_TOOLTIP 100

/*  default values */
#define DEFAULT_BUTTON_DIMENSIONS \
    {                             \
        .height = 100,            \
        .width = 100}

#define DEFAULT_BUTTON_MARGIN \
    {                         \
        .bottom = 0,          \
        .top = 0,             \
        .start = 0,           \
        .end = 0}

#define DEFAULT_BUTTON                                  \
    {                                                   \
        .label          = '\0',                      \
        .is_sensitive   = TRUE,                         \
        .is_visible     = TRUE,                         \
        .tooltip        = '\0',                         \
        .dimensions     = DEFAULT_BUTTON_DIMENSIONS,    \
        .margin         = DEFAULT_BUTTON_MARGIN,        \
        .expand = FALSE,                                \
        .bg_color = "#FFFF00",                          \
        .text_color = "#000000",                        \
        .image = NULL}

typedef struct
{
    /* Basic properties */
    gchar label[MAX_TEXT_LABEL];          // The text displayed on the button
    gboolean is_sensitive; // Whether the button is clickable or not
    gboolean is_visible;   // Whether the button is visible or hidden
    gchar tooltip[MAX_BUTTON_TOOLTIP];        // Tooltip text shown when hovering over the button

    /* Dimensions and placement */
    Dimensions dimensions; // dimensions of the button
    Margin margin;         // margin of the button
    gboolean expand;       // If the button expands in its container

    /* Button appearance */
    gchar bg_color[10];   // Background color (e.g., "#FFFFFF")
    gchar text_color[10]; // Text color (e.g., "#0000000" )

    /* widget relation */
    GtkWidget *image;

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

/**
 * @brief create button icon
 * @param[in] icon_name look here for more infomation https://www.notion.so/Button-1627f0b86e0380af9957e029522d8b22?pvs=4
 * @param icon_size enum, icon predefined size
 * @return icon on button form
 */
GtkWidget* create_button_icon(gchar* icon_name,GtkIconSize icon_size);

#endif