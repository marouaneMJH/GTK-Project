#include "./../../../include/widgets/dialogs/file_chooser_dialog.h" 


GtkWidget* create_file_chooser_dialog(FileChooserDialogConfig config)
{
    GtkWidget* dialog = gtk_file_chooser_dialog_new(
        config.title,
        config.parent,
        config.action,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Open", GTK_RESPONSE_ACCEPT,
        NULL
    );

    // Set default folder if provided
    if (config.default_folder[0] != '\0') {
        gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), config.default_folder);
    }

    return dialog;
}
