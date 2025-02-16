#include "./../../../include/builder.h"
#include "./../../../include/widgets/view/signals.h"

/**
 * @brief structure for handle signales parametres
 * //todo variable: checck if on_cllick signal activate or not and also for other signales
 */
typedef struct
{
    gchar params[PARAM_COUNT][MAX_SIGNAL_NAME_SIZE]; // First function parameter

} ParamNode;

// for test

gboolean sig_hello(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
    if (event->type == GDK_BUTTON_PRESS)
    {
        g_print("Label clicked! Button %d at (%.2f, %.2f)\n",
                event->button, event->x, event->y);
        // Return TRUE to indicate the event was handled.
        return TRUE;
    }
    return FALSE;
}

void widget_type(View *root)
{
    if (root == NULL)
        return;
    const char *type_name = G_OBJECT_TYPE_NAME(root->widget);
    if (root->parent)
    {
        const char *parent_type_name = G_OBJECT_TYPE_NAME(root->parent->widget);
        g_print("Widget type: %s\tContainer type:  %s.\n", type_name, parent_type_name);
    }
    else
    {

        g_print("Widget type: %s\tContainer type:  NULL.\n", type_name);
    }
    // if (type_name)
    //     free(type_name);

    // if (parent_type_name)
    //     free(parent_type_name);

    widget_type(root->child);
    widget_type(root->next);
}

static void sig_tree_widget_type(GtkWidget *widget, gpointer data)
{
    widget_type(root_view_global);
}

// end  testing signales

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

/**
 * color
 * font
 * size
 * margins
 * then the specify signales
 */

static void sig_change_friend_color(GtkWidget *widget, gpointer data)
{
    if (GTK_IS_ENTRY(widget))
    {
        const char *name = gtk_entry_get_text(GTK_ENTRY(widget)); // Get text from entry

        View *view = find_view_by_id("xxx-button", root_view_global);
        View *label = find_view_by_id("label_color", root_view_global);

        if (view && label)
        {
            widget_set_colors(view->widget, name, NULL); // Update widget color

            // Get the color (assuming `view->widget` is a color chooser)
            GdkRGBA color;
            gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(view->widget), &color);

            // Convert RGBA to HEX (#RRGGBB)
            char hex_color[8]; // Format: #RRGGBB
            snprintf(hex_color, sizeof(hex_color), "#%02X%02X%02X",
                     (int)(color.red * 255),
                     (int)(color.green * 255),
                     (int)(color.blue * 255));

            // Properly concatenate the label text
            char *label_text = g_strconcat("Color: ", hex_color, NULL);
            gtk_label_set_text(GTK_LABEL(label->widget), label_text);

            g_free(label_text); // Free allocated memory
        }
        else
        {
            g_print("\nThe view or label does not exist");
        }

        gtk_entry_set_text(GTK_ENTRY(widget), ""); // Clear entry text
    }
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
        gtk_widget_destroy(GTK_WIDGET(dialog)); // Close the dialog
        break;

    case 100: // Custom response
        g_print("Custom response 100 triggered.\n");
        break;

    default:
        g_print("Unknown response ID: %d\n", response_id);
        break;
    }
}

static void sig_self_destroy(GtkWidget *widget, gpointer data)
{
    gtk_widget_destroy(widget);
}


void sig_print_content(GtkWidget *widget, gpointer data)
{
    g_print("Content: %s\n", gtk_entry_get_text(GTK_ENTRY(widget)));
}

static void sig_destroy_dialog(GtkWidget *widget, gpointer data)
{
    gtk_widget_destroy(root_dialog_view_global->widget);
}

/* Button color signales */
// Go to signals.h to read documentation

