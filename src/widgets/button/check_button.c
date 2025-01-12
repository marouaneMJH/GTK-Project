#include "./../../../include/global.h"
#include "./../../../include/widgets/button/check_button.h"




ViewConfig *configure_check_button_property(CheckButtonConfig *check_button_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!check_button_config || !property || !value)
        return NULL;

    // Label
    if (g_strcmp0(property, "label") == 0)
        strcpy(check_button_config->label, value);

    // Tooltip
    if (g_strcmp0(property, "tooltip") == 0)
        strcpy(check_button_config->tooltip, value);

    // Active state
    if (g_strcmp0(property, "is_active") == 0)
        check_button_config->is_active = g_strcmp0(value, "true") == 0;

    // Inconsistent state
    if (g_strcmp0(property, "is_inconsistent") == 0)
        check_button_config->is_inconsistent = g_strcmp0(value, "true") == 0;

    // Use underline
    if (g_strcmp0(property, "use_underline") == 0)
        check_button_config->use_underline = g_strcmp0(value, "true") == 0;

        // Margins
    if (g_strcmp0(property, "mrgin_top") == 0)
        check_button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "mrgin_bottom") == 0)
        check_button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "mrgin_left") == 0)
        check_button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "mrgin_right") == 0)
        check_button_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        check_button_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        check_button_config->dimensions.height = atoi(value);

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(check_button_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(check_button_config->text_color, value);
        
    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_check_button_config(FILE *index, CheckButtonConfig *check_button_config)
{
    // Check if the check_button config and the index file is not null
    if (!check_button_config || !index)
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

        // If the all properties are readed then break the loop and return the view id and pass the properties to the check_button config
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
                    // Apply the property value to the check_button config
                    view_config = configure_check_button_property(check_button_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_config;
}

GtkWidget *create_check_button(CheckButtonConfig check_button_config)
{
    GtkWidget *check_button = NULL;

    // Création du bouton avec ou sans label
    if (check_button_config.label && check_button_config.label[0] != '\0')
    {
        if (check_button_config.use_underline)
        {
            check_button = gtk_check_button_new_with_mnemonic(check_button_config.label);
        }
        else
        {
            check_button = gtk_check_button_new_with_label(check_button_config.label);
        }
    }
    else
    {
        check_button = gtk_check_button_new(); // Bouton vide
    }

    // Configuration des propriétés
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button), check_button_config.is_active);
    gtk_toggle_button_set_inconsistent(GTK_TOGGLE_BUTTON(check_button), check_button_config.is_inconsistent);
    gtk_widget_set_tooltip_text(check_button, check_button_config.tooltip);

    // Dimensions
    if (check_button_config.dimensions.width > 0 && check_button_config.dimensions.height > 0)
    {
        gtk_widget_set_size_request(check_button, check_button_config.dimensions.width, check_button_config.dimensions.height);
    }

    // Couleurs
    widget_set_colors(check_button, check_button_config.bg_color, check_button_config.text_color);

    widget_set_margins(check_button, check_button_config.margins);

    return check_button;
}