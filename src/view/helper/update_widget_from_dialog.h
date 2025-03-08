#ifndef UPDATE_WIDGET_FROM_DIALOG_H
#define UPDATE_WIDGET_FROM_DIALOG_H

#include "./../../../include/builder.h"

/*void rebuild_graph(View **temp_root, View *view, View *updated_view, gchar *view_id, gboolean relative_container)
{
    if (!view || !updated_view)
        return;

    // Ref the widget to prevent destruction
    g_object_ref(view->widget);

    // Remove from parent
    gtk_container_remove(GTK_CONTAINER(gtk_widget_get_parent(view->widget)), view->widget);

    View *new_view = create_view(view->widget, view->view_config);
    if (g_strcmp0(view->view_config->view_id, view_id))
    {
        (*temp_root) = add_view(new_view, (*temp_root), relative_container);
        g_print("Old view is done: %s\n", (*temp_root)->view_config->view_id);
    }
    else
    {
        (*temp_root) = add_view(updated_view, (*temp_root), relative_container);
        g_print("Updated view is done: %s\n", (*temp_root)->view_config->view_id);
        (*temp_root)->view_config->box_expand ? g_print("BOX EXPAND ====> TRUE\n") : g_print("BOX EXPAND ====> FALSE\n");
    }

    // Unref after adding
    // g_object_unref(view->widget);

    g_print("Add is done: %s\n", (*temp_root)->view_config->view_id);

    // relative_container = check_relative_container((*temp_root)->widget);

    if (view->child)
        rebuild_graph(temp_root, view->child, updated_view, view_id, TRUE);

    if (view->next)
        rebuild_graph(temp_root, view->next, updated_view, view_id, FALSE);

}
*/

static View *temp_parent_view = NULL;
void rebuild_graph(View **temp_root, View *view, View *updated_view, gchar *view_id, gboolean relative_container)
{
    if (!view || !updated_view)
        return;

    // Ref the widget to prevent destruction
    g_object_ref(view->widget);

    // Remove from parent
    gtk_container_remove(GTK_CONTAINER(gtk_widget_get_parent(view->widget)), view->widget);

    View *new_view = create_view(view->widget, view->view_config);
    if (g_strcmp0(view->view_config->view_id, view_id))
    {
        temp_parent_view = add_view(new_view, temp_parent_view, relative_container);
        g_print("Old view is done: %s\n", temp_parent_view->view_config->view_id);
    }
    else
    {
        temp_parent_view = add_view(updated_view, temp_parent_view, relative_container);
        g_print("Updated view is done: %s\n", temp_parent_view->view_config->view_id);
        temp_parent_view->view_config->box_expand ? g_print("BOX EXPAND ====> TRUE\n") : g_print("BOX EXPAND ====> FALSE\n");
    }

    // Unref after adding
    // g_object_unref(view->widget);

    g_print("Add is done: %s\n", temp_parent_view->view_config->view_id);
    (*temp_root) = temp_parent_view;

    // relative_container = check_relative_container((*temp_root)->widget);

    if (view->child)
        rebuild_graph(temp_root, view->child, updated_view, view_id, TRUE);

    if (view->next)
        rebuild_graph(temp_root, view->next, updated_view, view_id, FALSE);

    else
        temp_parent_view = temp_parent_view->parent;
}

void set_current_view_config_to_dialog(ViewConfig *view_config)
{
    if (!view_config)
        return;
    write_view_config_to_dialog(view_config);
}

void destroy_dialog_input(gchar *view_id)
{
    View *target = find_view_by_id(view_id, root_dialog_view_global);
    if (!target)
    {
        g_print("Error: ==> cannot found the view: %s\n", view_id);
        return;
    }

    gtk_widget_destroy(target->widget);
    g_free(target->view_config);
    g_free(target);
}

void disable_dialog_input(gchar *view_id)
{
    View *target = find_view_by_id(view_id, root_dialog_view_global);
    if (!target)
    {
        g_print("Error: ==> cannot found the view: %s\n", view_id);
        return;
    }

    gtk_widget_set_sensitive(target->widget, FALSE);
}

