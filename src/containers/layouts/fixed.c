#include "./../../../include/containers/layouts/fixed.h"

ViewConfig *configure_fixed_property(FixedConfig *fixed_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!fixed_config || !property || !value)
        return NULL;

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        fixed_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        fixed_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        fixed_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        fixed_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        fixed_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        fixed_config->dimensions.height = atoi(value);

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(fixed_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(fixed_config->text_color, value);

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            fixed_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            fixed_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            fixed_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            fixed_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            fixed_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            fixed_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            fixed_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            fixed_config->halign = GTK_ALIGN_FILL;
    }

    // Icon image and icon

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_fixed_config(FILE *index, FixedConfig *fixed_config)
{
    return init_generic_config(index, (void *)fixed_config, (ConfigurePropertyCallback)configure_fixed_property);
}

GtkWidget *create_fixed(FixedConfig fixed_config)
{
    GtkWidget *fixed = NULL;

    // Creation
    fixed = gtk_fixed_new();

    // Set dimensions
    if (fixed_config.dimensions.width > 0 || fixed_config.dimensions.height)
        gtk_widget_set_size_request(fixed, fixed_config.dimensions.width, fixed_config.dimensions.height);

    // Set colors
    widget_set_colors(fixed, fixed_config.bg_color, fixed_config.text_color);

    // Set margins
    widget_set_margins(fixed, fixed_config.margins);

    // Enable or disable cells expand (the parent should be expandable; not important)
    gtk_widget_set_hexpand(fixed, fixed_config.hexpand);
    gtk_widget_set_vexpand(fixed, fixed_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(fixed, fixed_config.halign);
    gtk_widget_set_valign(fixed, fixed_config.valign);

    return fixed;
}

void add_fixed(GtkWidget *widget, gint x, gint y)
{
    gtk_fixed_put(GTK_FIXED(widget), widget, x, y);
}

FixedConfig *read_fixed_config_from_dialog()
{
    FixedConfig *fixed_config_ptr = NULL;
    SAFE_ALLOC(fixed_config_ptr, FixedConfig, 1);

    FixedConfig fixed_config = DEFAULT_FIXED;

    // Dimensions
    Dimensions *dimensions = read_dimensions_config();
    fixed_config.dimensions.width = dimensions->width;
    fixed_config.dimensions.height = dimensions->height;

    // Margins
    Margins *margins = read_margins_config();
    fixed_config.margins.top = margins->top;
    fixed_config.margins.bottom = margins->bottom;
    fixed_config.margins.start = margins->start;
    fixed_config.margins.end = margins->end;

    // HAlign
    fixed_config.halign = read_align_config("halign_combo");

    // VAlign
    fixed_config.valign = read_align_config("valign_combo");

    // HExpand
    gboolean hexpand = read_config_value_as_boolean("hexpand_switch");
    fixed_config.hexpand = hexpand;

    // VExpand
    gboolean vexpand = read_config_value_as_boolean("vexpand_switch");
    fixed_config.vexpand = vexpand;

    // Background color
    const gchar *bg_color = read_config_value_as_string("bg_color_entry");
    strcpy(fixed_config.bg_color, bg_color);

    // Text color
    const gchar *text_color = read_config_value_as_string("color_entry");
    strcpy(fixed_config.text_color, text_color);

    memcpy(fixed_config_ptr, &fixed_config, sizeof(FixedConfig));
    return fixed_config_ptr;
}


gchar *write_fixed_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "fixed", tabs_number);

    // Get the GtkFixed from the view
    GtkFixed *fixed = GTK_FIXED(view->widget);

    // Get the horizontal expand property
    gboolean hexpand = gtk_widget_get_hexpand(GTK_WIDGET(fixed));
    if (hexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "hexpand=\"%s\"\n", hexpand ? "true" : "false");
    }

    // Get the vertical expand property
    gboolean vexpand = gtk_widget_get_vexpand(GTK_WIDGET(fixed));
    if (vexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "vexpand=\"%s\"\n", vexpand ? "true" : "false");
    }

    // Get the horizontal alignment
    GtkAlign halign = gtk_widget_get_halign(GTK_WIDGET(fixed));
    if (halign != GTK_ALIGN_FILL) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "halign=\"%s\"\n", halign == GTK_ALIGN_START ? "start" : halign == GTK_ALIGN_END  ? "end"
                                                                                  : halign == GTK_ALIGN_CENTER ? "center"
                                                                                  : halign == GTK_ALIGN_FILL   ? "fill"
                                                                                                               : "unknown");
    }

    // Get the vertical alignment
    GtkAlign valign = gtk_widget_get_valign(GTK_WIDGET(fixed));
    if (valign != GTK_ALIGN_FILL) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "valign=\"%s\"\n", valign == GTK_ALIGN_START ? "start" : valign == GTK_ALIGN_END  ? "end"
                                                                                  : valign == GTK_ALIGN_CENTER ? "center"
                                                                                  : valign == GTK_ALIGN_FILL   ? "fill"
                                                                                                               : "unknown");
    }

    return "fixed";
}