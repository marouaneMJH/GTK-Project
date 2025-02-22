#include "./../../../include/widgets/button/button.h"
#include "./../../../include/widgets/image.h"

ViewConfig *configure_button_property(ButtonConfig *button_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!button_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "label") == 0)
        strcpy(button_config->label, value);

    if (g_strcmp0(property, "tooltip") == 0)
        strcpy(button_config->tooltip, value);

    if (g_strcmp0(property, "is_sensitive") == 0)
        button_config->is_sensitive = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_visible") == 0)
        button_config->is_visible = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "icon_path") == 0)
        strcpy(button_config->icon_path, value);

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "start") == 0)
            button_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "end") == 0)
            button_config->halign = GTK_ALIGN_END;
        else
            button_config->halign = GTK_ALIGN_CENTER;
    }

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "start") == 0)
            button_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "end") == 0)
            button_config->valign = GTK_ALIGN_END;
        else
            button_config->valign = GTK_ALIGN_CENTER;
    }

    if (g_strcmp0(property, "always_show_image") == 0)
        button_config->always_show_image = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "focus_on_click") == 0)
        button_config->focus_on_click = g_strcmp0(value, "true") == 0 ? TRUE : FALSE; // deprecated

    if (g_strcmp0(property, "use_underline") == 0)
        button_config->use_underline = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "use_stock") == 0)
        button_config->use_stock = g_strcmp0(value, "true") == 0 ? TRUE : FALSE; // deprecated

    if (g_strcmp0(property, "icon_position") == 0)
    {
        if (g_strcmp0(value, "top") == 0)
            button_config->icon_position = GTK_POS_TOP;
        else if (g_strcmp0(value, "bottom") == 0)
            button_config->icon_position = GTK_POS_BOTTOM;
        else if (g_strcmp0(value, "left") == 0)
            button_config->icon_position = GTK_POS_LEFT;
        else if (g_strcmp0(value, "right") == 0)
            button_config->icon_position = GTK_POS_RIGHT;
        else
            button_config->icon_position = GTK_POS_LEFT;
    }

    // Icon dimensions
    if (g_strcmp0(property, "icon_width") == 0)
        button_config->icon_dimensions.width = atoi(value);

    if (g_strcmp0(property, "icon_height") == 0)
        button_config->icon_dimensions.height = atoi(value);

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        button_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        button_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        button_config->dimensions.height = atoi(value);

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(button_config->bg_color, value);

    if (g_strcmp0(property, "color") == 0)
        strcpy(button_config->color, value);

    if (g_strcmp0(property, "hexpand") == 0)
        button_config->hexpand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "vexpand") == 0)
        button_config->vexpand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Icon image and icon

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_button_config(FILE *index, ButtonConfig *button_config)
{
    return init_generic_config(index, (void *)button_config, (ConfigurePropertyCallback)configure_button_property);
}


GtkWidget *create_button(ButtonConfig button_config)
{
    GtkWidget *button;

    // Create button with or without mnemonic based on use_underline flag
    button = gtk_button_new_with_mnemonic(button_config.label);


    // Set sensitivity
    gtk_widget_set_sensitive(button, button_config.is_sensitive);

    // Set visibility
    if (!button_config.is_visible)
        gtk_widget_hide(button);

    // Set tooltip
    if (button_config.tooltip) // Ensure tooltip is not empty
        gtk_widget_set_tooltip_text(button, button_config.tooltip);

    // Set dimensions (width and height)
    if (button_config.dimensions.width > 0 || button_config.dimensions.height > 0)
        gtk_widget_set_size_request(button, button_config.dimensions.width, button_config.dimensions.height);

    // Set expand property
    gtk_widget_set_hexpand(button, button_config.hexpand);
    gtk_widget_set_vexpand(button, button_config.vexpand);

    // Set icon if provided
    if (button_config.icon_path[0] != '\0')
    {
        Dimensions dimensions = {32, 32};
        GtkWidget *image = create_image_from_pixbuf(button_config.icon_path, dimensions);
        gtk_button_set_image(GTK_BUTTON(button), image);
        gtk_button_set_image_position(GTK_BUTTON(button), button_config.icon_position);
    }
     
    // to hide button border
    // gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE );

    // Set alignment
    gtk_widget_set_halign(button, button_config.halign);
    gtk_widget_set_valign(button, button_config.valign);

    // Control whether to always show the image
    gtk_button_set_always_show_image(GTK_BUTTON(button), button_config.always_show_image);

    // Set background and label colors
    widget_set_colors(button, button_config.bg_color, button_config.color);

    // Set margins
    widget_set_margins(button, button_config.margins);

    return button;
}

