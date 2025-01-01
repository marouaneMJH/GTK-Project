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
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gchar *css_style = NULL;

    GString *css_builder = g_string_new(".style { ");

    if ((color && color[0] != '\0') || (bg_color && bg_color[0] != '\0') || (bg_image && bg_image[0] != '\0'))
    {
        g_string_append_printf(css_builder, "background-image: url('./assets/images/%s'); ", (bg_image && bg_image[0] != '\0') ? bg_image : "none;");
        if ((bg_image && bg_image[0] != '\0'))
            g_string_append_printf(css_builder, "background-size: cover; ");
        if ((bg_color && bg_color[0] != '\0'))
            g_string_append_printf(css_builder, "background-color: %s; ", bg_color);
        if ((color && color[0] != '\0'))
            g_string_append_printf(css_builder, "color: %s; ", color);

        g_string_append(css_builder, "}");

        css_style = g_string_free(css_builder, FALSE);

        g_print("CSS style: \n %s \n", css_style);
    }
    else
    {
        // Use a default stylesheet if all args are null
        gtk_css_provider_load_from_path(css_provider, "./assets/style.css", NULL);
    }

    if (css_style)
    {
        GError *error = NULL;
        gtk_css_provider_load_from_data(css_provider, css_style, -1, &error);
        if (error)
        {
            g_printerr("Failed to load CSS: %s\n", error->message);
            g_error_free(error);
        }
        g_free(css_style);
    }

    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(css_provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(css_provider); // Free the CSS provider after use

    return context;
}

void widget_set_colors(GtkWidget *widget, const gchar *bg_color, const gchar *color)
{
    gtk_style_context_add_class(get_style_provider_context(widget, bg_color, color, NULL), "style");
}

void widget_set_background_image(GtkWidget *widget, const gchar *bg_image, const gchar *color)
{
    gtk_style_context_add_class(get_style_provider_context(widget, NULL, color, bg_image), "style");
}

void widget_set_margins(GtkWidget *widget, Margins margins)
{
    gtk_widget_set_margin_top(widget, margins.top);
    gtk_widget_set_margin_bottom(widget, margins.bottom);
    gtk_widget_set_margin_start(widget, margins.start);
    gtk_widget_set_margin_end(widget, margins.end);
}


void widget_set_font(GtkWidget *widget, const gchar *font_name, gint font_size)
{
    PangoFontDescription *font_desc = pango_font_description_new();
    pango_font_description_set_family(font_desc, font_name);
    pango_font_description_set_size(font_desc, font_size * PANGO_SCALE);
    gtk_widget_override_font(widget, font_desc);
    pango_font_description_free(font_desc);
}
