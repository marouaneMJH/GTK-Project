#include "./../../../include/containers/layouts/frame.h"

ViewConfig *configure_frame_property(FrameConfig *frame_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!frame_config || !property || !value)
        return NULL;

    // Set frame label
    if (g_strcmp0(property, "label") == 0)
        strcpy(frame_config->label, value);

    // Set label alignment (0.0 to 1.0)
    else if (g_strcmp0(property, "label_align") == 0)
        frame_config->label_align = atof(value);

    // Set label horizontal alignment
    else if (g_strcmp0(property, "label_xalign") == 0)
        frame_config->label_xalign = atof(value);

    // Set shadow type
    else if (g_strcmp0(property, "shadow_type") == 0)
    {
        if (g_strcmp0(value, "none") == 0)
            frame_config->shadow_type = GTK_SHADOW_NONE;
        else if (g_strcmp0(value, "in") == 0)
            frame_config->shadow_type = GTK_SHADOW_IN;
        else if (g_strcmp0(value, "out") == 0)
            frame_config->shadow_type = GTK_SHADOW_OUT;
        else if (g_strcmp0(value, "etched_in") == 0)
            frame_config->shadow_type = GTK_SHADOW_ETCHED_IN;
        else if (g_strcmp0(value, "etched_out") == 0)
            frame_config->shadow_type = GTK_SHADOW_ETCHED_OUT;
    }

    // Set background color
    else if (g_strcmp0(property, "bg_color") == 0)
        strcpy(frame_config->bg_color, value);

    // Set text color
    else if (g_strcmp0(property, "text_color") == 0)
        strcpy(frame_config->text_color, value);

    // Set widget dimensions
    else if (g_strcmp0(property, "width") == 0)
        frame_config->dimensions.width = atoi(value);

    else if (g_strcmp0(property, "height") == 0)
        frame_config->dimensions.height = atoi(value);

    // Set margins
    else if (g_strcmp0(property, "margin_top") == 0)
        frame_config->margins.top = atoi(value);

    else if (g_strcmp0(property, "margin_bottom") == 0)
        frame_config->margins.bottom = atoi(value);

    else if (g_strcmp0(property, "margin_left") == 0)
        frame_config->margins.start = atoi(value);

    else if (g_strcmp0(property, "margin_right") == 0)
        frame_config->margins.end = atoi(value);

    // Store additional properties in view_config (if needed)
    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_frame_config(FILE *index, FrameConfig *frame_config)
{
    return init_generic_config(index, (void*)frame_config, (ConfigurePropertyCallback)configure_frame_property);
}

GtkWidget *create_frame(FrameConfig frame_config)
{
    // Create a new GtkFrame widget
    GtkWidget *frame = gtk_frame_new(frame_config.label);

    // Set label alignment
    if(frame_config.label_xalign > 0.0 && frame_config.label_align > 0.0)
        gtk_frame_set_label_align(GTK_FRAME(frame), frame_config.label_xalign, frame_config.label_align);
    else
        gtk_frame_set_label(GTK_FRAME(frame), frame_config.label);
    // Set shadow type
    gtk_frame_set_shadow_type(GTK_FRAME(frame), frame_config.shadow_type);

    // Set widget size if specified
    if (frame_config.dimensions.width > 0 && frame_config.dimensions.height > 0)
        set_widget_size(frame, frame_config.dimensions);

    // Apply background and text colors if provided
    if(strcmp(frame_config.bg_color, "\0") != 0 && strcmp(frame_config.text_color, "\0") != 0)
        widget_set_colors(frame, frame_config.bg_color, frame_config.text_color);

    // Set margins
    widget_set_margins(frame, frame_config.margins);

    return frame;
}

void frame_add_child(GtkWidget *frame, GtkWidget *child)
{
    if (!frame || !child)
        return;

    // Add the child widget to the frame
    gtk_container_add(GTK_CONTAINER(frame), child);
}