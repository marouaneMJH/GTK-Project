#ifndef STACK_H
#define STACK_H

// TODO work with switcher for the signal the original stack container will be switcher 


#include "./../../global.h"

#define MAX_CHILD_NAME_SIZE 50

/*  default values */
#define DEFAULT_STACK_DIMENSIONS \
    {                            \
        .height = 0,             \
        .width = 0}

#define DEFAULT_STACK_MARGINS \
    {                         \
        .bottom = 0,          \
        .top = 0,             \
        .start = 0,           \
        .end = 0}

#define DEFAULT_STACK                                           \
    {                                                           \
        .is_homogeneous = FALSE,                                \
        .is_transition_enabled = TRUE,                          \
        .transition_duration = 250,                             \
        .transition_type = GTK_STACK_TRANSITION_TYPE_CROSSFADE, \
        .bg_color = "\0",                                       \
        .text_color = "\0",                                     \
        .margins = DEFAULT_STACK_MARGINS,                        \
        .dimensions = DEFAULT_STACK_DIMENSIONS}

typedef struct
{
    gboolean is_homogeneous;        // Whether all children should have the same size
    gboolean is_transition_enabled; // Whether transitions are enabled
    gint transition_duration;       // Duration of transitions in milliseconds

    GtkStackTransitionType transition_type; // Type of transition (e.g., slide, fade)
    gchar bg_color[MAX_COLOR_SIZE];         // Background color
    gchar text_color[MAX_COLOR_SIZE];       // Text color
    Margins margins;                        // Margins for spacing
    Dimensions dimensions;                  // Width and height of the stack
} StackConfig;

ViewConfig *configure_stack_property(StackConfig *stack_config, ViewConfig *view_config, gchar *property, gchar *value);

/**
 * @brief Initialize stack configuration
 * @param[in] index file pointer
 * @param[in] stack_config stack configuration
 * @return ViewConfig pointer
 */
ViewConfig *init_stack_config(FILE *index, StackConfig *stack_config);

/**
 * @brief create stack widget with default
 * @param[in] stack stack structure
 * @return[ou] GtkWidget pointer to new stack widget
 */
GtkWidget *create_stack(StackConfig stack_config);

#endif