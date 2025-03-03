#include "./../../include/widgets/text_area.h"

ViewConfig *configure_text_area_property(TextAreaConfig *text_area_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!text_area_config || !property || !value)
        return NULL;

    if (strcmp(property, "font_size") == 0)
    {
        text_area_config->font_size = atoi(value);
    }
    else if (strcmp(property, "text_color") == 0)
    {
        strncpy(text_area_config->text_color, value, MAX_COLOR_SIZE);
    }
    else if (strcmp(property, "background_color") == 0)
    {
        strncpy(text_area_config->bg_color, value, MAX_COLOR_SIZE);
    }
    else if (strcmp(property, "is_editable") == 0)
    {
        text_area_config->is_editable = (strcmp(value, "true") == 0) ? TRUE : FALSE;
    }
    else if (strcmp(property, "width") == 0)
    {
        text_area_config->dimensions.width = atoi(value);
    }
    else if (strcmp(property, "height") == 0)
    {
        text_area_config->dimensions.height = atoi(value);
    }
    else if (strcmp(property, "wrap_mode") == 0)
    {
        if (strcmp(value, "none") == 0)
            text_area_config->wrap_mode = GTK_WRAP_NONE;
        else if (strcmp(value, "char") == 0)
            text_area_config->wrap_mode = GTK_WRAP_CHAR;
        else if (strcmp(value, "word") == 0)
            text_area_config->wrap_mode = GTK_WRAP_WORD;
        else if (strcmp(value, "word-char") == 0)
            text_area_config->wrap_mode = GTK_WRAP_WORD_CHAR;
    }

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            text_area_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            text_area_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            text_area_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            text_area_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            text_area_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            text_area_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            text_area_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            text_area_config->halign = GTK_ALIGN_FILL;
    }

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_text_area_config(FILE *index, TextAreaConfig *text_area_config)
{
    return init_generic_config(index, (void *)text_area_config, (ConfigurePropertyCallback)configure_text_area_property);
}

GtkWidget *create_text_area(TextAreaConfig text_area)
{
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    GtkWidget *text_view = gtk_text_view_new();

    /* Apply properties */
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), text_area.wrap_mode);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), text_area.is_editable);

    if (text_area.font_size > 0)
        widget_set_font_size(text_view, text_area.font_size);

    widget_set_colors(text_view, text_area.bg_color, text_area.text_color);

    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    if (text_area.dimensions.width > 0 && text_area.dimensions.height > 0)
        set_widget_size(scrolled_window, text_area.dimensions);

    // Enable or disable cells expand (the parent should be expandable; not important)
    gtk_widget_set_hexpand(text_view, text_area.hexpand);
    gtk_widget_set_vexpand(text_view, text_area.vexpand);

    // Set alignments
    gtk_widget_set_halign(text_view, text_area.halign);
    gtk_widget_set_valign(text_view, text_area.valign);

    return scrolled_window;
}

TextAreaConfig *read_text_area_config_from_dialog()
{
    TextAreaConfig *text_area_config_ptr = NULL;
    SAFE_ALLOC(text_area_config_ptr, TextAreaConfig, 1);

    TextAreaConfig text_area_config = DEFAULT_TEXT_AREA;

    // Font size
    gint font_size = read_config_value_as_int("font_size_spin");
    text_area_config.font_size = font_size;

    // Wrap mode
    const gchar *wrap_mode = read_config_value_as_string("wrap_mode_combo");
    if (stricmp(wrap_mode, "none") == 0)
        text_area_config.wrap_mode = GTK_WRAP_NONE;
    else if (stricmp(wrap_mode, "word") == 0)
        text_area_config.wrap_mode = GTK_WRAP_WORD;
    else if (stricmp(wrap_mode, "word char") == 0)
        text_area_config.wrap_mode = GTK_WRAP_WORD_CHAR;
    else
        text_area_config.wrap_mode = GTK_WRAP_CHAR;

    // Editable
    gboolean is_editable = read_config_value_as_boolean("editable_switch");
    text_area_config.is_editable = is_editable;

    // Dimensions
    Dimensions *dimensions = read_dimensions_config();
    text_area_config.dimensions.width = dimensions->width;
    text_area_config.dimensions.height = dimensions->height;

    // // Margins
    // Margins *margins = read_margins_config();
    // text_area_config.margins.top = margins->top;
    // text_area_config.margins.bottom = margins->bottom;
    // text_area_config.margins.start = margins->start;
    // text_area_config.margins.end = margins->end;

    // HAlign
    text_area_config.halign = read_align_config("halign_combo");

    // VAlign
    text_area_config.valign = read_align_config("valign_combo");

    // HExpand
    gboolean hexpand = read_config_value_as_boolean("hexpand_switch");
    text_area_config.hexpand = hexpand;

    // VExpand
    gboolean vexpand = read_config_value_as_boolean("vexpand_switch");
    text_area_config.vexpand = vexpand;

    // Background color
    const gchar *bg_color = read_config_value_as_string("bg_color_entry");
    strcpy(text_area_config.bg_color, bg_color);

    // Text color
    const gchar *text_color = read_config_value_as_string("color_entry");
    strcpy(text_area_config.text_color, text_color);

    memcpy(text_area_config_ptr, &text_area_config, sizeof(TextAreaConfig));
    return text_area_config_ptr;
}

gchar *write_text_area_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "text_area", tabs_number);

    // Get the GtkTextView from the view
    GtkTextView *text_view = GTK_TEXT_VIEW(view->widget);

    // Check if the text area is editable
    gboolean is_editable = gtk_text_view_get_editable(text_view);
    if (is_editable != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_editable=\"%s\"\n", is_editable ? "true" : "false");
    }

    // Get the wrap mode
    GtkWrapMode wrap_mode = gtk_text_view_get_wrap_mode(text_view);
    if (wrap_mode != GTK_WRAP_WORD) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "wrap_mode=\"%s\"\n", wrap_mode == GTK_WRAP_NONE ? "none" : wrap_mode == GTK_WRAP_CHAR    ? "char"
                                                                                     : wrap_mode == GTK_WRAP_WORD      ? "word"
                                                                                     : wrap_mode == GTK_WRAP_WORD_CHAR ? "word_char"
                                                                                                                       : "unknown");
    }

    return "text_area";
}