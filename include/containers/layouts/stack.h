#ifndef STACK_H
#define STACK_H

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

#define DEFAULT_STACK                           \
    {                                           \
        .hhomogeneous = FALSE,                  \
        .vhomogeneous = FALSE,                  \
        .interpolate_size = FALSE,              \
        .transition_duration = 0,               \
        .visible_child_name = "\0",             \
        .margins = DEFAULT_STACK_MARGINS,       \
        .dimensions = DEFAULT_STACK_DIMENSIONS, \
        .bg_color = "\0",                       \
        .text_color = "\0"}

typedef struct
{

    gboolean hhomogeneous;
    gboolean vhomogeneous;
    gboolean interpolate_size;

    guint transition_duration;

    gchar visible_child_name[MAX_CHILD_NAME_SIZE];

    Margins margins;

    Dimensions dimensions;

    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} StackConfig;

StackConfig *init_stack();

/**
 * @brief create stack widget with default
 * @param[in] stack stack structure
 * @return[ou] GtkWidget pointer to new stack widget
 */
GtkWidget *create_stack(StackConfig stack_config);

#endif