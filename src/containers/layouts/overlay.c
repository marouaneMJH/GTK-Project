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

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            overlay_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            overlay_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            overlay_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            overlay_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            overlay_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            overlay_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            overlay_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            overlay_config->halign = GTK_ALIGN_FILL;
    }

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

    // Enable or disable cells expand (the parent should be expandable; not important)
    gtk_widget_set_hexpand(overlay, overlay_config.hexpand);
    gtk_widget_set_vexpand(overlay, overlay_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(overlay, overlay_config.halign);
    gtk_widget_set_valign(overlay, overlay_config.valign);

    return overlay;
}

OverlayConfig *read_overlay_config_from_dialog()
{
    OverlayConfig *overlay_config_ptr = NULL;
    SAFE_ALLOC(overlay_config_ptr, OverlayConfig, 1);

    OverlayConfig overlay_config = DEFAULT_OVERLAY;

    // Opacity
    overlay_config.opacity = read_config_value_as_double("opacity_spin");
    
    // Border radius
    overlay_config.border_radius = read_config_value_as_int("border_radius_spin");

    // Dimensions
    Dimensions *dimensions = read_dimensions_config();
    overlay_config.dimensions.width = dimensions->width;
    overlay_config.dimensions.height = dimensions->height;

    // Margins
    Margins *margins = read_margins_config();
    overlay_config.margins.top = margins->top;
    overlay_config.margins.bottom = margins->bottom;
    overlay_config.margins.start = margins->start;
    overlay_config.margins.end = margins->end;

    // HAlign
    overlay_config.halign = read_align_config("halign_combo");

    // VAlign
    overlay_config.valign = read_align_config("valign_combo");

    // HExpand
    gboolean hexpand = read_config_value_as_boolean("hexpand_switch");
    overlay_config.hexpand = hexpand;

    // VExpand
    gboolean vexpand = read_config_value_as_boolean("vexpand_switch");
    overlay_config.vexpand = vexpand;

    // Background color
    const gchar *bg_color = read_config_value_as_string("bg_color_entry");
    strcpy(overlay_config.bg_color, bg_color);

    // Text color
    const gchar *bg_image = read_config_value_as_string("bg_image_entry");
    strcpy(overlay_config.bg_image, bg_image);

    memcpy(overlay_config_ptr, &overlay_config, sizeof(OverlayConfig));
    return overlay_config_ptr;
}

OverlayConfig *read_overlay_config_from_widget(GtkWidget *widget)
{
    OverlayConfig *overlay_config_ptr = NULL;
    SAFE_ALLOC(overlay_config_ptr, OverlayConfig, 1);

    OverlayConfig overlay_config = DEFAULT_OVERLAY;

    // Opacity
    overlay_config.opacity = gtk_widget_get_opacity(widget);

    // Border radius
   
    // Dimensions
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    overlay_config.dimensions.width = allocation.width;
    overlay_config.dimensions.height = allocation.height;

    // Expand
    overlay_config.hexpand = gtk_widget_get_hexpand(widget);
    overlay_config.vexpand = gtk_widget_get_vexpand(widget);

    // HAlign
    GtkAlign halign = gtk_widget_get_halign(widget);
    overlay_config.halign = halign;

    // VAlign
    GtkAlign valign = gtk_widget_get_valign(widget);
    overlay_config.valign = valign;

    // Margins
    Margins margins;
    widget_get_margins(widget, &margins);
    overlay_config.margins = margins;

    gchar *property_value = NULL;

    // Background color
    property_value = read_bg_color_from_widget(widget);
    if (property_value)
        strcpy(overlay_config.bg_color, property_value);

    // Background image
    property_value = read_bg_image_from_widget(widget);
    if (property_value)
        strcpy(overlay_config.bg_image, property_value);

    memcpy(overlay_config_ptr, &overlay_config, sizeof(OverlayConfig));

    return overlay_config_ptr;
}

gchar *write_overlay_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "overlay", tabs_number);

    // Get the GtkOverlay from the view
    GtkOverlay *overlay = GTK_OVERLAY(view->widget);

    // Get the opacity
    gdouble opacity = gtk_widget_get_opacity(GTK_WIDGET(overlay));
    if (opacity != 1.0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "opacity=\"%f\"\n", opacity);
    }

    // Get the border radius (if applicable)
    // Note: GTK itself does not provide a direct API for border radius.
    // This would typically be handled via CSS or custom properties.
    // If you have a custom way to handle border radius, you can add it here.

    return "overlay";
}