#include "./../../../include/widgets/button/button.h"

ButtonConfig edit_button(
    gchar *label,
    gboolean is_sensitive,
    gboolean is_visible,
    gchar *tooltip,
    Dimensions dimensions,
    Margins margins,
    gboolean expand,
    gchar *bg_color,
    gchar *text_color

)
{
    ButtonConfig button_config;

    // Pointers  values
    if (label)
        g_strlcpy(button_config.label, label, MAX_BUTTON_LABEL_SIZE);
    if (tooltip)
        g_strlcpy(button_config.tooltip, tooltip, MAX_TOOLTIP_SIZE);
    if (bg_color)
        g_strlcpy(button_config.bg_color, bg_color, MAX_COLOR_SIZE);
    if (text_color)
        g_strlcpy(button_config.text_color, text_color, MAX_COLOR_SIZE);

    button_config.is_sensitive = is_sensitive;
    button_config.is_visible = is_visible;
    // button_config.tooltip=tooltip;
    button_config.dimensions = dimensions;
    button_config.margins = margins;
    button_config.expand = expand;

    return ((ButtonConfig)button_config);
}

GtkWidget *create_button(ButtonConfig button_config)
{
    // Create a new button with the given label
    GtkWidget *button = gtk_button_new_with_label(button_config.label);

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
   
    // Set margin
    widget_set_margins(button, button_config.margins);

    return ((GtkWidget *)button);
}
