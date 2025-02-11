#include "../../../include/containers/layouts/combo_text_box.h"

ViewConfig *configure_combo_text_box_property(
    ComboTextBoxConfig *combo_text_box_config,
    ViewConfig *view_config,
    gchar *property,
    gchar *value)
{
    if (!combo_text_box_config || !property || !value)
        return NULL;

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        combo_text_box_config->margins.top = atoi(value);
    else if (g_strcmp0(property, "margin_bottom") == 0)
        combo_text_box_config->margins.bottom = atoi(value);
    else if (g_strcmp0(property, "margin_start") == 0)
        combo_text_box_config->margins.start = atoi(value);
    else if (g_strcmp0(property, "margin_end") == 0)
        combo_text_box_config->margins.end = atoi(value);

    // Dimensions
    else if (g_strcmp0(property, "height") == 0)
        combo_text_box_config->dimensions.height = atoi(value);
    else if (g_strcmp0(property, "width") == 0)
        combo_text_box_config->dimensions.width = atoi(value);

    // Display properties
    else if (g_strcmp0(property, "popup_fixed_width") == 0)
        combo_text_box_config->popup_fixed_width = g_strcmp0(value, "true") == 0;
    else if (g_strcmp0(property, "wrap_width") == 0)
        combo_text_box_config->wrap_width = atoi(value);
    else if (g_strcmp0(property, "popup_shown_rows") == 0)
        combo_text_box_config->popup_shown_rows = atoi(value);
    else if (g_strcmp0(property, "placeholder_text") == 0)
        combo_text_box_config->placeholder_text = g_strdup(value);

    else if (g_strcmp0(property, "default_value") == 0)
        combo_text_box_config->default_value = g_strdup(value);

    else if (g_strcmp0(property, "default_index") == 0)
        combo_text_box_config->default_index = atoi(value);

    else if (g_strcmp0(property, "has_entry") == 0)
        combo_text_box_config->has_entry = (strcmp(value, "true") == 0);

    else if (g_strcmp0(property, "is_editable") == 0)
        combo_text_box_config->is_editable = (strcmp(value, "true") == 0);

    // Style properties
    else if (g_strcmp0(property, "bg_color") == 0)
        strcpy(combo_text_box_config->style.bg_color, value);
    else if (g_strcmp0(property, "color") == 0)
        strcpy(combo_text_box_config->style.color, value);
    else if (g_strcmp0(property, "font_family") == 0)
        strcpy(combo_text_box_config->style.font_family, value);
    else if (g_strcmp0(property, "font_size") == 0)
        combo_text_box_config->style.font_size = atoi(value);
    else if (g_strcmp0(property, "is_bold") == 0)
        combo_text_box_config->style.is_bold = g_strcmp0(value, "true") == 0;
    else if (g_strcmp0(property, "is_italic") == 0)
        combo_text_box_config->style.is_italic = g_strcmp0(value, "true") == 0;

    //  Type
    else if (g_strcmp0(property, "end") == 0)
        combo_text_box_config->type.end = atoi(value);
    else if (g_strcmp0(property, "start") == 0)
        combo_text_box_config->type.start = atoi(value);
    else if (g_strcmp0(property, "type") == 0)
    {
        if (g_strcmp0(value, "month") == 0)
            combo_text_box_config->type.type_counter = MONTH;
        else if (g_strcmp0(value, "day") == 0)
            combo_text_box_config->type.type_counter = DAY;

        else if (g_strcmp0(value, "year") == 0)
            combo_text_box_config->type.type_counter = YEAR;

        else if (g_strcmp0(value, "counter") == 0)
            combo_text_box_config->type.type_counter = COUNTER;
    }

    // Options handling
    else if (strncmp(property, "option", 6) == 0 && property[6] != '\0')
    {
        ComboTextBoxOption *combo_text_box_option = g_new(ComboTextBoxOption, 1);
        combo_text_box_option->key = g_strdup(property + 6);
        combo_text_box_option->value = g_strdup(value);

        if (!combo_text_box_config->options)
            combo_text_box_config->options = g_ptr_array_new_with_free_func(g_free);

        g_ptr_array_add(combo_text_box_config->options, combo_text_box_option);
    }

    // Set view config property
    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_combo_text_box_config(FILE *index, ComboTextBoxConfig *combo_text_box_config)
{
    return init_generic_config(index, (void *)combo_text_box_config, (ConfigurePropertyCallback)configure_combo_text_box_property);
}

GtkWidget *create_combo_text_box(ComboTextBoxConfig combo_text_box_config)
{
    GtkWidget *combo_text_box;

    // Create the combo box with or without an entry based on configuration
    if (combo_text_box_config.has_entry)
    {
        combo_text_box = gtk_combo_box_text_new_with_entry();
        GtkWidget *entry = gtk_bin_get_child(GTK_BIN(combo_text_box));

        // Set entry width
        if (combo_text_box_config.dimensions.width > 5 &&
            combo_text_box_config.dimensions.height > 5)
            gtk_widget_set_size_request(entry,
                                        combo_text_box_config.dimensions.width - 5,
                                        combo_text_box_config.dimensions.height - 5);

        // Set editable  permission
        gtk_editable_set_editable(GTK_EDITABLE(entry),
                                  combo_text_box_config.is_editable);

        // this functio

        // Set default text if provided, else set placeholder
        if (combo_text_box_config.default_value && combo_text_box_config.default_value[0] != '\0')
        {
            gtk_entry_set_text(GTK_ENTRY(entry), combo_text_box_config.default_value);
        }
        else if (combo_text_box_config.placeholder_text)
        {
            gtk_entry_set_placeholder_text(GTK_ENTRY(entry), combo_text_box_config.placeholder_text);
        }
    }
    else
    {
        combo_text_box = gtk_combo_box_text_new();
        g_print("label: %d ", combo_text_box_config.default_index);
    }

    /* Verify the type of counter */
    // Add options to the combo box
    if (combo_text_box_config.type.type_counter == NONE &&
        combo_text_box_config.options)
    {
        for (int i = 0; i < combo_text_box_config.options->len; i++)
        {
            ComboTextBoxOption *option = g_ptr_array_index(combo_text_box_config.options, i);
            gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text_box), option->key, option->value);
        }
    }
    else if (combo_text_box_config.type.type_counter == COUNTER)
        combo_box_make_interval(combo_text_box,
                                combo_text_box_config.type.start,
                                combo_text_box_config.type.end);

    else if (combo_text_box_config.type.type_counter == YEAR)
        combo_box_make_interval(combo_text_box, 2000, 2025);

    else if (combo_text_box_config.type.type_counter == MONTH)

        combo_box_make_interval(combo_text_box, 1, 12);

    else if (combo_text_box_config.type.type_counter == DAY)
        combo_box_make_interval(combo_text_box, 1, 31);

    // Apply widget dimensions and margins
    gtk_widget_set_size_request(combo_text_box,
                                combo_text_box_config.dimensions.width,
                                combo_text_box_config.dimensions.height);
    widget_set_margins(combo_text_box, combo_text_box_config.margins);

    // Set popup width and wrap width if specified
    gtk_combo_box_set_popup_fixed_width(GTK_COMBO_BOX(combo_text_box),
                                        combo_text_box_config.popup_fixed_width);

    if (combo_text_box_config.wrap_width > 0)
    {
        gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(combo_text_box),
                                     combo_text_box_config.wrap_width);
    }

    // Apply style properties (font, colors, bold, italic)
    if (combo_text_box_config.style.bg_color[0] != '\0' || combo_text_box_config.style.color[0] != '\0')
    {
        widget_set_colors(combo_text_box,
                          combo_text_box_config.style.bg_color,
                          combo_text_box_config.style.color);
    }

    if (combo_text_box_config.style.font_family[0] != '\0')
    {
        widget_set_font_family(combo_text_box,
                               combo_text_box_config.style.font_family);
    }

    if (combo_text_box_config.style.font_size > 0)
    {
        widget_set_font_size(combo_text_box,
                             combo_text_box_config.style.font_size);
    }

    // Apply bold and italic styles if entry exists
    if (combo_text_box_config.has_entry &&
        (combo_text_box_config.style.is_bold || combo_text_box_config.style.is_italic))
    {
        GtkWidget *entry = gtk_bin_get_child(GTK_BIN(combo_text_box));
        PangoAttrList *attrs = pango_attr_list_new();

        if (combo_text_box_config.style.is_bold)
        {
            pango_attr_list_insert(attrs, pango_attr_weight_new(PANGO_WEIGHT_BOLD));
        }

        if (combo_text_box_config.style.is_italic)
        {
            pango_attr_list_insert(attrs, pango_attr_style_new(PANGO_STYLE_ITALIC));
        }

        gtk_entry_set_attributes(GTK_ENTRY(entry), attrs);
        pango_attr_list_unref(attrs);
    }

    if (combo_text_box_config.default_index != -1 && !combo_text_box_config.has_entry)
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_text_box), combo_text_box_config.default_index);
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

void combo_text_box_insert(GtkComboBoxText *combo_text_box,
                           gint index,
                           const gchar *id,
                           const gchar *text)
{
    gtk_combo_box_text_insert(combo_text_box, index, id, text);
}

void combo_box_make_interval(GtkWidget *combo_text_box, int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text_box), (char *)g_strdup_printf("%0d", i), (char *)g_strdup_printf("%0d", i));
    }
}
