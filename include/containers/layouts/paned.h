#ifndef PANED_H
#define PANED_H

#include "./../../global.h"

/*  default values */
#define DEFAULT_PANED_DIMENSIONS \
    {                            \
        .height = 0,             \
        .width = 0}

#define DEFAULT_PANED_MARGINS \
    {                         \
        .bottom = 0,          \
        .top = 0,             \
        .start = 0,           \
        .end = 0}

#define DEFAULT_PANED                            \
    {                                            \
        .orientation = GTK_ORIENTATION_VERTICAL, \
        .position = 200,                         \
        .is_wide = FALSE,                        \
        .margins = DEFAULT_PANED_MARGINS,        \
        .dimensions = DEFAULT_PANED_DIMENSIONS,  \
        .hexpand = FALSE,                        \
        .vexpand = FALSE,                        \
        .halign = GTK_ALIGN_FILL,                \
        .valign = GTK_ALIGN_FILL,                \
        .bg_color = "\0",                        \
        .text_color = "\0"}

typedef struct
{
    // Define orientation
    GtkOrientation orientation;

    // Set paned position of the separator
    gint position;

    // Enable or diable wide handle
    gboolean is_wide;

    gboolean hexpand;
    gboolean vexpand;

    GtkAlign halign;
    GtkAlign valign;

    Margins margins;

    Dimensions dimensions;

    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} PanedConfig;

ViewConfig *configure_paned_property(PanedConfig *paned_config, ViewConfig *view_config, gchar *property, gchar *value);

ViewConfig *init_paned_config(FILE *index, PanedConfig *paned_box_config);

/**
 * @brief create paned widget with default
 * @param[in] paned paned structure
 * @return[ou] GtkWidget pointer to new paned widget
 */
GtkWidget *create_paned(PanedConfig paned_config);

#endif