#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include "./../../global.h"

#define MAX_GROUP_NAME_SIZE 50

/*  default values */
#define DEFAULT_NOTEBOOK_DIMENSIONS \
    {                               \
        .height = 0,                \
        .width = 0}

#define DEFAULT_NOTEBOOK_MARGINS \
    {                            \
        .bottom = 0,             \
        .top = 0,                \
        .start = 0,              \
        .end = 0}

#define DEFAULT_NOTEBOOK                           \
    {                                              \
        .group_name = "\0",                        \
        .current_page = 0,                         \
        .is_scrollable = TRUE,                     \
        .show_border = TRUE,                       \
        .show_tabs = TRUE,                         \
        .tab_position = GTK_POS_TOP,               \
        .margins = DEFAULT_NOTEBOOK_MARGINS,       \
        .dimensions = DEFAULT_NOTEBOOK_DIMENSIONS, \
        .hexpand = FALSE,                       \
        .vexpand = FALSE,                       \
        .halign = GTK_ALIGN_FILL,               \
        .valign = GTK_ALIGN_FILL,               \
        .bg_color = "\0",                          \
        .text_color = "\0"}

typedef struct
{
    // If there is another notebook with the same group name they can exchange the taps by drop and drag
    gchar group_name[MAX_GROUP_NAME_SIZE];

    // Select the current page
    gint current_page;

    // Enable or disable scrollable
    gboolean is_scrollable;

    // Show or hide border
    gboolean show_border;

    // Show or hide tabs
    gboolean show_tabs;

    // Position of tabs
    GtkPositionType tab_position;

    gboolean hexpand;
    gboolean vexpand;
    GtkAlign halign;
    GtkAlign valign;

    Margins margins;

    Dimensions dimensions;

    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} NotebookConfig;

ViewConfig *init_notebook_config(FILE *index, NotebookConfig *notebook_config);

/**
 * @brief create notebook widget with default
 * @param[in] notebook notebook structure
 * @return[ou] GtkWidget pointer to new notebook widget
 */
GtkWidget *create_notebook(NotebookConfig notebook_config);

NotebookConfig *read_notebook_config_from_dialog();

gchar *write_notebook_property(FILE *output_file, View *view, int tabs_number);

#endif