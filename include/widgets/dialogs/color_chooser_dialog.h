#ifndef COLOR_CHOOSER_DIALOG_H
#define COLOR_CHOOSER_DIALOG_H

#include "./../../global.h"

#define MAX_COLOR_DIALOG_TITLE_SIZE 50

// todo set a default title 

#define DEFAULT_COLOR_CHOOSER_DIALOG_CONFIG            \
    {                                                  \
        .title = "Colors",                             \
        .parent = NULL,                                \
        .is_modal = TRUE,                              \
        .initial_color = {1.0, 1.0, 1.0, 1.0},         \
        .selected_color = {0.0, 0.0, 0.0, 1.0}         \
    }

#endif



typedef struct {
    gchar title[MAX_COLOR_DIALOG_TITLE_SIZE];   // Title of the dialog
    GtkWindow *parent;                          // Parent window (can be NULL)
    gboolean is_modal;                          // Whether the dialog is modal
    GdkRGBA initial_color;                      // Initial color (optional)
    GdkRGBA selected_color;                     // Stores the selected color after use

} ColorChooserDialogConfig;




GtkWidget* create_color_chooser_dialog(ColorChooserDialogConfig config);