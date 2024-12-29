#include "./../../../include/global.h"
#include "./../../../include/widget/button/button.h"

Button edit_button(
    gchar *label,
    gboolean is_sensitive,
    gboolean is_visible,
    gchar *tooltip,
    Dimensions dimensions,
    Margin margin,
    gboolean expand,
    gchar *bg_color,
    gchar *text_color

)
{
    Button b;

    // Pointers  values
    if (label)
        g_strlcpy(b.label, label, MAX_BUTTON_LABEL_SIZE);
    if (tooltip)
        g_strlcpy(b.tooltip, tooltip, MAX_BUTTON_TOOLTIP_SIZE);
    if (bg_color)
        g_strlcpy(b.bg_color, bg_color, MAX_COLOR_SIZE);
    if (text_color)
        g_strlcpy(b.text_color, text_color, MAX_COLOR_SIZE);

    b.is_sensitive = is_sensitive;
    b.is_visible = is_visible;
    // b.tooltip=tooltip;
    b.dimensions = dimensions;
    b.margin = margin;
    b.expand = expand;

    return ((Button)b);
}

GtkWidget *create_button(Button button)
{
    // Create a new button with the given label
    GtkWidget *b = gtk_button_new_with_label(button.label);

    // Set sensitivity
    gtk_widget_set_sensitive(b, button.is_sensitive);

    // Set visibility
    if (!button.is_visible)
        gtk_widget_hide(b);

    // Set tooltip
    if (button.tooltip) // Ensure tooltip is not empty
        gtk_widget_set_tooltip_text(b, button.tooltip);

    // todo dimensions validate function
    // Set dimensions (width and height)
    if (button.dimensions.width > 0 && button.dimensions.height > 0)
        gtk_widget_set_size_request(b, button.dimensions.width, button.dimensions.height);

    // Set expand property
    if (button.expand)
    {
        gtk_widget_set_hexpand(b, TRUE);
        gtk_widget_set_vexpand(b, TRUE);
    }

    // Set background and/or label colors
    widget_set_colors(b, button.bg_color, button.text_color);

    // Set margin
    gtk_widget_set_margin_start(b, button.margin.start);
    gtk_widget_set_margin_end(b, button.margin.end);
    gtk_widget_set_margin_top(b, button.margin.top);
    gtk_widget_set_margin_bottom(b, button.margin.bottom);

    return ((GtkWidget *)b);
}
