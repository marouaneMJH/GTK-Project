#include "./../include/global.h"

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
// ########################## "This function should stop reading after the greater then symbol " > " exactelly"
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