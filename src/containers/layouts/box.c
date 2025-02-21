#include "./../../../include/containers/layouts/box.h"

ViewConfig *configure_box_property(BoxConfig *box_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!box_config || !property || !value)
        return NULL;

    // Orientation
    if (g_strcmp0(property, "orientation") == 0)
        box_config->orientation = g_strcmp0(value, "horizontal") == 0 ? GTK_ORIENTATION_HORIZONTAL : GTK_ORIENTATION_VERTICAL;

    // Spacing
    if (g_strcmp0(property, "spacing") == 0)
        box_config->spacing = atoi(value);

    // Homogeneous
    if (g_strcmp0(property, "homogeneous") == 0)
        box_config->homogeneous = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Baseline position
    if (g_strcmp0(property, "baseline_position") == 0)
        box_config->baseline_position = g_strcmp0(value, "top") == 0 ? GTK_BASELINE_POSITION_TOP : g_strcmp0(value, "center") == 0 ? GTK_BASELINE_POSITION_CENTER
                                                                                                                                   : GTK_BASELINE_POSITION_BOTTOM;

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        box_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        box_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        box_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        box_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        box_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        box_config->dimensions.height = atoi(value);

    // Colors
    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(box_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(box_config->text_color, value);

    if (g_strcmp0(property, "bg_image") == 0)
        strcpy(box_config->bg_image, value);

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            box_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            box_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            box_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            box_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            box_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            box_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            box_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            box_config->halign = GTK_ALIGN_FILL;
    }

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_box_config(FILE *index, BoxConfig *box_config)
{
    return init_generic_config(index, (void *)box_config, (ConfigurePropertyCallback)configure_box_property);
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
    if (box_config.dimensions.width > 0 || box_config.dimensions.height > 0)
        gtk_widget_set_size_request(box, box_config.dimensions.width, box_config.dimensions.height);

    // Set colors
    widget_set_colors(box, box_config.bg_color, box_config.text_color);

    // Set margins
    widget_set_margins(box, box_config.margins);

    // Set background image
    if (box_config.bg_image[0] != '\0')
    {
        widget_set_background_image(box, box_config.bg_image, box_config.text_color);
    }

    // Enable or disable cells expand (the parent should be expandable; not important)
    gtk_widget_set_hexpand(box, box_config.hexpand);
    gtk_widget_set_vexpand(box, box_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(box, box_config.halign);
    gtk_widget_set_valign(box, box_config.valign);

    // Set spacing
    gtk_box_set_spacing(GTK_BOX(box), box_config.spacing);
    // Set packing
    // gtk_box_set_child_packing(GTK_BOX(box), child_widget, is_expand, is_fill, padding, GTK_PACK_START)

    return box;
}

gchar *write_box_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "box", tabs_number);

    // Get the GtkBox from the view
    GtkBox *box = GTK_BOX(view->widget);

    // Get the orientation
    GtkOrientation orientation = gtk_orientable_get_orientation(GTK_ORIENTABLE(box));
    if (orientation != GTK_ORIENTATION_VERTICAL) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "orientation=\"%s\"\n", orientation == GTK_ORIENTATION_HORIZONTAL ? "horizontal" : "vertical");
    }

    // Get the spacing between children
    gint spacing = gtk_box_get_spacing(box);
    if (spacing != 0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "spacing=\"%d\"\n", spacing);
    }

    // Check if the box is homogeneous
    gboolean homogeneous = gtk_box_get_homogeneous(box);
    if (homogeneous != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "homogeneous=\"%s\"\n", homogeneous ? "true" : "false");
    }

    // Get the baseline position
    GtkBaselinePosition baseline_position = gtk_box_get_baseline_position(box);
    if (baseline_position != GTK_BASELINE_POSITION_CENTER) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "baseline_position=\"%s\"\n", baseline_position == GTK_BASELINE_POSITION_TOP ? "top" : baseline_position == GTK_BASELINE_POSITION_BOTTOM ? "bottom"
                                                                                                                : baseline_position == GTK_BASELINE_POSITION_CENTER   ? "center"
                                                                                                                                                                      : "unknown");
    }

    // Get the horizontal expand property
    gboolean hexpand = gtk_widget_get_hexpand(GTK_WIDGET(box));
    if (hexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "hexpand=\"%s\"\n", hexpand ? "true" : "false");
    }

    // Get the vertical expand property
    gboolean vexpand = gtk_widget_get_vexpand(GTK_WIDGET(box));
    if (vexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "vexpand=\"%s\"\n", vexpand ? "true" : "false");
    }

    // Get the horizontal alignment
    GtkAlign halign = gtk_widget_get_halign(GTK_WIDGET(box));
    if (halign != GTK_ALIGN_FILL) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "halign=\"%s\"\n", halign == GTK_ALIGN_START ? "start" : halign == GTK_ALIGN_END  ? "end"
                                                                                  : halign == GTK_ALIGN_CENTER ? "center"
                                                                                  : halign == GTK_ALIGN_FILL   ? "fill"
                                                                                                               : "unknown");
    }

    // Get the vertical alignment
    GtkAlign valign = gtk_widget_get_valign(GTK_WIDGET(box));
    if (valign != GTK_ALIGN_FILL) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "valign=\"%s\"\n", valign == GTK_ALIGN_START ? "start" : valign == GTK_ALIGN_END  ? "end"
                                                                                  : valign == GTK_ALIGN_CENTER ? "center"
                                                                                  : valign == GTK_ALIGN_FILL   ? "fill"
                                                                                                               : "unknown");
    }

    return "box";
}