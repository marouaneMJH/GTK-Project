#include "./../../../include/widgets/menu/menu_item.h"

ViewConfig *configure_menu_item_property(MenuItemConfig *menu_item_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!menu_item_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "label") == 0)
        strcpy(menu_item_config->label, value);

    if (g_strcmp0(property, "tooltip") == 0)
        strcpy(menu_item_config->tooltip, value);

    if (g_strcmp0(property, "accel_path") == 0)
        strcpy(menu_item_config->accel_path, value);

    if (g_strcmp0(property, "is_memonic") == 0)
        menu_item_config->is_memonic = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "use_underline") == 0)
        menu_item_config->use_underline = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "reserve_indicator") == 0)
        menu_item_config->reserve_indicator = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        menu_item_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        menu_item_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        menu_item_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        menu_item_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        menu_item_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        menu_item_config->dimensions.height = atoi(value);

    // Colors
    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(menu_item_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(menu_item_config->text_color, value);

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_menu_item_config(FILE *index, MenuItemConfig *menu_item_config)
{
    return init_generic_config(index,(void*)menu_item_config,(ConfigurePropertyCallback)configure_menu_item_property);
}
GtkWidget *create_menu_item(MenuItemConfig menu_item_config)
{
    GtkWidget *menu_item = NULL;

    // Creation
    menu_item = gtk_menu_item_new();

    if (menu_item_config.is_memonic && menu_item_config.label && menu_item_config.label[0] != '\0')
        menu_item = gtk_menu_item_new_with_mnemonic(menu_item_config.label);

    else if (menu_item_config.label && menu_item_config.label[0] != '\0')
        menu_item = gtk_menu_item_new_with_label(menu_item_config.label);

    if (menu_item_config.accel_path && menu_item_config.accel_path[0] != '\0')
        gtk_menu_item_set_accel_path(GTK_MENU_ITEM(menu_item), menu_item_config.accel_path);

    gtk_menu_item_set_reserve_indicator(GTK_MENU_ITEM(menu_item), menu_item_config.reserve_indicator);
    gtk_menu_item_set_use_underline(GTK_MENU_ITEM(menu_item), menu_item_config.use_underline);
    // gtk_menu_item_set_right_justified(GTK_MENU_ITEM(menu_item), menu_item_config.right_justified); => Deprecated

    // Set the tooltip
    if (menu_item_config.tooltip && menu_item_config.tooltip[0] != '\0')
        gtk_widget_set_tooltip_text(menu_item, menu_item_config.tooltip);

    // Set dimensions
    if (menu_item_config.dimensions.width > 0 && menu_item_config.dimensions.height > 0)
        gtk_widget_set_size_request(menu_item, menu_item_config.dimensions.width, menu_item_config.dimensions.height);

    // Set colors
    widget_set_colors(menu_item, menu_item_config.bg_color, menu_item_config.text_color);

    widget_set_margins(menu_item, menu_item_config.margins);

    return menu_item;
}

void menu_item_set_submenu(GtkWidget *widget, GtkWidget *submenu)
{
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(widget), submenu);
}