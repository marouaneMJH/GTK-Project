/* gtk_overlay.h */
#ifndef GTK_OVERLAY_H
#define GTK_OVERLAY_H

// todo solve execution bugs

#include "./../../global.h"

/*  default values */
#define DEFAULT_OVERLAY_DIMENSIONS \
    {                              \
        .height = 0,               \
        .width = 0}

#define DEFAULT_OVERLAY_MARGINS \
    {                           \
        .bottom = 0,            \
        .top = 0,               \
        .start = 0,             \
        .end = 0}

/* Default overlay properties */
#define DEFAULT_OVERLAY                     \
    {                                       \
        .opacity = 1,                       \
        .bg_color = "#ffffff",              \
        .border_radius = 0,                 \
        .margins = DEFAULT_OVERLAY_MARGINS, \
        .bg_image[0] = '\0',                \
        .dimensions = DEFAULT_OVERLAY_DIMENSIONS}

typedef struct
{
    gdouble opacity;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar bg_image[MAX_ICON_PATH_SIZE];
    gint border_radius;
    Margins margins;
    Dimensions dimensions;
} OverlayConfig;

/**
 * @brief Configure overlay properties.
 */
ViewConfig *configure_overlay_property(OverlayConfig *overlay_config, ViewConfig *view_config, gchar *property, gchar *value);

/**
 * @brief Initialize overlay configuration.
 */
ViewConfig *init_overlay_config(FILE *index, OverlayConfig *overlay_config);
/**
 * @brief Create an overlay widget.
 */
GtkWidget *create_overlay(OverlayConfig overlay_config);

gchar *write_overlay_property(FILE *output_file, View *view, int tabs_number);

#endif