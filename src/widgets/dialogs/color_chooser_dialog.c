#include "./../../../include/widgets/dialogs/color_chooser_dialog.h" 


GtkWidget* create_color_chooser_dialog(ColorChooserDialogConfig config)
{
    GtkWidget* dialog = gtk_color_chooser_dialog_new(config.title, config.parent);

    // Set initial color
    gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(dialog), &config.initial_color);

    return dialog;
}
