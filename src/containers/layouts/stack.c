#include "./../../../include/containers/layouts/stack.h"

StackConfig *init_stack()
{
    StackConfig *stack_config = NULL;
    SAFE_ALLOC(stack_config, StackConfig, 1);

    return stack_config;
}

GtkWidget *create_stack(StackConfig stack_config)
{
    GtkWidget *stack = NULL;

    // Creation
    stack = gtk_stack_new();

    // Enable or disable homogeneous
    gtk_stack_set_hhomogeneous(GTK_STACK(stack), stack_config.hhomogeneous);
    gtk_stack_set_vhomogeneous(GTK_STACK(stack), stack_config.vhomogeneous);

    // Enable or disable interpolate size
    gtk_stack_set_interpolate_size(GTK_STACK(stack), stack_config.interpolate_size);

    // Set transition duration
    gtk_stack_set_transition_duration(GTK_STACK(stack), stack_config.transition_duration);

    // Set visible child name
    if (stack_config.visible_child_name)
        gtk_stack_set_visible_child_name(GTK_STACK(stack), stack_config.visible_child_name);

    // Set dimensions
    if (stack_config.dimensions.width > 0 || stack_config.dimensions.height)
        gtk_widget_set_size_request(stack, stack_config.dimensions.width, stack_config.dimensions.height);

    // Set colors
    widget_set_colors(stack, stack_config.bg_color, stack_config.text_color);

    // Set margins
    widget_set_margins(stack, stack_config.margins);

    // gtk_stack_set_visible_child(GTK_STACK(stack), child);

    return stack;
}