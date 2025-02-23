#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

#include "./../../global.h"
#include "./button.h"

/*  default values */
#define DEFAULT_RADIO_BUTTON_DIMENSIONS \
    {                                   \
        .height = 0,                    \
        .width = 0}

#define DEFAULT_RADIO_BUTTON_MARGIN \
    {                               \
        .bottom = 0,                \
        .top = 0,                   \
        .start = 0,                 \
        .end = 0}

#define DEFAULT_RADIO_BUTTON                           \
    {                                                  \
        .label = "\0",                                 \
        .icon_name = "\0",                             \
        .tooltip = "\0",                               \
        .is_group = TRUE,                              \
        .group = NULL,                                 \
        .is_mnemonic = FALSE,                          \
        .is_selected = FALSE,                          \
        .is_button_mode = FALSE,                       \
        .is_inconsistent = FALSE,                      \
        .use_underline = FALSE,                        \
        .icon_position = GTK_POS_LEFT,                 \
        .margins = DEFAULT_RADIO_BUTTON_MARGIN,        \
        .dimensions = DEFAULT_RADIO_BUTTON_DIMENSIONS, \
        .hexpand = FALSE,                              \
        .vexpand = FALSE,                              \
        .halign = GTK_ALIGN_FILL,                      \
        .valign = GTK_ALIGN_FILL,                      \
        .bg_color = "\0",                              \
        .text_color = "\0"}
// .margin = DEFAULT_RADIO_BUTTON_MARGIN,

typedef struct
{
    gchar label[MAX_BUTTON_LABEL_SIZE];
    gchar icon_name[MAX_ICON_NAME_SIZE];
    gchar tooltip[MAX_TOOLTIP_SIZE];

    gboolean is_group;
    GtkRadioButton *group;

    gboolean is_mnemonic;
    gboolean is_selected;
    gboolean is_button_mode;
    gboolean is_inconsistent;
    gboolean use_underline;

    GtkPositionType icon_position;

    gboolean hexpand;
    gboolean vexpand;
    GtkAlign halign;
    GtkAlign valign;
    Dimensions dimensions;
    Margins margins;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} RadioButtonConfig;

ViewConfig *init_radio_button_config(FILE *index, RadioButtonConfig *radio_button_config);

GtkWidget *create_radio_button(RadioButtonConfig radio_button_config);

void radio_button_set_group(GtkWidget *widget, GtkWidget *group);

gchar *write_radio_button_property(FILE *output_file, View *view, int tabs_number);

#endif