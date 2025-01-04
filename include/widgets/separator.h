#ifndef SEPARATOR_H
#define SEPARATOR_H
#include "./../global.h"

#define DEFAULT_SEPARATOR_DIMENSIONS \
    {                                \
        .width = 0,                  \
        .height = 0}

#define DEFAULT_SEPARATOR                           \
    {                                               \
        .tooltip = "\0",                            \
        .orientation = GTK_ORIENTATION_VERTICAL,    \
        .dimensions = DEFAULT_SEPARATOR_DIMENSIONS, \
        .is_visible = TRUE}

typedef struct
{
    gchar tooltip[MAX_TOOLTIP_SIZE];
    GtkOrientation orientation;
    gboolean is_visible;
    Dimensions dimensions;
} SeparatorConfig;

SeparatorConfig *init_separator(GtkOrientation orientation);

GtkWidget *create_separator(SeparatorConfig separator_config);

#endif