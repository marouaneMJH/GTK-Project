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

    if (g_strcmp0(property, "is_mnemonic") == 0)
        menu_item_config->is_mnemonic = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

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

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            menu_item_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            menu_item_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            menu_item_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            menu_item_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            menu_item_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            menu_item_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            menu_item_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            menu_item_config->halign = GTK_ALIGN_FILL;
    }
    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_menu_item_config(FILE *index, MenuItemConfig *menu_item_config)
{
    return init_generic_config(index, (void *)menu_item_config, (ConfigurePropertyCallback)configure_menu_item_property);
}

GtkWidget *create_menu_item(MenuItemConfig menu_item_config)
{
    GtkWidget *menu_item = NULL;

    // Creation
    if (menu_item_config.is_mnemonic && menu_item_config.label[0] != '\0')
    {
        // Create with mnemonic
        menu_item = gtk_menu_item_new_with_mnemonic(menu_item_config.label);
    }
    else if (menu_item_config.label[0] != '\0')
    {
        // Create with label
        menu_item = gtk_menu_item_new_with_label(menu_item_config.label);
        // Only set underline if explicitly requested
        gtk_menu_item_set_use_underline(GTK_MENU_ITEM(menu_item), menu_item_config.use_underline);
    }
    else
    {
        // Create empty menu item
        menu_item = gtk_menu_item_new();
    }

    // Accelerator path setup
    if (menu_item_config.accel_path && menu_item_config.accel_path[0] != '\0')
        gtk_menu_item_set_accel_path(GTK_MENU_ITEM(menu_item), menu_item_config.accel_path);

    gtk_menu_item_set_reserve_indicator(GTK_MENU_ITEM(menu_item), menu_item_config.reserve_indicator);

    // Set the tooltip
    if (menu_item_config.tooltip && menu_item_config.tooltip[0] != '\0')
        gtk_widget_set_tooltip_text(menu_item, menu_item_config.tooltip);

    // Set dimensions
    if (menu_item_config.dimensions.width > 0 && menu_item_config.dimensions.height > 0)
        gtk_widget_set_size_request(menu_item, menu_item_config.dimensions.width, menu_item_config.dimensions.height);

    // Set colors
    widget_set_colors(menu_item, menu_item_config.bg_color, menu_item_config.text_color);

    widget_set_margins(menu_item, menu_item_config.margins);

    // Enable or disable cells expand (the parent should be expandable; not important)
    gtk_widget_set_hexpand(menu_item, menu_item_config.hexpand);
    gtk_widget_set_vexpand(menu_item, menu_item_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(menu_item, menu_item_config.halign);
    gtk_widget_set_valign(menu_item, menu_item_config.valign);

    return menu_item;
}

MenuItemConfig *read_menu_item_config_from_dialog()
{
    MenuItemConfig *menu_item_config_ptr = NULL;
    SAFE_ALLOC(menu_item_config_ptr, MenuItemConfig, 1);

    MenuItemConfig menu_item_config = DEFAULT_MENU_ITEM;

    // Label
    const gchar *label = read_config_value_as_string("label_entry");
    strcpy(menu_item_config.label, label);

    // Tooltip
    const gchar *tooltip = read_config_value_as_string("tooltip_entry");
    strcpy(menu_item_config.tooltip, tooltip);

    // Accel Path
    // const gchar *accel_path = read_config_value_as_string("accel_path_entry");
    // strcpy(menu_item_config.accel_path, accel_path);

    // Is Mnemonic
    gboolean is_mnemonic = read_config_value_as_boolean("mnemonic_switch");
    menu_item_config.is_mnemonic = is_mnemonic;

    // Use Underline
    gboolean use_underline = read_config_value_as_boolean("use_underline_switch");
    menu_item_config.use_underline = use_underline;

    // Reserve Indicator
    gboolean reserve_indicator = read_config_value_as_boolean("reserve_indicator_switch");
    menu_item_config.reserve_indicator = reserve_indicator;

    // Dimensions
    Dimensions *dimensions = read_dimensions_config();
    menu_item_config.dimensions.width = dimensions->width;
    menu_item_config.dimensions.height = dimensions->height;

    // Margins
    Margins *margins = read_margins_config();
    menu_item_config.margins.top = margins->top;
    menu_item_config.margins.bottom = margins->bottom;
    menu_item_config.margins.start = margins->start;
    menu_item_config.margins.end = margins->end;

    // HAlign
    menu_item_config.halign = read_align_config("halign_combo");

    // VAlign
    menu_item_config.valign = read_align_config("valign_combo");

    // HExpand
    gboolean hexpand = read_config_value_as_boolean("hexpand_switch");
    menu_item_config.hexpand = hexpand;

    // VExpand
    gboolean vexpand = read_config_value_as_boolean("vexpand_switch");
    menu_item_config.vexpand = vexpand;

    // Background color
    const gchar *bg_color = read_config_value_as_string("bg_color_entry");
    strcpy(menu_item_config.bg_color, bg_color);

    // Text color
    const gchar *text_color = read_config_value_as_string("color_entry");
    strcpy(menu_item_config.text_color, text_color);

    memcpy(menu_item_config_ptr, &menu_item_config, sizeof(MenuItemConfig));
    return menu_item_config_ptr;
}

MenuItemConfig *read_menu_item_config_from_widget(GtkWidget *widget)
{
    MenuItemConfig *menu_item_config_ptr = NULL;
    SAFE_ALLOC(menu_item_config_ptr, MenuItemConfig, 1);

    MenuItemConfig menu_item_config = DEFAULT_MENU_ITEM;

    // Label
    const gchar *label = gtk_menu_item_get_label(GTK_MENU_ITEM(widget));
    if (label)
        strcpy(menu_item_config.label, label);

    // Tooltip
    const gchar *tooltip = gtk_widget_get_tooltip_text(widget);
    if (tooltip)
        strcpy(menu_item_config.tooltip, tooltip);

    // // Accel Path
    // const gchar *accel_path = gtk_menu_item_get_accel_path(GTK_MENU_ITEM(widget));
    // if (accel_path)
    //     strcpy(menu_item_config.accel_path, accel_path);

    // Is Mnemonic
    menu_item_config.is_mnemonic = gtk_menu_item_get_use_underline(GTK_MENU_ITEM(widget));

    // Use Underline
    menu_item_config.use_underline = gtk_menu_item_get_use_underline(GTK_MENU_ITEM(widget));

    // Reserve Indicator
    menu_item_config.reserve_indicator = gtk_menu_item_get_reserve_indicator(GTK_MENU_ITEM(widget));
   
    // Dimensions
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    menu_item_config.dimensions.width = allocation.width;
    menu_item_config.dimensions.height = allocation.height;

    // Expand
    menu_item_config.hexpand = gtk_widget_get_hexpand(widget);
    menu_item_config.vexpand = gtk_widget_get_vexpand(widget);

    // HAlign
    GtkAlign halign = gtk_widget_get_halign(widget);
    menu_item_config.halign = halign;

    // VAlign
    GtkAlign valign = gtk_widget_get_valign(widget);
    menu_item_config.valign = valign;

    // Margins
    Margins margins;
    widget_get_margins(widget, &margins);
    menu_item_config.margins = margins;

    gchar *property_value = NULL;
    // Background color
    property_value = read_bg_color_from_widget(widget);
    if (property_value)
        strcpy(menu_item_config.bg_color, property_value);

    // Text color
    property_value = read_text_color_from_widget(widget);
    if (property_value)
        strcpy(menu_item_config.text_color, property_value);

    memcpy(menu_item_config_ptr, &menu_item_config, sizeof(MenuItemConfig));

    return menu_item_config_ptr;
}

gchar *write_menu_item_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "menu_item", tabs_number);

    // Get the GtkMenuItem from the view
    GtkMenuItem *menu_item = GTK_MENU_ITEM(view->widget);

    // Get the label text
    const gchar *label = gtk_menu_item_get_label(menu_item);
    if (g_strcmp0(label, "\0") != 0) // Check if the label text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "label=\"%s\"\n", label);
    }

    // Get the accelerator path
    const gchar *accel_path = gtk_menu_item_get_accel_path(menu_item);
    if (accel_path && g_strcmp0(accel_path, "\0") != 0) // Check if the accelerator path is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "accel_path=\"%s\"\n", accel_path);
    }

    // Check if the menu item reserves space for an indicator
    gboolean reserve_indicator = gtk_menu_item_get_reserve_indicator(menu_item);
    if (reserve_indicator != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "reserve_indicator=\"%s\"\n", reserve_indicator ? "true" : "false");
    }

    // Check if the menu item uses underline in the label
    gboolean use_underline = gtk_menu_item_get_use_underline(menu_item);
    if (use_underline != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "use_underline=\"%s\"\n", use_underline ? "true" : "false");
    }

    // Check if the menu item uses mnemonics
    gboolean is_mnemonic = gtk_menu_item_get_use_underline(menu_item);
    if (is_mnemonic != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_mnemonic=\"%s\"\n", is_mnemonic ? "true" : "false");
    }

    // Get the tooltip text
    const gchar *tooltip = gtk_widget_get_tooltip_text(GTK_WIDGET(menu_item));
    if (tooltip && g_strcmp0(tooltip, "\0") != 0) // Check if the tooltip text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "tooltip=\"%s\"\n", tooltip);
    }

    return "menu_item";
}
