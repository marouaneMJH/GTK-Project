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
    GtkWidget *combo_text_box = NULL;

    // Create combo box with entry only if has_entry is true
    if (combo_text_box_config.has_entry)
    {
        combo_text_box = gtk_combo_box_text_new_with_entry();

        // Configure entry-specific properties if has_entry is true
        if (combo_text_box_config.placeholder_text)
        {
            GtkWidget *entry = gtk_bin_get_child(GTK_BIN(combo_text_box));
            gtk_entry_set_placeholder_text(GTK_ENTRY(entry), combo_text_box_config.placeholder_text);
        }

        // Check for default text or any text set through options (e.g., <entry />)
        if (combo_text_box_config.options)
        {
            for (int i = 0; i < combo_text_box_config.options->len; i++)
            {
                ComboTextBoxOption *option = g_ptr_array_index(combo_text_box_config.options, i);
                
                if (g_strcmp0(option->value, "<entry />") == 0)
                {
                    GtkWidget *entry = gtk_bin_get_child(GTK_BIN(combo_text_box));
                    gtk_entry_set_text(GTK_ENTRY(entry), option->key);
                }
                else
                {
                    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text_box), option->key, option->value);
                }
            }
        }
    }
    else
    {
        combo_text_box = gtk_combo_box_text_new();
        
        // Add options if no entry field is visible
        if (combo_text_box_config.options)
        {
            for (int i = 0; i < combo_text_box_config.options->len; i++)
            {
                ComboTextBoxOption *option = g_ptr_array_index(combo_text_box_config.options, i);
                gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text_box), option->key, option->value);
            }
        }
    }

    // Set dimensions for the combo box
    gtk_widget_set_size_request(combo_text_box,
                                combo_text_box_config.dimensions.width,
                                combo_text_box_config.dimensions.height);

    // Set margins
    widget_set_margins(combo_text_box, combo_text_box_config.margins);

    // Set popup width if needed
    gtk_combo_box_set_popup_fixed_width(GTK_COMBO_BOX(combo_text_box),
                                        combo_text_box_config.popup_fixed_width);

    // Set wrap width if specified
    if (combo_text_box_config.wrap_width > 0)
        gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(combo_text_box),
                                     combo_text_box_config.wrap_width);

    // Apply style properties (font, colors, bold, italic)
    if (combo_text_box_config.style.bg_color[0] != '\0' || combo_text_box_config.style.color[0] != '\0')
        widget_set_colors(combo_text_box,
                          combo_text_box_config.style.bg_color,
                          combo_text_box_config.style.color);

    if (combo_text_box_config.style.font_family[0] != '\0')
        widget_set_font_family(combo_text_box,
                               combo_text_box_config.style.font_family);

    if (combo_text_box_config.style.font_size > 0)
        widget_set_font_size(combo_text_box,
                             combo_text_box_config.style.font_size);

    // Apply bold and italic styles
    if (combo_text_box_config.style.is_bold || combo_text_box_config.style.is_italic)
    {
        PangoAttrList *attrs = pango_attr_list_new();

        if (combo_text_box_config.style.is_bold)
            pango_attr_list_insert(attrs, pango_attr_weight_new(PANGO_WEIGHT_BOLD));

        if (combo_text_box_config.style.is_italic)
            pango_attr_list_insert(attrs, pango_attr_style_new(PANGO_STYLE_ITALIC));

        GtkWidget *entry = gtk_bin_get_child(GTK_BIN(combo_text_box));
        gtk_entry_set_attributes(GTK_ENTRY(entry), attrs);

        pango_attr_list_unref(attrs);
    }

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





// todo 
// GtkWidget *create_combo_text_box(ComboTextBoxConfig combo_text_box_config)
// {
//     GtkWidget *combo_text_box = gtk_combo_box_text_new_with_entry();

//     // Configure entry-specific properties
//     if (combo_text_box_config.placeholder_text)
//     {
//         GtkWidget *entry = gtk_bin_get_child(GTK_BIN(combo_text_box));
//         gtk_entry_set_placeholder_text(GTK_ENTRY(entry), combo_text_box_config.placeholder_text);
//     }

//     // Add options
//     if (combo_text_box_config.options)
//     {
//         for (int i = 0; i < combo_text_box_config.options->len; i++)
//         {
//             ComboTextBoxOption *option = g_ptr_array_index(combo_text_box_config.options, i);

//             if (g_strcmp0(option->value, "<entry />") == 0)
//             {
//                 GtkWidget *entry = gtk_bin_get_child(GTK_BIN(combo_text_box));
//                 gtk_entry_set_text(GTK_ENTRY(entry), option->key);
//             }
//             else
//             {
//                 gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text_box), option->key, option->value);
//             }
//         }
//     }

//     // Set dimensions
//     gtk_widget_set_size_request(combo_text_box,
//                                 combo_text_box_config.dimensions.width,
//                                 combo_text_box_config.dimensions.height);

//     // Set margins
//     widget_set_margins(combo_text_box, combo_text_box_config.margins);

//     // Set popup width
//     gtk_combo_box_set_popup_fixed_width(GTK_COMBO_BOX(combo_text_box),
//                                         combo_text_box_config.popup_fixed_width);

//     // Set wrap width if needed
//     if (combo_text_box_config.wrap_width > 0)
//         gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(combo_text_box),
//                                      combo_text_box_config.wrap_width);

//     // Apply styles
//     if (combo_text_box_config.style.bg_color[0] != '\0' || combo_text_box_config.style.color[0] != '\0')
//         widget_set_colors(combo_text_box,
//                           combo_text_box_config.style.bg_color,
//                           combo_text_box_config.style.color);

//     if (combo_text_box_config.style.font_family[0] != '\0')
//         widget_set_font_family(combo_text_box,
//                                combo_text_box_config.style.font_family);

//     if (combo_text_box_config.style.font_size > 0)
//         widget_set_font_size(combo_text_box,
//                              combo_text_box_config.style.font_size);

//     // Apply bold & italic styles
//     if (combo_text_box_config.style.is_bold || combo_text_box_config.style.is_italic)
//     {
//         PangoAttrList *attrs = pango_attr_list_new();

//         if (combo_text_box_config.style.is_bold)
//             pango_attr_list_insert(attrs, pango_attr_weight_new(PANGO_WEIGHT_BOLD));

//         if (combo_text_box_config.style.is_italic)
//             pango_attr_list_insert(attrs, pango_attr_style_new(PANGO_STYLE_ITALIC));

//         GtkWidget *entry = gtk_bin_get_child(GTK_BIN(combo_text_box));
//         gtk_entry_set_attributes(GTK_ENTRY(entry), attrs);

//         pango_attr_list_unref(attrs);
//     }

//     return combo_text_box;
// }
