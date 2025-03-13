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

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            color_button_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            color_button_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            color_button_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            color_button_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            color_button_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            color_button_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            color_button_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            color_button_config->halign = GTK_ALIGN_FILL;
    }

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

    // Enable or disable cells expand (the parent should be expandable; not important)
    gtk_widget_set_hexpand(color_button, color_button_config.hexpand);
    gtk_widget_set_vexpand(color_button, color_button_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(color_button, color_button_config.halign);
    gtk_widget_set_valign(color_button, color_button_config.valign);

    // Set margins
    widget_set_margins(color_button, color_button_config.margins);

    return color_button;
}

ColorButtonConfig *read_color_button_config_from_dialog()
{
    ColorButtonConfig *color_button_config_ptr = NULL;
    SAFE_ALLOC(color_button_config_ptr, ColorButtonConfig, 1);

    ColorButtonConfig color_button_config = DEFAULT_COLOR_BUTTON;

    // Tooltip
    const gchar *tooltip = read_config_value_as_string("tooltip_entry");
    strcpy(color_button_config.tooltip, tooltip);

    // Sensitivity
    gboolean is_sensitive = read_config_value_as_boolean("sensitive_switch");
    color_button_config.is_sensitive = is_sensitive;

    // Visibility
    gboolean is_visible = read_config_value_as_boolean("visible_switch");
    color_button_config.is_visible = is_visible;

    // Dimensions
    Dimensions *dimensions = read_dimensions_config();
    color_button_config.dimensions.width = dimensions->width;
    color_button_config.dimensions.height = dimensions->height;

    // Margins
    Margins *margins = read_margins_config();
    color_button_config.margins.top = margins->top;
    color_button_config.margins.bottom = margins->bottom;
    color_button_config.margins.start = margins->start;
    color_button_config.margins.end = margins->end;

    // HAlign
    color_button_config.halign = read_align_config("halign_combo");

    // VAlign
    color_button_config.valign = read_align_config("valign_combo");

    // HExpand
    gboolean hexpand = read_config_value_as_boolean("hexpand_switch");
    color_button_config.hexpand = hexpand;

    // VExpand
    gboolean vexpand = read_config_value_as_boolean("vexpand_switch");
    color_button_config.vexpand = vexpand;

    memcpy(color_button_config_ptr, &color_button_config, sizeof(ColorButtonConfig));
    return color_button_config_ptr;
}

ColorButtonConfig *read_color_button_config_from_widget(GtkWidget *widget)
{
    ColorButtonConfig *color_button_config_ptr = NULL;
    SAFE_ALLOC(color_button_config_ptr, ColorButtonConfig, 1);

    ColorButtonConfig color_button_config = DEFAULT_COLOR_BUTTON;

    // Tooltip
    const gchar *tooltip = gtk_widget_get_tooltip_text(widget);
    if (tooltip)
        strcpy(color_button_config.tooltip, tooltip);

    // Sensitivity
    gboolean is_sensitive = gtk_widget_get_sensitive(widget);
    color_button_config.is_sensitive = is_sensitive;

    // Visibility
    gboolean is_visible = gtk_widget_get_visible(widget);
    color_button_config.is_visible = is_visible;

    // Dimensions
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    color_button_config.dimensions.width = allocation.width;
    color_button_config.dimensions.height = allocation.height;

    // Expand
    color_button_config.hexpand = gtk_widget_get_hexpand(widget);
    color_button_config.vexpand = gtk_widget_get_vexpand(widget);

    // HAlign
    GtkAlign halign = gtk_widget_get_halign(widget);
    color_button_config.halign = halign;

    // VAlign
    GtkAlign valign = gtk_widget_get_valign(widget);
    color_button_config.valign = valign;

    // Margins
    Margins margins;
    widget_get_margins(widget, &margins);
    color_button_config.margins = margins;

    memcpy(color_button_config_ptr, &color_button_config, sizeof(ColorButtonConfig));

    return color_button_config_ptr;
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
    if (tooltip && g_strcmp0(tooltip, "\0") != 0) // Check if the tooltip text is not the default
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