#ifndef CREATE_NEW_WIDGET_FROM_DIALOG_H
#define CREATE_NEW_WIDGET_FROM_DIALOG_H

#include "./../../../include/builder.h"




View *create_new_box_from_dialog(View *parent_view, gboolean is_relative_container)
{

    BoxConfig *box_config = read_box_config_from_dialog();

    GtkWidget *new_box = create_box(*box_config);

    // View config
    View *new_box_view = create_view(new_box, read_view_config_from_dialog());

    g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
    add_view(new_box_view, parent_view, is_relative_container);

    return new_box_view;
}

View *create_new_button_from_dialog(View *parent_view, gboolean is_relative_container)
{

    ButtonConfig *button_config = read_button_config_from_dialog();

    GtkWidget *new_button = create_button(*button_config);

    View *new_button_view = create_view(new_button, read_view_config_from_dialog());

    g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);

    add_view(new_button_view, parent_view, is_relative_container);

    return new_button_view;
}


#endif