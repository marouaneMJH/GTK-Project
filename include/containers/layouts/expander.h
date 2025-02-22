#ifndef EXPANDER_H
#define EXPANDER_H

#include "./../../global.h"

/*  default values */
#define DEFAULT_EXPANDER_DIMENSIONS \
    {                               \
        .height = 0,                \
        .width = 0}

#define DEFAULT_EXPANDER_MARGINS \
    {                            \
        .bottom = 0,             \
        .top = 0,                \
        .start = 0,              \
        .end = 0}

#define DEFAULT_EXPANDER_CONFIG                    \
    {                                              \
        .label = "\0",                             \
        .is_expanded = FALSE,                      \
        .is_label_fill = FALSE,                    \
        .is_markup = TRUE,                         \
        .is_underline = TRUE,                      \
        .is_resize_toplevel = FALSE,               \
        .margins = DEFAULT_EXPANDER_MARGINS,       \
        .dimensions = DEFAULT_EXPANDER_DIMENSIONS, \
        .hexpand = FALSE,                          \
        .vexpand = FALSE,                          \
        .halign = GTK_ALIGN_START,                 \
        .valign = GTK_ALIGN_START,                 \
        .bg_color = "\0",                          \
        .color = "\0",                             \
        .bg_image = "\0",                          \
        .font_size = 10}

typedef struct
{

    gchar label[MAX_LABEL_SIZE];
    gboolean is_expanded;        // The current state of the expander.
    gboolean is_label_fill;      // TRUE if the label widget will fill all available horizontal space.
    gboolean is_markup;          // TRUE if the label’s text will be parsed for markup.
    gboolean is_underline;       // if underlines in the text indicate mnemonics.
    gboolean is_resize_toplevel; // Whether to resize the toplevel. (will effect the container size)

    Margins margins;
    Dimensions dimensions;
    gint font_size;

    gboolean hexpand;
    gboolean vexpand;

    GtkAlign halign;
    GtkAlign valign;

    gchar bg_color[MAX_COLOR_SIZE];
    gchar color[MAX_COLOR_SIZE];

    // bg path image (form the assets folder)
    gchar bg_image[MAX_ICON_PATH_SIZE];

} ExpanderConfig;

ViewConfig *configure_expander_property(ExpanderConfig *expander_config, ViewConfig *view_config, gchar *property, gchar *value);

ViewConfig *init_expander_config(FILE *index, ExpanderConfig *expander_config);

GtkWidget *create_expander(ExpanderConfig expander_config);

gchar *write_expander_property(FILE *output_file, View *view, int tabs_number);


#endif