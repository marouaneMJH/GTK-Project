#include "../../include/widgets/separator.h"

ViewConfig *configure_separator_property(SeparatorConfig *separator_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!separator_config || !property || !value)
        return NULL;

    // Orientation
    if (g_strcmp0(property, "orientation") == 0)
    {
        if (g_strcmp0(value, "horizontal") == 0)
            separator_config->orientation = GTK_ORIENTATION_HORIZONTAL;
        else if (g_strcmp0(value, "vertical") == 0)
            separator_config->orientation = GTK_ORIENTATION_VERTICAL;
    }

    // Visibility
    if (g_strcmp0(property, "visible") == 0)
    {
        if (g_strcmp0(value, "true") == 0)
            separator_config->is_visible = TRUE;
        else if (g_strcmp0(value, "false") == 0)
            separator_config->is_visible = FALSE;
    }

    // Margins
    if (g_strcmp0(property, "mrgin_top") == 0)
        separator_config->margins.top = atoi(value);

    if (g_strcmp0(property, "mrgin_bottom") == 0)
        separator_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "mrgin_left") == 0)
        separator_config->margins.start = atoi(value);

    if (g_strcmp0(property, "mrgin_right") == 0)
        separator_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        separator_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        separator_config->dimensions.height = atoi(value);
        
    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_separator_config(FILE *index, SeparatorConfig *separator_config)
{
    // Check if the separator config and the index file is not null
    if (!separator_config || !index)
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

        // If the all properties are readed then break the loop and return the view id and pass the properties to the separator config
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
                    // Apply the property value to the separator config
                    view_config = configure_separator_property(separator_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_config;
}

GtkWidget *create_separator(SeparatorConfig separator_config)
{

    GtkWidget *separator = NULL;

    // Creation
    separator = gtk_separator_new(separator_config.orientation);

    // Set visibility
    if (separator_config.is_visible)
        gtk_widget_show(separator);
    else
        gtk_widget_hide(separator);

    if (separator_config.dimensions.width > 0 || separator_config.dimensions.height > 0)
        gtk_widget_set_size_request(separator, separator_config.dimensions.width, separator_config.dimensions.height);

    widget_set_margins(separator, separator_config.margins);
    
    return separator;
}