#include "../../include/widgets/entry.h"

Entry *init_entry(gchar *text, gchar *placeholder_text,Dimensions dimension)
{
    Entry *entry = (Entry*)malloc(sizeof(Entry));
    entry->text = (gchar*) malloc(50*sizeof(gchar));
    entry->placeholder_text = (gchar*) malloc(50*sizeof(gchar));
    strcpy(entry->text, text);
    strcpy(entry->placeholder_text, placeholder_text);
    entry->dimension = dimension;
    entry->is_visible = TRUE;
    entry->is_editable = TRUE;
    entry->purpose = GTK_INPUT_PURPOSE_FREE_FORM;
    entry->max_length = 50;
    entry->alignment = 0;
    strcpy(entry->bg_color, "#FFFFFF");
    strcpy(entry->text_color, "#000000");
    return entry;
}

GtkWidget *create_entry(Entry *entry_data)
{
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry), entry_data->text);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), entry_data->placeholder_text);
    gtk_entry_set_visibility(GTK_ENTRY(entry), entry_data->is_visible);
    // ERROR gtk_entry_set_editable(GTK_ENTRY(entry), entry_data->is_editable);
    gtk_entry_set_input_purpose(GTK_ENTRY(entry), entry_data->purpose);
    gtk_entry_set_max_length(GTK_ENTRY(entry), entry_data->max_length);
    gtk_entry_set_alignment(GTK_ENTRY(entry), entry_data->alignment);
    GdkRGBA bg_color;
    gdk_rgba_parse(&bg_color, entry_data->bg_color);
    gtk_widget_override_background_color(GTK_WIDGET(entry), GTK_STATE_FLAG_NORMAL, &bg_color);
    GdkRGBA text_color;
    gdk_rgba_parse(&text_color, entry_data->text_color);
    gtk_widget_override_color(GTK_WIDGET(entry), GTK_STATE_FLAG_NORMAL, &text_color);
    return entry;
}