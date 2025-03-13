#ifndef MENU_BAR_H
#define MENU_BAR_H

#include "./../../global.h"

/*  default values */
#define DEFAULT_MENU_BAR_DIMENSIONS \
    {                               \
        .height = 0,                \
        .width = 0}

#define DEFAULT_MENU_BAR_MARGIN \
    {                           \
        .bottom = 0,            \
        .top = 0,               \
        .start = 0,             \
        .end = 0}

#define DEFAULT_MENU_BAR                           \
    {                                              \
        .tooltip = "\0",                           \
        .dimensions = DEFAULT_MENU_BAR_DIMENSIONS, \
        .margins = DEFAULT_MENU_BAR_MARGIN,        \
        .pack_direction = GTK_PACK_DIRECTION_LTR,  \
        .hexpand = FALSE,                       \
        .vexpand = FALSE,                       \
        .halign = GTK_ALIGN_FILL,               \
        .valign = GTK_ALIGN_FILL,               \
        .bg_color = "\0",                          \
        .text_color = "\0"}
// .margin = DEFAULT_MENU_BAR_MARGIN,

typedef struct
{
    gchar tooltip[MAX_TOOLTIP_SIZE];
    GtkPackDirection pack_direction;

    gboolean hexpand;
    gboolean vexpand;
    GtkAlign halign;
    GtkAlign valign;
    Dimensions dimensions;
    Margins margins;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} MenuBarConfig;

ViewConfig *init_menu_bar_config(FILE *index, MenuBarConfig *menu_bar_config);

GtkWidget *create_menu_bar(MenuBarConfig menu_bar_config);

MenuBarConfig *read_menu_bar_config_from_dialog();

MenuBarConfig *read_menu_bar_config_from_widget(GtkWidget *widget);

gchar *write_menu_bar_property(FILE *output_file, View *view, int tabs_number);

#endif