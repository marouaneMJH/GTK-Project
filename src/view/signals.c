#include "./../../include/builder.h"
#include "./../../include/widgets/view/signals.h"

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
    build_app(root_app, NULL, DIALOG_TXT);
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

    box2_config.dimensions.width = 199;
    box2_config.dimensions.width = 199;

    GtkWidget *box2 = create_box(box2_config);

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

static void sig_show_image(GtkWidget *widget, gpointer data)
{
    ParamNode *param_array = (ParamNode *)data;
    if (!param_array)
    {
        g_print("\nError: sig_show_image(), missing parameters.\n");
        return;
    }

    // Set up dialog configuration
    DialogConfig dialog_config = DEFAULT_DIALOG;
    strcpy(dialog_config.title, param_array->params[1][0] != '\0' ? param_array->params[1] : "Image Viewer");

    // Set up box configuration
    BoxConfig box_image_config = DEFAULT_BOX;
    box_image_config.dimensions.height = 300; // Adjusted height
    box_image_config.dimensions.width = 300;  // Adjusted width
    box_image_config.halign = GTK_ALIGN_CENTER;
    box_image_config.valign = GTK_ALIGN_CENTER;

    // Create the box
    GtkWidget *box = create_box(box_image_config);

    // Set up image configuration
    ImageConfig image_config = DEFAULT_IMAGE;
    strcpy(image_config.path, param_array->params[0][0] != '\0' ? param_array->params[0] : "./assets/images/smale/img1.jpg");
    image_config.dimensions.height = 200; // Adjusted image height
    image_config.dimensions.width = 200;  // Adjusted image width
    image_config.opacity = 1.0;           // Full opacity

    // Check if the image file exists
    if (!g_file_test(image_config.path, G_FILE_TEST_EXISTS))
    {
        g_print("Error: Image file '%s' not found.\n", image_config.path);
        GtkWidget *error_label = gtk_label_new("Image not found.");
        gtk_box_pack_start(GTK_BOX(box), error_label, TRUE, TRUE, 0);
    }
    else
    {
        // Create the image widget and add to the box
        GtkWidget *image_widget = create_image(image_config);
        gtk_box_pack_start(GTK_BOX(box), image_widget, TRUE, TRUE, 0);
    }

    // Create the dialog and add the box to its content area
    GtkWidget *dialog = create_dialog(dialog_config);
    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), box);

    // Show the dialog
    show_dialog(dialog);
}

void sig_print_content(GtkWidget *widget, gpointer data)
{
    g_print("Content: %s\n", gtk_entry_get_text(GTK_ENTRY(widget)));
}

static void sig_destroy_dialog(GtkWidget *widget, gpointer data)
{
    gtk_widget_destroy(root_dialog_view_global->widget);
}

// Callback for key press events
gboolean sig_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    g_print("Key pressed: %s (keyval: %d)\n", gdk_keyval_name(event->keyval), event->keyval);

    // Check for specific keys
    if (event->keyval == GDK_KEY_Escape) {
        g_print("Escape key pressed. Exiting...\n");
        gtk_main_quit();  // Exit the application on Esc
    } else if (event->keyval == GDK_KEY_Return) {
        g_print("Enter key pressed!\n");
    } else if (event->keyval == GDK_KEY_Left) {
        g_print("Left arrow key pressed!\n");
    } else if (event->keyval == GDK_KEY_Right) {
        g_print("Right arrow key pressed!\n");
    }

    return FALSE;  // Return FALSE to propagate the event further
}

void connect_signales(View *view)
{
    // Exit the function if no signale triggered
    if (view->view_config->signal.event_type == SIG_NONE)
        return;

    void *callback_function = NULL;

    // Map event names to their corresponding callback functions
    if (view->view_config->signal.event_type != SIG_NONE)
    {
        if (strcmp(view->view_config->signal.sig_handler, "sig_change_self_bg_color") == 0)
            callback_function = sig_change_self_bg_color;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_dialog_message") == 0)
            callback_function = sig_dialog_message;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_change_friend_bg_color") == 0)
            callback_function = sig_change_friend_bg_color;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_change_font_size") == 0)
            callback_function = sig_change_font_size;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_destroy") == 0)
            callback_function = sig_destroy;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_dialog") == 0)
            callback_function = sig_dialog;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_dialog_response") == 0)
            callback_function = sig_dialog_response;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_dialog_color") == 0)
            callback_function = sig_dialog_color;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_dialog_font") == 0)
            callback_function = sig_dialog_font;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_self_destroy") == 0)
            callback_function = sig_self_destroy;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_dialog_warning") == 0)
            callback_function = sig_dialog_warning;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_show_image") == 0)
            callback_function = sig_show_image;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_print_content") == 0)
            callback_function = sig_print_content;
        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_destroy_dialog") == 0)
            callback_function = sig_destroy_dialog;
        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_key_press") == 0)
            callback_function = sig_key_press;
    }

    // Connect the callback function
    if (callback_function)
    {
        switch (view->view_config->signal.event_type)
        {
        case SIG_ON_CLICK:
            g_signal_connect(G_OBJECT(view->widget), "clicked", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_TOGGLE:
            g_signal_connect(G_OBJECT(view->widget), "toggled", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_CHANGE:
            g_signal_connect(G_OBJECT(view->widget), "changed", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_ACTIVATE:
            g_signal_connect(G_OBJECT(view->widget), "activate", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_DELETE_EVENT:
            g_signal_connect(G_OBJECT(view->widget), "delete-event", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_DESTROY:
            g_signal_connect(G_OBJECT(view->widget), "destroy", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_VALUE_CHANGED:
            g_signal_connect(G_OBJECT(view->widget), "value-changed", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_ROW_ACTIVATED:
            g_signal_connect(G_OBJECT(view->widget), "row-activated", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_KEY_PRESS:
            g_signal_connect(G_OBJECT(view->widget), "key-press-event", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_KEY_RELEASE:
            g_signal_connect(G_OBJECT(view->widget), "key-release-event", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_BUTTON_PRESS:
            g_signal_connect(G_OBJECT(view->widget), "button-press-event", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_BUTTON_RELEASE:
            g_signal_connect(G_OBJECT(view->widget), "button-release-event", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_MOTION_NOTIFY:
            g_signal_connect(G_OBJECT(view->widget), "motion-notify-event", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_FOCUS_IN:
            g_signal_connect(G_OBJECT(view->widget), "focus-in-event", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_FOCUS_OUT:
            g_signal_connect(G_OBJECT(view->widget), "focus-out-event", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_SWITCH_PAGE:
            g_signal_connect(G_OBJECT(view->widget), "switch-page", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_SELECTION_CHANGED:
            g_signal_connect(G_OBJECT(view->widget), "selection-changed", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_POPUP_MENU:
            g_signal_connect(G_OBJECT(view->widget), "popup-menu", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_SCROLL:
            g_signal_connect(G_OBJECT(view->widget), "scroll-event", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_ENTER_NOTIFY:
            g_signal_connect(G_OBJECT(view->widget), "enter-notify-event", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_LEAVE_NOTIFY:
            g_signal_connect(G_OBJECT(view->widget), "leave-notify-event", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        case SIG_ON_RESPONSE:
            g_signal_connect(G_OBJECT(view->widget), "response", G_CALLBACK(callback_function), NULL);
            break;

        default:
            // Handle SIG_NONE or unknown signals if necessary
            g_print("\nError signale type %d not found.", view->view_config->signal.event_type);
            break;
        }
    }
}
