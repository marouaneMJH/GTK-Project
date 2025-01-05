#include "./../../../include/widgets/menu/menu_bar.h"

int configure_menu_bar_property(MenuBarConfig *menu_bar_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!menu_bar_config || !property || !value)
        return -1;

    if (g_strcmp0(property, "pack_direction") == 0)
    {
        if (g_strcmp0(value, "LTR") == 0)
            menu_bar_config->pack_direction = GTK_PACK_DIRECTION_LTR;

        if (g_strcmp0(value, "RTL") == 0)
            menu_bar_config->pack_direction = GTK_PACK_DIRECTION_RTL;

        if (g_strcmp0(value, "TTB") == 0)
            menu_bar_config->pack_direction = GTK_PACK_DIRECTION_TTB;

        if (g_strcmp0(value, "BTT") == 0)
            menu_bar_config->pack_direction = GTK_PACK_DIRECTION_BTT;
    }

    if (g_strcmp0(property, "tooltip") == 0)
        strcpy(menu_bar_config->tooltip, value);

    // Margins
    if (g_strcmp0(property, "mrgin_top") == 0)
        menu_bar_config->margins.top = atoi(value);

    if (g_strcmp0(property, "mrgin_bottom") == 0)
        menu_bar_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "mrgin_left") == 0)
        menu_bar_config->margins.start = atoi(value);

    if (g_strcmp0(property, "mrgin_right") == 0)
        menu_bar_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        menu_bar_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        menu_bar_config->dimensions.height = atoi(value);

    // Colors
    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(menu_bar_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(menu_bar_config->text_color, value);

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return 1;
}

gchar *init_menu_bar_config(FILE *index, MenuBarConfig *menu_bar_config, ViewConfig *view_config)
{
    // Check if the menu_bar config and the index file is not null
    if (!menu_bar_config || !index)
        return NULL;

    // Store the property and value of the tag
    gchar *property = NULL;
    gchar *value = NULL;

    // The view id of the tag
    gchar *view_id = NULL;

    // Read the tag character by character
    gchar c;
    while ((c = fgetc(index)) != '>')
    {
        /* If the character is a letter then go back one character
            Because when the tag is readed the cursor will start with the first letter in the property and it will be lost */
        if (is_character(c))
            fseek(index, -1, SEEK_CUR);

        int status = -1;

        // Read the property of the tag
        property = read_property(index, &status);

        // If the all properties are readed then break the loop and return the view id and pass the properties to the menu_bar config
        if (status == 2)
            return view_id;

        // If the property is readed then read the value of the property
        else if (status == 1 && property)
        {
            // Read the value of the property
            value = read_value(index, &status);
            if (status == 1 && value)
            {
                if (g_strcmp0(property, "id") == 0) // Store the view id
                {
                    view_id = value;
                    free(property);
                }
                else
                {
                    // Apply the property value to the menu_bar config
                    configure_menu_bar_property(menu_bar_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_id;
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
