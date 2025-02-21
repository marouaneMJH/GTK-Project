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
    else if (g_strcmp0(property, "width") == 0)
        button_config->dimensions.width = atoi(value);

    else if (g_strcmp0(property, "height") == 0)
        button_config->dimensions.height = atoi(value);

    else if (g_strcmp0(property, "bg_color") == 0)
        strcpy(button_config->bg_color, value);

    else if (g_strcmp0(property, "color") == 0)
        strcpy(button_config->color, value);

    else if (g_strcmp0(property, "hexpand") == 0)
        button_config->hexpand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    else if (g_strcmp0(property, "vexpand") == 0)
        button_config->vexpand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    else if (g_strcmp0(property, "bg_image") == 0)
        strcpy(button_config->bg_image, value);

    else if (g_strcmp0(property, "font_size") == 0)
        button_config->font_size = atoi(value);

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

    // Set bg_image
    if (strcmp(button_config.bg_image, "\0") != 0)
        widget_set_background_image(button, button_config.bg_image, NULL);

    // Set Font Size
    if (button_config.font_size != 10)
        widget_set_font_size(button, button_config.font_size);

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

gchar *write_button_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "button", tabs_number);

    // Get the GtkButton from the view
    GtkButton *button = GTK_BUTTON(view->widget);

    // Get the label text
    const gchar *label = gtk_button_get_label(button);
    if (g_strcmp0(label, "Click here") != 0) // Check if the label text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "label=\"%s\"\n", label);
    }

    // Check if the button is sensitive
    gboolean is_sensitive = gtk_widget_get_sensitive(GTK_WIDGET(button));
    if (is_sensitive != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_sensitive=\"%s\"\n", is_sensitive ? "true" : "false");
    }

    // Check if the button is visible
    gboolean is_visible = gtk_widget_get_visible(GTK_WIDGET(button));
    if (is_visible != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_visible=\"%s\"\n", is_visible ? "true" : "false");
    }

    // Get the tooltip text
    const gchar *tooltip = gtk_widget_get_tooltip_text(GTK_WIDGET(button));
    if (g_strcmp0(tooltip, "\0") != 0) // Check if the tooltip text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "tooltip=\"%s\"\n", tooltip);
    }

    // Get the horizontal expand property
    gboolean hexpand = gtk_widget_get_hexpand(GTK_WIDGET(button));
    if (hexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "hexpand=\"%s\"\n", hexpand ? "true" : "false");
    }

    // Get the vertical expand property
    gboolean vexpand = gtk_widget_get_vexpand(GTK_WIDGET(button));
    if (vexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "vexpand=\"%s\"\n", vexpand ? "true" : "false");
    }

    // Check if the button always shows the image
    gboolean always_show_image = gtk_button_get_always_show_image(button);
    if (always_show_image != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "always_show_image=\"%s\"\n", always_show_image ? "true" : "false");
    }

    // Check if the button uses underline in the label
    gboolean use_underline = gtk_button_get_use_underline(button);
    if (use_underline != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "use_underline=\"%s\"\n", use_underline ? "true" : "false");
    }

    // Get the icon position
    GtkPositionType icon_position = gtk_button_get_image_position(button);
    if (icon_position != GTK_POS_LEFT) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "icon_position=\"%s\"\n", icon_position == GTK_POS_LEFT ? "left" : icon_position == GTK_POS_RIGHT ? "right"
                                                                                            : icon_position == GTK_POS_TOP     ? "top"
                                                                                            : icon_position == GTK_POS_BOTTOM  ? "bottom"
                                                                                                                               : "unknown");
    }

    return "button";
}