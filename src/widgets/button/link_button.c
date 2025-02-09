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
    if (g_strcmp0(property, "margin_top") == 0)
        link_button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        link_button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        link_button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
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
    return init_generic_config(index,(void*)link_button_config,(ConfigurePropertyCallback)configure_link_button_property);
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