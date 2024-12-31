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
    Dimensions dimensions;
    Margins margins;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} SwitchButtonConfig;

SwitchButtonConfig *init_switch_button_config(const gchar *label);

GtkWidget *create_switch_button(SwitchButtonConfig switch_button_config);

#endif