// set current config to dialog
void set_current_button_config_to_dialog(ButtonConfig *button_config)
{
    // Label
    write_config_value_as_string("label_entry", button_config->label);

    // Width
    write_config_value_as_int("width_spin", button_config->dimensions.width);

    // Height
    write_config_value_as_int("height_spin", button_config->dimensions.height);

    // Margin top
    write_config_value_as_int("margin_top_spin", button_config->margins.top);

    // Margin bottom
    write_config_value_as_int("margin_bottom_spin", button_config->margins.bottom);

    // Margin left
    write_config_value_as_int("margin_left_spin", button_config->margins.start);

    // Margin right
    write_config_value_as_int("margin_right_spin", button_config->margins.end);

    // HAlign
    gchar *halign = NULL;
    switch (button_config->halign)
    {
    case GTK_ALIGN_START:
        halign = "start";
        break;
    case GTK_ALIGN_END:
        halign = "end";
        break;
    case GTK_ALIGN_BASELINE:
        halign = "baseline";
        break;
    case GTK_ALIGN_CENTER:
        halign = "center";
        break;
    default:
        halign = "center";
        break;
    }
    write_config_value_as_string("halign_combo", halign);

    // VAlign
    gchar *valign = NULL;
    switch (button_config->valign)
    {
    case GTK_ALIGN_START:
        valign = "start";
        break;
    case GTK_ALIGN_END:
        valign = "end";
        break;
    case GTK_ALIGN_BASELINE:
        valign = "baseline";
        break;
    case GTK_ALIGN_CENTER:
        valign = "center";
        break;
    default:
        valign = "center";
        break;
    }
    write_config_value_as_string("valign_combo", valign);

    // HExpand
    write_config_value_as_boolean("hexpand_switch", button_config->hexpand);

    // VExpand
    write_config_value_as_boolean("vexpand_switch", button_config->vexpand);

    // Background color
    write_config_value_as_string("bg_color_entry", button_config->bg_color);

    // Text color
    write_config_value_as_string("color_entry", button_config->color);
}

// prepare the update dialog and show it
GtkWidget *prepare_update_button_config(View *target_view)
{
    ButtonConfig *button_config = read_button_config_from_widget(target_view->widget);
    build_app(root_app, NULL, BUTTON_PROPERTIES_DIALOG_TXT);
    set_current_button_config_to_dialog(button_config);
    set_current_view_config_to_dialog(target_view->view_config);
    // set_available_scopes(target_view->view_config->view_id);

    // TODO: Destroy the view_id and scope back inputs
    disable_dialog_input("view_id_entry");
    disable_dialog_input("scope_back_combo");
    return root_dialog_view_global->widget;
}

// update config
View *update_button_config()
{
    g_print("UPDATING BUTTON WIDGET\n");

    View *viewer = find_view_by_id("viewer", root_view_global);
    if (!viewer)
    {
        g_print("ERROR: ==> cannot find the viewer\n");
        return NULL;
    }

    ButtonConfig *button_config = read_button_config_from_dialog();

    ViewConfig *view_config = read_view_config_from_dialog(TRUE);

    GtkWidget *button_widget = create_button(*button_config);

    View *updated_button_view = create_view(button_widget, view_config);

    if (!viewer->child)
    {
        g_print("ERROR: ==> VIEWER HAS NO CHILD\n");
        return NULL;
    }

    View *temp_root = NULL;
    rebuild_graph(&temp_root, viewer->child, updated_button_view, view_config->view_id, check_relative_container(viewer->widget));

    if (!temp_root)
    {
        g_print("ERROR: ==> TEMP ROOT NOT COMPLETED\n");
        return NULL;
    }

    // parent_view = temp_root;

    // Add the the new graph to viewer
    g_print("DEBUG: ==> TEMP ROOT TREE\n");
    while (temp_root->parent)
        temp_root = temp_root->parent;
    add_view(temp_root, viewer, TRUE);
    print_graph_to_debug(viewer);
    gtk_widget_show_all(gtk_widget_get_toplevel(temp_root->widget));

    return temp_root;
}

#endif