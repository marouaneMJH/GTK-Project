#include "./../../../include/widgets/dialogs/dialog.h" 


GtkWidget* create_dialog(DialogConfig config)
{
    GtkWidget* dialog = gtk_dialog_new_with_buttons(
        config.title,
        config.parent,
        config.is_modal ? GTK_DIALOG_MODAL : 0,
        "_OK", GTK_RESPONSE_OK,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_OK", GTK_RESPONSE_CLOSE,
        NULL
    );

    // Set dimensions
    gtk_window_set_default_size(GTK_WINDOW(dialog), config.dimensions.width, config.dimensions.height);

    // Set background color if provided
    widget_set_colors(dialog,config.bg_color,config.text_color);

    return dialog;
}



void show_dialog(GtkWidget* dialog)
{
        /* Run the dialog */
    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
}

void destroy_dialog(GtkWidget* dialog)
{
    gtk_widget_destroy(dialog);
}