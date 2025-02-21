#include "./../../../include/global.h"
#include "./../../../include/widgets/button/radio_button.h"

ViewConfig *configure_radio_button_property(RadioButtonConfig *radio_button_config, ViewConfig *view_config, gchar *property, gchar *value, int *status)
{
    if (!radio_button_config || !property || !value)
    {
        *status = 0;
        return NULL;
    }

    if (g_strcmp0(property, "label") == 0)
        strcpy(radio_button_config->label, value);

    if (g_strcmp0(property, "icon_name") == 0)
        strcpy(radio_button_config->icon_name, value);

    if (g_strcmp0(property, "tooltip") == 0)
        strcpy(radio_button_config->tooltip, value);

    if (g_strcmp0(property, "is_group") == 0)
    {
        radio_button_config->is_group = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;
        view_config->group = NULL;
    }

    if (g_strcmp0(property, "is_mnemonic") == 0)
        radio_button_config->is_mnemonic = g_strcmp0(property, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_selected") == 0)
        radio_button_config->is_selected = g_strcmp0(property, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_button_mode") == 0)
        radio_button_config->is_button_mode = g_strcmp0(property, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_inconsistent") == 0)
        radio_button_config->is_inconsistent = g_strcmp0(property, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "use_underline") == 0)
        radio_button_config->use_underline = g_strcmp0(property, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "icon_position") == 0)
    {
        if (g_strcmp0(property, "left") == 0)
            radio_button_config->icon_position = GTK_POS_LEFT;
        else if (g_strcmp0(property, "right") == 0)
            radio_button_config->icon_position = GTK_POS_RIGHT;
        else if (g_strcmp0(property, "top") == 0)
            radio_button_config->icon_position = GTK_POS_TOP;
        else if (g_strcmp0(property, "bottom") == 0)
            radio_button_config->icon_position = GTK_POS_BOTTOM;
    }

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        radio_button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        radio_button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        radio_button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        radio_button_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        radio_button_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        radio_button_config->dimensions.height = atoi(value);

    // Colors
    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(radio_button_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(radio_button_config->text_color, value);

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_radio_button_config(FILE *index, RadioButtonConfig *radio_button_config)
{
    return init_generic_config(index, (void *)radio_button_config, (ConfigurePropertyCallback)configure_radio_button_property);
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
    else
    {
        g_print("Error while creating a radio button");
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
        gtk_button_set_image_position(GTK_BUTTON(radio_button), radio_button_config.icon_position);
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

gchar *write_radio_button_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    write_widget_tag_style_view_config(output_file, view, "radio_button", tabs_number);

    return "radio_button";
}
