#ifndef FONT_CHOOSER_DIALOG_H
#define FONT_CHOOSER_DIALOG_H

#include "./../../global.h"

#define MAX_FONT_DIALOG_TITLE_SIZE 50

#define DEFAULT_FONT_CHOOSER_DIALOG_CONFIG             \
    {                                                  \
        .title = "Font Chooser",                       \
        .parent = NULL,                                \
        .is_modal = TRUE,                              \
        .initial_font = "Sans 12",                     \
        .selected_font = "\0"                          \
    }


#endif



typedef struct {
    gchar title[MAX_FONT_DIALOG_TITLE_SIZE];    // Title of the dialog
    GtkWindow *parent;                          // Parent window (can be NULL)
    gboolean is_modal;                          // Whether the dialog is modal
    gchar *initial_font;                        // Initial font (e.g., "Sans 12")
    gchar *selected_font;                       // Stores the selected font after use
} FontChooserDialogConfig;



GtkWidget* create_font_chooser_dialog(FontChooserDialogConfig config);