ButtonConfig* read_button_config_from_dialog()
{
    ButtonConfig *button_config_ptr = NULL;
    SAFE_ALLOC(button_config_ptr, ButtonConfig, 1);

    ButtonConfig button_config = DEFAULT_BUTTON;

    // Label
    gchar *label = read_config_value_as_string("label_entry");
    strcpy(button_config.label, label);
    // Width
    gint width = read_config_value_as_int("width_spin");
    button_config.dimensions.width = width;

    // Height
    gint height = read_config_value_as_int("height_spin");
    button_config.dimensions.height = height;

    // Margin top
    gint margin_top = read_config_value_as_int("margin_top_spin");
    button_config.margins.top = margin_top;

    // Margin bottom
    gint margin_bottom = read_config_value_as_int("margin_bottom_spin");
    button_config.margins.bottom = margin_bottom;

    // Margin left
    gint margin_left = read_config_value_as_int("margin_left_spin");
    button_config.margins.start = margin_left;

    // Margin right
    gint margin_right = read_config_value_as_int("margin_right_spin");
    button_config.margins.end = margin_right;

    // HAlign
    gchar *halign = read_config_value_as_string("halign_combo");
    if (stricmp(halign, "start") == 0)
        button_config.halign = GTK_ALIGN_START;
    else if (stricmp(halign, "end") == 0)
        button_config.halign = GTK_ALIGN_END;
    else if (stricmp(halign, "baseline") == 0)
        button_config.halign = GTK_ALIGN_BASELINE;
    else if (stricmp(halign, "center") == 0)
        button_config.halign = GTK_ALIGN_CENTER;

    // VAlign
    gchar *valign = read_config_value_as_string("valign_combo");
    if (stricmp(valign, "start") == 0)
        button_config.valign = GTK_ALIGN_START;
    else if (stricmp(valign, "end") == 0)
        button_config.valign = GTK_ALIGN_END;
    else if (stricmp(valign, "baseline") == 0)
        button_config.valign = GTK_ALIGN_BASELINE;
    else if (stricmp(valign, "center") == 0)
        button_config.valign = GTK_ALIGN_CENTER;

    // HExpand
    gboolean hexpand = read_config_value_as_boolean("hexpand_switch");
    button_config.hexpand = hexpand;

    // VExpand
    gboolean vexpand = read_config_value_as_boolean("vexpand_switch");
    button_config.vexpand = vexpand;

    // Background color
    const gchar *bg_color = read_config_value_as_string("bg_color_entry");
    strcpy(button_config.bg_color, bg_color);

    // Text color
    const gchar *text_color = read_config_value_as_string("color_entry");
    strcpy(button_config.color, text_color);

    button_config_ptr = &button_config;
    return button_config_ptr;
}


ButtonConfig* read_button_config_from_widget(GtkWidget *widget)
{
    ButtonConfig *button_config_ptr = NULL;
    SAFE_ALLOC(button_config_ptr, ButtonConfig, 1);

    const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));
    strcpy(button_config_ptr->label, label ? label : "");

    button_config_ptr->is_sensitive = gtk_widget_get_sensitive(widget);
    button_config_ptr->is_visible = gtk_widget_get_visible(widget);

    const gchar *tooltip = gtk_widget_get_tooltip_text(widget);
    strcpy(button_config_ptr->tooltip, tooltip ? tooltip : "");

    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    button_config_ptr->dimensions.width = allocation.width;
    button_config_ptr->dimensions.height = allocation.height;

    button_config_ptr->hexpand = gtk_widget_get_hexpand(widget);
    button_config_ptr->vexpand = gtk_widget_get_vexpand(widget);

    GtkAlign halign = gtk_widget_get_halign(widget);
    button_config_ptr->halign = halign;

    GtkAlign valign = gtk_widget_get_valign(widget);
    button_config_ptr->valign = valign;

    GtkWidget *image = gtk_button_get_image(GTK_BUTTON(widget));
    if (image)
    {
        const gchar *icon_path = g_object_get_data(G_OBJECT(image), "icon_path");
        if (icon_path)
            strcpy(button_config_ptr->icon_path, icon_path);
    }

    button_config_ptr->always_show_image = gtk_button_get_always_show_image(GTK_BUTTON(widget));

    Margins *margins = widget_get_margins(widget);
    button_config_ptr->margins = *margins;

    return button_config_ptr;
}