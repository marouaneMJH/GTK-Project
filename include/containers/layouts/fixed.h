#ifndef FIXED_H
#define FIXED_H

#include "./../../global.h"

/*  default values */
#define DEFAULT_FIXED_DIMENSIONS \
    {                            \
        .height = 0,             \
        .width = 0}

#define DEFAULT_FIXED_MARGINS \
    {                         \
        .bottom = 0,          \
        .top = 0,             \
        .start = 0,           \
        .end = 0}

#define DEFAULT_FIXED                           \
    {                                           \
        .margins = DEFAULT_FIXED_MARGINS,       \
        .dimensions = DEFAULT_FIXED_DIMENSIONS, \
        .hexpand = FALSE,                       \
        .vexpand = FALSE,                       \
        .halign = GTK_ALIGN_FILL,               \
        .valign = GTK_ALIGN_FILL,               \
        .bg_color = "\0",                       \
        .text_color = "\0"}

typedef struct
{
    Margins margins;
    Dimensions dimensions;
    gboolean hexpand;
    gboolean vexpand;
    GtkAlign halign;
    GtkAlign valign;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} FixedConfig;

ViewConfig *init_fixed_config(FILE *index, FixedConfig *fixed_config);

/**
 * @brief create fixed widget with default
 * @param[in] fixed fixed structure
 * @return[ou] GtkWidget pointer to new fixed widget
 */
GtkWidget *create_fixed(FixedConfig fixed_config);

void add_fixed(GtkWidget *widget, gint x, gint y);

FixedConfig *read_fixed_config_from_dialog();

FixedConfig *read_fixed_config_from_widget(GtkWidget *widget);

gchar *write_fixed_property(FILE *output_file, View *view, int tabs_number);


#endif