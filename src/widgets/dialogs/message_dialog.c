#include "./../../../include/widgets/dialogs/message_dialog.h" 


GtkWidget* create_message_dialog(MessageDialogConfig config)
{
    GtkWidget* dialog = gtk_message_dialog_new(
        config.parent,
        config.is_modal ? GTK_DIALOG_MODAL : 0,
        config.message_type,
        config.buttons_type,
        "%s", config.message
    );

    // Set dialog title
    gtk_window_set_title(GTK_WINDOW(dialog), config.title);

    //  Set default dimensions
    gtk_window_set_default_size(GTK_WINDOW(dialog), config.dimensions.width, config.dimensions.height);


    return dialog;
}

