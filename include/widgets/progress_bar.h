#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include "./../global.h"



/* Max size of progress bar text */
#define MAX_PROGRESS_BAR_TEXT_SIZE 50

/* Default dimensions for progress bar */
#define DEFAULT_PROGRESS_BAR_DIMENSIONS \
    {                                   \
        .height = 50,                   \
        .width = 200}

/* Default margins for progress bar */
#define DEFAULT_PROGRESS_BAR_MARGINS \
    {                                \
        .bottom = 0,                 \
        .top = 0,                    \
        .start = 0,                  \
        .end = 0}

/* Default progress bar configuration */
#define DEFAULT_PROGRESS_BAR \
    {                        \
        .text = "",          \
        .dimensions = DEFAULT_PROGRESS_BAR_DIMENSIONS, \
        .margins = DEFAULT_PROGRESS_BAR_MARGINS, \
        .progress_fraction = 0, \
        .progress_pulse_step = 0, \
        .is_text_visible = TRUE, \
        .is_inverted = FALSE, \
        .ellipsize = PANGO_ELLIPSIZE_END, \
        .opacity = 1, \
        .bg_color = "\0", \
        .text_color = "\0", \
    }

/**
 * @brief Structure to configure a progress bar widget
 */
typedef struct
{
    gchar text[MAX_PROGRESS_BAR_TEXT_SIZE];               ///< The text displayed in the progress bar
    Dimensions dimensions;                          ///< The dimensions of the progress bar
    Margins margins;                               ///< The margins of the progress bar
    gdouble progress_fraction;                     ///< The fraction of the progress bar (0.0 to 1.0)
    gdouble progress_pulse_step;                   ///< The pulse step of the progress bar
    gboolean is_text_visible;                      ///< Whether the text is visible or hidden
    gboolean is_inverted;                          ///< Whether the progress bar is inverted
    PangoEllipsizeMode ellipsize;                  ///< The ellipsize mode of the progress bar
    gboolean opacity;                              ///< The opacity of the progress bar (0.0 to 1.0)
    gchar bg_color[MAX_COLOR_SIZE];                ///< The background color of the progress bar
    gchar text_color[MAX_COLOR_SIZE];              ///< The text color of the progress bar
} ProgressBarConfig;


ViewConfig *init_progress_bar_config(FILE *index, ProgressBarConfig *progress_bar_config);


/**
 * @brief Create a progress bar widget
 * @param progress_bar_config The configuration of the progress bar
 * @return GtkWidget* The progress bar widget
 */
GtkWidget *create_progress_bar(ProgressBarConfig progress_bar_config);


#endif