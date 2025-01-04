#include "./../../../include/widgets/menu/menu.h"

MenuConfig *init_menu_config(const gchar *label, gboolean is_group)
{
    MenuConfig *menu_config;
    SAFE_ALLOC(menu_config, MenuConfig, 1);

    // TODO: Config from xml

    return menu_config;
}

GtkWidget *create_menu(MenuConfig menu_config)
{
    GtkWidget *menu = NULL;

    // Creation
    menu = gtk_menu_new();


    // gtk_menu_set_title(GTK_MENU(menu), menu_config.title); // Deprecated

    if (menu_config.accel_group)
    {
        gtk_menu_set_accel_group(GTK_MENU(menu), menu_config.accel_group);
    }

    if (strlen(menu_config.accel_path) > 0)
    {
        gtk_menu_set_accel_path(GTK_MENU(menu), menu_config.accel_path);
    }
    gtk_menu_set_active(GTK_MENU(menu), menu_config.active_index);
    gtk_menu_set_monitor(GTK_MENU(menu), menu_config.monitor_num);
    gtk_menu_set_reserve_toggle_size(GTK_MENU(menu), menu_config.reserve_toggle_size);
    gtk_menu_set_screen(GTK_MENU(menu), menu_config.screen);
    // gtk_menu_set_tearoff_state(GTK_MENU(menu), menu_config.torn_off); // Deprecated
    

    // Set the tooltip
    gtk_widget_set_tooltip_text(menu, menu_config.tooltip);

    // Set dimensions
    if (menu_config.dimensions.width > 0 && menu_config.dimensions.height > 0)
    {
        gtk_widget_set_size_request(menu, menu_config.dimensions.width, menu_config.dimensions.height);
    }

    // Set colors
    widget_set_colors(menu, menu_config.bg_color, menu_config.text_color);

    widget_set_margins(menu, menu_config.margins);

    return menu;
}

void menu_set_group(GtkWidget *widget, GtkWidget *group)
{
    // gtk_menu_set_group(GTK_MENU(widget), gtk_menu_get_group(GTK_MENU(group)));
}