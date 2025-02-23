#include "./../../../include/widgets/menu/menu.h"

ViewConfig *configure_menu_property(MenuConfig *menu_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!menu_config || !property || !value)
        return NULL;

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
    if (g_strcmp0(property, "margin_top") == 0)
        menu_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        menu_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        menu_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
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

    return view_config;
}

ViewConfig *init_menu_config(FILE *index, MenuConfig *menu_config)
{
    return init_generic_config(index, (void *)menu_config, (ConfigurePropertyCallback)configure_menu_property);
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

gchar *write_menu_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "menu", tabs_number);

    // Get the GtkMenu from the view
    GtkMenu *menu = GTK_MENU(view->widget);

    // Get the accelerator path
    const gchar *accel_path = gtk_menu_get_accel_path(menu);
    if (accel_path && g_strcmp0(accel_path, "\0") != 0) // Check if the accelerator path is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "accel_path=\"%s\"\n", accel_path);
    }

    // Get the active menu item
    GtkWidget *active_item = gtk_menu_get_active(menu);
    if (active_item != NULL) // Check if there is an active item
    {
        // Get the index of the active menu item
        GList *children = gtk_container_get_children(GTK_CONTAINER(menu));
        gint active_index = g_list_index(children, active_item);
        g_list_free(children);

        if (active_index != 0) // Check if it's not the default value
        {
            print_tabs(output_file, tabs_number + 1);
            fprintf(output_file, "active_index=\"%d\"\n", active_index);
        }
    }

    // Check if the menu reserves space for toggle indicators
    gboolean reserve_toggle_size = gtk_menu_get_reserve_toggle_size(menu);
    if (reserve_toggle_size != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "reserve_toggle_size=\"%s\"\n", reserve_toggle_size ? "true" : "false");
    }

    // Get the monitor number
    gint monitor_num = gtk_menu_get_monitor(menu);
    if (monitor_num != 0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "monitor_num=\"%d\"\n", monitor_num);
    }

    // Get the tooltip text
    const gchar *tooltip = gtk_widget_get_tooltip_text(GTK_WIDGET(menu));
    if (tooltip && g_strcmp0(tooltip, "\0") != 0) // Check if the tooltip text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "tooltip=\"%s\"\n", tooltip);
    }

    return "menu";
}
