#include "./../../../include/containers/windows/scrolled_window.h"



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
    return init_generic_config(index,(void*)scrolled_window_config,(ConfigurePropertyCallback)configure_scrolled_window_property);
}
// Function to create a scrolled window with specified scrollbar policies
GtkWidget* create_scrolled_window(ScrolledWindowConfig scrolled_window_config)
 {
    GtkWidget *scrolled_window = gtk_scrolled_window_new(scrolled_window_config.h_adjustment, scrolled_window_config.v_adjustment);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), scrolled_window_config.h_policy, scrolled_window_config.v_policy);

    return scrolled_window;

}
