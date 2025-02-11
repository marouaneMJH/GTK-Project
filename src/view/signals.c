#include "./../../include/builder.h"
/**
 * @brief structure for handle signales parametres
 * //todo variable: checck if on_cllick signal activate or not and also for other signales
 */
typedef struct
{
    gchar params[PARAM_COUNT][MAX_SIGNAL_NAME_SIZE]; // First function parameter
} ParamNode;

static void sig_change_self_bg_color(GtkWidget *widget, gpointer data)
{
    ParamNode *param_array = (ParamNode *)data;
    if (!param_array)
    {
        g_print("\nError: sig_change_friend_bg_color(), passing argument.\n");
        return;
    }

    widget_set_colors(widget, param_array->params[0], param_array->params[1]);
}

static void sig_change_friend_bg_color(GtkWidget *widget, gpointer data)
{

    ParamNode *param_array = (ParamNode *)data;
    if (!param_array)
    {
        g_print("\nError: sig_change_friend_bg_color(), passing argument.\n");
        return;
    }
    View *friend = find_view_by_id(param_array->params[0], root_view_global);
    widget_set_colors(friend->widget, param_array->params[1], param_array->params[2]);
}

static void sig_dialog_message(GtkWidget *widget, gpointer data)
{
    ParamNode *param_array = (ParamNode *)data;
    MessageDialogConfig message_dialog_config = DEFAULT_MESSAGE_DIALOG_CONFIG;
    strcpy(message_dialog_config.message, param_array->params[0]);
    GtkWidget *dialog_widget = create_message_dialog(message_dialog_config);
    show_dialog(dialog_widget);
}

static void sig_change_font_size(GtkWidget *widget, gpointer data)
{
    ParamNode *param_array = (ParamNode *)data;

    View *label_view = find_view_by_id(param_array->params[0], root_view_global);

    widget_set_font_size(label_view->widget, atoi(param_array->params[1]));
}

static void sig_destroy(GtkWidget *widget, gpointer data)
{
    GtkWidget *window = root_view_global->widget;

    gtk_widget_destroy(window);
}

static void sig_dialog(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog = root_dialog_view_global->widget;

    show_dialog(dialog);
}

static void sig_dialog_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
    switch (response_id)
    {
    case GTK_RESPONSE_OK:
        g_print("User clicked OK.\n");
        break;

    case GTK_RESPONSE_CANCEL:
    case GTK_RESPONSE_CLOSE:
    case GTK_RESPONSE_DELETE_EVENT:
        g_print("User clicked Exiting the box.\n");
        gtk_widget_destroy(GTK_WIDGET(dialog)); // Close the dialog
        break;

    case GTK_RESPONSE_YES:
        g_print("User clicked Yes.\n");
        break;

    case GTK_RESPONSE_NO:
        g_print("User clicked No.\n");
        break;

    case 100: // Custom response
        g_print("Custom response 100 triggered.\n");
        break;

    default:
        g_print("Unknown response ID: %d\n", response_id);
        break;
    }
}

static void sig_dialog_color(GtkWidget *widget, gpointer data)
{
    ColorChooserDialogConfig dialog_color_config = DEFAULT_COLOR_CHOOSER_DIALOG_CONFIG;
    GtkWidget *dialog_color_widget = create_color_chooser_dialog(dialog_color_config);

    show_dialog(dialog_color_widget);
}

static void sig_dialog_font(GtkWidget *widget, gpointer data)
{
    FontChooserDialogConfig dialog_font_config = DEFAULT_FONT_CHOOSER_DIALOG_CONFIG;
    GtkWidget *dialog_font_widget = create_font_chooser_dialog(dialog_font_config);

    show_dialog(dialog_font_widget);
}

static void sig_self_destroy(GtkWidget *widget, gpointer data)
{

    gtk_widget_destroy(widget);
}

