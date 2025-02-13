#include "./../../../include/widgets/button/color_button.h"

ViewConfig *configure_color_button_property(ColorButtonConfig *color_button_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!color_button_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "label") == 0)
        strcpy(color_button_config->label, value);

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

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "start") == 0)
            color_button_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "end") == 0)
            color_button_config->halign = GTK_ALIGN_END;
        else
            color_button_config->halign = GTK_ALIGN_CENTER;
    }

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "start") == 0)
            color_button_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "end") == 0)
            color_button_config->valign = GTK_ALIGN_END;
        else
            color_button_config->valign = GTK_ALIGN_CENTER;
    }

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(color_button_config->bg_color, value);

    if (g_strcmp0(property, "color") == 0)
        strcpy(color_button_config->color, value);

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

    // Set the label
    gtk_button_set_label(GTK_BUTTON(color_button), color_button_config.label);

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
        gtk_widget_set_size_request(color_button, color_button_config.dimensions.width, color_button_config.dimensions.height);

    // Set expand property
    gtk_widget_set_hexpand(color_button, color_button_config.hexpand);
    gtk_widget_set_vexpand(color_button, color_button_config.vexpand);

    // Set alignment
    gtk_widget_set_halign(color_button, color_button_config.halign);
    gtk_widget_set_valign(color_button, color_button_config.valign);

    // Set margins
    gtk_widget_set_margin_start(color_button, color_button_config.margins.start);
    gtk_widget_set_margin_end(color_button, color_button_config.margins.end);
    gtk_widget_set_margin_top(color_button, color_button_config.margins.top);
    gtk_widget_set_margin_bottom(color_button, color_button_config.margins.bottom);

    // Set background and label colors
    GdkRGBA bg_color;
    gdk_rgba_parse(&bg_color, color_button_config.bg_color);
    gtk_widget_override_background_color(color_button, GTK_STATE_FLAG_NORMAL, &bg_color);

    GdkRGBA color;
    gdk_rgba_parse(&color, color_button_config.color);
    gtk_widget_override_color(color_button, GTK_STATE_FLAG_NORMAL, &color);

    return color_button;
}

