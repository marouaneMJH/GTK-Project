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
        .is_homogeneous = FALSE,                   \
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
    gboolean is_homogeneous;

    GtkSelectionMode selection_mode;

    GtkAdjustment *hadjustment;
    GtkAdjustment *vadjustment;

    Margins margins;

    Dimensions dimensions;
    
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} FlowBoxConfig;

/**
 * @brief Applies configuration settings from a file to the specified properties.
 *
 * This function reads the provided configuration object and applies
 * matching values to the target properties, as defined in the
 * specified configuration file.
 *
 * @param config A configuration object containing the values to apply.
 * @return An integer indicating success (-1) or failure (-1) of the operation.
 */
ViewConfig *configure_flow_box_property(FlowBoxConfig *flow_box_config, ViewConfig *view_config, gchar *property, gchar *value);


ViewConfig *init_flow_box_config(FILE *index, FlowBoxConfig *flow_box_config);


/**
 * @brief create flow_box widget with default
 * @param[in] flow_box flow_box structure
 * @return[ou] GtkWidget pointer to new flow_box widget
 */
GtkWidget *create_flow_box(FlowBoxConfig flow_box_config);

#endif