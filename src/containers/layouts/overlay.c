#include "./../../../include/containers/layouts/overlay.h"

ViewConfig *configure_overlay_property(OverlayConfig *overlay_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!overlay_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "opacity") == 0)
    {
        overlay_config->opacity = g_ascii_strtod(value, NULL);
    }
    else if (g_strcmp0(property, "bg_color") == 0)
    {
        strcpy(overlay_config->bg_color, value);
    }
    else if (g_strcmp0(property, "border_radius") == 0)
    {
        overlay_config->border_radius = atoi(value);
    }
    else if (g_strcmp0(property, "bg_image") == 0)
    {
        strcpy(overlay_config->bg_image, value);
    }
    // Margins
    else if (g_strcmp0(property, "margin_top") == 0)
        overlay_config->margins.top = atoi(value);

    else if (g_strcmp0(property, "margin_bottom") == 0)
        overlay_config->margins.bottom = atoi(value);

    else if (g_strcmp0(property, "margin_left") == 0)
        overlay_config->margins.start = atoi(value);

    else if (g_strcmp0(property, "margin_right") == 0)
        overlay_config->margins.end = atoi(value);

    // Dimensions
    else if (g_strcmp0(property, "width") == 0)
        overlay_config->dimensions.width = atoi(value);

    else if (g_strcmp0(property, "height") == 0)
        overlay_config->dimensions.height = atoi(value);

    else if (g_strcmp0(property, "opacity") == 0)
        overlay_config->opacity = atof(value);

    // configure default properties
    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_overlay_config(FILE *index, OverlayConfig *overlay_config)
{
    return init_generic_config(index, (void *)overlay_config, (ConfigurePropertyCallback)configure_overlay_property);
}

GtkWidget *create_overlay(OverlayConfig overlay_config)
{
    GtkWidget *overlay = gtk_overlay_new();

    gtk_widget_set_opacity(overlay, overlay_config.opacity);
    if (overlay_config.bg_color && overlay_config.bg_image[0] != '\0')
        widget_set_background_image(overlay, overlay_config.bg_image, overlay_config.bg_color);
    if (overlay_config.dimensions.height || overlay_config.dimensions.width)
        set_widget_size(overlay, overlay_config.dimensions);

    if (overlay_config.margins.top ||
        overlay_config.margins.bottom ||
        overlay_config.margins.end ||
        overlay_config.margins.start)
        widget_set_margins(overlay, overlay_config.margins);
    return overlay;
}

gchar *write_overlay_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    write_widget_tag_style_view_config(output_file, view, "overlay", tabs_number);

    return "overlay";
}