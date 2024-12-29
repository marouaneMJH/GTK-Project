#include "./../include/global.h"

// inline void free_widget(GtkWidget *widget)
// {
//     if (widget != NULL)
//     {
//         gtk_widget_destroy(widget);
//         widget = NULL; // Avoid dangling pointers
//     }
// }

GtkStyleContext* get_style_provider_context(GtkWidget *widget, const gchar *bg_color, const gchar *color)
{
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gchar *css_style = NULL;

    if (bg_color && color)
    {
        css_style = g_strconcat(
            ".colors { ",
            "background-image: none; ",
            "background-color: ", bg_color,
            "; color: ", color,
            "; }", NULL);
    }
    else if (bg_color)
    {
        css_style = g_strconcat(
            ".colors { ",
            "background-image: none; ",
            "background-color: ", bg_color,
            "; }", NULL);
    }
    else if (color)
    {
        css_style = g_strconcat(
            ".colors { ",
            "background-image: none; ",
            "color: ", color,
            "; }", NULL);
    }
    else
    {
        // Use a default stylesheet if no color is provided
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
    gtk_style_context_add_class(get_style_provider_context(widget, bg_color, color), "colors");
}