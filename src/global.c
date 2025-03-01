#include "./../include/global.h"

View *root_view_global;
View *root_dialog_view_global;
GtkApplication *root_app;

View *new_root_view_global;

// inline void free_widget(GtkWidget *widget)
// {
//     if (widget != NULL)
//     {
//         gtk_widget_destroy(widget);
//         widget = NULL; // Avoid dangling pointers
//     }
// }

/////////// /_!_\ Untouchable please //////////////
GtkStyleContext *get_style_provider_context(GtkWidget *widget, const gchar *bg_color, const gchar *color, const gchar *bg_image)
{
    // Create a new CSS provider
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gchar *css_style = NULL;

    // Initialize a GString to build the CSS style
    GString *css_builder = g_string_new(".style { ");

    // Check if any of the color or background image parameters are provided
    if ((color && color[0] != '\0') || (bg_color && bg_color[0] != '\0') || (bg_image && bg_image[0] != '\0'))
    {
        // Append background image to the CSS style if provided
        g_string_append_printf(css_builder, "background-image: url('./assets/images/%s'); ", (bg_image && bg_image[0] != '\0') ? bg_image : "none;");

        // Append background size to the CSS style if background image is provided
        if ((bg_image && bg_image[0] != '\0'))
            g_string_append_printf(css_builder, "background-size: cover; ");

        // Append background color to the CSS style if provided
        if ((bg_color && bg_color[0] != '\0'))
            g_string_append_printf(css_builder, "background-color: %s; ", bg_color);

        // Append text color to the CSS style if provided
        if ((color && color[0] != '\0'))
            g_string_append_printf(css_builder, "color: %s; ", color);

        // Close the CSS style
        g_string_append(css_builder, "}");

        // Convert GString to gchar*
        css_style = g_string_free(css_builder, FALSE);
    }
    else
    {
        // Use a default stylesheet if all arguments are null
        gtk_css_provider_load_from_path(css_provider, "./assets/style.css", NULL);
    }

    // Load the generated CSS style into the CSS provider
    if (css_style)
    {
        GError *error = NULL;
        gtk_css_provider_load_from_data(css_provider, css_style, -1, &error);
        if (error)
        {
            // Print an error message if loading the CSS failed
            g_printerr("Failed to load CSS: %s\n", error->message);
            g_error_free(error);
        }
        g_free(css_style);
    }

    // Get the style context of the widget
    GtkStyleContext *context = gtk_widget_get_style_context(widget);

    // Add the CSS provider to the widget's style context
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(css_provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Free the CSS provider after use
    g_object_unref(css_provider);

    // Return the style context
    return context;
}

// Function to set both background and text colors for a widget
void widget_set_colors(GtkWidget *widget, const gchar *bg_color, const gchar *color)
{
    // Add a CSS class to the widget's style context with the specified colors
    gtk_style_context_add_class(get_style_provider_context(widget, bg_color, color, NULL), "style");
}

// Function to set a background image for a widget
void widget_set_background_image(GtkWidget *widget, const gchar *bg_image, const gchar *color)
{
    // Add a CSS class to the widget's style context with the specified background image
    gtk_style_context_add_class(get_style_provider_context(widget, NULL, color, bg_image), "style");
}

void widget_set_margins(GtkWidget *widget, Margins margins)
{
    gtk_widget_set_margin_top(widget, margins.top);
    gtk_widget_set_margin_bottom(widget, margins.bottom);
    gtk_widget_set_margin_start(widget, margins.start);
    gtk_widget_set_margin_end(widget, margins.end);
}

void widget_get_margins(GtkWidget *widget, Margins *margins)
{
    if (!margins)
        return;
    margins->top = gtk_widget_get_margin_top(widget);
    margins->bottom = gtk_widget_get_margin_bottom(widget);
    margins->start = gtk_widget_get_margin_start(widget);
    margins->end = gtk_widget_get_margin_end(widget);
}

void widget_set_font_size(GtkWidget *widget, int size)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GtkStyleContext *context = gtk_widget_get_style_context(widget);

    // Create CSS string for font size
    gchar *css = g_strdup_printf("* { font-size: %dpt; }", size);

    // Load and apply CSS
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Cleanup
    g_free(css);
    g_object_unref(provider);
}

