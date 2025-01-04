#include "./../../../include/widgets/menu/menu_item.h"

MenuItemConfig *init_menu_item_config(const gchar *label, gboolean is_group)
{
    MenuItemConfig *menu_item_config;
    SAFE_ALLOC(menu_item_config, MenuItemConfig, 1);

    // TODO: Config from xml

    return menu_item_config;
}

GtkWidget *create_menu_item(MenuItemConfig menu_item_config)
{
    GtkWidget *menu_item = NULL;

    // Creation
    menu_item = gtk_menu_item_new();
    gtk_menu_item_new_with_label(menu_item_config.label);

    gtk_menu_item_set_label(GTK_MENU_ITEM(menu_item), menu_item_config.label);
    gtk_menu_item_set_accel_path(GTK_MENU_ITEM(menu_item), menu_item_config.accel_path);
    gtk_menu_item_set_reserve_indicator(GTK_MENU_ITEM(menu_item), menu_item_config.reserve_indicator);
    gtk_menu_item_set_use_underline(GTK_MENU_ITEM(menu_item), menu_item_config.use_underline);
    // gtk_menu_item_set_right_justified(GTK_MENU_ITEM(menu_item), menu_item_config.right_justified); => Deprecated
    
    

    // Set the tooltip
    gtk_widget_set_tooltip_text(menu_item, menu_item_config.tooltip);

    // Set dimensions
    if (menu_item_config.dimensions.width > 0 && menu_item_config.dimensions.height > 0)
    {
        gtk_widget_set_size_request(menu_item, menu_item_config.dimensions.width, menu_item_config.dimensions.height);
    }

    // Set colors
    widget_set_colors(menu_item, menu_item_config.bg_color, menu_item_config.text_color);

    widget_set_margins(menu_item, menu_item_config.margins);

    return menu_item;
}

void menu_item_set_submenu(GtkWidget *widget, GtkWidget *submenu)
{
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(widget), submenu);
}