#include "./../../include/widgets/label.h"


ViewConfig *configure_label_property(LabelConfig *label_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!label_config || !property || !value)
        return NULL;


    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_label_config(FILE *index, LabelConfig *label_config)
{
    return init_generic_config(index,(void*)label_config,(ConfigurePropertyCallback)configure_label_property);
}

GtkWidget* create_label(LabelConfig* label) 
{
    IS_EXISTE(label);
    GtkWidget *label_widget = gtk_label_new(label->label_text);

    /* Set Properties */
    gtk_label_set_justify(GTK_LABEL(label_widget), label->jtype);
    gtk_label_set_selectable(GTK_LABEL(label_widget), label->is_selectable);
    gtk_label_set_ellipsize(GTK_LABEL(label_widget), label->ellipsize);
    gtk_label_set_line_wrap(GTK_LABEL(label_widget), label->is_wrap);
    gtk_label_set_use_underline(GTK_LABEL(label_widget), label->is_underline);
    
    if (label->is_markup)
    {
        gtk_label_set_markup(GTK_LABEL(label_widget), label->label_text);
    }

    //  apply the font and bg color 
    // apply_label_colors(label_widget, label);

    // Set bg and text colors
    widget_set_colors(label_widget, label->background_color, label->text_color);


    return label_widget;
}

