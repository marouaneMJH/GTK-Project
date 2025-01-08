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
    // Check if the combo text box config and the index file is not null
    if (!combo_text_box_config || !index)
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

        // If the all properties are readed then break the loop and return the view config
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
                    // Apply the property value to the window config
                    view_config = configure_combo_text_box_property(combo_text_box_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_config;
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
