#ifndef FIXED_H
#define FIXED_H

#include "./../../global.h"

/*  default values */
#define DEFAULT_FIXED_DIMENSIONS \
    {                          \
        .height = 0,           \
        .width = 0}

#define DEFAULT_FIXED_MARGINS \
    {                       \
        .bottom = 0,        \
        .top = 0,           \
        .start = 0,         \
        .end = 0}

#define DEFAULT_FIXED                                        \
    {                                                      \
        .orientation = GTK_ORIENTATION_VERTICAL,           \
        .spacing = 0,                                      \
        .homogeneous = FALSE,                              \
        .center_widget = NULL,                             \
        .baseline_position = GTK_BASELINE_POSITION_CENTER, \
        .margins = DEFAULT_FIXED_MARGINS,                    \
        .dimensions = DEFAULT_FIXED_DIMENSIONS,              \
        .bg_color = "\0",                                  \
        .text_color = "\0"}

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

} FixedConfig;

FixedConfig *init_fixed();

/**
 * @brief create fixed widget with default
 * @param[in] fixed fixed structure
 * @return[ou] GtkWidget pointer to new fixed widget
 */
GtkWidget *create_fixed(FixedConfig fixed_config);

#endif