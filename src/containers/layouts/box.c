#include "./../../../include/containers/layouts/box.h"

int configure_box_property(BoxConfig *box_config, gchar *property, gchar *value)
{
    if (!box_config || !property || !value)
        return -1;

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
    if (g_strcmp0(property, "mrgin_top") == 0)
        box_config->margins.top = atoi(value);

    if (g_strcmp0(property, "mrgin_bottom") == 0)
        box_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "mrgin_left") == 0)
        box_config->margins.start = atoi(value);

    if (g_strcmp0(property, "mrgin_right") == 0)
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

    return 1;
}

gchar *init_box_config(FILE *index, BoxConfig *box_config, ViewConfig *view_config)
{
    // Check if the window config and the index file is not null
    if (!box_config || !index)
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

        // If the all properties are readed then break the loop and return the view id and pass the properties to the window config
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
                    // Apply the property value to the window config
                    configure_box_property(box_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_id;
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