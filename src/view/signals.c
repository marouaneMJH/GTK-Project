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
        g_print("User clicked Cancel.\n");
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

    case GTK_RESPONSE_DELETE_EVENT: 
        gtk_widget_destroy(GTK_WIDGET(dialog));
        break;

    default:
        g_print("Unknown response ID: %d\n", response_id);
        break;
    }
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