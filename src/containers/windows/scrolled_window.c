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

    // Colors
    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(scrolled_window_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(scrolled_window_config->text_color, value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        scrolled_window_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        scrolled_window_config->dimensions.height = atoi(value);

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        scrolled_window_config->margins.top = atoi(value);
    if (g_strcmp0(property, "margin_bottom") == 0)
        scrolled_window_config->margins.bottom = atoi(value);
    if (g_strcmp0(property, "margin_left") == 0)
        scrolled_window_config->margins.start = atoi(value);
    if (g_strcmp0(property, "margin_right") == 0)
        scrolled_window_config->margins.end = atoi(value);

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            scrolled_window_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            scrolled_window_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            scrolled_window_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            scrolled_window_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            scrolled_window_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            scrolled_window_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            scrolled_window_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            scrolled_window_config->halign = GTK_ALIGN_FILL;
    }

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_scrolled_window_config(FILE *index, ScrolledWindowConfig *scrolled_window_config)
{
    return init_generic_config(index, (void *)scrolled_window_config, (ConfigurePropertyCallback)configure_scrolled_window_property);
}
// Function to create a scrolled window with specified scrollbar policies
GtkWidget *create_scrolled_window(ScrolledWindowConfig scrolled_window_config)
{
    GtkWidget *scrolled_window = gtk_scrolled_window_new(scrolled_window_config.h_adjustment, scrolled_window_config.v_adjustment);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), scrolled_window_config.h_policy, scrolled_window_config.v_policy);

    // Enable or disable cells expand (the parent should be expandable; not important)
    gtk_widget_set_hexpand(scrolled_window, scrolled_window_config.hexpand);
    gtk_widget_set_vexpand(scrolled_window, scrolled_window_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(scrolled_window, scrolled_window_config.halign);
    gtk_widget_set_valign(scrolled_window, scrolled_window_config.valign);

    // Set dimensions
    if (scrolled_window_config.dimensions.width > 0 || scrolled_window_config.dimensions.height > 0)
        gtk_widget_set_size_request(scrolled_window, scrolled_window_config.dimensions.width, scrolled_window_config.dimensions.height);

    // Set colors
    widget_set_colors(scrolled_window, scrolled_window_config.bg_color, scrolled_window_config.text_color);

    // Set margins
    widget_set_margins(scrolled_window, scrolled_window_config.margins);

    return scrolled_window;
}
