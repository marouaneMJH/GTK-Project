#include "./../../include/widgets/label.h"

ViewConfig *configure_label_property(LabelConfig *label_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!label_config || !property || !value)
        return NULL;

    if (strcmp(property, "label_text") == 0)
    {
        strcpy(label_config->label_text, value);
    }
    if (strcmp(property, "is_markup") == 0)
    {
        label_config->is_markup = (strcmp(value, "true") == 0) ? TRUE : FALSE;
    }
    if (strcmp(property, "is_underline") == 0)
    {
        label_config->is_underline = (strcmp(value, "true") == 0) ? TRUE : FALSE;
    }
    if (strcmp(property, "font_size") == 0)
    {
        label_config->font_size = atoi(value);
    }
    else if (strcmp(property, "jtype") == 0)
    {
        if (strcmp(value, "left") == 0)
            label_config->jtype = GTK_JUSTIFY_LEFT;
        else if (strcmp(value, "right") == 0)
            label_config->jtype = GTK_JUSTIFY_RIGHT;
        else if (strcmp(value, "center") == 0)
            label_config->jtype = GTK_JUSTIFY_CENTER;
        else if (strcmp(value, "fill") == 0)
            label_config->jtype = GTK_JUSTIFY_FILL;
    }

    else if (strcmp(property, "ellipsize") == 0)
    {
        if (strcmp(value, "none") == 0)
            label_config->ellipsize = PANGO_ELLIPSIZE_NONE;
        else if (strcmp(value, "start") == 0)
            label_config->ellipsize = PANGO_ELLIPSIZE_START;
        else if (strcmp(value, "middle") == 0)
            label_config->ellipsize = PANGO_ELLIPSIZE_MIDDLE;
        else if (strcmp(value, "end") == 0)
            label_config->ellipsize = PANGO_ELLIPSIZE_END;
    }
    else if (strcmp(property, "is_wrap") == 0)
        label_config->is_wrap = (strcmp(value, "true") == 0) ? TRUE : FALSE;

    else if (strcmp(property, "text_color") == 0)
        strncpy(label_config->text_color, value, MAX_COLOR_SIZE);

    else if (strcmp(property, "bg_color") == 0)
        strncpy(label_config->bg_color, value, MAX_COLOR_SIZE);

    else if (strcmp(property, "is_selectable") == 0)
        label_config->is_selectable = (strcmp(value, "true") == 0) ? TRUE : FALSE;

    else if (!g_strcmp0(property, "font_family"))
        strcpy(label_config->font_family, value);

    else if (!g_strcmp0(property, "xalign"))
        label_config->xalign = atof(value);

    else if (!g_strcmp0(property, "yalign"))
        label_config->yalign = atof(value);

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        label_config->margins.top = atoi(value);
    else if (g_strcmp0(property, "margin_bottom") == 0)
        label_config->margins.bottom = atoi(value);
    else if (g_strcmp0(property, "margin_start") == 0)
        label_config->margins.start = atoi(value);
    else if (g_strcmp0(property, "margin_end") == 0)
        label_config->margins.end = atoi(value);

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            label_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            label_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            label_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            label_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            label_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            label_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            label_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            label_config->halign = GTK_ALIGN_FILL;
    }

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_label_config(FILE *index, LabelConfig *label_config)
{
    return init_generic_config(index, (void *)label_config, (ConfigurePropertyCallback)configure_label_property);
}

