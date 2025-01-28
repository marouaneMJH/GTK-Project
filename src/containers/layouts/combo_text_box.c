#include "../../../include/containers/layouts/combo_text_box.h"

ViewConfig *configure_combo_text_box_property(ComboTextBoxConfig *combo_text_box_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!combo_text_box_config || !property || !value)
        return NULL;


    // <Margins

    if (g_strcmp0(property, "margin_top") == 0)
        combo_text_box_config->margins.top = atoi(value);
    else if (g_strcmp0(property, "margin_bottom") == 0)
        combo_text_box_config->margins.bottom = atoi(value);
    else if (g_strcmp0(property, "margin_start") == 0)
        combo_text_box_config->margins.start = atoi(value);
    else if (g_strcmp0(property, "margin_end") == 0)
        combo_text_box_config->margins.end = atoi(value);

    // <Dimensions
    else if (g_strcmp0(property, "height") == 0)
        combo_text_box_config->dimensions.height = atoi(value);
    else if (g_strcmp0(property, "width") == 0)
        combo_text_box_config->dimensions.width = atoi(value);

    else
    {
        // Allocate memory for the combo box option structure
        ComboTextBoxOptions *combo_text_box_option = g_new(ComboTextBoxOptions, 1);

        // Allocate memory for key and value strings
        combo_text_box_option->key = g_strdup(property);
        combo_text_box_option->value = g_strdup(value);

        // Allocate memory for combo box options array if it doesn't exist
        if (!combo_text_box_config->options)
            combo_text_box_config->options = g_ptr_array_new_with_free_func(g_free);

        // Add the option to the options array
        g_ptr_array_add(combo_text_box_config->options, combo_text_box_option);
    }

    return view_config;
}

ViewConfig *init_combo_text_box_config(FILE *index, ComboTextBoxConfig *combo_text_box_config)
{
        return init_generic_config(index,(void*)combo_text_box_config,(ConfigurePropertyCallback)configure_combo_text_box_property);
}
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
    if (combo_text_box_config.options)
    {
        for (int i = 0; i < combo_text_box_config.options->len; i++)
        {
            ComboTextBoxOptions *option = g_ptr_array_index(combo_text_box_config.options, i);
            gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text_box), option->key, option->value);
        }
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
