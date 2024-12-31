
#include "./../../../include/widgets/button/switch_button.h"

SwitchButtonConfig *init_switch_button_config(const gchar *label)
{
    SwitchButtonConfig *switch_button_config;
    SAFE_ALLOC(switch_button_config, SwitchButtonConfig, 1);

    g_strlcpy(switch_button_config->label, label, MAX_BUTTON_LABEL_SIZE);
    return switch_button_config;
}

GtkWidget *create_switch_button(SwitchButtonConfig switch_button_config)
{
    GtkWidget *switch_button = NULL;

    // Creation
    switch_button = gtk_switch_new();

    // Set dimensions
    if (switch_button_config.dimensions.width > 0 && switch_button_config.dimensions.height > 0)
    {
        gtk_widget_set_size_request(switch_button, switch_button_config.dimensions.width, switch_button_config.dimensions.height);
    }

    // Set colors (background and/or text colors)
    widget_set_colors(switch_button, switch_button_config.bg_color, switch_button_config.text_color);

    // Enable or disable the switch
    gtk_switch_set_active(GTK_SWITCH(switch_button), switch_button_config.is_active);

    // Set visibility
    if (switch_button_config.is_visible)
        gtk_widget_show(switch_button);

    // Set a tooltip
    gtk_widget_set_tooltip_text(switch_button, switch_button_config.tooltip);

    // Set the state to ON or OFF like active but this one controll the switch during transition not only the final state
    gtk_switch_set_state(GTK_SWITCH(switch_button), switch_button_config.state);

    // Set margins
    widget_set_margins(switch_button, switch_button_config.margins);

    return switch_button;
}
