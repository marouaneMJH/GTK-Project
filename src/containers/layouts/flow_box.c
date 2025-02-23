#include "./../../../include/containers/layouts/flow_box.h"

ViewConfig *configure_flow_box_property(FlowBoxConfig *flow_box_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!flow_box_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "min_childern_per_line") == 0)
        flow_box_config->min_childern_per_line = atoi(value);

    if (g_strcmp0(property, "max_childern_per_line") == 0)
        flow_box_config->max_childern_per_line = atoi(value);

    if (g_strcmp0(property, "column_spacing") == 0)
        flow_box_config->column_spacing = atoi(value);

    if (g_strcmp0(property, "row_spacing") == 0)
        flow_box_config->row_spacing = atoi(value);

    if (g_strcmp0(property, "homogeneous") == 0)
        flow_box_config->is_homogeneous = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "selection_mode") == 0)
    {
        if (g_strcmp0(value, "none") == 0)
            flow_box_config->selection_mode = GTK_SELECTION_NONE;
        else if (g_strcmp0(value, "single") == 0)
            flow_box_config->selection_mode = GTK_SELECTION_SINGLE;
        else if (g_strcmp0(value, "browse") == 0)
            flow_box_config->selection_mode = GTK_SELECTION_BROWSE;
        else if (g_strcmp0(value, "multiple") == 0)
            flow_box_config->selection_mode = GTK_SELECTION_MULTIPLE;
    }

    // todo : add the adjustment
    // if (g_strcmp0(property, "hadjustment") == 0)
    //     flow_box_config->hadjustment = (GtkAdjustment *)value;

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        flow_box_config->margins.top = atoi(value);
    if (g_strcmp0(property, "margin_bottom") == 0)
        flow_box_config->margins.bottom = atoi(value);
    if (g_strcmp0(property, "margin_left") == 0)
        flow_box_config->margins.start = atoi(value);
    if (g_strcmp0(property, "margin_right") == 0)
        flow_box_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        flow_box_config->dimensions.width = atoi(value);
    if (g_strcmp0(property, "height") == 0)
        flow_box_config->dimensions.height = atoi(value);

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            flow_box_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            flow_box_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            flow_box_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            flow_box_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            flow_box_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            flow_box_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            flow_box_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            flow_box_config->halign = GTK_ALIGN_FILL;
    }

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_flow_box_config(FILE *index, FlowBoxConfig *flow_box_config)
{
    return init_generic_config(index, (void *)flow_box_config, (ConfigurePropertyCallback)configure_flow_box_property);
}

GtkWidget *create_flow_box(FlowBoxConfig flow_box_config)
{
    GtkWidget *flow_box = NULL;
    flow_box = gtk_flow_box_new();

    // Enable or disable homogeneous mode
    gtk_flow_box_set_homogeneous(GTK_FLOW_BOX(flow_box), flow_box_config.is_homogeneous);

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

    // Enable or disable cells expand (the parent should be expandable; not important)
    gtk_widget_set_hexpand(flow_box, flow_box_config.hexpand);
    gtk_widget_set_vexpand(flow_box, flow_box_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(flow_box, flow_box_config.halign);
    gtk_widget_set_valign(flow_box, flow_box_config.valign);

    // Set colors
    widget_set_colors(flow_box, flow_box_config.bg_color, flow_box_config.text_color);

    // Set margins
    widget_set_margins(flow_box, flow_box_config.margins);

    return flow_box;
}

gchar *write_flow_box_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "flow_box", tabs_number);

    // Get the GtkFlowBox from the view
    GtkFlowBox *flow_box = GTK_FLOW_BOX(view->widget);

    // Get the minimum number of children per line
    guint min_children_per_line = gtk_flow_box_get_min_children_per_line(flow_box);
    if (min_children_per_line != 1) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "min_children_per_line=\"%u\"\n", min_children_per_line);
    }

    // Get the maximum number of children per line
    guint max_children_per_line = gtk_flow_box_get_max_children_per_line(flow_box);
    if (max_children_per_line != 5) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "max_children_per_line=\"%u\"\n", max_children_per_line);
    }

    // Get the column spacing
    guint column_spacing = gtk_flow_box_get_column_spacing(flow_box);
    if (column_spacing != 0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "column_spacing=\"%u\"\n", column_spacing);
    }

    // Get the row spacing
    guint row_spacing = gtk_flow_box_get_row_spacing(flow_box);
    if (row_spacing != 0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "row_spacing=\"%u\"\n", row_spacing);
    }

    // Check if the flow box is homogeneous
    gboolean is_homogeneous = gtk_flow_box_get_homogeneous(flow_box);
    if (is_homogeneous != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_homogeneous=\"%s\"\n", is_homogeneous ? "true" : "false");
    }

    // Get the selection mode
    GtkSelectionMode selection_mode = gtk_flow_box_get_selection_mode(flow_box);
    if (selection_mode != GTK_SELECTION_SINGLE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "selection_mode=\"%s\"\n", selection_mode == GTK_SELECTION_NONE ? "none" : selection_mode == GTK_SELECTION_SINGLE ? "single"
                                                                                                    : selection_mode == GTK_SELECTION_BROWSE   ? "browse"
                                                                                                    : selection_mode == GTK_SELECTION_MULTIPLE ? "multiple"
                                                                                                                                               : "unknown");
    }

    return "flow_box";
}