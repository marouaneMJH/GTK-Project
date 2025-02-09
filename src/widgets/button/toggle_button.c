#include "./../../../include/global.h"
#include "./../../../include/widgets/button/toggle_button.h"

// Fonction de configuration des propriétés du ToggleButton
ViewConfig *configure_toggle_button_property(ToggleButtonConfig *toggle_button_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!toggle_button_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "label") == 0)
        strncpy(toggle_button_config->label, value, MAX_BUTTON_LABEL_SIZE - 1);

    else if (g_strcmp0(property, "tooltip") == 0)
        strncpy(toggle_button_config->tooltip, value, MAX_TOOLTIP_SIZE - 1);

    else if (g_strcmp0(property, "is_mnemonic") == 0)
        toggle_button_config->is_mnemonic = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    else if (g_strcmp0(property, "is_active") == 0)
        toggle_button_config->is_active = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    else if (g_strcmp0(property, "is_visible") == 0)
        toggle_button_config->is_visible = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    else if (g_strcmp0(property, "mode") == 0)
        toggle_button_config->mode = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    else if (g_strcmp0(property, "is_inconsistent") == 0)
        toggle_button_config->is_inconsistent = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    else if (g_strcmp0(property, "bg_color") == 0)
        strncpy(toggle_button_config->bg_color, value, MAX_COLOR_SIZE - 1);

    else if (g_strcmp0(property, "text_color") == 0)
        strncpy(toggle_button_config->text_color, value, MAX_COLOR_SIZE - 1);

    else if (g_strcmp0(property, "width") == 0)
        toggle_button_config->dimensions.width = atoi(value);

    else if (g_strcmp0(property, "height") == 0)
        toggle_button_config->dimensions.height = atoi(value);

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_toggle_button_config(FILE *index, ToggleButtonConfig *toggle_button_config)
{
    return init_generic_config(index, (void *)toggle_button_config, (ConfigurePropertyCallback)configure_toggle_button_property);
}

// Fonction de création du ToggleButton
GtkWidget *create_toggle_button(ToggleButtonConfig toggle_button_config)
{
    GtkWidget *w_toggle_button;

    // Création avec ou sans mnémonique
    if (toggle_button_config.is_mnemonic)
        w_toggle_button = gtk_toggle_button_new_with_mnemonic(toggle_button_config.label);
    else
        w_toggle_button = gtk_toggle_button_new_with_label(toggle_button_config.label);

    // Définition des dimensions si spécifiées
    if (toggle_button_config.dimensions.width > 0 || toggle_button_config.dimensions.height > 0)
    {
        gtk_widget_set_size_request(
            w_toggle_button,
            toggle_button_config.dimensions.width,
            toggle_button_config.dimensions.height);
    }

    // Appliquer la visibilité
    gtk_widget_set_visible(w_toggle_button, toggle_button_config.is_visible);

    // Appliquer l'état actif
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(w_toggle_button), toggle_button_config.is_active);

    // Appliquer le mode indicateur
    gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(w_toggle_button), toggle_button_config.mode);

    // Appliquer l'état incohérent
    gtk_toggle_button_set_inconsistent(GTK_TOGGLE_BUTTON(w_toggle_button), toggle_button_config.is_inconsistent);

    // Ajouter une infobulle si définie
    if (strlen(toggle_button_config.tooltip) > 0)
        gtk_widget_set_tooltip_text(w_toggle_button, toggle_button_config.tooltip);

    return w_toggle_button;
}

/* Signaux */

// Callback lorsque le ToggleButton change d'état
static void toggle_button_toggled_callback(GtkWidget *toggle_button, gpointer user_data)
{
    gboolean state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_button));
    g_print("Toggle button state: %s\n", state ? "ON" : "OFF");
}

// Connexion du signal "toggled"
void connect_toggle_button_signal(GtkWidget *toggle_button)
{
    g_signal_connect(toggle_button, "toggled", G_CALLBACK(toggle_button_toggled_callback), NULL);
}

/* Fonctions utilitaires */

void set_toggle_button_active(GtkWidget *toggle_button, gboolean is_active)
{
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_button), is_active);
}

gboolean get_toggle_button_active(GtkWidget *toggle_button)
{
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_button));
}

void set_toggle_button_mode(GtkWidget *toggle_button, gboolean mode)
{
    gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(toggle_button), mode);
}

gboolean get_toggle_button_mode(GtkWidget *toggle_button)
{
    return gtk_toggle_button_get_mode(GTK_TOGGLE_BUTTON(toggle_button));
}

void set_toggle_button_inconsistent(GtkWidget *toggle_button, gboolean is_inconsistent)
{
    gtk_toggle_button_set_inconsistent(GTK_TOGGLE_BUTTON(toggle_button), is_inconsistent);
}

gboolean get_toggle_button_inconsistent(GtkWidget *toggle_button)
{
    return gtk_toggle_button_get_inconsistent(GTK_TOGGLE_BUTTON(toggle_button));
}
