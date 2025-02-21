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

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "radio_button", tabs_number);

    // Get the GtkRadioButton from the view
    GtkRadioButton *radio_button = GTK_RADIO_BUTTON(view->widget);

    // Get the label text
    const gchar *label = gtk_button_get_label(GTK_BUTTON(radio_button));
    if (g_strcmp0(label, "\0") != 0) // Check if the label text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "label=\"%s\"\n", label);
    }

    // Get the icon name GtkWidget *image = gtk_button_get_image(GTK_BUTTON(radio_button));
    // if (image && GTK_IS_IMAGE(image)) // Check if the button has an image
    // {
    //     const gchar *icon_name = gtk_image_get_icon_name(GTK_IMAGE(image));
    //     if (g_strcmp0(icon_name, "\0") != 0) // Check if the icon name is not the default
    //     {
    //         print_tabs(output_file, tabs_number + 1);
    //         fprintf(output_file, "icon_name=\"%s\"\n", icon_name);
    //     }
    // }

    // Get the tooltip text
    const gchar *tooltip = gtk_widget_get_tooltip_text(GTK_WIDGET(radio_button));
    if (g_strcmp0(tooltip, "\0") != 0) // Check if the tooltip text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "tooltip=\"%s\"\n", tooltip);
    }

    // Check if the radio button is part of a group
    gboolean is_group = gtk_radio_button_get_group(radio_button) != NULL;
    if (is_group != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_group=\"%s\"\n", is_group ? "true" : "false");
    }

    // Check if the radio button uses mnemonics
    gboolean is_mnemonic = gtk_button_get_use_underline(GTK_BUTTON(radio_button));
    if (is_mnemonic != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_mnemonic=\"%s\"\n", is_mnemonic ? "true" : "false");
    }

    // Check if the radio button is selected
    gboolean is_selected = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_button));
    if (is_selected != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_selected=\"%s\"\n", is_selected ? "true" : "false");
    }

    // Check if the radio button is in button mode
    gboolean is_button_mode = gtk_toggle_button_get_mode(GTK_TOGGLE_BUTTON(radio_button));
    if (is_button_mode != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_button_mode=\"%s\"\n", is_button_mode ? "true" : "false");
    }

    // Check if the radio button is in an inconsistent state
    gboolean is_inconsistent = gtk_toggle_button_get_inconsistent(GTK_TOGGLE_BUTTON(radio_button));
    if (is_inconsistent != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_inconsistent=\"%s\"\n", is_inconsistent ? "true" : "false");
    }

    // Check if the radio button uses underline in the label
    gboolean use_underline = gtk_button_get_use_underline(GTK_BUTTON(radio_button));
    if (use_underline != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "use_underline=\"%s\"\n", use_underline ? "true" : "false");
    }

    // Get the icon position
    GtkPositionType icon_position = gtk_button_get_image_position(GTK_BUTTON(radio_button));
    if (icon_position != GTK_POS_LEFT) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "icon_position=\"%s\"\n", icon_position == GTK_POS_LEFT ? "left" : icon_position == GTK_POS_RIGHT ? "right"
                                                                                            : icon_position == GTK_POS_TOP     ? "top"
                                                                                            : icon_position == GTK_POS_BOTTOM  ? "bottom"
                                                                                                                               : "unknown");
    }

    return "radio_button";
}