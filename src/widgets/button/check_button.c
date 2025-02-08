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
    if (g_strcmp0(property, "margin_top") == 0)
        check_button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        check_button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        check_button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
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
    return init_generic_config(index,(void*)check_button_config,(ConfigurePropertyCallback)configure_check_button_property);
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