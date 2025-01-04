#ifndef MESSAGE_DIALOG_H
#define MESSAGE_DIALOG_H

#include "./../../global.h"

#define MAX_MESSAGE_DIALOG_SIZE 255
#define MAX_MESSAGE_DIALOG_TITLE_SIZE 50
#define DEFAULT_MESSAGE_DIALOG_DIMENSIONS \
    {                             \
        .height = 200,            \
        .width = 300}


/* Default configuration for message dialog */
#define DEFAULT_MESSAGE_DIALOG_CONFIG                  \
    {                                                  \
        .title = "Message",                            \
        .message = "Hello there, wellcom :D.",       \
        .dimensions = DEFAULT_MESSAGE_DIALOG_DIMENSIONS, \
        .message_type = GTK_MESSAGE_INFO,              \
        .buttons_type = GTK_BUTTONS_OK,                \
        .is_modal = TRUE,                              \
        .parent = NULL                                 \
    }

#endif


typedef struct {
    gchar title[MAX_MESSAGE_DIALOG_TITLE_SIZE]; // Title of the dialog
    gchar message[MAX_MESSAGE_DIALOG_SIZE];     // Message to display
    GtkMessageType message_type;                // Type: INFO, WARNING, ERROR, QUESTION, 
    Dimensions dimensions;
    GtkButtonsType buttons_type;                // Buttons: OK, CANCEL, YES/NO, 
    gboolean is_modal;                          // Whether the dialog is modal
    GtkWindow *parent;                          // Parent window (can be NULL)
} MessageDialogConfig;


// todo we can add message body in params
GtkWidget* create_message_dialog(MessageDialogConfig config);