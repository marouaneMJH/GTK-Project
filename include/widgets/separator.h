#ifndef SEPARATOR_H
#define SEPARATOR_H
#include "./../global.h"

#define DEFAULT_SEPARATOR_DIMENSIONS \
    {                                \
        .width = 0,                  \
        .height = 0}

/* Default margins for entry */
#define DEFAULT_SEPARATOR_MARGINS \
    {                             \
        .bottom = 0,              \
        .top = 0,                 \
        .start = 0,               \
        .end = 0}

#define DEFAULT_SEPARATOR                           \
    {                                               \
        .tooltip = "\0",                            \
        .orientation = GTK_ORIENTATION_VERTICAL,    \
        .dimensions = DEFAULT_SEPARATOR_DIMENSIONS, \
        .margins = DEFAULT_SEPARATOR_MARGINS,       \
        .hexpand = FALSE,                           \
        .vexpand = FALSE,                           \
        .halign = GTK_ALIGN_FILL,                   \
        .valign = GTK_ALIGN_FILL,                   \
        .is_visible = TRUE}

typedef struct
{
    gchar tooltip[MAX_TOOLTIP_SIZE];
    GtkOrientation orientation;
    gboolean is_visible;
    gboolean hexpand;
    gboolean vexpand;

    GtkAlign halign;
    GtkAlign valign;

    Dimensions dimensions;
    Margins margins;
} SeparatorConfig;

ViewConfig *init_separator_config(FILE *index, SeparatorConfig *separator_config);

GtkWidget *create_separator(SeparatorConfig separator_config);

gchar *write_separator_property(FILE *output_file, View *view, int tabs_number);

#endif