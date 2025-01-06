#include "./../../../include/containers/layouts/flow_box.h"


int configure_flow_box_property(FlowBoxConfig *flow_box_config,ViewConfig *view_config ,gchar *property, gchar *value)
{   
    if (!flow_box_config || !property || !value)
        return -1;

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

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);
    return 1;
}

gchar* init_flow_box(FILE *index, FlowBoxConfig *flow_box_config, ViewConfig *view_config)
{
    // Check if the flow box config and the index file is not null
    if (!flow_box_config || !index)
        return NULL;

    // Store the property and value of the tag
    gchar *property = NULL;
    gchar *value = NULL;

    // The view id of the tag
    gchar *view_id = NULL;

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

        // If the all properties are readed then break the loop and return the view id and pass the properties to the flow box config
        if (status == 2)
            return view_id;

        // If the property is readed then read the value of the property
        else if (status == 1 && property)
        {
            // Read the value of the property
            value = read_value(index, &status);
            if (status == 1 && value)
            {
                if (g_strcmp0(property, "id") == 0) // Store the view id
                {
                    view_id = value;
                    free(property);
                }
                else
                {
                    // Apply the property value to the flow box config
                    configure_flow_box_property(flow_box_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_id;
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

    // Set colors
    widget_set_colors(flow_box, flow_box_config.bg_color, flow_box_config.text_color);

    // Set margins
    widget_set_margins(flow_box, flow_box_config.margins);

    return flow_box;
}