static void sig_color_btn_friend_bg_color(GtkWidget *widget, gpointer data)
{
    ParamNode *param_array = (ParamNode *)data;

    if (!param_array)
    {
        g_print("\nthe param_array passed to sig_color_btn_friend_bg_color is null");
        return; // exit the function
    }
    // review instead of seaching, we can make our main widget a broder to our app root
    // review it will drop the complexity, other raison, in modifying dialog we have just one main widget

    View *view = find_view_by_id(param_array->params[0], root_view_global);

    if (!view)
    {
        g_print("\nthe view passed to sig_color_btn_friend_bg_color is null");
        return; // exit the function
    }

    // to save given color by button color
    GdkRGBA bg_color;

    // geting the color from the color button
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(widget), &bg_color);

    // converting the rgba color to readable string for next function
    char *bg_color_str = gdk_rgba_to_string(&bg_color);

    // change the target widget bg color
    widget_set_colors(view->widget, bg_color_str, NULL);

    // deallocate the memory
    if (bg_color_str)
        free(bg_color_str);
}

static void sig_color_btn_friend_color(GtkWidget *widget, gpointer data)
{
    ParamNode *param_array = (ParamNode *)data;

    if (!param_array)
    {
        g_print("\nthe param_array passed to sig_color_btn_friend_color is null");
        return; // exit the function
    }
    View *view = find_view_by_id(param_array->params[0], root_view_global);

    if (!view)
    {
        g_print("\nthe view passed to sig_color_btn_friend_color is null");
        return; // exit the function
    }

    // to save given color by button color
    GdkRGBA bg_color;

    // geting the color from the color button
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(widget), &bg_color);

    // converting the rgba color to readable string for next function
    char *bg_color_str = gdk_rgba_to_string(&bg_color);

    // change the target widget color
    widget_set_colors(view->widget, NULL, bg_color_str);

    // deallocate the memory
    if (bg_color_str)
        free(bg_color_str);
}

/* End of Color signales */

// Callback for key press events
gboolean sig_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    g_print("Key pressed: %s (keyval: %d)\n", gdk_keyval_name(event->keyval), event->keyval);

    // Check for specific keys
    if (event->keyval == GDK_KEY_Escape)
    {
        g_print("Escape key pressed. Exiting...\n");
        gtk_main_quit(); // Exit the application on Esc
    }
    else if (event->keyval == GDK_KEY_Return)
    {
        g_print("Enter key pressed!\n");
    }
    else if (event->keyval == GDK_KEY_Left)
    {
        g_print("Left arrow key pressed!\n");
    }
    else if (event->keyval == GDK_KEY_Right)
    {
        g_print("Right arrow key pressed!\n");
    }

    return FALSE; // Return FALSE to propagate the event further
}

static void sig_properties_dialog(GtkWidget *widget, gpointer data)
{
    ParamNode *param_array = (ParamNode *)data;
    if (!param_array)
    {
        g_print("\nError: sig_change_friend_bg_color(), passing argument.\n");
        return;
    }

    if (g_strcmp0(param_array->params[0], "box") == 0)
        build_app(root_app, NULL, BOX_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "fixed") == 0)
        build_app(root_app, NULL, FIXED_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "grid") == 0)
        build_app(root_app, NULL, GRID_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "paned") == 0)
        build_app(root_app, NULL, PANED_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "frame") == 0)
        build_app(root_app, NULL, FRAME_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "flowbox") == 0)
        build_app(root_app, NULL, FLOWBOX_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "overlay") == 0)
        build_app(root_app, NULL, OVERLAY_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "notebook") == 0)
        build_app(root_app, NULL, NOTEBOOK_PROPERTIES_DIALOG_TXT);

    GtkWidget *dialog = root_dialog_view_global->widget;

    show_dialog(dialog);
}

