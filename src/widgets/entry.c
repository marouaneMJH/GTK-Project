#include "../../include/widgets/entry.h"

ViewConfig *configure_entry_property(EntryConfig *entry_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!entry_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "text") == 0)
        strcpy(entry_config->text, value);

    if (g_strcmp0(property, "placeholder_text") == 0)
        strcpy(entry_config->placeholder_text, value);

    if (g_strcmp0(property, "is_visible") == 0)
        entry_config->is_visible = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;
    
    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        entry_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        entry_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        entry_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        entry_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        entry_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        entry_config->dimensions.height = atoi(value);

    // Appearance
    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(entry_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(entry_config->text_color, value);

    if (g_strcmp0(property, "opacity") == 0)
        entry_config->opacity = atof(value);

    if (g_strcmp0(property, "has_frame") == 0)
        entry_config->has_frame = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Text handling
    if (g_strcmp0(property, "overwrite_mode") == 0)
        entry_config->overwrite_mode = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "max_length") == 0)
        entry_config->max_length = atoi(value);
    
    if (g_strcmp0(property, "alignment") == 0)
        entry_config->alignment = atof(value);

    if (g_strcmp0(property, "progress_fraction") == 0)
        entry_config->progress_fraction = atof(value);
    else if (g_strcmp0(property, "progress_pulse_step") == 0)
        entry_config->progress_pulse_step = atof(value);

    if (g_strcmp0(property, "activates_default") == 0)
        entry_config->activates_default = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "type") == 0)
    {
        if (g_strcmp0(value, "number") == 0)
            entry_config->purpose = GTK_INPUT_PURPOSE_NUMBER;
        else if (g_strcmp0(value, "email") == 0)
            entry_config->purpose = GTK_INPUT_PURPOSE_EMAIL;
        else if (g_strcmp0(value, "name") == 0)
            entry_config->purpose = GTK_INPUT_PURPOSE_NAME;
        else if (g_strcmp0(value, "password") == 0)
            entry_config->purpose = GTK_INPUT_PURPOSE_PASSWORD;
        else if (g_strcmp0(value, "pin") == 0)
            entry_config->purpose = GTK_INPUT_PURPOSE_PIN;
    }

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_entry_config(FILE *index, EntryConfig *entry_config)
{
    return init_generic_config(index, (void *)entry_config, (ConfigurePropertyCallback)configure_entry_property);
}


void numeric_field_handler(GtkEntry *entry, const gchar *text, gint length) {
    // Allow only digits
    for (int i = 0; i < length; i++) {
        if (!g_ascii_isdigit(text[i])) {
            g_signal_stop_emission_by_name(entry, "insert-text");
            return;
        }
    }
}

void email_field_handler(GtkEntry *entry, const gchar *text, gint length) {
    // Allow only email characters
    for (int i = 0; i < length; i++) {
        if (!g_ascii_isalnum(text[i]) && text[i] != '@' && text[i] != '.' && text[i] != '_') {
            g_signal_stop_emission_by_name(entry, "insert-text");
            return;
        }
    }
}
void on_icon_press(GtkEntry *entry,gpointer user_data)
{
    
        gtk_entry_set_text(entry, "");
}

