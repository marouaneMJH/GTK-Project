#include "../../include/widgets/entry.h"
//TODO: Add a init_entry with buffer function 
// EntryConfig *init_entry(gchar *text, gchar *placeholder_text,Dimensions dimension)
// {
//     EntryConfig *entry = (EntryConfig*)malloc(sizeof(EntryConfig));
//     entry->text = (gchar*) malloc(50*sizeof(gchar));
//     entry->placeholder_text = (gchar*) malloc(50*sizeof(gchar));
//     strcpy(entry->text, text);
//     strcpy(entry->placeholder_text, placeholder_text);
//     entry->dimension = dimension;
//     entry->is_visible = TRUE;
//     entry->is_editable = TRUE;
//     entry->purpose = GTK_INPUT_PURPOSE_FREE_FORM;
//     entry->max_length = 50;
//     entry->alignment = 0;
//     strcpy(entry->bg_color, "#FFFFFF");
//     strcpy(entry->text_color, "#000000");
//     return entry;
// }

GtkWidget *create_entry(EntryConfig *entry_data)
{
    if (!entry_data)
        exit(EXIT_FAILURE);


    GtkWidget *entry = gtk_entry_new();

    gtk_entry_set_text(GTK_ENTRY(entry), entry_data->text);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), entry_data->placeholder_text);
    gtk_entry_set_visibility(GTK_ENTRY(entry), entry_data->is_visible);
    gtk_entry_set_input_purpose(GTK_ENTRY(entry), entry_data->purpose);
    gtk_entry_set_max_length(GTK_ENTRY(entry), entry_data->max_length);
    gtk_widget_set_size_request(entry, entry_data->dimension.width, entry_data->dimension.height);
    gtk_widget_set_opacity(entry, entry_data->opacity);
    gtk_entry_set_alignment(GTK_ENTRY(entry), entry_data->alignment);
    gtk_entry_set_has_frame(GTK_ENTRY(entry), entry_data->has_frame);
    gtk_entry_set_overwrite_mode(GTK_ENTRY(entry), entry_data->overwrite_mode);
    if (entry_data->progress_fraction > 0)
        gtk_entry_set_progress_fraction(GTK_ENTRY(entry), entry_data->progress_fraction);
    gtk_entry_set_activates_default(GTK_ENTRY(entry), entry_data->activates_default);
    if (entry_data->progress_pulse_step > 0)
        gtk_entry_set_progress_pulse_step(GTK_ENTRY(entry), entry_data->progress_pulse_step);
    if(entry_data->completion)
        gtk_entry_set_completion(GTK_ENTRY(entry), entry_data->completion);

    widget_set_colors(GTK_WIDGET(entry), entry_data->bg_color, entry_data->text_color);
    widget_set_margins(GTK_WIDGET(entry), entry_data->margins);

    //To look at later:
    //gtk_entry_set_cursor_hadjustment(GTK_ENTRY(Myentry), hadjustment);
    // GdkRGBA bg_color;
    // gdk_rgba_parse(&bg_color, entry_data->bg_color);
    // gtk_widget_override_background_color(GTK_WIDGET(entry), GTK_STATE_FLAG_NORMAL, &bg_color);
    // GdkRGBA text_color;
    // gdk_rgba_parse(&text_color, entry_data->text_color);
    // gtk_widget_override_color(GTK_WIDGET(entry), GTK_STATE_FLAG_NORMAL, &text_color);
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