void create_new_box_from_dialog()
{
    View *viewer = find_view_by_id("viewer", root_view_global);
    if (!viewer)
    {
        g_print("Error: ==> Cannot find the viewer\n");
        return;
    }

    BoxConfig box_config = DEFAULT_BOX;
    View *input_widget = NULL;

    // Orientation
    input_widget = find_view_by_id("orientation_combo", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the viewer\n");
        return;
    }
    gchar *selected_orientation = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(input_widget->widget));
    g_print("SELECTED ORIENTATION: ===> %s \n", selected_orientation);
    if (stricmp(selected_orientation, "horizontal") == 0)
        box_config.orientation = GTK_ORIENTATION_HORIZONTAL;

    // Spacing
    input_widget = find_view_by_id("spacing_spin", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the viewer\n");
        return;
    }
    gint spacing = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_widget->widget));
    g_print("SELECTED SPACING: ===> %d \n", spacing);
    box_config.spacing = spacing;

    // Width
    input_widget = find_view_by_id("width_spin", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the viewer\n");
        return;
    }
    gint width = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_widget->widget));
    box_config.dimensions.width = width;

    // Height
    input_widget = find_view_by_id("height_spin", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the viewer\n");
        return;
    }
    gint height = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_widget->widget));
    box_config.dimensions.height = height;

    // Margin top
    input_widget = find_view_by_id("margin_top_spin", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the margin_top_spin\n");
        return;
    }
    gint margin_top = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_widget->widget));
    box_config.margins.top = margin_top;

    // Margin bottom
    input_widget = find_view_by_id("margin_bottom_spin", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the margin_bottom_spin\n");
        return;
    }
    gint margin_bottom = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_widget->widget));
    box_config.margins.bottom = margin_bottom;

    // Margin left
    input_widget = find_view_by_id("margin_left_spin", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the margin_left_spin\n");
        return;
    }
    gint margin_left = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_widget->widget));
    box_config.margins.start = margin_left;

    // Margin right
    input_widget = find_view_by_id("margin_right_spin", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the margin_right_spin\n");
        return;
    }
    gint margin_right = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_widget->widget));
    box_config.margins.end = margin_right;

    // Baseline
    input_widget = find_view_by_id("baseline_combo", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the viewer\n");
        return;
    }
    gchar *baseline = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(input_widget->widget));
    if (stricmp(selected_orientation, "top") == 0)
        box_config.baseline_position = GTK_BASELINE_POSITION_TOP;
    else if (stricmp(selected_orientation, "bottom") == 0)
        box_config.baseline_position = GTK_BASELINE_POSITION_BOTTOM;

    // HAlign
    input_widget = find_view_by_id("halign_combo", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the viewer\n");
        return;
    }
    gchar *halign = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(input_widget->widget));
    if (stricmp(halign, "start") == 0)
        box_config.halign = GTK_ALIGN_START;
    else if (stricmp(halign, "end") == 0)
        box_config.halign = GTK_ALIGN_END;
    else if (stricmp(halign, "baseline") == 0)
        box_config.halign = GTK_ALIGN_BASELINE;
    else if (stricmp(halign, "center") == 0)
        box_config.halign = GTK_ALIGN_CENTER;

    // VAlign
    input_widget = find_view_by_id("valign_combo", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the viewer\n");
        return;
    }
    gchar *valign = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(input_widget->widget));
    if (stricmp(valign, "start") == 0)
        box_config.valign = GTK_ALIGN_START;
    else if (stricmp(valign, "end") == 0)
        box_config.valign = GTK_ALIGN_END;
    else if (stricmp(valign, "baseline") == 0)
        box_config.valign = GTK_ALIGN_BASELINE;
    else if (stricmp(valign, "center") == 0)
        box_config.valign = GTK_ALIGN_CENTER;

    // Homogeneous
    input_widget = find_view_by_id("homogeneous_switch", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the homogeneous_switch\n");
        return;
    }
    gboolean homogeneous = gtk_switch_get_active(GTK_SWITCH(input_widget->widget));
    box_config.homogeneous = homogeneous;

    // HExpand
    input_widget = find_view_by_id("hexpand_switch", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the hexpand_switch\n");
        return;
    }
    gboolean hexpand = gtk_switch_get_active(GTK_SWITCH(input_widget->widget));
    box_config.hexpand = hexpand;

    // VExpand
    input_widget = find_view_by_id("vexpand_switch", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the vexpand_switch\n");
        return;
    }
    gboolean vexpand = gtk_switch_get_active(GTK_SWITCH(input_widget->widget));
    box_config.vexpand = vexpand;

    // Background color
    input_widget = find_view_by_id("bg_color_entry", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the bg_color_entry\n");
        return;
    }
    const gchar *bg_color = gtk_entry_get_text(GTK_ENTRY(input_widget->widget));
    strcpy(box_config.bg_color, bg_color);

    strcpy(box_config.bg_color, "red");

    // Text color
    input_widget = find_view_by_id("color_entry", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the color_entry\n");
        return;
    }
    const gchar *text_color = gtk_entry_get_text(GTK_ENTRY(input_widget->widget));
    strcpy(box_config.text_color, text_color);

    // Background image
    input_widget = find_view_by_id("bg_image_entry", root_dialog_view_global);
    if (!input_widget)
    {
        g_print("Error: ==> Cannot find the bg_image_entry\n");
        return;
    }
    const gchar *bg_image = gtk_entry_get_text(GTK_ENTRY(input_widget->widget));
    strcpy(box_config.bg_image, bg_image);

    GtkWidget *new_box = create_box(box_config);
    gtk_container_add(GTK_CONTAINER(viewer->widget), new_box);
    gtk_widget_show_all(root_view_global->widget);
}

