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
        .is_group = FALSE,                             \
        .group = NULL,                                 \
        .is_mnemonic = FALSE,                          \
        .is_selected = FALSE,                          \
        .is_button_mode = FALSE,                       \
        .is_inconsistent = FALSE,                      \
        .use_underline = FALSE,                        \
        .icon_position = GTK_POS_LEFT,                 \
        .dimensions = DEFAULT_RADIO_BUTTON_DIMENSIONS, \
        .bg_color = "\0",                         \
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
    Dimensions dimensions;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} RadioButtonConfig;

RadioButtonConfig *init_radio_button_config(const gchar *label, gboolean is_group);

GtkWidget *create_radio_button(RadioButtonConfig radio_button_config);

void radio_button_set_group(GtkWidget *widget, GtkWidget *group);

#endif