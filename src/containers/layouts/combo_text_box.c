#include "../../../include/containers/layouts/combo_text_box.h"

GtkWidget *create_combo_text_box(ComboTextBoxConfig combo_text_box_config)
{
    GtkWidget *combo_text_box = NULL;  
    // Creation
    if (combo_text_box_config.has_entry)
    {
        combo_text_box = gtk_combo_box_text_new_with_entry();
    }
    else
    {
        combo_text_box = gtk_combo_box_text_new();
    }

    // // Set options
    for (int i = 0; i < combo_text_box_config.options->len; i++)
    {
        ComboTextBoxOptions *option = g_ptr_array_index(combo_text_box_config.options, i);
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text_box),option->key, option->value);
    }

    // Set dimensions
    gtk_widget_set_size_request(combo_text_box, combo_text_box_config.dimensions.width, combo_text_box_config.dimensions.height);

    // Set margins
    widget_set_margins(combo_text_box, combo_text_box_config.margins);

    // Set text and value
    gtk_combo_box_set_active_id(GTK_COMBO_BOX(combo_text_box), combo_text_box_config.deafault_value);


    return combo_text_box;
}


void combo_text_box_remove_all(GtkComboBoxText *combo_text_box)
{
    gtk_combo_box_text_remove_all(combo_text_box);
}

void combo_text_box_remove(GtkComboBoxText *combo_text_box, gint index)
{
    gtk_combo_box_text_remove(combo_text_box, index);
}

void combo_text_box_insert(GtkComboBoxText *combo_text_box, gint index, const gchar *id, const gchar *text)
{
    gtk_combo_box_text_insert(combo_text_box, index, id, text);
}

