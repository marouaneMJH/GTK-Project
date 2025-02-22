#ifndef LIST_LIST_BOX_H
#define LIST_LIST_BOX_H

#include "./../../global.h"

/*  default values */
#define DEFAULT_LIST_LIST_BOX_DIMENSIONS \
    {                                    \
        .height = 0,                     \
        .width = 0}

#define DEFAULT_LIST_LIST_BOX_MARGINS \
    {                                 \
        .bottom = 0,                  \
        .top = 0,                     \
        .start = 0,                   \
        .end = 0}

#define DEFAULT_LIST_LIST_BOX                           \
    {                                                   \
        .selection_mode = GTK_SELECTION_SINGLE,         \
        .placeholder = NULL,                            \
        .margins = DEFAULT_LIST_LIST_BOX_MARGINS,       \
        .dimensions = DEFAULT_LIST_LIST_BOX_DIMENSIONS, \
        .bg_color = "\0",                               \
        .text_color = "\0"}

typedef struct
{

    GtkSelectionMode selection_mode;

    GtkWidget *placeholder;

    Margins margins;

    Dimensions dimensions;

    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} ListBoxConfig;

ListBoxConfig *init_list_box();

/**
 * @brief create list_box widget with default
 * @param[in] list_box list_box structure
 * @return[ou] GtkWidget pointer to new list_box widget
 */
GtkWidget *create_list_box(ListBoxConfig list_box_config);

gchar *write_list_box_property(FILE *output_file, View *view, int tabs_number);


#endif