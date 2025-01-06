#include "./../../../include/containers/windows/scrolled_window.h"





int configure_scrolled_window_property(ScrolledWindowConfig *scrolled_window_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!scrolled_window_config || view_config || !property || !value)
        return -1;

    // todo add adjustment property

    if (strcmp(property, "h_policy") == 0)
    {
        if (strcmp(value, "always") == 0)
            scrolled_window_config->h_policy = GTK_POLICY_ALWAYS;
        else if (strcmp(value, "automatic") == 0)
            scrolled_window_config->h_policy = GTK_POLICY_AUTOMATIC;
        else if (strcmp(value, "never") == 0)
            scrolled_window_config->h_policy = GTK_POLICY_NEVER;
        else
        {
            g_warning("Invalid value for h_policy: %s", value);
            return -1;
        }
    }

    if (strcmp(property, "v_policy") == 0)
    {
        if (strcmp(value, "always") == 0)
            scrolled_window_config->v_policy = GTK_POLICY_ALWAYS;
        else if (strcmp(value, "automatic") == 0)
            scrolled_window_config->v_policy = GTK_POLICY_AUTOMATIC;
        else if (strcmp(value, "never") == 0)
            scrolled_window_config->v_policy = GTK_POLICY_NEVER;
        else
        {
            g_warning("Invalid value for v_policy: %s", value);
            return -1;
        }
    }

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);


    return 1;
}


gchar *init_scrolled_window_config(FILE *index,ScrolledWindowConfig  *scrolled_window_config, ViewConfig *view_config)
{

    if(!scrolled_window_config || !view_config)
        return NULL;
    
    // Store the property and value of the tag
    gchar *property = NULL;
    gchar *value = NULL;

    // The view id of the tag
    gchar *view_id = NULL;

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

        // If the all properties are readed then break the loop and return the view id and pass the properties to the window config
        if (status == 2)
            return view_id;

        // If the property is readed then read the value of the property
        else if (status == 1 && property)
        {
            // Read the value of the property
            value = read_value(index, &status);
            if (status == 1 && value)
            {
                if (g_strcmp0(property, "id") == 0) // Store the view id
                {
                    view_id = value;
                    free(property);
                }
                else
                {
                    // Apply the property value to the scrolled window config
                    configure_scrolled_window_property(scrolled_window_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }
    return view_id;
}

// Function to create a scrolled window with specified scrollbar policies
GtkWidget* create_scrolled_window(ScrolledWindowConfig scrolled_window_config)
 {
    GtkWidget *scrolled_window = gtk_scrolled_window_new(scrolled_window_config.h_adjustment, scrolled_window_config.v_adjustment);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), scrolled_window_config.h_policy, scrolled_window_config.v_policy);
    return scrolled_window;

}


// GtkWidget* create_scrolled_window(ScrolledWindowConfig *scrolled_window_config) {
//     // Ensure that content is set before proceeding
//     if (scrolled_window_config->content == NULL) {
//         g_warning("Content widget is NULL!");
//         return NULL;
//     }

//     GtkWidget *scrolled_window = gtk_scrolled_window_new(scrolled_window_config->h_adjustment, scrolled_window_config->v_adjustment);
//     gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), scrolled_window_config->h_policy, scrolled_window_config->v_policy);
    
//     // Add the content widget to the scrolled window
//     gtk_container_add(GTK_CONTAINER(scrolled_window), scrolled_window_config->content);

//     // If a parent window is defined, add the scrolled window to it
//     if (scrolled_window_config->window) {
//         gtk_container_add(GTK_CONTAINER(scrolled_window_config->window), scrolle d_window);
//     }

//     return scrolled_window;
// }