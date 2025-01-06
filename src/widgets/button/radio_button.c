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
    if (g_strcmp0(property, "mrgin_top") == 0)
        radio_button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "mrgin_bottom") == 0)
        radio_button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "mrgin_left") == 0)
        radio_button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "mrgin_right") == 0)
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
    // Check if the radio_button config and the index file is not null
    if (!radio_button_config || !index)
        return NULL;

    // Create view config
    ViewConfig *view_config = NULL;
    SAFE_ALLOC(view_config, ViewConfig, 1);
    DFEAULT_VIEW_CONFIG(view_config);

    // Store the property and value of the tag
    gchar *property = NULL;
    gchar *value = NULL;

    // Read the tag character by character
    gchar c;
    while ((c = fgetc(index)) != '>')
    {
        /* If the character is a letter then go back one character
            Because when the tag is readed the cursor will start with the first letter in the property and it will be lost */
        if (is_character(c))
            fseek(index, -1, SEEK_CUR);

        int status = -1;

        // Read the property of the tag
        property = read_property(index, &status);

        // If the all properties are readed then break the loop and return the view id and pass the properties to the radio_button config
        if (status == 2)
            return view_config;

        // If the property is readed then read the value of the property
        else if (status == 1 && property)
        {
            // Read the value of the property
            value = read_value(index, &status);
            if (status == 1 && value)
            {
                if (g_strcmp0(property, "id") == 0) // Store the view id
                {
                    strcpy(view_config->view_id, value);
                    free(property);
                }
                else
                {
                    // Apply the property value to the radio_button config
                    int config_status;
                    view_config = configure_radio_button_property(radio_button_config, view_config, property, value, &config_status);
                    if (!config_status)
                    {
                        printf("Error configuring the property %s\n", property);
                    }
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_config;
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