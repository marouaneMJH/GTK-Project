#include "./../../../include/widgets/button/button.h"

ViewConfig *configure_button_property(ButtonConfig *button_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!button_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "label") == 0)
        strcpy(button_config->label, value);

    if (g_strcmp0(property, "tooltip") == 0)
        strcpy(button_config->tooltip, value);

    if (g_strcmp0(property, "is_sensitive") == 0)
        button_config->is_sensitive = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_visible") == 0)
        button_config->is_visible = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Margins
    if (g_strcmp0(property, "mrgin_top") == 0)
        button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "mrgin_bottom") == 0)
        button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "mrgin_left") == 0)
        button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "mrgin_right") == 0)
        button_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        button_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        button_config->dimensions.height = atoi(value);

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(button_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(button_config->text_color, value);

    if (g_strcmp0(property, "expand") == 0)
        button_config->expand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;
    

    if (g_strcmp0(property, "expand") == 0)
        button_config->expand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;
    

    // Icon image and icon

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_button_config(FILE *index, ButtonConfig *button_config)
{
    // Check if the button config and the index file is not null
    if (!button_config || !index)
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

        // If the all properties are readed then break the loop and return the view id and pass the properties to the button config
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
                    // Apply the property value to the button config
                    view_config = configure_button_property(button_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_config;
}

GtkWidget *create_button(ButtonConfig button_config)
{
    // Create a new button with the given label
    GtkWidget *button = gtk_button_new_with_label(button_config.label);

    // Set sensitivity
    gtk_widget_set_sensitive(button, button_config.is_sensitive);

    // Set visibility
    if (!button_config.is_visible)
        gtk_widget_hide(button);

    // Set tooltip
    if (button_config.tooltip) // Ensure tooltip is not empty
        gtk_widget_set_tooltip_text(button, button_config.tooltip);

    // todo dimensions validate function
    // Set dimensions (width and height)
    if (button_config.dimensions.width > 0 && button_config.dimensions.height > 0)
        gtk_widget_set_size_request(button, button_config.dimensions.width, button_config.dimensions.height);

    // Set expand property
    if (button_config.expand)
    {
        gtk_widget_set_hexpand(button, TRUE);
        gtk_widget_set_vexpand(button, TRUE);
    }

    // Set background and/or label colors
   widget_set_colors(button, button_config.bg_color, button_config.text_color);
   
   widget_set_colors(button, button_config.bg_color, button_config.text_color);
   
    // Set margin
    widget_set_margins(button, button_config.margins);

    return ((GtkWidget *)button);
}