void widget_set_font_family(GtkWidget *widget, const char *font_family)
{
    // If font_family is NULL, do nothing
    if (font_family == NULL)
    {
        return;
    }

    GtkCssProvider *provider = gtk_css_provider_new();
    GtkStyleContext *context = gtk_widget_get_style_context(widget);

    // Create CSS string for font family
    gchar *css = g_strdup_printf("* { font-family: '%s'; }", font_family);

    // Load and apply CSS
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Cleanup
    g_free(css);
    g_object_unref(provider);
}

void set_header_bar(GtkWidget *window, const gchar *title, const gchar *icon_path)
{
    // Create a header bar
    GtkWidget *header_bar = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(header_bar), "menu:close");

    // Set the title of the header bar
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), title);

    // Load the icon from the specified path
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(icon_path, NULL);
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, 32, 32, GDK_INTERP_BILINEAR);

    // Create a horizontal box to hold the icon and title
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *icon = gtk_image_new_from_pixbuf(scaled_pixbuf);

    // Add the icon to the box
    gtk_box_pack_start(GTK_BOX(box), icon, FALSE, FALSE, 0);

    // Add the box to the header bar
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), box);

    // Set the header bar as the title bar of the window
    gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);
}

// These functions are just for comparing with CSS not for use because the most of them are deprecated
// void widget_set_text_color(GtkWidget *widget, const gchar *color,GtkStateFlags state)
// {
//     GdkRGBA color_rgba;
//     gdk_rgba_parse(&color_rgba, color);
//     gtk_widget_override_color(widget, state, &color_rgba);
// }

// void widget_set_background_color(GtkWidget *widget, const gchar *color,GtkStateFlags state)
// {
//     GdkRGBA color_rgba;
//     gdk_rgba_parse(&color_rgba, color);
//     gtk_widget_override_background_color(widget, state, &color_rgba);
// }

// void widget_set_font(GtkWidget *widget, const gchar *font_name, gint font_size)
// {
//     PangoFontDescription *font_desc = pango_font_description_new();
//     pango_font_description_set_family(font_desc, font_name);
//     pango_font_description_set_size(font_desc, font_size * PANGO_SCALE);
//     gtk_widget_override_font(widget, font_desc);
//     pango_font_description_free(font_desc);
// }

// TODO: Should be not manipulate the end of tag ">" in the file
// TODO: Should manipulate spaces and tabs and new lines
// ########################## "This function should stop reading after the greater than symbol " > " exactelly"
gchar *read_property(FILE *index, int *status)
{
    gchar *property = NULL;
    SAFE_ALLOC(property, gchar, MAX_PROPERTY_SIZE);

    int i = 0;
    gchar c;
    while ((c = fgetc(index)) != '>')
    {
        if (c == '=')
        {
            *status = 1;
            property[i] = '\0';
            return property;
        }
        if (c != ' ' && c != '\n' && c != '\t')
            property[i++] = c;
    }
    if (c == '>')
        *status = 2;
    return NULL;
}

gchar *read_value(FILE *index, int *status)
{
    gchar *value = NULL;
    SAFE_ALLOC(value, gchar, MAX_VALUE_SIZE);

    int i = 0;
    gboolean reading_flag = FALSE;
    gchar c;

    while (((c = fgetc(index)) != '"' || !reading_flag) && c != EOF)
    {
        if (c != '"' && !reading_flag)
        {
            *status = -1;
            return value;
        }

        if (c == '"' && !reading_flag)
            reading_flag = !reading_flag;

        else if (c != '\n')
            value[i++] = c;
        else
        {
            // Debugging part
            if (c == '\n')
            {
                value[i] = '\0';
                g_critical("ERROR: while reading the value %s\n", value);
                exit(EXIT_FAILURE);
            }
        }
    }
    value[i] = '\0';
    *status = 1;
    return value;
}

