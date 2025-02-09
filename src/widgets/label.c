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

    else if (strcmp(property, "padding") == 0)
        label_config->padding = atoi(value);

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
        label_config.margins.bottom  ||
        label_config.margins.top  ||
        label_config.margins.start  ||
        label_config.margins.end )
    {
        widget_set_margins(label_widget, label_config.margins);
    }

    // apply font color
    widget_set_colors(label_widget, label_config.bg_color, label_config.text_color);

    // apply font family
    if (label_config.font_family[0] != '\0')
        widget_set_font_family(label_widget, label_config.font_family);
    return label_widget;
}
