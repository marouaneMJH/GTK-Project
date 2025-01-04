#include "./../../../include/containers/layouts/box.h"

BoxConfig *init_box()
{
    BoxConfig *box_config = NULL;
    SAFE_ALLOC(box_config, BoxConfig, 1);

    return box_config;
}

GtkWidget *create_box(BoxConfig box_config)
{
    GtkWidget *box = NULL;

    // Creation
    box = gtk_box_new(box_config.orientation, box_config.spacing);

    // Enable or disable homogeneous (Give all children the same size)
    gtk_box_set_homogeneous(GTK_BOX(box), box_config.homogeneous);

    // Set center widget
    if (box_config.center_widget)
        gtk_box_set_center_widget(GTK_BOX(box), box_config.center_widget);

    // Set baseline position
    gtk_box_set_baseline_position(GTK_BOX(box), box_config.baseline_position);

    // Set dimensions
    if (box_config.dimensions.width > 0 || box_config.dimensions.height)
        gtk_widget_set_size_request(box, box_config.dimensions.width, box_config.dimensions.height);

    // Set colors
    widget_set_colors(box, box_config.bg_color, box_config.text_color);

    // Set margins
    widget_set_margins(box, box_config.margins);

    // Set spacing
    // gtk_box_set_spacing(GTK_BOX(box), box_config.spacing);
    // Set packing
    // gtk_box_set_child_packing(GTK_BOX(box), child_widget, is_expand, is_fill, padding, GTK_PACK_START)

    return box;
}