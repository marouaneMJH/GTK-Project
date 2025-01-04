#include "./../../../include/widgets/dialogs/font_choser_dialog.h" 




GtkWidget* create_font_chooser_dialog(FontChooserDialogConfig config)
{
    GtkWidget* dialog = gtk_font_chooser_dialog_new(config.title, config.parent);

    // Set initial font if provided
    if (config.initial_font[0] != '\0') {
        gtk_font_chooser_set_font(GTK_FONT_CHOOSER(dialog), config.initial_font);
    }

    return dialog;
}
