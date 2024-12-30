#include "./../../../include/containers/layouts/flow_box.h"

FlowBoxConfig *init_flow_box()
{
    FlowBoxConfig *flow_box_config = NULL;
    SAFE_ALLOC(flow_box_config, FlowBoxConfig, 1);

    return flow_box_config;
}

GtkWidget *create_flow_box(FlowBoxConfig flow_box_config)
{
    GtkWidget *flow_box = NULL;
    flow_box = gtk_flow_box_new();

    // Enable or disable homogeneous mode
    gtk_flow_box_set_homogeneous(GTK_FLOW_BOX(flow_box), flow_box_config.homogeneous);

    // Set min children per line
    gtk_flow_box_set_min_children_per_line(GTK_FLOW_BOX(flow_box), flow_box_config.min_childern_per_line);

    // Set max children per line
    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(flow_box), flow_box_config.max_childern_per_line);

    // Set column space
    gtk_flow_box_set_column_spacing(GTK_FLOW_BOX(flow_box), flow_box_config.column_spacing);

    // Set row space
    gtk_flow_box_set_row_spacing(GTK_FLOW_BOX(flow_box), flow_box_config.row_spacing);

    // Set selection mode
    gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(flow_box), flow_box_config.selection_mode);

    // Adjustment is just for controll the scroll
    // Set horizontal adjustment
    if (flow_box_config.hadjustment)
        gtk_flow_box_set_hadjustment(GTK_FLOW_BOX(flow_box), flow_box_config.hadjustment);

    // Set vertical adjustment
    if (flow_box_config.vadjustment)
        gtk_flow_box_set_vadjustment(GTK_FLOW_BOX(flow_box), flow_box_config.vadjustment);

    // Set dimensions
    if (flow_box_config.dimensions.width > 0 || flow_box_config.dimensions.height)
        gtk_widget_set_size_request(flow_box, flow_box_config.dimensions.width, flow_box_config.dimensions.height);

    // Set colors
    widget_set_colors(flow_box, flow_box_config.bg_color, flow_box_config.text_color);

    // Set margins
    widget_set_margins(flow_box, flow_box_config.margins);

    return flow_box;
}