gboolean is_character(gchar c)
{
    return (c > 'A' && c < 'Z') || (c > 'a' && c < 'z');
}

ViewConfig *init_generic_config(FILE *index, void *config, ConfigurePropertyCallback configure_property_callback)
{
    if (!config || !index)
        return NULL;

    ViewConfig *view_config = NULL;
    SAFE_ALLOC(view_config, ViewConfig, 1);
    DFEAULT_VIEW_CONFIG(view_config);

    gchar *property = NULL;
    gchar *value = NULL;

    gchar c;
    while ((c = fgetc(index)) != '>')
    {
        if (is_character(c))
            fseek(index, -1, SEEK_CUR);

        int status = -1;
        property = read_property(index, &status);

        if (status == 2)
            return view_config;

        if (status == 1 && property)
        {
            value = read_value(index, &status);
            if (status == 1 && value)
            {
                if (g_strcmp0(property, "id") == 0)
                {
                    strcpy(view_config->view_id, value);
                    free(property);
                }
                else
                {
                    view_config = configure_property_callback(config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_config;
}

View *find_view_by_id(char *view_id, View *root_view)
{
    // g_print("PASSED WIDGETS WHILE SEARCHING: %s\n", root_view->view_config->view_id);
    if (g_strcmp0(root_view->view_config->view_id, view_id) == 0)
        return (View *)root_view;

    View *view = NULL;
    if (root_view->next)
    {
        view = find_view_by_id(view_id, root_view->next);
        if (view)
            return view;
    }
    if (root_view->child)
    {
        view = find_view_by_id(view_id, root_view->child);
        if (view)
            return view;
    }
    return (View *)view;
}

// Function to force width and height using CSS for a widget
void set_widget_size(GtkWidget *widget, Dimensions dimensions)
{
    gtk_widget_set_size_request(widget, dimensions.width, dimensions.height);
    // // Create a CSS provider
    // GtkCssProvider *css_provider = gtk_css_provider_new();
    // GdkScreen *screen = gtk_widget_get_screen(widget);

    // // Create the CSS rule as a string
    // gchar *css = g_strdup_printf(
    //     ".fixed-size { "
    //     "  min-width: %dpx; "
    //     "  max-width: %dpx; "
    //     "  width: %dpx; "
    //     "  min-height: %dpx; "
    //     "  max-height: %dpx; "
    //     "  height: %dpx; "
    //     "}",
    //     dimensions.width, dimensions.width, dimensions.width, dimensions.height, dimensions.height, dimensions.height);

    // // Load the CSS data into the provider
    // gtk_css_provider_load_from_data(css_provider, css, -1, NULL);

    // // Apply the CSS provider to the widget's style context
    // gtk_style_context_add_provider(
    //     gtk_widget_get_style_context(widget),
    //     GTK_STYLE_PROVIDER(css_provider),
    //     GTK_STYLE_PROVIDER_PRIORITY_USER
    // );

    // // Add the 'fixed-size' class to the widget
    // gtk_style_context_add_class(gtk_widget_get_style_context(widget), "fixed-size");

    // // Clean up
    // g_free(css);
    // g_object_unref(css_provider);
}

// Readers

ViewConfig *read_view_config_from_dialog()
{
    // View config
    ViewConfig *view_config = NULL;
    SAFE_ALLOC(view_config, ViewConfig, 1);
    DFEAULT_VIEW_CONFIG(view_config);

    const gchar *view_id = read_config_value_as_string("view_id_entry");
    strcpy(view_config->view_id, view_id);

    // Box config
    gboolean box_expand = read_config_value_as_boolean("box_expand_switch");
    view_config->box_expand = box_expand;

    gboolean box_fill = read_config_value_as_boolean("box_fill_switch");
    view_config->box_fill = box_fill;

    gint box_padding = read_config_value_as_int("box_padding_spin");
    view_config->box_padding = box_padding;

    const gchar *pack_direction = read_config_value_as_string("pack_direction_combo");
    if (stricmp(pack_direction, "end") == 0)
        view_config->pack_direction = 0;
    else
        view_config->pack_direction = 1;

    // Fixed config
    gint position = read_config_value_as_int("position_x_spin");
    view_config->position_x = position;
    position = read_config_value_as_int("position_y_spin");
    view_config->position_y = position;


    // Notebook config
    const gchar *tab_label = read_config_value_as_string("tab_label_entry");
    g_strlcpy(view_config->tab_label, tab_label, MAX_LABEL_SIZE);

    gboolean is_reorderable = read_config_value_as_boolean("is_reorderable_switch");
    view_config->is_reorderable = is_reorderable;

    // TODO: Complete other view config properties

    // Signals config
    // OnClick
    const gchar *sig_on_click_handler = read_config_value_as_string("on_click_entry");
    if (sig_on_click_handler)
    {
        view_config->signal.event_type = SIG_ON_CLICK;
        g_strlcpy(view_config->signal.sig_handler, sig_on_click_handler, MAX_SIGNAL_NAME_SIZE);
    }

    return view_config;
}

const gchar *read_config_value_as_string(gchar *view_id)
{
    View *input_view = find_view_by_id(view_id, root_dialog_view_global);
    if (!input_view)
    {
        g_print("Error: ==> Cannot find the %s\n", view_id);
        return NULL;
    }
    if (GTK_IS_COMBO_BOX(input_view->widget))
        return gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(input_view->widget));
    else if (GTK_IS_ENTRY(input_view->widget))
        return gtk_entry_get_text(GTK_ENTRY(input_view->widget));
    g_print("Error: => Widget type not compatible with the expected value\n");
    return NULL;
}

gint read_config_value_as_int(gchar *view_id)
{
    View *input_view = find_view_by_id(view_id, root_dialog_view_global);
    if (!input_view)
    {
        g_print("Error: ==> Cannot find the %s\n", view_id);
        return 0;
    }
    if (GTK_IS_SPIN_BUTTON(input_view->widget))
        return gtk_spin_button_get_value(GTK_SPIN_BUTTON(input_view->widget));

    g_print("Error: => Widget type not compatible with the expected value\n");
    return 0;
}

gdouble read_config_value_as_double(gchar *view_id)
{
    View *input_view = find_view_by_id(view_id, root_dialog_view_global);
    if (!input_view)
    {
        g_print("Error: ==> Cannot find the %s\n", view_id);
        return 0;
    }
    if (GTK_IS_SPIN_BUTTON(input_view->widget))
        return gtk_spin_button_get_value(GTK_SPIN_BUTTON(input_view->widget));

    g_print("Error: => Widget type not compatible with the expected value\n");
    return 0;
}

gboolean read_config_value_as_boolean(gchar *view_id)
{
    View *input_view = find_view_by_id(view_id, root_dialog_view_global);
    if (!input_view)
    {
        g_print("Error: ==> Cannot find the %s\n", view_id);
        return false;
    }
    if (GTK_IS_SWITCH(input_view->widget))
        return gtk_switch_get_active(GTK_SWITCH(input_view->widget));

    g_print("Error: => Widget type not compatible with the expected value\n");
    return false;
}

GtkAlign read_align_config(gchar *input_combo)
{
    const gchar *valign = read_config_value_as_string(input_combo);
    if (valign)
    {
        if (stricmp(valign, "start") == 0)
            return GTK_ALIGN_START;
        else if (stricmp(valign, "end") == 0)
            return GTK_ALIGN_END;
        else if (stricmp(valign, "baseline") == 0)
            return GTK_ALIGN_BASELINE;
        else if (stricmp(valign, "center") == 0)
            return GTK_ALIGN_CENTER;
        else
            return GTK_ALIGN_FILL;
    }
}

GtkPositionType read_position_config(gchar *input_combo, GtkPositionType default_position)
{
    const gchar *icon_position = read_config_value_as_string(input_combo);
    if (stricmp(icon_position, "top") == 0)
        return GTK_POS_TOP;
    else if (stricmp(icon_position, "bottom") == 0)
        return GTK_POS_BOTTOM;
    else if (stricmp(icon_position, "left") == 0)
        return GTK_POS_LEFT;
    else if (stricmp(icon_position, "right") == 0)
        return GTK_POS_RIGHT;
    else
        return default_position;
}

Dimensions *read_dimensions_config()
{
    Dimensions *dimensions;
    SAFE_ALLOC(dimensions, Dimensions, 1);
    gint width = read_config_value_as_int("width_spin");
    gint height = read_config_value_as_int("height_spin");
    dimensions->width = width;
    dimensions->height = height;

    return dimensions;
}

Margins *read_margins_config()
{
    Margins *margins;
    SAFE_ALLOC(margins, Margins, 1);

    // Margin top
    gint margin_top = read_config_value_as_int("margin_top_spin");
    margins->top = margin_top;

    // Margin bottom
    gint margin_bottom = read_config_value_as_int("margin_bottom_spin");
    margins->bottom = margin_bottom;

    // Margin left
    gint margin_left = read_config_value_as_int("margin_left_spin");
    margins->start = margin_left;

    // Margin right
    gint margin_right = read_config_value_as_int("margin_right_spin");
    margins->end = margin_right;

    return margins;
}

// Writers

void write_view_config_to_dialog(ViewConfig *view_config)
{
    if (!view_config)
        return;

    // View config
    write_config_value_as_string("view_id_entry", view_config->view_id);

    // Box config
    write_config_value_as_boolean("box_expand_switch", view_config->box_expand);
    write_config_value_as_boolean("box_fill_switch", view_config->box_fill);
    write_config_value_as_int("box_padding_spin", view_config->box_padding);

    gchar *pack_direction = (view_config->pack_direction == 0) ? "end" : "start";
    write_config_value_as_string("pack_direction_combo", pack_direction);

    // Fixed config
    write_config_value_as_int("position_x_spin", view_config->position_x);
    write_config_value_as_int("position_y_spin", view_config->position_y);

    // TODO: Complete other view config properties

    // Signals config
    // OnClick
    write_config_value_as_string("on_click_entry", view_config->signal.sig_handler);
}

void write_config_value_as_string(gchar *view_id, const gchar *value)
{
    View *output_view = find_view_by_id(view_id, root_dialog_view_global);
    if (!output_view)
    {
        g_print("Error: ==> Cannot find the %s\n", view_id);
        return;
    }
    g_print("OWIDGET FOUND IS: %s\n", output_view->view_config->view_id);
    if (GTK_IS_COMBO_BOX_TEXT(output_view->widget))
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(output_view->widget), value);
    else if (GTK_IS_ENTRY(output_view->widget))
        gtk_entry_set_text(GTK_ENTRY(output_view->widget), value);
    else
        g_print("Error: => OWidget type not compatible with the expected value\n");
}

void write_config_value_as_int(gchar *view_id, gint value)
{
    View *input_view = find_view_by_id(view_id, root_dialog_view_global);
    if (!input_view)
    {
        g_print("Error: ==> Cannot find the %s\n", view_id);
        return;
    }
    if (GTK_IS_SPIN_BUTTON(input_view->widget))
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(input_view->widget), value);
    else
        g_print("Error: => Widget type not compatible with the expected value\n");
}

void write_config_value_as_double(gchar *view_id, gdouble value)
{
    View *input_view = find_view_by_id(view_id, root_dialog_view_global);
    if (!input_view)
    {
        g_print("Error: ==> Cannot find the %s\n", view_id);
        return;
    }
    if (GTK_IS_SPIN_BUTTON(input_view->widget))
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(input_view->widget), value);
    else
        g_print("Error: => Widget type not compatible with the expected value\n");
}

void write_config_value_as_boolean(gchar *view_id, gboolean value)
{
    View *input_view = find_view_by_id(view_id, root_dialog_view_global);
    if (!input_view)
    {
        g_print("Error: ==> Cannot find the %s\n", view_id);
        return;
    }
    if (GTK_IS_SWITCH(input_view->widget))
        gtk_switch_set_active(GTK_SWITCH(input_view->widget), value);
    else
        g_print("Error: => Widget type not compatible with the expected value\n");
}
