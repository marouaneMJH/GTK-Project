#ifndef GRID_H
#define GRID_H

#include "./../../global.h"

/*  default values */
#define DEFAULT_GRID_DIMENSIONS \
    {                           \
        .height = 0,            \
        .width = 0}

#define DEFAULT_GRID_MARGINS \
    {                        \
        .bottom = 0,         \
        .top = 0,            \
        .start = 0,          \
        .end = 0}

#define DEFAULT_GRID                           \
    {                                          \
        .row_spacing = 0,                      \
        .column_spacing = 0,                   \
        .column_homogeneous = FALSE,           \
        .row_homogeneous = FALSE,              \
        .hexpand = TRUE,                       \
        .vexpand = TRUE,                       \
        .halign = GTK_ALIGN_CENTER,            \
        .valign = GTK_ALIGN_CENTER,            \
        .margins = DEFAULT_GRID_MARGINS,       \
        .dimensions = DEFAULT_GRID_DIMENSIONS, \
        .bg_color = "\0",                      \
        .text_color = "\0"}

typedef struct
{
    // Put a space between children
    gint row_spacing;
    gint column_spacing;

    // Give the same size to all children
    gboolean column_homogeneous;
    gboolean row_homogeneous;
    gboolean hexpand;
    gboolean vexpand;

    GtkAlign halign;
    GtkAlign valign;

    Margins margins;

    Dimensions dimensions;

    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} GridConfig;

ViewConfig *init_grid_config(FILE *index, GridConfig *grid_config);

/**
 * @brief create grid widget with default
 * @param[in] grid grid structure
 * @return[ou] GtkWidget pointer to new grid widget
 */
GtkWidget *create_grid(GridConfig grid_config);

#endif