static void sig_create_new_view(GtkWidget *widget, gpointer data)
{

    // TODO: Add the new widget to viewer
    // Steps:
    // 1 - Get viewer
    // 2 - Read config from root dialog for each widget
    // 3 - Create the view basing on the config
    // 4 - Add the view a new view graph (or exist one except the main)

    ParamNode *param_array = (ParamNode *)data;
    if (!param_array)
    {
        g_print("Error: ==> passing argument.\n");
        return;
    }

    if (g_strcmp0(param_array->params[0], "box") == 0)
    {
        create_new_box_from_dialog();
    }
    else if (g_strcmp0(param_array->params[0], "fixed") == 0)
    {
    }
    else if (g_strcmp0(param_array->params[0], "grid") == 0)
        build_app(root_app, NULL, GRID_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "paned") == 0)
        build_app(root_app, NULL, PANED_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "frame") == 0)
        build_app(root_app, NULL, FRAME_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "flowbox") == 0)
        build_app(root_app, NULL, FLOWBOX_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "overlay") == 0)
        build_app(root_app, NULL, OVERLAY_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "notebook") == 0)
        build_app(root_app, NULL, NOTEBOOK_PROPERTIES_DIALOG_TXT);
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
                        "sig_self_destroy") == 0)
            callback_function = sig_self_destroy;


        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_print_content") == 0)
            callback_function = sig_print_content;
        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_destroy_dialog") == 0)
            callback_function = sig_destroy_dialog;
        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_key_press") == 0)
            callback_function = sig_key_press;
        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_properties_dialog") == 0)
            callback_function = sig_properties_dialog;
        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_create_new_view") == 0)
            callback_function = sig_create_new_view;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_change_friend_color") == 0)
            callback_function = sig_change_friend_color;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_hello") == 0)
            callback_function = sig_hello;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_color_btn_friend_bg_color") == 0)
            callback_function = sig_color_btn_friend_bg_color;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_color_btn_friend_color") == 0)
            callback_function = sig_color_btn_friend_color;

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_tree_widget_type") == 0)
            callback_function = sig_tree_widget_type;
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

        case SIG_ON_COLOR_SET:
            g_signal_connect(G_OBJECT(view->widget), "color-set", G_CALLBACK(callback_function), (ParamNode *)view->view_config->param);
            break;

        default:
            // Handle SIG_NONE or unknown signals if necessary
            g_print("\nError signale type %d not found.", view->view_config->signal.event_type);
            break;
        }
    }
}
