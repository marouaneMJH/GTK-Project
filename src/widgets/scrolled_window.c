#include "./../../include/widgets/scrolled_window.h"



ViewConfig *configure_scrolled_window_property(ScrolledWindowConfig *scrolled_window_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!scrolled_window_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "hscrollbar-policy") == 0)
    {
        if (g_strcmp0(value, "never") == 0)
            scrolled_window_config->h_policy = GTK_POLICY_NEVER;
        else if (g_strcmp0(value, "always") == 0)
            scrolled_window_config->h_policy = GTK_POLICY_ALWAYS;
        else if (g_strcmp0(value, "automatic") == 0)
            scrolled_window_config->h_policy = GTK_POLICY_AUTOMATIC;
    }
    else if (g_strcmp0(property, "vscrollbar-policy") == 0)
    {
        if (g_strcmp0(value, "never") == 0)
            scrolled_window_config->v_policy = GTK_POLICY_NEVER;
        else if (g_strcmp0(value, "always") == 0)
            scrolled_window_config->v_policy = GTK_POLICY_ALWAYS;
        else if (g_strcmp0(value, "automatic") == 0)
            scrolled_window_config->v_policy = GTK_POLICY_AUTOMATIC;
    }

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_scrolled_window_config(FILE *index, ScrolledWindowConfig *scrolled_window_config)
{
    // Check if the scrolled_window config and the index file is not null
    if (!scrolled_window_config || !index)
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

        // If the all properties are readed then break the loop and return the view id and pass the properties to the scrolled_window config
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
                    // Apply the property value to the scrolled_window config
                    view_config = configure_scrolled_window_property(scrolled_window_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_config;
}

// Function to create a scrolled window with specified scrollbar policies
GtkWidget* create_scrolled_window(ScrolledWindowConfig scrolled_window_config)
 {
    GtkWidget *scrolled_window = gtk_scrolled_window_new(scrolled_window_config.h_adjustment, scrolled_window_config.v_adjustment);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), scrolled_window_config.h_policy, scrolled_window_config.v_policy);

    return scrolled_window;

}