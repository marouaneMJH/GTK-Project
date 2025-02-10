#ifndef FRAME_H
#define FRAME_H

#include "./../../global.h"

/*  default values */

#define DEFAULT_FRAME_DIMENSIONS \
    {                            \
        .height = 0,             \
        .width = 0}

#define DEFAULT_FRAME_MARGINS \
    {                         \
        .bottom = 0,         \
        .top = 0,            \
        .start = 0,          \
        .end = 0}

#define DEFAULT_FRAME                     \
    {                                     \
        .label = "\0",                    \
        .label_yalign = 0.0,               \
        .label_xalign = 0.0,              \
        .shadow_type = GTK_SHADOW_IN,     \
        .bg_color = "\0",                 \
        .text_color = "\0",               \
        .margins = DEFAULT_FRAME_MARGINS, \
        .dimensions = DEFAULT_FRAME_DIMENSIONS}

typedef struct
{
    gchar label[MAX_LABEL_SIZE];      // Frame label text
    gfloat label_yalign;               // Label alignment (0.0 to 1.0)
    gfloat label_xalign;              // Horizontal alignment of the label
    GtkShadowType shadow_type;        // Type of shadow around the frame
    gchar bg_color[MAX_COLOR_SIZE];   // Background color
    gchar text_color[MAX_COLOR_SIZE]; // Text color
    Margins margins;                  // Margins for spacing
    Dimensions dimensions;            // Width and height of the frame
} FrameConfig;

/**
 * @brief Configure frame properties
 * @param[in] frame_config pointer to frame configuration
 * @param[in] view_config pointer to view configuration
 * @param[in] property property name to configure
 * @param[in] value property value to set
 * @return ViewConfig pointer
 */
ViewConfig *configure_frame_property(FrameConfig *frame_config, ViewConfig *view_config, gchar *property, gchar *value);

/**
 * @brief Initialize frame configuration
 * @param[in] index file pointer
 * @param[in] frame_config frame configuration
 * @return ViewConfig pointer
 */
ViewConfig *init_frame_config(FILE *index, FrameConfig *frame_config);

/**
 * @brief Create frame widget with configuration
 * @param[in] frame_config frame configuration structure
 * @return GtkWidget pointer to new frame widget
 */
GtkWidget *create_frame(FrameConfig frame_config);

void frame_add_child(GtkWidget *frame, GtkWidget *child);

#endif