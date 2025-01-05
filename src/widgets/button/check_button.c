#include "./../../../include/global.h"
#include "./../../../include/widgets/button/check_button.h"





CheckButtonConfig *init_check_button_config(const gchar *label, gboolean is_active)
{
    CheckButtonConfig *check_button_config;
    SAFE_ALLOC(check_button_config, CheckButtonConfig, 1);
    Dimensions d = DEFAULT_CHECK_BUTTON_DIMENSIONS; 
    g_strlcpy(check_button_config->label, label, MAX_BUTTON_LABEL_SIZE);
    check_button_config->is_active = is_active;
    check_button_config->is_inconsistent = FALSE;
    check_button_config->use_underline = FALSE;
    check_button_config->dimensions = d;
    g_strlcpy(check_button_config->bg_color, "\0", MAX_COLOR_SIZE);
    g_strlcpy(check_button_config->text_color, "\0", MAX_COLOR_SIZE);

    return check_button_config;
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

    return check_button;
}