// #include "./../../../include/widgets/dialogs/message_dialog.h"
#include "./../../../include/widgets.h"

GtkWidget *create_message_dialog(MessageDialogConfig config)
{
    DialogConfig dialog_config = DEFAULT_DIALOG;

    strcpy(dialog_config.title, config.title);
    dialog_config.is_modal = config.is_modal;
    dialog_config.dimensions = config.dimensions;
    dialog_config.parent = config.parent;

    dialog_config.has_header = TRUE;
    GtkWidget *dialog = create_dialog(dialog_config);

    LabelConfig label_config = DEFAULT_LABEL;
    strcpy(label_config.label_text, config.message);
    label_config.font_size = 15;
    GtkWidget *label = create_label(label_config);

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_box_pack_start(GTK_BOX(content_area), label, FALSE, FALSE, 0);

    // Add "OK" button
    GtkWidget *button = gtk_dialog_add_button(GTK_DIALOG(dialog), "OK", GTK_RESPONSE_CLOSE);

    // Get the action area (button box)
    GtkWidget *action_area = gtk_dialog_get_action_area(GTK_DIALOG(dialog));

    // Set button box layout to expand buttons fully
    gtk_button_box_set_layout(GTK_BUTTON_BOX(action_area), GTK_BUTTONBOX_EXPAND);

    return dialog;
}

// GtkWidget* dialog = gtk_message_dialog_new(
//     config.parent,
//     config.is_modal ? GTK_DIALOG_MODAL : 0,
//     config.message_type,
//     config.buttons_type,
//     "%s", config.message
// );