static void sig_dialog_warning(GtkWidget *widget, gpointer data)
{
    ParamNode *param_array = (ParamNode *)data;
    if (!param_array)
    {
        g_print("\nError: sig_dialog_warning(), missing parameters.\n");
        return;
    }

    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *image;
    GtkWidget *label;
    GtkWidget *box;

    ImageConfig image_config = DEFAULT_IMAGE;
    LabelConfig label_config = DEFAULT_LABEL;
    BoxConfig box_config = DEFAULT_BOX;
    BoxConfig box2_config = DEFAULT_BOX;

    // Create the dialog window
    dialog = gtk_dialog_new_with_buttons("Warning",
                                         GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         "_OK", GTK_RESPONSE_OK,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         "_Quit", GTK_RESPONSE_CANCEL,

                                         NULL);

    // Get the content area of the dialog
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create a horizontal box to hold the image and label
    box_config.orientation = GTK_ORIENTATION_HORIZONTAL;
    box_config.spacing = 10;

    box = create_box(box_config);
    gtk_container_add(GTK_CONTAINER(content_area), box);

    // Load the image from the file
    strcpy(image_config.path, "./assets/images/warning_icon.jpeg");
    image_config.dimensions.height = 20;
    image_config.dimensions.width = 20;
    image = create_image(image_config);
    if (!image)
    {
        g_print("Error: Unable to load image './assets/images/warning_icon.jpeg'\n");
    }

    box2_config.dimensions.width=199;
    box2_config.dimensions.width=199;

    GtkWidget *box2=create_box(box2_config);

    gtk_box_pack_start(GTK_BOX(box2), image, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), box2, FALSE, FALSE, 10);

    // Create the warning label using the first parameter
    strcpy(label_config.label_text,
           param_array->params[0][0] != '\0'
               ? param_array->params[0]
               : "This is a warning message!");

    label = create_label(label_config);

    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 10);

    // Show all widgets in the dialog
    show_dialog(dialog);

    // Run the dialog and wait for user response
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    // Handle dialog response if needed
    if (response == GTK_RESPONSE_OK)
    {
        g_print("Warning dialog acknowledged.\n");
    }

    // Destroy the dialog after response
    gtk_widget_destroy(dialog);
}

void connect_signales(View *view)
{
    void *callback_function = NULL;

    // Extract the event name once to avoid repetition
    const char *event_name = NULL;
    if (view->view_config->onclick[0] != '\0')
    {
        event_name = view->view_config->onclick;
    }
    else if (view->view_config->on_active[0] != '\0')
    {
        event_name = view->view_config->on_active;
    }
    else if (view->view_config->on_response[0] != '\0')
    {
        event_name = view->view_config->on_response;
    }

    // Map event names to their corresponding callback functions
    if (event_name)
    {
        if (strcmp(event_name, "sig_change_self_bg_color") == 0)
            callback_function = sig_change_self_bg_color;

        else if (strcmp(event_name, "sig_dialog_message") == 0)
            callback_function = sig_dialog_message;

        else if (strcmp(event_name, "sig_change_friend_bg_color") == 0)
            callback_function = sig_change_friend_bg_color;

        else if (strcmp(event_name, "sig_change_font_size") == 0)
            callback_function = sig_change_font_size;

        else if (strcmp(event_name, "sig_destroy") == 0)
            callback_function = sig_destroy;

        else if (strcmp(event_name, "sig_dialog") == 0)
            callback_function = sig_dialog;

        else if (strcmp(event_name, "sig_dialog_response") == 0)
            callback_function = sig_dialog_response;

        else if (strcmp(event_name, "sig_dialog_color") == 0)
            callback_function = sig_dialog_color;

        else if (strcmp(event_name, "sig_dialog_font") == 0)
            callback_function = sig_dialog_font;

        else if (strcmp(event_name, "sig_self_destroy") == 0)
            callback_function = sig_self_destroy;

        else if (strcmp(event_name, "sig_dialog_warning") == 0)
            callback_function = sig_dialog_warning;
    }

    // Connect the callback function
    if (callback_function)
        if (view->view_config->onclick[0] != '\0')
            g_signal_connect(G_OBJECT(view->widget), "clicked", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);

        else if (view->view_config->on_active[0] != '\0')
            g_signal_connect(G_OBJECT(view->widget), "activate", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);

        else if (view->view_config->on_response[0] != '\0')
            g_signal_connect(G_OBJECT(view->widget), "response", G_CALLBACK(callback_function), NULL);
}

// Link signals
// if (view_config->onclick[0] != '\0')
// {
//     if (g_strcmp0(view_config->onclick, "click1") == 0)
//         g_signal_connect(G_OBJECT(button_widget), "clicked", G_CALLBACK(click1), NULL);
//     else if (g_strcmp0(view_config->onclick, "click2") == 0)
//         g_signal_connect(G_OBJECT(button_widget), "clicked", G_CALLBACK(click2), NULL);
// }

// if (view_config->onclick[0] != '\0')
// {
//     if (g_strcmp0(view_config->onclick, "menu_onclick") == 0)
//         g_signal_connect(G_OBJECT(menu_item_widget), "activate", G_CALLBACK(menu_item_onclick), NULL);
//     else if (g_strcmp0(view_config->onclick, "menu_onclick1") == 0)
//         g_signal_connect(G_OBJECT(menu_item_widget), "activate", G_CALLBACK(menu_item_onclick), NULL);
//     }