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
        .position = 0,                           \
        .is_wide = FALSE,                        \
        .margins = DEFAULT_PANED_MARGINS,        \
        .dimensions = DEFAULT_PANED_DIMENSIONS,  \
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

    Margins margins;

    Dimensions dimensions;

    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} PanedConfig;


int configure_paned_property(PanedConfig *paned_config,ViewConfig *view_config ,gchar *property, gchar *value);

gchar *init_paned_config(FILE *index, PanedConfig *paned_box_config, ViewConfig *view_config);



/**
 * @brief create paned widget with default
 * @param[in] paned paned structure
 * @return[ou] GtkWidget pointer to new paned widget
 */
GtkWidget *create_paned(PanedConfig paned_config);

#endif