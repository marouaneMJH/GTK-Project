#ifndef BOX_H
#define BOX_H

#include "./../../global.h"

/*  default values */
#define DEFAULT_BOX_DIMENSIONS \
    {                          \
        .height = 100,         \
        .width = 100}

#define DEFAULT_BOX_MARGINS \
    {                       \
        .bottom = 0,        \
        .top = 0,           \
        .start = 0,         \
        .end = 0}

#define DEFAULT_BOX                                        \
    {                                                      \
        .orientation = GTK_ORIENTATION_VERTICAL,           \
        .spacing = 0,                                      \
        .homogeneous = FALSE,                              \
        .center_widget = NULL,                             \
        .baseline_position = GTK_BASELINE_POSITION_CENTER, \
        .margins = DEFAULT_BOX_MARGINS,                    \
        .dimensions = DEFAULT_BOX_DIMENSIONS,              \
        .bg_color = "\0",                                  \
        .text_color = "\0",                                \
        .bg_image = "\0"}

typedef struct
{
    GtkOrientation orientation;
    // Put a space between children
    gint spacing;
    // Give the same size to all children
    gboolean homogeneous;

    GtkWidget *center_widget;

    // Baseline position
    GtkBaselinePosition baseline_position;

    Margins margins;

    Dimensions dimensions;

    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

    // bg path image
    gchar bg_image[MAX_ICON_PATH_SIZE];

} BoxConfig;

gchar *init_box_config(FILE *index, BoxConfig *box_config, ViewConfig *view_config);

/**
 * @brief create box widget with default
 * @param[in] box box structure
 * @return[ou] GtkWidget pointer to new box widget
 */
GtkWidget *create_box(BoxConfig box_config);

#endif