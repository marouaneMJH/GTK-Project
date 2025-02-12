#ifndef LINK_WITH_CONTAINER_H
#define LINK_WITH_CONTAINER_H

#include "./../../../include/index.h"


/**
 * @file function that link between widget and ther container 
 * 
 * each function verify if the whidget it's a container 
 * if yes, it will include the child and if not, it will just ignore it
 * 
 */

int link_with_box_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_BOX(parent))
        return 0;

    if (view_config->pack_direction == 0)
        gtk_box_pack_end(GTK_BOX(parent), child, view_config->box_expand, view_config->box_fill, view_config->box_padding);
    else
        gtk_box_pack_start(GTK_BOX(parent), child, view_config->box_expand, view_config->box_fill, view_config->box_padding);

    return 1;
}

int link_with_fixed_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_FIXED(parent))
        return 0;
    gtk_fixed_put(GTK_FIXED(parent), child, view_config->position_x, view_config->position_y);
    return 1;
}

int link_with_flow_box_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_FLOW_BOX(parent))
        return 0;

    // debug the view config not working
    gtk_flow_box_insert(GTK_FLOW_BOX(parent), child, view_config->flow_box_order);
    return 1;
}

int link_with_paned_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_PANED(parent))
        return 0;

    gtk_paned_add1(GTK_PANED(parent), child);
    if (view_config->paned_order == 1)
        gtk_paned_add1(GTK_PANED(parent), child);
    else
        gtk_paned_add2(GTK_PANED(parent), child);

    return 1;
}

int link_with_grid_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_GRID(parent))
        return 0;

    gtk_grid_attach(GTK_GRID(parent), child, view_config->column, view_config->row, view_config->column_span, view_config->row_span);

    return 1;
}

int link_with_stack_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_STACK(parent))
        return 0;
    gtk_stack_add_named(GTK_STACK(parent), child, view_config->view_id);
    return 1;
}

int link_with_overlay_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_OVERLAY(parent))
        return 0;
    gtk_overlay_add_overlay(GTK_OVERLAY(parent), child);
    return 1;
}

int link_with_frame_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_FRAME(parent))
        return 0;
    frame_add_child(parent, child);
    return 1;
}

int link_with_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (GTK_IS_MENU_ITEM(child) || GTK_IS_MENU(child) || GTK_IS_NOTEBOOK(parent))
        return 0;
    return ((link_with_box_container(parent, child, view_config) ||
             link_with_fixed_container(parent, child, view_config) ||
             link_with_flow_box_container(parent, child, view_config) ||
             link_with_paned_container(parent, child, view_config) ||
             link_with_grid_container(parent, child, view_config) ||
             link_with_stack_container(parent, child, view_config) ||
             link_with_frame_container(parent, child, view_config) ||
             link_with_overlay_container(parent, child, view_config))
                ? 1
                : 0);
    ;
}

#endif