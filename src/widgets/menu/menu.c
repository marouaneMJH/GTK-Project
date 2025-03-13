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

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            menu_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            menu_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            menu_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            menu_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            menu_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            menu_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            menu_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            menu_config->halign = GTK_ALIGN_FILL;
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

    // Enable or disable cells expand (the parent should be expandable; not important)
    gtk_widget_set_hexpand(menu, menu_config.hexpand);
    gtk_widget_set_vexpand(menu, menu_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(menu, menu_config.halign);
    gtk_widget_set_valign(menu, menu_config.valign);

    return menu;
}

void menu_set_group(GtkWidget *widget, GtkWidget *group)
{
    // gtk_menu_set_group(GTK_MENU(widget), gtk_menu_get_group(GTK_MENU(group)));
}

MenuConfig *read_menu_config_from_dialog()
{
    MenuConfig *menu_config_ptr = NULL;
    SAFE_ALLOC(menu_config_ptr, MenuConfig, 1);

    MenuConfig menu_config = DEFAULT_MENU;

    // Tooltip
    const gchar *tooltip = read_config_value_as_string("tooltip_entry");
    strcpy(menu_config.tooltip, tooltip);

    // Accel Path
    // const gchar *accel_path = read_config_value_as_string("accel_path_entry");
    // strcpy(menu_config.accel_path, accel_path);

    // Active Index
    gint active_index = read_config_value_as_int("active_index_spin");
    menu_config.active_index = active_index;

    // Monitor Number
    gint monitor_num = read_config_value_as_int("monitor_num_spin");
    menu_config.monitor_num = monitor_num;

    // Reserve Toggle Size
    gboolean reserve_toggle_size = read_config_value_as_boolean("reserve_toggle_size_switch");
    menu_config.reserve_toggle_size = reserve_toggle_size;

    // Dimensions
    Dimensions *dimensions = read_dimensions_config();
    menu_config.dimensions.width = dimensions->width;
    menu_config.dimensions.height = dimensions->height;

    // Margins
    Margins *margins = read_margins_config();
    menu_config.margins.top = margins->top;
    menu_config.margins.bottom = margins->bottom;
    menu_config.margins.start = margins->start;
    menu_config.margins.end = margins->end;

    // HAlign
    menu_config.halign = read_align_config("halign_combo");

    // VAlign
    menu_config.valign = read_align_config("valign_combo");

    // HExpand
    gboolean hexpand = read_config_value_as_boolean("hexpand_switch");
    menu_config.hexpand = hexpand;

    // VExpand
    gboolean vexpand = read_config_value_as_boolean("vexpand_switch");
    menu_config.vexpand = vexpand;

    // Background color
    const gchar *bg_color = read_config_value_as_string("bg_color_entry");
    strcpy(menu_config.bg_color, bg_color);

    // Text color
    const gchar *text_color = read_config_value_as_string("color_entry");
    strcpy(menu_config.text_color, text_color);

    memcpy(menu_config_ptr, &menu_config, sizeof(MenuConfig));
    return menu_config_ptr;
}

MenuConfig *read_menu_config_from_widget(GtkWidget *widget)
{
    MenuConfig *menu_config_ptr = NULL;
    SAFE_ALLOC(menu_config_ptr, MenuConfig, 1);

    MenuConfig menu_config = DEFAULT_MENU;

    // Tooltip
    const gchar *tooltip = gtk_widget_get_tooltip_text(widget);
    if (tooltip)
        strcpy(menu_config.tooltip, tooltip);

    // // Accel Path
    // const gchar *accel_path = gtk_menu_get_accel_path(GTK_MENU(widget));
    // if (accel_path)
    //     strcpy(menu_config.accel_path, accel_path);

    // Active Index
    GtkWidget *active_item = gtk_menu_get_active(GTK_MENU(widget));
    if (active_item)
    {
        GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
        gint active_index = g_list_index(children, active_item);
        g_list_free(children);
        menu_config.active_index = active_index;
    }

    // Monitor Number
    gint monitor_num = gtk_menu_get_monitor(GTK_MENU(widget));
    menu_config.monitor_num = monitor_num;

    // Reserve Toggle Size
    gboolean reserve_toggle_size = gtk_menu_get_reserve_toggle_size(GTK_MENU(widget));
    menu_config.reserve_toggle_size = reserve_toggle_size;
   
    // Dimensions
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    menu_config.dimensions.width = allocation.width;
    menu_config.dimensions.height = allocation.height;

    // Expand
    menu_config.hexpand = gtk_widget_get_hexpand(widget);
    menu_config.vexpand = gtk_widget_get_vexpand(widget);

    // HAlign
    GtkAlign halign = gtk_widget_get_halign(widget);
    menu_config.halign = halign;

    // VAlign
    GtkAlign valign = gtk_widget_get_valign(widget);
    menu_config.valign = valign;

    // Margins
    Margins margins;
    widget_get_margins(widget, &margins);
    menu_config.margins = margins;

    gchar *property_value = NULL;
    // Background color
    property_value = read_bg_color_from_widget(widget);
    if (property_value)
        strcpy(menu_config.bg_color, property_value);

    // Text color
    property_value = read_text_color_from_widget(widget);
    if (property_value)
        strcpy(menu_config.text_color, property_value);

    memcpy(menu_config_ptr, &menu_config, sizeof(MenuConfig));

    return menu_config_ptr;
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
