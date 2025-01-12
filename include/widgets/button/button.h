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
        .height = 0,            \
        .width = 0}

#define DEFAULT_BUTTON_MARGINS \
    {                          \
        .bottom = 0,           \
        .top = 0,              \
        .start = 0,            \
        .end = 0}

#define DEFAULT_BUTTON                           \
    {                                            \
        .label = "Click here",                   \
        .is_sensitive = TRUE,                    \
        .is_visible = TRUE,                      \
        .tooltip = "\0",                         \
        .dimensions = DEFAULT_BUTTON_DIMENSIONS, \
        .margins = DEFAULT_BUTTON_MARGINS,         \
        .expand = FALSE,                         \
        .bg_color = "\0",                   \
        .text_color = "\0"}

typedef struct
{
    /* Basic properties */
    gchar label[MAX_BUTTON_LABEL_SIZE];          // The text displayed on the button
    gboolean is_sensitive; // Whether the button is clickable or not
    gboolean is_visible;   // Whether the button is visible or hidden
    gchar tooltip[MAX_TOOLTIP_SIZE];        // Tooltip text shown when hovering over the button

    /* Dimensions and placement */
    Dimensions dimensions; // dimensions of the button
    Margins margins;         // margin of the button
    gboolean expand;       // If the button expands in its container

    /* Button appearance */
    gchar bg_color[MAX_COLOR_SIZE];   // Background color (e.g., "\0")
    gchar text_color[MAX_COLOR_SIZE]; // Text color (e.g., "#0000000" )

} ButtonConfig;


ViewConfig *init_button_config(FILE *index, ButtonConfig *button_config);

/**
 * @brief create button widget with default
 * @param[in] button button structure
 * @return[ou] GtkWidget pointer to new button widget
 */
GtkWidget *create_button(ButtonConfig button);


#endif