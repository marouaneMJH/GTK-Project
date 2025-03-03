#ifndef SWITCH_BUTTON_H
#define SWITCH_BUTTON_H

#include "./../../global.h"
#include "./../../../include/widgets/button/button.h"

/*  default values */
#define DEFAULT_SWITCH_BUTTON_DIMENSIONS \
    {                                    \
        .height = 0,                     \
        .width = 0}

#define DEFAULT_SWITCH_BUTTON_MARGINS \
    {                                 \
        .bottom = 0,                  \
        .top = 0,                     \
        .start = 0,                   \
        .end = 0}

#define DEFAULT_SWITCH_BUTTON                           \
    {                                                   \
        .label = "\0",                                  \
        .is_mnemonic = FALSE,                           \
        .is_active = FALSE,                             \
        .state = FALSE,                                 \
        .is_visible = FALSE,                            \
        .hexpand = FALSE,                               \
        .vexpand = FALSE,                               \
        .halign = GTK_ALIGN_FILL,                       \
        .valign = GTK_ALIGN_FILL,                       \
        .dimensions = DEFAULT_SWITCH_BUTTON_DIMENSIONS, \
        .margins = DEFAULT_SWITCH_BUTTON_MARGINS,       \
        .bg_color = "\0",                               \
        .text_color = "\0"}

typedef struct
{
    gchar label[MAX_BUTTON_LABEL_SIZE];
    gchar tooltip[MAX_TOOLTIP_SIZE];
    gboolean is_mnemonic;
    gboolean is_active;
    gboolean is_visible;
    gboolean state;

    gboolean hexpand;
    gboolean vexpand;
    GtkAlign halign;
    GtkAlign valign;
    Dimensions dimensions;
    Margins margins;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} SwitchButtonConfig;

ViewConfig *init_switch_button_config(FILE *index, SwitchButtonConfig *switch_buttton_config);

GtkWidget *create_switch_button(SwitchButtonConfig switch_button_config);

SwitchButtonConfig *read_switch_button_config_from_dialog();

gchar *write_switch_button_property(FILE *output_file, View *view, int tabs_number);

#endif