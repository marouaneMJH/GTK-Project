#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include "./../../global.h"

#define MAX_ACCEL_PATH_SIZE 100

/*  default values */
#define DEFAULT_MENU_ITEM_DIMENSIONS \
    {                                \
        .height = 0,                 \
        .width = 0}

#define DEFAULT_MENU_ITEM_MARGIN \
    {                            \
        .bottom = 0,             \
        .top = 0,                \
        .start = 0,              \
        .end = 0}

#define DEFAULT_MENU_ITEM                           \
    {                                               \
        .label = "\0",                              \
        .accel_path = "\0",                         \
        .reserve_indicator = FALSE,                 \
        .use_underline = FALSE,                     \
        .is_mnemonic = TRUE,                         \
        .tooltip = "\0",                            \
        .dimensions = DEFAULT_MENU_ITEM_DIMENSIONS, \
        .margins = DEFAULT_MENU_ITEM_MARGIN,        \
        .hexpand = FALSE,                       \
        .vexpand = FALSE,                       \
        .halign = GTK_ALIGN_FILL,               \
        .valign = GTK_ALIGN_FILL,               \
        .bg_color = "\0",                           \
        .text_color = "\0"}
// .margin = DEFAULT_MENU_ITEM_MARGIN,

typedef struct
{
    gchar label[MAX_LABEL_SIZE];           // Add simple label
    gchar accel_path[MAX_ACCEL_PATH_SIZE]; // Add accel path (keyboard shortcuts)
    gboolean reserve_indicator;
    gboolean use_underline; // Associate to the parent screen or else
    gboolean is_mnemonic;
    gchar tooltip[MAX_TOOLTIP_SIZE];
    
    gboolean hexpand;
    gboolean vexpand;
    GtkAlign halign;
    GtkAlign valign;
    Dimensions dimensions;
    Margins margins;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} MenuItemConfig;

ViewConfig *init_menu_item_config(FILE *index, MenuItemConfig *menu_item_config);

GtkWidget *create_menu_item(MenuItemConfig menu_item_config);

void menu_item_set_submenu(GtkWidget *widget, GtkWidget *group);

MenuItemConfig *read_menu_item_config_from_dialog();

MenuItemConfig *read_menu_item_config_from_widget(GtkWidget *widget);

gchar *write_menu_item_property(FILE *output_file, View *view, int tabs_number);

#endif