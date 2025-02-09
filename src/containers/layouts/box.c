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
    
    if(g_strcmp0(property, "bg_image") == 0)
        strcpy(box_config->bg_image, value);

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_box_config(FILE *index, BoxConfig *box_config)
{
        return init_generic_config(index,(void*)box_config,(ConfigurePropertyCallback)configure_box_property);
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

    // Set background image
    if(box_config.bg_image[0] != '\0'){
        widget_set_background_image(box, box_config.bg_image, box_config.text_color);
    }
    // Set spacing
    // gtk_box_set_spacing(GTK_BOX(box), box_config.spacing);
    // Set packing
    // gtk_box_set_child_packing(GTK_BOX(box), child_widget, is_expand, is_fill, padding, GTK_PACK_START)

    return box;
}