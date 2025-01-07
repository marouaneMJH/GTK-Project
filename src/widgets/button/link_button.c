#include "./../../../include/global.h"
#include "./../../../include/widgets/button/link_button.h"



ViewConfig *configure_link_button_property(LinkButtonConfig *link_button_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!link_button_config || !property || !value)
        return NULL;

    // URI
    if (g_strcmp0(property, "uri") == 0)
        strcpy(link_button_config->uri, value);

    // Label
    if (g_strcmp0(property, "label") == 0)
        strcpy(link_button_config->label, value);

    // Tooltip
    if (g_strcmp0(property, "tooltip") == 0)
        strcpy(link_button_config->tooltip, value);

    // Visited state
    if (g_strcmp0(property, "is_visited") == 0)
        link_button_config->is_visited = g_strcmp0(value, "true") == 0;

        // Margins
    if (g_strcmp0(property, "mrgin_top") == 0)
        link_button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "mrgin_bottom") == 0)
        link_button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "mrgin_left") == 0)
        link_button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "mrgin_right") == 0)
        link_button_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        link_button_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        link_button_config->dimensions.height = atoi(value);

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(link_button_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(link_button_config->text_color, value);


    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_link_button_config(FILE *index, LinkButtonConfig *link_button_config)
{
    // Check if the link_button config and the index file is not null
    if (!link_button_config || !index)
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

        // If the all properties are readed then break the loop and return the view id and pass the properties to the link_button config
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
                    // Apply the property value to the link_button config
                    view_config = configure_link_button_property(link_button_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_config;
}

GtkWidget *create_link_button(LinkButtonConfig link_button_config)
{
    GtkWidget *link_button = gtk_link_button_new_with_label(link_button_config.uri, link_button_config.label);

    // Set tooltip
    gtk_widget_set_tooltip_text(link_button, link_button_config.tooltip);

    // Set visited state
    gtk_link_button_set_visited(GTK_LINK_BUTTON(link_button), link_button_config.is_visited);

    // Set dimensions
    if (link_button_config.dimensions.width > 0 && link_button_config.dimensions.height > 0)
    {
        gtk_widget_set_size_request(link_button, link_button_config.dimensions.width, link_button_config.dimensions.height);
    }

    // Set colors
    widget_set_colors(link_button, link_button_config.bg_color, link_button_config.text_color);

    widget_set_margins(link_button, link_button_config.margins);

    return link_button;
}