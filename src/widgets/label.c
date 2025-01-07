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
    // Check if the label config and the index file is not null
    if (!label_config || !index)
        return NULL;

    // Create view config
    ViewConfig *view_config = NULL;
    SAFE_ALLOC(view_config, ViewConfig, 1);
    DFEAULT_VIEW_CONFIG(view_config);

    // Store the property and value of the tag
    gchar *property = NULL;
    gchar *value = NULL;

    // Read the tag character by character
    gchar c;
    while ((c = fgetc(index)) != '>')
    {
        /* If the character is a letter then go back one character
            Because when the tag is readed the cursor will start with the first letter in the property and it will be lost */
        if (is_character(c))
            fseek(index, -1, SEEK_CUR);

        int status = -1;

        // Read the property of the tag
        property = read_property(index, &status);

        // If the all properties are readed then break the loop and return the view id and pass the properties to the label config
        if (status == 2)
            return view_config;

        // If the property is readed then read the value of the property
        else if (status == 1 && property)
        {
            // Read the value of the property
            value = read_value(index, &status);
            if (status == 1 && value)
            {
                if (g_strcmp0(property, "id") == 0) // Store the view id
                {
                    strcpy(view_config->view_id, value);
                    free(property);
                }
                else
                {
                    // Apply the property value to the label config
                    view_config = configure_label_property(label_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_config;
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

