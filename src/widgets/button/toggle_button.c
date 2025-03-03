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

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            toggle_button_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            toggle_button_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            toggle_button_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            toggle_button_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            toggle_button_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            toggle_button_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            toggle_button_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            toggle_button_config->halign = GTK_ALIGN_FILL;
    }

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
    GtkWidget *toggle_button_widget;

    // Création avec ou sans mnémonique
    if (toggle_button_config.is_mnemonic)
        toggle_button_widget = gtk_toggle_button_new_with_mnemonic(toggle_button_config.label);
    else
        toggle_button_widget = gtk_toggle_button_new_with_label(toggle_button_config.label);

    // Définition des dimensions si spécifiées
    if (toggle_button_config.dimensions.width > 0 || toggle_button_config.dimensions.height > 0)
    {
        gtk_widget_set_size_request(
            toggle_button_widget,
            toggle_button_config.dimensions.width,
            toggle_button_config.dimensions.height);
    }

    // Appliquer la visibilité
    gtk_widget_set_visible(toggle_button_widget, toggle_button_config.is_visible);

    // Appliquer l'état actif
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_button_widget), toggle_button_config.is_active);

    // Appliquer le mode indicateur
    gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(toggle_button_widget), toggle_button_config.mode);

    // Appliquer l'état incohérent
    gtk_toggle_button_set_inconsistent(GTK_TOGGLE_BUTTON(toggle_button_widget), toggle_button_config.is_inconsistent);

    // Ajouter une infobulle si définie
    if (strlen(toggle_button_config.tooltip) > 0)
        gtk_widget_set_tooltip_text(toggle_button_widget, toggle_button_config.tooltip);

    gtk_widget_set_hexpand(toggle_button_widget, toggle_button_config.hexpand);
    gtk_widget_set_vexpand(toggle_button_widget, toggle_button_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(toggle_button_widget, toggle_button_config.halign);
    gtk_widget_set_valign(toggle_button_widget, toggle_button_config.valign);

    return toggle_button_widget;
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

ToggleButtonConfig *read_toggle_button_config_from_dialog()
{
    ToggleButtonConfig *toggle_button_config_ptr = NULL;
    SAFE_ALLOC(toggle_button_config_ptr, ToggleButtonConfig , 1);

    ToggleButtonConfig toggle_button_config = DEFAULT_TOGGLE_BUTTON;

    // Label
    const gchar *label = read_config_value_as_string("label_entry");
    strncpy(toggle_button_config.label, label, MAX_BUTTON_LABEL_SIZE - 1);

    // Tooltip
    const gchar *tooltip = read_config_value_as_string("tooltip_entry");
    strncpy(toggle_button_config.tooltip, tooltip, MAX_TOOLTIP_SIZE - 1);

    // Is mnemonic
    gboolean is_mnemonic = read_config_value_as_boolean("mnemonic_switch");
    toggle_button_config.is_mnemonic = is_mnemonic;

    // Is active
    gboolean is_active = read_config_value_as_boolean("active_switch");
    toggle_button_config.is_active = is_active;

    // Is visible
    gboolean is_visible = read_config_value_as_boolean("visible_switch");
    toggle_button_config.is_visible = is_visible;

    // Mode
    gboolean mode = read_config_value_as_boolean("mode_switch");
    toggle_button_config.mode = mode;

    // Is inconsistent
    gboolean is_inconsistent = read_config_value_as_boolean("inconsistent_switch");
    toggle_button_config.is_inconsistent = is_inconsistent;

    // Dimensions
    Dimensions *dimensions = read_dimensions_config();
    toggle_button_config.dimensions.width = dimensions->width;
    toggle_button_config.dimensions.height = dimensions->height;

    // Margins
    Margins *margins = read_margins_config();
    toggle_button_config.margins.top = margins->top;
    toggle_button_config.margins.bottom = margins->bottom;
    toggle_button_config.margins.start = margins->start;
    toggle_button_config.margins.end = margins->end;

    // HAlign
    toggle_button_config.halign = read_align_config("halign_combo");

    // VAlign
    toggle_button_config.valign = read_align_config("valign_combo");

    // HExpand
    gboolean hexpand = read_config_value_as_boolean("hexpand_switch");
    toggle_button_config.hexpand = hexpand;

    // VExpand
    gboolean vexpand = read_config_value_as_boolean("vexpand_switch");
    toggle_button_config.vexpand = vexpand;

    // Background color
    const gchar *bg_color = read_config_value_as_string("bg_color_entry");
    strcpy(toggle_button_config.bg_color, bg_color);

    // Text color
    const gchar *text_color = read_config_value_as_string("color_entry");
    strcpy(toggle_button_config.text_color, text_color);

    memcpy(toggle_button_config_ptr, &toggle_button_config, sizeof(ToggleButtonConfig ));
    return toggle_button_config_ptr;
}


gchar *write_toggle_button_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "toggle_button", tabs_number);

    // Get the GtkToggleButton from the view
    GtkToggleButton *toggle_button = GTK_TOGGLE_BUTTON(view->widget);

    // Get the label text
    const gchar *label = gtk_button_get_label(GTK_BUTTON(toggle_button));
    if (g_strcmp0(label, "") != 0) // Check if the label text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "label=\"%s\"\n", label);
    }

    // Get the tooltip text
    const gchar *tooltip = gtk_widget_get_tooltip_text(GTK_WIDGET(toggle_button));
    if (g_strcmp0(tooltip, "") != 0) // Check if the tooltip text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "tooltip=\"%s\"\n", tooltip);
    }

    // Check if the toggle button uses mnemonics
    gboolean is_mnemonic = gtk_button_get_use_underline(GTK_BUTTON(toggle_button));
    if (is_mnemonic != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_mnemonic=\"%s\"\n", is_mnemonic ? "true" : "false");
    }

    // Check if the toggle button is active
    gboolean is_active = gtk_toggle_button_get_active(toggle_button);
    if (is_active != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_active=\"%s\"\n", is_active ? "true" : "false");
    }

    // Check if the toggle button is visible
    gboolean is_visible = gtk_widget_get_visible(GTK_WIDGET(toggle_button));
    if (is_visible != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_visible=\"%s\"\n", is_visible ? "true" : "false");
    }

    // Check if the toggle button is in button mode
    gboolean mode = gtk_toggle_button_get_mode(toggle_button);
    if (mode != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "mode=\"%s\"\n", mode ? "true" : "false");
    }

    // Check if the toggle button is in an inconsistent state
    gboolean is_inconsistent = gtk_toggle_button_get_inconsistent(toggle_button);
    if (is_inconsistent != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_inconsistent=\"%s\"\n", is_inconsistent ? "true" : "false");
    }

    // Get the horizontal expand property
    gboolean hexpand = gtk_widget_get_hexpand(GTK_WIDGET(toggle_button));
    if (hexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "hexpand=\"%s\"\n", hexpand ? "true" : "false");
    }

    // Get the vertical expand property
    gboolean vexpand = gtk_widget_get_vexpand(GTK_WIDGET(toggle_button));
    if (vexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "vexpand=\"%s\"\n", vexpand ? "true" : "false");
    }

    return "toggle_button";
}