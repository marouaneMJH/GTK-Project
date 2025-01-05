#include "./../../../include/widgets/menu/menu.h"

int configure_menu_property(MenuConfig *menu_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!menu_config || !property || !value)
        return -1;

    if (g_strcmp0(property, "tooltip") == 0)
        strcpy(menu_config->tooltip, value);

    if (g_strcmp0(property, "accel_path") == 0)
        strcpy(menu_config->accel_path, value);

    if (g_strcmp0(property, "active_index") == 0)
        menu_config->active_index = atoi(value);

    if (g_strcmp0(property, "monitor_num") == 0)
        menu_config->monitor_num = atoi(value);

    if (g_strcmp0(property, "reserve_toggle_size") == 0)
        menu_config->reserve_toggle_size = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Margins
    if (g_strcmp0(property, "mrgin_top") == 0)
        menu_config->margins.top = atoi(value);

    if (g_strcmp0(property, "mrgin_bottom") == 0)
        menu_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "mrgin_left") == 0)
        menu_config->margins.start = atoi(value);

    if (g_strcmp0(property, "mrgin_right") == 0)
        menu_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        menu_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        menu_config->dimensions.height = atoi(value);

    // Colors
    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(menu_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(menu_config->text_color, value);

    if (g_strcmp0(property, "accel_group") == 0)
    {
        // TODO: advanced feature to be done later
    }

    if (g_strcmp0(property, "screen") == 0)
    {
        // TODO: advanced feature to be done later
    }

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return 1;
}

gchar *init_menu_config(FILE *index, MenuConfig *menu_config, ViewConfig *view_config)
{
    // Check if the menu config and the index file is not null
    if (!menu_config || !index)
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

        // If the all properties are readed then break the loop and return the view id and pass the properties to the menu config
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
                    // Apply the property value to the menu config
                    configure_menu_property(menu_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_id;
}

GtkWidget *create_menu(MenuConfig menu_config)
{
    GtkWidget *menu = NULL;

    // Creation
    menu = gtk_menu_new();

    // gtk_menu_set_title(GTK_MENU(menu), menu_config.title); // Deprecated

    if (menu_config.accel_group)
        gtk_menu_set_accel_group(GTK_MENU(menu), menu_config.accel_group);

    if (menu_config.accel_path && menu_config.accel_path[0] != '\0')
        gtk_menu_set_accel_path(GTK_MENU(menu), menu_config.accel_path);

    gtk_menu_set_active(GTK_MENU(menu), menu_config.active_index);
    gtk_menu_set_monitor(GTK_MENU(menu), menu_config.monitor_num);
    gtk_menu_set_reserve_toggle_size(GTK_MENU(menu), menu_config.reserve_toggle_size);
    gtk_menu_set_screen(GTK_MENU(menu), menu_config.screen);
    // gtk_menu_set_tearoff_state(GTK_MENU(menu), menu_config.torn_off); // Deprecated

    // Set the tooltip
    if (menu_config.tooltip && menu_config.tooltip[0] != '\0')
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