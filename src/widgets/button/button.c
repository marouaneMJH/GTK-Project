#include "./../../../include/widgets/button/button.h"

ViewConfig *configure_button_property(ButtonConfig *button_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!button_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "label") == 0)
        strcpy(button_config->label, value);

    if (g_strcmp0(property, "tooltip") == 0)
        strcpy(button_config->tooltip, value);

    if (g_strcmp0(property, "is_sensitive") == 0)
        button_config->is_sensitive = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_visible") == 0)
        button_config->is_visible = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Margins
    if (g_strcmp0(property, "mrgin_top") == 0)
        button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "mrgin_bottom") == 0)
        button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "mrgin_left") == 0)
        button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "mrgin_right") == 0)
        button_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        button_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        button_config->dimensions.height = atoi(value);

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(button_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(button_config->text_color, value);

    if (g_strcmp0(property, "expand") == 0)
        button_config->expand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;
    

    if (g_strcmp0(property, "expand") == 0)
        button_config->expand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;
    

    // Icon image and icon

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_button_config(FILE *index, ButtonConfig *button_config)
{
    return init_generic_config(index,(void*)button_config,(ConfigurePropertyCallback)configure_button_property);
}

GtkWidget *create_button(ButtonConfig button_config)
{
    // Create a new button with the given label
    GtkWidget *button = gtk_button_new_with_mnemonic(button_config.label);

    // Set sensitivity
    gtk_widget_set_sensitive(button, button_config.is_sensitive);

    // Set visibility
    if (!button_config.is_visible)
        gtk_widget_hide(button);

    // Set tooltip
    if (button_config.tooltip) // Ensure tooltip is not empty
        gtk_widget_set_tooltip_text(button, button_config.tooltip);

    // todo dimensions validate function
    // Set dimensions (width and height)
    if (button_config.dimensions.width > 0 && button_config.dimensions.height > 0)
        gtk_widget_set_size_request(button, button_config.dimensions.width, button_config.dimensions.height);

    // Set expand property
    if (button_config.expand)
    {
        gtk_widget_set_hexpand(button, TRUE);
        gtk_widget_set_vexpand(button, TRUE);
    }

    // Set background and/or label colors
   widget_set_colors(button, button_config.bg_color, button_config.text_color);
   
   widget_set_colors(button, button_config.bg_color, button_config.text_color);
   
    // Set margin
    widget_set_margins(button, button_config.margins);

    return ((GtkWidget *)button);
}
