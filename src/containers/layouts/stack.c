#include "./../../../include/containers/layouts/stack.h"

ViewConfig *configure_stack_property(StackConfig *stack_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!stack_config || !property || !value)
        return NULL;

    // Set whether the stack should have homogeneous children
    if (g_strcmp0(property, "is_homogeneous") == 0)
        stack_config->is_homogeneous = g_strcmp0(value, "true") == 0;

    // Enable or disable transitions
    else if (g_strcmp0(property, "is_transition_enabled") == 0)
        stack_config->is_transition_enabled = g_strcmp0(value, "true") == 0;

    // Set transition duration in milliseconds
    else if (g_strcmp0(property, "transition_duration") == 0)
        stack_config->transition_duration = atoi(value);

    // Set transition type
    else if (g_strcmp0(property, "transition_type") == 0)
    {
        if (g_strcmp0(value, "slide_left") == 0)
            stack_config->transition_type = GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT;
        else if (g_strcmp0(value, "slide_right") == 0)
            stack_config->transition_type = GTK_STACK_TRANSITION_TYPE_SLIDE_RIGHT;
        else if (g_strcmp0(value, "slide_up") == 0)
            stack_config->transition_type = GTK_STACK_TRANSITION_TYPE_SLIDE_UP;
        else if (g_strcmp0(value, "slide_down") == 0)
            stack_config->transition_type = GTK_STACK_TRANSITION_TYPE_SLIDE_DOWN;
        else if (g_strcmp0(value, "crossfade") == 0)
            stack_config->transition_type = GTK_STACK_TRANSITION_TYPE_CROSSFADE;
    }

    // Set background color
    else if (g_strcmp0(property, "bg_color") == 0)
        strcpy(stack_config->bg_color, value);

    // Set text color
    else if (g_strcmp0(property, "text_color") == 0)
        strcpy(stack_config->text_color, value);

    // Set widget dimensions
    else if (g_strcmp0(property, "width") == 0)
        stack_config->dimensions.width = atoi(value);

    else if (g_strcmp0(property, "height") == 0)
        stack_config->dimensions.height = atoi(value);

    // Set margins
    else if (g_strcmp0(property, "margin_top") == 0)
        stack_config->margins.top = atoi(value);

    else if (g_strcmp0(property, "margin_bottom") == 0)
        stack_config->margins.bottom = atoi(value);

    else if (g_strcmp0(property, "margin_left") == 0)
        stack_config->margins.start = atoi(value);

    else if (g_strcmp0(property, "margin_right") == 0)
        stack_config->margins.end = atoi(value);

    // Store additional properties in view_config (if needed)
    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_stack_config(FILE *index, StackConfig *stack_config)
{
    return init_generic_config(index, (void *)stack_config, (ConfigurePropertyCallback)configure_stack_property);
}

GtkWidget *create_stack(StackConfig stack_config)
{
    // Create a new GtkStack widget
    GtkWidget *stack = gtk_stack_new();

    // Set homogeneous mode (whether all children have the same size)
    gtk_stack_set_homogeneous(GTK_STACK(stack), stack_config.is_homogeneous);

    // Enable or disable transitions
    if (stack_config.is_transition_enabled)
        gtk_stack_get_transition_running(GTK_STACK(stack));

    // Set transition duration (milliseconds)
    gtk_stack_set_transition_duration(GTK_STACK(stack), stack_config.transition_duration);

    // Set transition type (slide, crossfade, etc.)
    gtk_stack_set_transition_type(GTK_STACK(stack), stack_config.transition_type);

    // Set widget size if specified
    if (stack_config.dimensions.width > 0 && stack_config.dimensions.height > 0)
        gtk_widget_set_size_request(stack, stack_config.dimensions.width, stack_config.dimensions.height);

    // Apply background and text colors if provided
    widget_set_colors(stack, stack_config.bg_color, stack_config.text_color);

    // Set margins
    widget_set_margins(stack, stack_config.margins);

    return stack;
}

gchar *write_stack_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "stack", tabs_number);

    // Get the GtkStack from the view
    GtkStack *stack = GTK_STACK(view->widget);

    // Check if the stack is homogeneous
    gboolean is_homogeneous = gtk_stack_get_homogeneous(stack);
    if (is_homogeneous != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_homogeneous=\"%s\"\n", is_homogeneous ? "true" : "false");
    }

    // Check if transitions are enabled
    gboolean is_transition_enabled = gtk_stack_get_transition_type(stack) != GTK_STACK_TRANSITION_TYPE_NONE;
    if (is_transition_enabled != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_transition_enabled=\"%s\"\n", is_transition_enabled ? "true" : "false");
    }

    // Get the transition duration
    guint transition_duration = gtk_stack_get_transition_duration(stack);
    if (transition_duration != 250) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "transition_duration=\"%d\"\n", transition_duration);
    }

    // Get the transition type
    GtkStackTransitionType transition_type = gtk_stack_get_transition_type(stack);
    if (transition_type != GTK_STACK_TRANSITION_TYPE_CROSSFADE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "transition_type=\"%s\"\n", transition_type == GTK_STACK_TRANSITION_TYPE_NONE ? "none" : transition_type == GTK_STACK_TRANSITION_TYPE_CROSSFADE      ? "crossfade"
                                                                                                                  : transition_type == GTK_STACK_TRANSITION_TYPE_SLIDE_RIGHT      ? "slide_right"
                                                                                                                  : transition_type == GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT       ? "slide_left"
                                                                                                                  : transition_type == GTK_STACK_TRANSITION_TYPE_SLIDE_UP         ? "slide_up"
                                                                                                                  : transition_type == GTK_STACK_TRANSITION_TYPE_SLIDE_DOWN       ? "slide_down"
                                                                                                                  : transition_type == GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT ? "slide_left_right"
                                                                                                                  : transition_type == GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN    ? "slide_up_down"
                                                                                                                                                                                  : "unknown");
    }

    return "stack";
}