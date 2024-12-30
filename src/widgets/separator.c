#include "../../include/widgets/separator.h"

SeparatorConfig *init_separator(GtkOrientation orientation)
{
    SeparatorConfig *separator_config;
    SAFE_ALLOC(separator_config, SeparatorConfig, 1);

    // Init other properties

    return separator_config;
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
    return separator;
}