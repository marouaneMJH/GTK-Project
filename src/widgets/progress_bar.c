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
    if (g_strcmp0(property, "mrgin_top") == 0)
        progress_bar_config->margins.top = atoi(value);

    if (g_strcmp0(property, "mrgin_bottom") == 0)
        progress_bar_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "mrgin_left") == 0)
        progress_bar_config->margins.start = atoi(value);

    if (g_strcmp0(property, "mrgin_right") == 0)
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
    // Check if the progress_bar config and the index file is not null
    if (!progress_bar_config || !index)
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

        // If the all properties are readed then break the loop and return the view id and pass the properties to the progress_bar config
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
                    // Apply the property value to the progress_bar config
                    view_config = configure_progress_bar_property(progress_bar_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_config;
}

GtkWidget *create_progress_bar(ProgressBarConfig progress_bar_config)
{

    GtkWidget *progress_bar = gtk_progress_bar_new();

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

    widget_set_colors(GTK_WIDGET(progress_bar), progress_bar_config.bg_color, progress_bar_config.text_color);
    widget_set_margins(GTK_WIDGET(progress_bar), progress_bar_config.margins);

    return progress_bar;
}