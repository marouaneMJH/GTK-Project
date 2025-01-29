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

/**
 * @brief Creates a dialog with the specified configuration.
 *
 * @param config The configuration for the dialog.
 * @return GtkWidget* The created dialog widget.
 */
GtkWidget* create_dialog(DialogConfig config);

/**
 * @brief Displays all widgets inside this dialog and the dialog itself.
 *
 * This function iterates through all the widgets contained within the dialog
 * and displays them. It also ensures that the dialog itself is displayed.
 *
 * @param dialog The dialog containing the widgets to be displayed.
 */
void show_dialog(GtkWidget* dialog);


/**
 * @brief Destroys the dialog and releases all associated resources.
 *
 * This function properly destroys the dialog window, freeing any allocated resources
 * and performing necessary cleanup operations.
 *
 * @param dialog The dialog to destroy.
 */
void destroy_dialog(GtkWidget* dialog);