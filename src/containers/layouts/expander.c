#include "../../../include/containers/layouts/expander.h"

ViewConfig *configure_expander_property(ExpanderConfig *expander_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!expander_config || !property || !value)
        return NULL;

    // Label
    if (g_strcmp0(property, "label") == 0)
        strncpy(expander_config->label, value, MAX_LABEL_SIZE - 1);

    // Expansion state
    if (g_strcmp0(property, "is_expanded") == 0)
        expander_config->is_expanded = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Label fill
    if (g_strcmp0(property, "is_label_fill") == 0)
        expander_config->is_label_fill = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Markup parsing
    if (g_strcmp0(property, "is_markup") == 0)
        expander_config->is_markup = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Underline mnemonics
    if (g_strcmp0(property, "is_underline") == 0)
        expander_config->is_underline = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Resize top-level
    if (g_strcmp0(property, "is_resize_toplevel") == 0)
        expander_config->is_resize_toplevel = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        expander_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        expander_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        expander_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        expander_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        expander_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        expander_config->dimensions.height = atoi(value);

    // Expand properties
    if (g_strcmp0(property, "hexpand") == 0)
        expander_config->hexpand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "vexpand") == 0)
        expander_config->vexpand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Horizontal alignment
    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            expander_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            expander_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            expander_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            expander_config->halign = GTK_ALIGN_FILL;
    }

    // Vertical alignment
    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            expander_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            expander_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            expander_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            expander_config->valign = GTK_ALIGN_FILL;
    }

    // Colors
    if (g_strcmp0(property, "bg_color") == 0)
        strncpy(expander_config->bg_color, value, MAX_COLOR_SIZE - 1);

    if (g_strcmp0(property, "color") == 0)
        strncpy(expander_config->color, value, MAX_COLOR_SIZE - 1);

    if (g_strcmp0(property, "font_size") == 0)
        expander_config->font_size = atoi(value);

    // Background image
    if (g_strcmp0(property, "bg_image") == 0)
        strncpy(expander_config->bg_image, value, MAX_ICON_PATH_SIZE - 1);

    // Apply property to ViewConfig
    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_expander_config(FILE *index, ExpanderConfig *expander_config)
{
    return init_generic_config(index, (void *)expander_config, (ConfigurePropertyCallback)configure_expander_property);
}

GtkWidget *create_expander(ExpanderConfig expander_config)
{

    GtkWidget *expander = gtk_expander_new_with_mnemonic(NULL);

    gtk_expander_set_label(GTK_EXPANDER(expander), expander_config.label);

    gtk_expander_set_expanded(GTK_EXPANDER(expander), expander_config.is_expanded);
    gtk_expander_set_label_fill(GTK_EXPANDER(expander), expander_config.is_label_fill);

    gtk_expander_set_use_markup(GTK_EXPANDER(expander), expander_config.is_markup);
    gtk_expander_set_use_underline(GTK_EXPANDER(expander), expander_config.is_underline);         // if underlines in the text indicate mnemonics.
    gtk_expander_set_resize_toplevel(GTK_EXPANDER(expander), expander_config.is_resize_toplevel); // if underlines in the text indicate mnemonics.

    gtk_widget_set_valign(expander, expander_config.valign);
    gtk_widget_set_halign(expander, expander_config.halign);

    gtk_widget_set_hexpand(expander, expander_config.hexpand);
    gtk_widget_set_vexpand(expander, expander_config.vexpand);

    widget_set_margins(expander, expander_config.margins);
    set_widget_size(expander, expander_config.dimensions);

    widget_set_colors(expander, expander_config.bg_color, expander_config.color);

    widget_set_background_image(expander, expander_config.bg_image, NULL);

    widget_set_font_size(expander, expander_config.font_size);

    return expander;
}

gchar *write_expander_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "expander", tabs_number);

    // Get the GtkExpander from the view
    GtkExpander *expander = GTK_EXPANDER(view->widget);

    // Get the label text
    const gchar *label = gtk_expander_get_label(expander);
    if (g_strcmp0(label, "\0") != 0) // Check if the label text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "label=\"%s\"\n", label);
    }

    // Check if the expander is expanded
    gboolean is_expanded = gtk_expander_get_expanded(expander);
    if (is_expanded != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_expanded=\"%s\"\n", is_expanded ? "true" : "false");
    }

    // Check if the label fills all available horizontal space
    gboolean is_label_fill = gtk_expander_get_label_fill(expander);
    if (is_label_fill != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_label_fill=\"%s\"\n", is_label_fill ? "true" : "false");
    }

    // Check if the label uses Pango markup
    gboolean is_markup = gtk_expander_get_use_markup(expander);
    if (is_markup != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_markup=\"%s\"\n", is_markup ? "true" : "false");
    }

    // Check if the label has an underline
    gboolean is_underline = gtk_expander_get_use_underline(expander);
    if (is_underline != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_underline=\"%s\"\n", is_underline ? "true" : "false");
    }

    // Check if the expander resizes the toplevel
    gboolean is_resize_toplevel = gtk_expander_get_resize_toplevel(expander);
    if (is_resize_toplevel != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_resize_toplevel=\"%s\"\n", is_resize_toplevel ? "true" : "false");
    }

    // Get the horizontal expand property
    gboolean hexpand = gtk_widget_get_hexpand(GTK_WIDGET(expander));
    if (hexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "hexpand=\"%s\"\n", hexpand ? "true" : "false");
    }

    // Get the vertical expand property
    gboolean vexpand = gtk_widget_get_vexpand(GTK_WIDGET(expander));
    if (vexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "vexpand=\"%s\"\n", vexpand ? "true" : "false");
    }

    // Get the horizontal alignment
    GtkAlign halign = gtk_widget_get_halign(GTK_WIDGET(expander));
    if (halign != GTK_ALIGN_START) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "halign=\"%s\"\n", halign == GTK_ALIGN_START ? "start" : halign == GTK_ALIGN_END  ? "end"
                                                                                  : halign == GTK_ALIGN_CENTER ? "center"
                                                                                  : halign == GTK_ALIGN_FILL   ? "fill"
                                                                                                               : "unknown");
    }

    // Get the vertical alignment
    GtkAlign valign = gtk_widget_get_valign(GTK_WIDGET(expander));
    if (valign != GTK_ALIGN_START) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "valign=\"%s\"\n", valign == GTK_ALIGN_START ? "start" : valign == GTK_ALIGN_END  ? "end"
                                                                                  : valign == GTK_ALIGN_CENTER ? "center"
                                                                                  : valign == GTK_ALIGN_FILL   ? "fill"
                                                                                                               : "unknown");
    }

    return "expander";
}