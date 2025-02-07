#include "./../../include/widgets/label.h"

// debug label not working att all()

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
        {
            label_config->jtype = GTK_JUSTIFY_LEFT;
        }
        else if (strcmp(value, "right") == 0)
        {
            label_config->jtype = GTK_JUSTIFY_RIGHT;
        }
        else if (strcmp(value, "center") == 0)
        {
            label_config->jtype = GTK_JUSTIFY_CENTER;
        }
        else if (strcmp(value, "fill") == 0)
        {
            label_config->jtype = GTK_JUSTIFY_FILL;
        }
    }
    else if (strcmp(property, "ellipsize") == 0)
    {
        if (strcmp(value, "none") == 0)
        {
            label_config->ellipsize = PANGO_ELLIPSIZE_NONE;
        }
        else if (strcmp(value, "start") == 0)
        {
            label_config->ellipsize = PANGO_ELLIPSIZE_START;
        }
        else if (strcmp(value, "middle") == 0)
        {
            label_config->ellipsize = PANGO_ELLIPSIZE_MIDDLE;
        }
        else if (strcmp(value, "end") == 0)
        {
            label_config->ellipsize = PANGO_ELLIPSIZE_END;
        }
    }
    else if (strcmp(property, "is_wrap") == 0)
    {
        label_config->is_wrap = (strcmp(value, "true") == 0) ? TRUE : FALSE;
    }
    else if (strcmp(property, "text_color") == 0)
    {
        strncpy(label_config->text_color, value, MAX_COLOR_SIZE);
    }
    else if (strcmp(property, "background_color") == 0)
    {
        strncpy(label_config->bg_color, value, MAX_COLOR_SIZE);
    }
    else if (strcmp(property, "is_selectable") == 0)
    {
        label_config->is_selectable = (strcmp(value, "true") == 0) ? TRUE : FALSE;
    }
    else if (strcmp(property, "padding") == 0)
    {
        label_config->padding = atoi(value);
    }
    else if (!g_strcmp0(property,"font_family"))
        strcpy(label_config->font_family ,value);

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_label_config(FILE *index, LabelConfig *label_config)
{
    return init_generic_config(index, (void *)label_config, (ConfigurePropertyCallback)configure_label_property);
}

GtkWidget *create_label(LabelConfig label)
{
    GtkWidget *label_widget = gtk_label_new(label.label_text);

    /* Set Properties */
    gtk_label_set_justify(GTK_LABEL(label_widget), label.jtype);
    gtk_label_set_selectable(GTK_LABEL(label_widget), label.is_selectable);
    gtk_label_set_ellipsize(GTK_LABEL(label_widget), label.ellipsize);
    gtk_label_set_line_wrap(GTK_LABEL(label_widget), label.is_wrap);
    gtk_label_set_use_underline(GTK_LABEL(label_widget), label.is_underline);

    if (label.font_size > 0)
        widget_set_font_size(label_widget, label.font_size);
    if (label.is_markup)
    {
        gtk_label_set_markup(GTK_LABEL(label_widget), label.label_text);
    }

    if (label.padding > 0)
    {
        gtk_widget_set_margin_start(label_widget, label.padding);
        gtk_widget_set_margin_end(label_widget, label.padding);
        gtk_widget_set_margin_top(label_widget, label.padding);
        gtk_widget_set_margin_bottom(label_widget, label.padding);
    }

    // apply font color
    widget_set_colors(label_widget, label.bg_color, label.text_color);

    // apply font family
    if(label.font_family[0] != '\0')
        widget_set_font_family(label_widget,label.font_family);
    return label_widget;
}
