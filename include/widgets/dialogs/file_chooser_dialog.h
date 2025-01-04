#ifndef FILE_CHOOSER_DIALOG_H
#define FILE_CHOOSER_DIALOG_H

#include "./../../global.h"

#define MAX_FILE_DIALOG_TITLE_SIZE 50

/* Default configuration for file chooser dialog */
#define DEFAULT_FILE_CHOOSER_DIALOG_CONFIG             \
    {                                                  \
        .title = "File Chooser",                       \
        .action = GTK_FILE_CHOOSER_ACTION_OPEN,        \
        .parent = NULL,                                \
        .is_modal = TRUE,                              \
        .default_folder = g_get_home_dir(),            \
        .selected_filename = "\0"                      \
    }

#endif

typedef struct {
    gchar title[MAX_FILE_DIALOG_TITLE_SIZE]; // Title of the dialog
    GtkFileChooserAction action;            // OPEN, SAVE, SELECT_FOLDER, CREATE_FOLDER
    GtkWindow *parent;                      // Parent window (can be NULL)
    gboolean is_modal;                      // Whether the dialog is modal
    gchar *default_folder;                  // Default folder to open
    gchar *selected_filename;               // Stores the selected filename after use
} FileChooserDialogConfig;



GtkWidget* create_file_chooser_dialog(FileChooserDialogConfig config);




