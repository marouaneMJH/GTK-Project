#include "./../../../include/containers/layouts/list_box.h"

ListBoxConfig *init_list_box()
{
    ListBoxConfig *list_box_config = NULL;
    SAFE_ALLOC(list_box_config, ListBoxConfig, 1);

    return list_box_config;
}

GtkWidget *create_list_box(ListBoxConfig list_box_config)
{
    GtkWidget *list_box = NULL;

    // Creation
    list_box = gtk_list_box_new();

    // Set selection mode
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(list_box), list_box_config.selection_mode);

    // Set placeholder
    if (list_box_config.placeholder)
        gtk_list_box_set_placeholder(GTK_LIST_BOX(list_box), list_box_config.placeholder);

    // Set dimensions
    if (list_box_config.dimensions.width > 0 || list_box_config.dimensions.height)
        gtk_widget_set_size_request(list_box, list_box_config.dimensions.width, list_box_config.dimensions.height);

    // Set colors
    widget_set_colors(list_box, list_box_config.bg_color, list_box_config.text_color);

    // Set margins
    widget_set_margins(list_box, list_box_config.margins);

    // Set spacing
    // gtk_list_box_set_spacing(GTK_LIST_BOX(list_box), list_box_config.spacing);
    // Set packing
    // gtk_list_box_set_child_packing(GTK_LIST_BOX(list_box), child_widget, is_expand, is_fill, padding, GTK_PACK_START)
    return list_box;
}

gchar *write_list_box_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    write_widget_tag_style_view_config(output_file, view, "list_box", tabs_number);

    return "list_box";
}