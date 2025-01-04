#include "./../../../include/global.h"
#include "./../../../include/widgets/button/link_button.h"




LinkButtonConfig *init_link_button_config(const gchar *uri, const gchar *label)
{
    LinkButtonConfig *link_button_config;
    SAFE_ALLOC(link_button_config, LinkButtonConfig, 1);

    // copy URI and label to the configuration
    g_strlcpy(link_button_config->uri, uri, MAX_URI_SIZE);
    g_strlcpy(link_button_config->label, label, MAX_BUTTON_LABEL_SIZE);

    // Initialize other fields with default values
    g_strlcpy(link_button_config->tooltip, "", MAX_TOOLTIP_SIZE);
    link_button_config->is_visited = FALSE;
    //link_button_config->dimensions = DEFAULT_LINK_BUTTON_DIMENSIONS;
    g_strlcpy(link_button_config->bg_color, "", MAX_COLOR_SIZE);
    g_strlcpy(link_button_config->text_color, "", MAX_COLOR_SIZE);

    return link_button_config;
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

    return link_button;
}