GtkWidget *create_label(LabelConfig label_config)
{
    GtkWidget *label_widget = gtk_label_new(label_config.label_text);

    /* Set Properties */
    gtk_label_set_justify(GTK_LABEL(label_widget), label_config.jtype);
    gtk_label_set_selectable(GTK_LABEL(label_widget), label_config.is_selectable);
    gtk_label_set_ellipsize(GTK_LABEL(label_widget), label_config.ellipsize);
    gtk_label_set_line_wrap(GTK_LABEL(label_widget), label_config.is_wrap);
    gtk_label_set_use_underline(GTK_LABEL(label_widget), label_config.is_underline);

    // gtk_label_set_width_chars(GTK_LABEL(label_widget),20);
    gtk_label_set_xalign(GTK_LABEL(label_widget), label_config.xalign);
    gtk_label_set_yalign(GTK_LABEL(label_widget), label_config.yalign);

    if (label_config.font_size > 0)
        widget_set_font_size(label_widget, label_config.font_size);
    if (label_config.is_markup)
    {
        gtk_label_set_markup(GTK_LABEL(label_widget), label_config.label_text);
    }

    // Update the margin when label_config margin updated
    if (
        label_config.margins.bottom ||
        label_config.margins.top ||
        label_config.margins.start ||
        label_config.margins.end)
    {
        widget_set_margins(label_widget, label_config.margins);
    }

    // apply font color
    widget_set_colors(label_widget, label_config.bg_color, label_config.text_color);

    gtk_widget_set_hexpand(label_widget, label_config.hexpand);
    gtk_widget_set_vexpand(label_widget, label_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(label_widget, label_config.halign);
    gtk_widget_set_valign(label_widget, label_config.valign);

    // apply font family
    if (label_config.font_family[0] != '\0')
        widget_set_font_family(label_widget, label_config.font_family);
    return label_widget;
}

gchar *write_label_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "label", tabs_number);

    // Get the GtkLabel from the view
    GtkLabel *label = GTK_LABEL(view->widget);

    // Get the label text
    const gchar *label_text = gtk_label_get_label(label);
    if (g_strcmp0(label_text, "\0") != 0) // Check if the label text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "label_text=\"%s\"\n", label_text);
    }

    // Check if the label uses Pango markup
    gboolean is_markup = gtk_label_get_use_markup(label);
    if (is_markup != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_markup=\"%s\"\n", is_markup ? "true" : "false");
    }

    // Check if the label has an underline
    gboolean is_underline = gtk_label_get_use_underline(label);
    if (is_underline != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_underline=\"%s\"\n", is_underline ? "true" : "false");
    }

    // Get the justification type
    GtkJustification jtype = gtk_label_get_justify(label);
    if (jtype != GTK_JUSTIFY_CENTER) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "jtype=\"%s\"\n", jtype == GTK_JUSTIFY_LEFT ? "left" : jtype == GTK_JUSTIFY_RIGHT ? "right"
                                                                                : jtype == GTK_JUSTIFY_CENTER  ? "center"
                                                                                : jtype == GTK_JUSTIFY_FILL    ? "fill"
                                                                                                               : "unknown");
    }

    // Get the ellipsize mode
    PangoEllipsizeMode ellipsize = gtk_label_get_ellipsize(label);
    if (ellipsize != PANGO_ELLIPSIZE_NONE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "ellipsize=\"%s\"\n", ellipsize == PANGO_ELLIPSIZE_START ? "start" : ellipsize == PANGO_ELLIPSIZE_MIDDLE ? "middle"
                                                                                              : ellipsize == PANGO_ELLIPSIZE_END      ? "end"
                                                                                                                                      : "none");
    }

    // Check if the label wraps text
    gboolean is_wrap = gtk_label_get_line_wrap(label);
    if (is_wrap != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_wrap=\"%s\"\n", is_wrap ? "true" : "false");
    }

    // Get the horizontal alignment
    gfloat xalign = gtk_label_get_xalign(label);
    if (xalign != 0.0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "xalign=\"%f\"\n", xalign);
    }

    // Get the vertical alignment
    gfloat yalign = gtk_label_get_yalign(label);
    if (yalign != 0.0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "yalign=\"%f\"\n", yalign);
    }

    // Check if the label is selectable
    gboolean is_selectable = gtk_label_get_selectable(label);
    if (is_selectable != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_selectable=\"%s\"\n", is_selectable ? "true" : "false");
    }

    // Get the horizontal expand property
    gboolean hexpand = gtk_widget_get_hexpand(GTK_WIDGET(label));
    if (hexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "hexpand=\"%s\"\n", hexpand ? "true" : "false");
    }

    // Get the vertical expand property
    gboolean vexpand = gtk_widget_get_vexpand(GTK_WIDGET(label));
    if (vexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "vexpand=\"%s\"\n", vexpand ? "true" : "false");
    }

    // Get the horizontal alignment
    GtkAlign halign = gtk_widget_get_halign(GTK_WIDGET(label));
    if (halign != GTK_ALIGN_FILL) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "halign=\"%s\"\n", halign == GTK_ALIGN_START ? "start" : halign == GTK_ALIGN_END  ? "end"
                                                                                  : halign == GTK_ALIGN_CENTER ? "center"
                                                                                  : halign == GTK_ALIGN_FILL   ? "fill"
                                                                                                               : "unknown");
    }

    // Get the vertical alignment
    GtkAlign valign = gtk_widget_get_valign(GTK_WIDGET(label));
    if (valign != GTK_ALIGN_FILL) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "valign=\"%s\"\n", valign == GTK_ALIGN_START ? "start" : valign == GTK_ALIGN_END  ? "end"
                                                                                  : valign == GTK_ALIGN_CENTER ? "center"
                                                                                  : valign == GTK_ALIGN_FILL   ? "fill"
                                                                                                               : "unknown");
    }

    return "label";
}