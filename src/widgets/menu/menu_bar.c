#include "./../../../include/widgets/menu/menu_bar.h"

MenuBarConfig *init_menu_bar_config(const gchar *label, gboolean is_group)
{
    MenuBarConfig *menu_bar_config;
    SAFE_ALLOC(menu_bar_config, MenuBarConfig, 1);

    // TODO: Config from xml

    return menu_bar_config;
}

GtkWidget *create_menu_bar(MenuBarConfig menu_bar_config)
{
    GtkWidget *menu_bar = NULL;

    // Creation
    menu_bar = gtk_menu_bar_new();


    gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(menu_bar), menu_bar_config.pack_direction);
    

    // Set the tooltip
    gtk_widget_set_tooltip_text(menu_bar, menu_bar_config.tooltip);

    // Set dimensions
    if (menu_bar_config.dimensions.width > 0 && menu_bar_config.dimensions.height > 0)
    {
        gtk_widget_set_size_request(menu_bar, menu_bar_config.dimensions.width, menu_bar_config.dimensions.height);
    }

    // Set colors
    widget_set_colors(menu_bar, menu_bar_config.bg_color, menu_bar_config.text_color);

    widget_set_margins(menu_bar, menu_bar_config.margins);

    return menu_bar;
}

void menu_bar_set_group(GtkWidget *widget, GtkWidget *group)
{
    // gtk_menu_bar_set_group(GTK_MENU_BAR(widget), gtk_menu_bar_get_group(GTK_MENU_BAR(group)));
}