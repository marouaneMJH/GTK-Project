#include "./../../../include/containers/layouts/fixed.h"

ViewConfig *configure_fixed_property(FixedConfig *fixed_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!fixed_config || !property || !value)
        return NULL;

    // Margins
    if (g_strcmp0(property, "mrgin_top") == 0)
        fixed_config->margins.top = atoi(value);

    if (g_strcmp0(property, "mrgin_bottom") == 0)
        fixed_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "mrgin_left") == 0)
        fixed_config->margins.start = atoi(value);

    if (g_strcmp0(property, "mrgin_right") == 0)
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

    // Icon image and icon

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_fixed_config(FILE *index, FixedConfig *fixed_config)
{
    // Check if the fixed config and the index file is not null
    if (!fixed_config || !index)
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

        // If the all properties are readed then break the loop and return the view id and pass the properties to the fixed config
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
                    // Apply the property value to the fixed config
                    view_config = configure_fixed_property(fixed_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_config;
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

    return fixed;
}