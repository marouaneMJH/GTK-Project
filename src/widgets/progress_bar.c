#include "../../include/widgets/progress_bar.h"

ViewConfig *configure_progress_bar_property(ProgressBarConfig *progress_bar_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!progress_bar_config || !property || !value)
        return NULL;

    // Progress fraction
    if (g_strcmp0(property, "progress_fraction") == 0)
        progress_bar_config->progress_fraction = atof(value);

    // Pulse step
    if (g_strcmp0(property, "progress_pulse_step") == 0)
        progress_bar_config->progress_pulse_step = atof(value);

    // Text
    if (g_strcmp0(property, "text") == 0)
        strcpy(progress_bar_config->text, value);

    // Text visibility
    if (g_strcmp0(property, "is_text_visible") == 0)
        progress_bar_config->is_text_visible = g_strcmp0(value, "true") == 0;

    // Inverted
    if (g_strcmp0(property, "is_inverted") == 0)
        progress_bar_config->is_inverted = g_strcmp0(value, "true") == 0;

    // Ellipsize
    if (g_strcmp0(property, "ellipsize") == 0)
    {
        if (g_strcmp0(value, "middle") == 0)
            progress_bar_config->ellipsize = PANGO_ELLIPSIZE_MIDDLE;
        else if (g_strcmp0(value, "start") == 0)
            progress_bar_config->ellipsize = PANGO_ELLIPSIZE_START;
        else if (g_strcmp0(value, "end") == 0)
            progress_bar_config->ellipsize = PANGO_ELLIPSIZE_END;
        else if (g_strcmp0(value, "none") == 0)
            progress_bar_config->ellipsize = PANGO_ELLIPSIZE_NONE;
    }

    // Opacity
    if (g_strcmp0(property, "opacity") == 0)
        progress_bar_config->opacity = atof(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        progress_bar_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        progress_bar_config->dimensions.height = atoi(value);

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        progress_bar_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        progress_bar_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        progress_bar_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        progress_bar_config->margins.end = atoi(value);

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(progress_bar_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(progress_bar_config->text_color, value);

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_progress_bar_config(FILE *index, ProgressBarConfig *progress_bar_config)
{
    return init_generic_config(index, (void *)progress_bar_config, (ConfigurePropertyCallback)configure_progress_bar_property);
}

GtkWidget *create_progress_bar(ProgressBarConfig progress_bar_config)
{

    GtkWidget *progress_bar = gtk_progress_bar_new();

    if (progress_bar_config.text[0] != '\0')
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress_bar), progress_bar_config.text);

    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), progress_bar_config.progress_fraction);

    if (progress_bar_config.progress_pulse_step > 0)
        gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(progress_bar), progress_bar_config.progress_pulse_step);

    gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progress_bar), progress_bar_config.is_text_visible);
    gtk_progress_bar_set_inverted(GTK_PROGRESS_BAR(progress_bar), progress_bar_config.is_inverted);
    gtk_progress_bar_set_ellipsize(GTK_PROGRESS_BAR(progress_bar), progress_bar_config.ellipsize);
    gtk_widget_set_opacity(progress_bar, progress_bar_config.opacity);

    if (progress_bar_config.dimensions.width > 0 && progress_bar_config.dimensions.height > 0)
        gtk_widget_set_size_request(progress_bar, progress_bar_config.dimensions.width, progress_bar_config.dimensions.height);

    widget_set_colors(progress_bar, progress_bar_config.bg_color, progress_bar_config.text_color);

    widget_set_margins(progress_bar, progress_bar_config.margins);

    return progress_bar;
}

gchar *write_progress_bar_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    write_widget_tag_style_view_config(output_file, view, "progress_bar", tabs_number);

    return "progress_bar";
}