#include "./../../../include/containers/layouts/frame.h"

GtkWidget *create_frame(FrameConfig frame_config)
{
    GtkWidget *frame = gtk_frame_new(NULL);

    // Set dimensions
    gtk_widget_set_size_request(frame, frame_config.dimensions.width, frame_config.dimensions.height);

    // Set margins
    widget_set_margins(frame, frame_config.margins);
    // Set colors
    widget_set_colors(frame, frame_config.bg_color, frame_config.text_color);

    return frame;
}