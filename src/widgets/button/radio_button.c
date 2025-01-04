#include "./../../../include/global.h"
#include "./../../../include/widgets/button/radio_button.h"

RadioButtonConfig *init_radio_button_config(const gchar *label, gboolean is_group)
{
    RadioButtonConfig *radio_button_config;
    SAFE_ALLOC(radio_button_config, RadioButtonConfig, 1);

    g_strlcpy(radio_button_config->label, label, MAX_BUTTON_LABEL_SIZE);
    radio_button_config->is_group = is_group;
    return radio_button_config;
}

GtkWidget *create_radio_button(RadioButtonConfig radio_button_config)
{
    GtkWidget *radio_button = NULL;

    // Creation
    if (radio_button_config.is_group) // Create as group
    {
        if (radio_button_config.label && radio_button_config.label[0] != '\0') // Create with label
        {
            if (radio_button_config.is_mnemonic)
            {
                // Create with mnemonic
                radio_button = gtk_radio_button_new_with_mnemonic(NULL, radio_button_config.label);
            }
            else
            {
                // Create with simple label
                radio_button = gtk_radio_button_new_with_label(NULL, radio_button_config.label);
            }
        }
        else
        {
            // Create empty radio button
            radio_button = gtk_radio_button_new(NULL);
        }
    }
    else if (radio_button_config.group) // Create as member of group
    {
        if (radio_button_config.label && radio_button_config.label[0] != '\0')
        {
            if (radio_button_config.is_mnemonic)
            {
                // Create with mnemonic from a group
                radio_button = gtk_radio_button_new_with_mnemonic_from_widget(GTK_RADIO_BUTTON(radio_button_config.group), radio_button_config.label);
            }
            else
            {
                // Create with mnemonic from a group
                radio_button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_button_config.group), radio_button_config.label);
            }
        }
        else
        {
            // Create empty radio button from a group
            radio_button = gtk_radio_button_new(gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio_button_config.group)));
        }
    }

    // Enable or disable the radio button
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button), radio_button_config.is_selected);

    // Set normal button mode
    gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(radio_button), !radio_button_config.is_button_mode);

    // Set inconsistent mode (ambiguity mode)
    gtk_toggle_button_set_inconsistent(GTK_TOGGLE_BUTTON(radio_button), radio_button_config.is_inconsistent);

    // Set underline mode
    gtk_button_set_use_underline(GTK_BUTTON(radio_button), radio_button_config.use_underline);

    // Set the tooltip
    gtk_widget_set_tooltip_text(radio_button, radio_button_config.tooltip);

    // Set icon
    if (radio_button_config.icon_name && radio_button_config.icon_name[0] != '\0')
    {
        GtkWidget *radio_button_icon = gtk_image_new_from_icon_name(radio_button_config.icon_name, GTK_ICON_SIZE_BUTTON);
        gtk_button_set_image(GTK_BUTTON(radio_button), radio_button_icon);
        gtk_button_set_image_position(GTK_BUTTON(radio_button), GTK_POS_RIGHT);
    }

    // Set margins
    widget_set_margins(radio_button, radio_button_config.margins);

    // Set dimensions
    if (radio_button_config.dimensions.width > 0 && radio_button_config.dimensions.height > 0)
    {
        gtk_widget_set_size_request(radio_button, radio_button_config.dimensions.width, radio_button_config.dimensions.height);
    }

    // Set colors
    widget_set_colors(radio_button, radio_button_config.bg_color, radio_button_config.text_color);

    // Old way (deprecated for either background or text color)
    // GdkRGBA bg_color;
    // gdk_rgba_parse(&bg_color, "#ff00ff");
    // gtk_widget_override_background_color(GTK_WIDGET(rb2), GTK_STATE_FLAG_NORMAL, &bg_color);

    return radio_button;
}

void radio_button_set_group(GtkWidget *widget, GtkWidget *group)
{
    gtk_radio_button_set_group(GTK_RADIO_BUTTON(widget), gtk_radio_button_get_group(GTK_RADIO_BUTTON(group)));
}