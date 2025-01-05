#ifndef MENU_BAR_H
#define MENU_BAR_H

#include "./../../global.h"

/*  default values */
#define DEFAULT_MENU_BAR_DIMENSIONS \
    {                                   \
        .height = 0,                    \
        .width = 0}

#define DEFAULT_MENU_BAR_MARGIN \
    {                               \
        .bottom = 0,                \
        .top = 0,                   \
        .start = 0,                 \
        .end = 0}

#define DEFAULT_MENU_BAR                           \
    {                                                  \
        .tooltip = "\0",                               \
        .dimensions = DEFAULT_MENU_BAR_DIMENSIONS,     \
        .margins = DEFAULT_MENU_BAR_MARGIN,            \
        .pack_direction = GTK_PACK_DIRECTION_LTR,      \
        .bg_color = "\0",                              \
        .text_color = "\0"}
// .margin = DEFAULT_MENU_BAR_MARGIN,

typedef struct
{
    gchar tooltip[MAX_TOOLTIP_SIZE];
    Dimensions dimensions;
    GtkPackDirection pack_direction;
    Margins margins;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} MenuBarConfig;

MenuBarConfig *init_menu_bar_config(const gchar *label, gboolean is_group);

GtkWidget *create_menu_bar(MenuBarConfig menu_bar_config);

void menu_bar_set_group(GtkWidget *widget, GtkWidget *group);

#endif