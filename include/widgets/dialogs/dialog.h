#ifndef DIALOG_H
#define DIALOG_H



#include "./../../global.h"

/**
 * //todo: main thing s to add:
 * signals
 * modification function 
*/

/* Max sizes for dialog elements */
#define MAX_DIALOG_TITLE_SIZE 50

/* Default dimensions for general dialogs */
#define DEFAULT_DIALOG_DIMENSIONS \
    {                             \
        .width = 500,             \
        .height = 500             \
    }

/* Default configuration for general dialog */
#define DEFAULT_DIALOG_CONFIG                          \
    {                                                  \
        .title = "General Dialog",                     \
        .is_modal = TRUE,                              \
        .dimensions = DEFAULT_DIALOG_DIMENSIONS,       \
        .parent = NULL,                                \
        .bg_color = "\0",                              \
        .text_color = "\0"                             \
    }

#endif


typedef struct
{
    gchar title[MAX_DIALOG_TITLE_SIZE]; // Title of the dialog
    gboolean is_modal;                  // Whether the dialog is modal
    Dimensions dimensions;              // initial dimensions  
    GtkWindow *parent;                  // Parent window (can be NULL)
    gchar bg_color[MAX_COLOR_SIZE];     // Background color 
    gchar text_color[MAX_COLOR_SIZE];   // Font color
} DialogConfig;



GtkWidget* create_dialog(DialogConfig config);



void show_dialog(GtkWidget* dialog);


void destroy_dialog(GtkWidget* dialog);