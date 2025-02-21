#include "./../../../include/widgets/button/color_button.h"

ViewConfig *configure_color_button_property(ColorButtonConfig *color_button_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!color_button_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "tooltip") == 0)
        strcpy(color_button_config->tooltip, value);

    if (g_strcmp0(property, "is_sensitive") == 0)
        color_button_config->is_sensitive = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_visible") == 0)
        color_button_config->is_visible = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "hexpand") == 0)
        color_button_config->hexpand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "vexpand") == 0)
        color_button_config->vexpand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        color_button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        color_button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        color_button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        color_button_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        color_button_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        color_button_config->dimensions.height = atoi(value);

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_color_button_config(FILE *index, ColorButtonConfig *color_button_config)
{
    return init_generic_config(index, (void *)color_button_config, (ConfigurePropertyCallback)configure_color_button_property);
}

GtkWidget *create_color_button(ColorButtonConfig color_button_config)
{
    GtkWidget *color_button;

    // Create a new color button
    color_button = gtk_color_button_new();

    // Set sensitivity
    gtk_widget_set_sensitive(color_button, color_button_config.is_sensitive);

    // Set visibility
    if (!color_button_config.is_visible)
        gtk_widget_hide(color_button);

    // Set tooltip
    if (color_button_config.tooltip[0] != '\0') // Ensure tooltip is not empty
        gtk_widget_set_tooltip_text(color_button, color_button_config.tooltip);

    // Set dimensions (width and height)
    if (color_button_config.dimensions.width > 0 || color_button_config.dimensions.height > 0)
        set_widget_size(color_button, color_button_config.dimensions);

    // Set expand property
    gtk_widget_set_hexpand(color_button, color_button_config.hexpand);
    gtk_widget_set_vexpand(color_button, color_button_config.vexpand);

    // Set margins
    widget_set_margins(color_button, color_button_config.margins);

    return color_button;
}

gchar *write_color_button_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "color_button", tabs_number);

    // Get the GtkColorButton from the view
    GtkColorButton *color_button = GTK_COLOR_BUTTON(view->widget);

    // Check if the color button is sensitive
    gboolean is_sensitive = gtk_widget_get_sensitive(GTK_WIDGET(color_button));
    if (is_sensitive != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_sensitive=\"%s\"\n", is_sensitive ? "true" : "false");
    }

    // Check if the color button is visible
    gboolean is_visible = gtk_widget_get_visible(GTK_WIDGET(color_button));
    if (is_visible != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_visible=\"%s\"\n", is_visible ? "true" : "false");
    }

    // Get the tooltip text
    const gchar *tooltip = gtk_widget_get_tooltip_text(GTK_WIDGET(color_button));
    if (g_strcmp0(tooltip, "\0") != 0) // Check if the tooltip text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "tooltip=\"%s\"\n", tooltip);
    }

    // Get the horizontal expand property
    gboolean hexpand = gtk_widget_get_hexpand(GTK_WIDGET(color_button));
    if (hexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "hexpand=\"%s\"\n", hexpand ? "true" : "false");
    }

    // Get the vertical expand property
    gboolean vexpand = gtk_widget_get_vexpand(GTK_WIDGET(color_button));
    if (vexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "vexpand=\"%s\"\n", vexpand ? "true" : "false");
    }

    return "color_button";
}