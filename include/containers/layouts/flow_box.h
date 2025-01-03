#ifndef FLOW_BOX_H
#define FLOW_BOX_H

#include "./../../global.h"

/*  default values */
#define DEFAULT_FLOW_BOX_DIMENSIONS \
    {                               \
        .height = 0,                \
        .width = 0}

#define DEFAULT_FLOW_BOX_MARGINS \
    {                            \
        .bottom = 0,             \
        .top = 0,                \
        .start = 0,              \
        .end = 0}

#define DEFAULT_FLOW_BOX                           \
    {                                              \
        .min_childern_per_line = 1,                \
        .max_childern_per_line = 5,                \
        .column_spacing = 0,                       \
        .row_spacing = 0,                          \
        .homogeneous = FALSE,                      \
        .selection_mode = GTK_SELECTION_SINGLE,    \
        .hadjustment = NULL,                       \
        .vadjustment = NULL,                       \
        .margins = DEFAULT_FLOW_BOX_MARGINS,       \
        .dimensions = DEFAULT_FLOW_BOX_DIMENSIONS, \
        .bg_color = "\0",                          \
        .text_color = "\0"}

typedef struct
{

    guint min_childern_per_line;
    guint max_childern_per_line;
    guint column_spacing;
    guint row_spacing;
    gboolean homogeneous;

    GtkSelectionMode selection_mode;

    GtkAdjustment *hadjustment;
    GtkAdjustment *vadjustment;

    Margins margins;

    Dimensions dimensions;

    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} FlowBoxConfig;

FlowBoxConfig *init_flow_box();

/**
 * @brief create flow_box widget with default
 * @param[in] flow_box flow_box structure
 * @return[ou] GtkWidget pointer to new flow_box widget
 */
GtkWidget *create_flow_box(FlowBoxConfig flow_box_config);

#endif