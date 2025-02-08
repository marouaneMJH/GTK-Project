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
    if (g_strcmp0(property, "margin_top") == 0)
        separator_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        separator_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        separator_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
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
    return init_generic_config(index,(void*)separator_config,(ConfigurePropertyCallback)configure_separator_property);
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