GtkWidget *create_entry(EntryConfig entry_config)
{

    
    g_print("=============================================\n");
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(entry), GTK_ENTRY_ICON_SECONDARY, "edit-clear");
    gtk_entry_set_text(GTK_ENTRY(entry), entry_config.text);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), entry_config.placeholder_text);
    gtk_entry_set_visibility(GTK_ENTRY(entry), entry_config.is_visible);
    gtk_entry_set_input_purpose(GTK_ENTRY(entry), entry_config.purpose);
    //
    if (entry_config.purpose == GTK_INPUT_PURPOSE_EMAIL)
        g_signal_connect(entry, "insert-text", G_CALLBACK(email_field_handler), NULL);
        
    if ((entry_config.purpose == GTK_INPUT_PURPOSE_NUMBER) || (entry_config.purpose == GTK_INPUT_PURPOSE_PIN))
        g_signal_connect(entry, "insert-text", G_CALLBACK(numeric_field_handler), NULL);
    if( (entry_config.purpose == GTK_INPUT_PURPOSE_PASSWORD) || (entry_config.purpose == GTK_INPUT_PURPOSE_PIN) )
        gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);

    const gchar* icon=gtk_entry_get_icon_name(GTK_ENTRY(entry), GTK_ENTRY_ICON_SECONDARY);
    if(icon)
        g_signal_connect(entry, "icon-press", G_CALLBACK(on_icon_press), NULL);
    
    
    gtk_entry_set_max_length(GTK_ENTRY(entry), entry_config.max_length);
    g_print("Entry max length: %d\n", entry_config.max_length);
    gtk_widget_set_size_request(entry, entry_config.dimensions.width, entry_config.dimensions.height);

    gtk_widget_set_opacity(entry, entry_config.opacity);
    gtk_entry_set_alignment(GTK_ENTRY(entry), entry_config.alignment);
    gtk_entry_set_has_frame(GTK_ENTRY(entry), entry_config.has_frame);
    gtk_entry_set_overwrite_mode(GTK_ENTRY(entry), entry_config.overwrite_mode);
    if (entry_config.progress_fraction > 0)
        gtk_entry_set_progress_fraction(GTK_ENTRY(entry), entry_config.progress_fraction);
    gtk_entry_set_activates_default(GTK_ENTRY(entry), entry_config.activates_default);
    if (entry_config.progress_pulse_step > 0)
        gtk_entry_set_progress_pulse_step(GTK_ENTRY(entry), entry_config.progress_pulse_step);
    if (entry_config.completion)
        gtk_entry_set_completion(GTK_ENTRY(entry), entry_config.completion);

    g_print("Entry bg color: %s\n", entry_config.bg_color);
    widget_set_colors(GTK_WIDGET(entry), entry_config.bg_color, entry_config.text_color);
    widget_set_margins(GTK_WIDGET(entry), entry_config.margins);


    // To look at later:
    // gtk_entry_set_cursor_hadjustment(GTK_ENTRY(Myentry), hadjustment);
    //  GdkRGBA bg_color;
    //  gdk_rgba_parse(&bg_color, entry_config.bg_color);
    //  gtk_widget_override_background_color(GTK_WIDGET(entry), GTK_STATE_FLAG_NORMAL, &bg_color);
    //  GdkRGBA text_color;
    //  gdk_rgba_parse(&text_color, entry_config.text_color);
    //  gtk_widget_override_color(GTK_WIDGET(entry), GTK_STATE_FLAG_NORMAL, &text_color);
    return entry;
}

// To look at later: Function to create a completion system for an entry

// GtkEntryCompletion* create_completion_system() {
//     // Create a completion object
//     GtkEntryCompletion *completion = gtk_entry_completion_new();

//     // Create a model with some sample completion data (a simple list of strings)
//     GtkListStore *store = gtk_list_store_new(1, G_TYPE_STRING);
//     gtk_list_store_insert_with_values(store, NULL, -1, 0, "Apple", -1);
//     gtk_list_store_insert_with_values(store, NULL, -1, 0, "Banana", -1);
//     gtk_list_store_insert_with_values(store, NULL, -1, 0, "Cherry", -1);
//     gtk_list_store_insert_with_values(store, NULL, -1, 0, "Grape", -1);
//     gtk_list_store_insert_with_values(store, NULL, -1, 0, "Orange", -1);

//     // Set the model for the completion system
//     gtk_entry_completion_set_model(completion, GTK_TREE_MODEL(store));

//     // Set the column that will be used for completion (in this case, the first column)
//     gtk_entry_completion_set_text_column(completion, 0);

//     return completion;
// }

