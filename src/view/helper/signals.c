#include "./../../../include/builder.h"
#include "./../../../include/widgets/view/signals.h"
#include "./../../../include/widgets/view/view.h"
#include "./create_new_widget_from_dialog.h"

static View *parent_view = NULL;
static gboolean is_relative_container = TRUE;

static gboolean update_mode = FALSE;

/**
 * @brief structure for handle signales parametres
 * //todo variable: checck if on_cllick signal activate or not and also for other signales
 */
typedef struct
{
    gchar params[PARAM_COUNT][MAX_SIGNAL_NAME_SIZE]; // First function parameter

} ParamNode;

void print_graph_to_debug(View *root)
{
    if (!root)
        return;

    if (root->parent)
        g_print("WIDGET: ===> %s => PARENT ==> %s\n", root->view_config->view_id, root->parent->view_config->view_id);
    else
        g_print("WIDGET: ===> %s => PARENT ==> ROOT\n", root->view_config->view_id);
    if (root->next)
        g_print("Has next: %s\n", root->next->view_config->view_id);
    if (root->child)
        g_print("Has child: %s\n", root->child->view_config->view_id);
    print_graph_to_debug(root->child);
    print_graph_to_debug(root->next);
}

// debug for test

gboolean sig_hello(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
    g_print("\nsignale: hello\n");
    // print_graph_to_debug(root_view_global);
    // if (event->type == GDK_BUTTON_PRESS)
    // {
    //     g_print("Label clicked! Button %d at (%.2f, %.2f)\n",
    //             event->button, event->x, event->y);
    //     // Return TRUE to indicate the event was handled.
    //     return TRUE;
    // }
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

static void sig_generate_xml(GtkWidget *widget, gpointer data)
{
    build_xml("file.xml");
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

// Show dialog from xml file
static void sig_dialog(GtkWidget *widget, gpointer data)
{
    build_app(root_app, NULL, DIALOG_TXT);
    GtkWidget *dialog = root_dialog_view_global->widget;

    show_dialog(dialog);
}

// Set view config from the dialog
static void sig_properties_dialog(GtkWidget *widget, gpointer data)
{
    ParamNode *param_array = (ParamNode *)data;
    if (!param_array)
    {
        g_print("\nError: ==> passing argument.\n");
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
    else if (g_strcmp0(param_array->params[0], "button") == 0)
        build_app(root_app, NULL, BUTTON_PROPERTIES_DIALOG_TXT);

    GtkWidget *dialog = root_dialog_view_global->widget;

    show_dialog(dialog);
}

// TODO: Complete is_relative_container constraint later
static void remove_widget_from_graph(GtkWidget *widget, gpointer data)
{
    const gchar *view_id = gtk_button_get_label(GTK_BUTTON(widget));
    View *target = find_view_by_id((gchar *)view_id, root_view_global);
    View *temp = NULL;

    if (target)
    {
        temp = target->parent;

        g_print("TEMP: %s\n", temp->view_config->view_id);
        if (g_strcmp0(temp->child->view_config->view_id, view_id) == 0)
        {
            g_print("REMOVE CHILD\n");
            // TODO: remove the child
            temp->child = temp->child->next;
        }
        else
        {
            g_print("REMOVE BROTHER\n");
            // TODO: Search the previous of the trget and remove it
            temp = temp->child;
            while (temp->next)
            {
                if (g_strcmp0(temp->next->view_config->view_id, view_id) == 0)
                {
                    temp->next = temp->next->next;
                    break;
                }
                else
                    temp = temp->next;
            }
        }
        g_print("CHECK PARENT\n");
        // TODO: if the child is a container the whole sub-graph should be removed
        if (parent_view == target)
        {
            parent_view = temp;
            g_print("PARENT AFTER REMOVE: %s\n", parent_view->view_config->view_id);
        }

        gtk_widget_destroy(target->widget);

        // TODO: Adapte it for each widget
        is_relative_container = TRUE;

        free(target->view_config);
        free(target);
    }

    // gtk_widget_destroy(target->widget);
    gtk_widget_destroy(widget);

    View *root_v = find_view_by_id("viewer", root_view_global);
    print_graph_to_debug(root_v);
}

void set_current_button_config_to_dialog(ButtonConfig *button_config)
{
    // Label
    write_config_value_as_string("label_entry", button_config->label);
    // Width
    write_config_value_as_int("width_spin", button_config->dimensions.width);

    // Height
    write_config_value_as_int("height_spin", button_config->dimensions.height);

    // Margin top
    write_config_value_as_int("margin_top_spin", button_config->margins.top);

    // Margin bottom
    write_config_value_as_int("margin_bottom_spin", button_config->margins.bottom);

    // Margin left
    write_config_value_as_int("margin_left_spin", button_config->margins.start);

    // Margin right
    write_config_value_as_int("margin_right_spin", button_config->margins.end);

    // HAlign
    gchar *halign = NULL;
    switch (button_config->halign)
    {
    case GTK_ALIGN_START:
        halign = "start";
        break;
    case GTK_ALIGN_END:
        halign = "end";
        break;
    case GTK_ALIGN_BASELINE:
        halign = "baseline";
        break;
    case GTK_ALIGN_CENTER:
        halign = "center";
        break;
    default:
        halign = "center";
        break;
    }
    write_config_value_as_string("halign_combo", halign);

    // VAlign
    gchar *valign = NULL;
    switch (button_config->valign)
    {
    case GTK_ALIGN_START:
        valign = "start";
        break;
    case GTK_ALIGN_END:
        valign = "end";
        break;
    case GTK_ALIGN_BASELINE:
        valign = "baseline";
        break;
    case GTK_ALIGN_CENTER:
        valign = "center";
        break;
    default:
        valign = "center";
        break;
    }
    write_config_value_as_string("valign_combo", valign);

    // HExpand
    write_config_value_as_boolean("hexpand_switch", button_config->hexpand);

    // VExpand
    write_config_value_as_boolean("vexpand_switch", button_config->vexpand);

    // Background color
    write_config_value_as_string("bg_color_entry", button_config->bg_color);

    // Text color
    write_config_value_as_string("color_entry", button_config->color);
}

void set_current_view_config_to_dialog(ViewConfig *view_config)
{
    if (!view_config)
        return;
    write_view_config_to_dialog(view_config);
}

static void update_widget_config(GtkWidget *widget, gpointer data)
{

    // TODO: Update widget config
    // Steps:
    // 1 - Get the view id
    // 2 - Find the view by id
    // 3 - Read the current config from the widget
    // 3 - Read new view config from the dialog
    // 4 - Update the view config

    const gchar *view_id = gtk_button_get_label(GTK_BUTTON(widget));
    View *target_view = find_view_by_id((gchar *)view_id, root_view_global);

    GtkWidget *dialog = NULL;

    if (target_view)
    {
        if (GTK_IS_BOX(target_view->widget))
        {
        }
        else if (GTK_IS_BUTTON(target_view->widget))
        {
            ButtonConfig *button_config = read_button_config_from_widget(target_view->widget);
            build_app(root_app, NULL, BUTTON_PROPERTIES_DIALOG_TXT);
            dialog = root_dialog_view_global->widget;
            set_current_button_config_to_dialog(button_config);
            set_current_view_config_to_dialog(target_view->view_config);
        }

        update_mode = TRUE;
        show_dialog(dialog);
    }
}

void add_view_to_content_box(View *view)
{
    ButtonConfig content_btn_config = DEFAULT_BUTTON;
    strcpy(content_btn_config.label, parent_view->view_config->view_id);
    GtkWidget *content_btn = create_button(content_btn_config);

    View *content_box_view = find_view_by_id("content_box", root_view_global);
    if (content_box_view)
    {
        g_print("PARENT-VIEW: %s\n", parent_view->view_config->view_id);
        g_signal_connect(G_OBJECT(content_btn), "clicked", G_CALLBACK(update_widget_config), NULL);
        gtk_box_pack_end(GTK_BOX(content_box_view->widget), content_btn, TRUE, FALSE, 0);
    }
}

// TODO: complete this function with the new logic
void update_button_config()
{
    g_print("UPDATING BUTTON WIDGET\n");
    ButtonConfig button_config = DEFAULT_BUTTON;

    // Label
    const gchar *label = read_config_value_as_string("label_entry");
    strcpy(button_config.label, label);
    // Width
    gint width = read_config_value_as_int("width_spin");
    button_config.dimensions.width = width;

    // Height
    gint height = read_config_value_as_int("height_spin");
    button_config.dimensions.height = height;

    // Margin top
    gint margin_top = read_config_value_as_int("margin_top_spin");
    button_config.margins.top = margin_top;

    // Margin bottom
    gint margin_bottom = read_config_value_as_int("margin_bottom_spin");
    button_config.margins.bottom = margin_bottom;

    // Margin left
    gint margin_left = read_config_value_as_int("margin_left_spin");
    button_config.margins.start = margin_left;

    // Margin right
    gint margin_right = read_config_value_as_int("margin_right_spin");
    button_config.margins.end = margin_right;

    // HAlign
    const gchar *halign = read_config_value_as_string("halign_combo");
    if (stricmp(halign, "start") == 0)
        button_config.halign = GTK_ALIGN_START;
    else if (stricmp(halign, "end") == 0)
        button_config.halign = GTK_ALIGN_END;
    else if (stricmp(halign, "baseline") == 0)
        button_config.halign = GTK_ALIGN_BASELINE;
    else if (stricmp(halign, "center") == 0)
        button_config.halign = GTK_ALIGN_CENTER;

    // VAlign
    const gchar *valign = read_config_value_as_string("valign_combo");
    if (stricmp(valign, "start") == 0)
        button_config.valign = GTK_ALIGN_START;
    else if (stricmp(valign, "end") == 0)
        button_config.valign = GTK_ALIGN_END;
    else if (stricmp(valign, "baseline") == 0)
        button_config.valign = GTK_ALIGN_BASELINE;
    else if (stricmp(valign, "center") == 0)
        button_config.valign = GTK_ALIGN_CENTER;

    // HExpand
    gboolean hexpand = read_config_value_as_boolean("hexpand_switch");
    button_config.hexpand = hexpand;

    // VExpand
    gboolean vexpand = read_config_value_as_boolean("vexpand_switch");
    button_config.vexpand = vexpand;

    // Background color
    const gchar *bg_color = read_config_value_as_string("bg_color_entry");
    strcpy(button_config.bg_color, bg_color);

    // Text color
    const gchar *text_color = read_config_value_as_string("color_entry");
    strcpy(button_config.color, text_color);

    // TODO: FIX THIS LATER (read_button_config_from_dialog() is not working => label gives undefined behavior)
    // ButtonConfig *button_config = read_button_config_from_dialog();

    ViewConfig *view_config = read_view_config_from_dialog();

    g_print("BTN LOOKING FOR %s\n", view_config->view_id);
    View *target_view = find_view_by_id(view_config->view_id, root_view_global);
    if (target_view)
    {
        g_print("BTN FOUND\n");
        g_print("NEW BTN LABEL: %s\n", button_config.label);
        apply_button_config_changes(target_view->widget, button_config);
        target_view->view_config = view_config;
    }
}

static void sig_create_new_view(GtkWidget *widget, gpointer data)
{

    // TODO: Add the new widget to viewer
    // Steps:
    // 1 - Get viewer
    // 2 - Read config from root dialog for each widget
    // 3 - Create the view basing on the config
    // 4 - Add the view a new view graph (or exist one except the main)

    View *viewer = find_view_by_id("viewer", root_view_global);
    if (!viewer)
    {
        g_print("Error: ==> Cannot find the viewer\n");
        return;
    }

    if (!parent_view)
        parent_view = viewer;

    ParamNode *param_array = (ParamNode *)data;
    if (!param_array)
    {
        g_print("Error: ==> passing argument.\n");
        return;
    }

    // Update mode
    if (update_mode)
    {
        g_print("UPDATE MODE\n");
        if (g_strcmp0(param_array->params[0], "box") == 0)
        {
        }
        else if (g_strcmp0(param_array->params[0], "fixed") == 0)
        {
        }
        else if (g_strcmp0(param_array->params[0], "grid") == 0)
        {
        }
        else if (g_strcmp0(param_array->params[0], "paned") == 0)
        {
        }
        else if (g_strcmp0(param_array->params[0], "frame") == 0)
        {
        }
        else if (g_strcmp0(param_array->params[0], "flowbox") == 0)
        {
        }
        else if (g_strcmp0(param_array->params[0], "overlay") == 0)
        {
        }
        else if (g_strcmp0(param_array->params[0], "notebook") == 0)
        {
        }
        else if (g_strcmp0(param_array->params[0], "button") == 0)
        {
            update_button_config();
        }

        update_mode = FALSE;
    }
    else // Create mode
    {

        g_print("NORMAL MODE\n");
        if (g_strcmp0(param_array->params[0], "box") == 0)
        {
            parent_view = create_new_box_from_dialog(parent_view, is_relative_container);
            is_relative_container = TRUE;
            g_print("PARENT VIEW AFTER ===============> %s \n", parent_view->view_config->view_id);
        }
        else if (g_strcmp0(param_array->params[0], "fixed") == 0)
        {
        }

        else if (g_strcmp0(param_array->params[0], "frame") == 0)
        {
        }
        else if (g_strcmp0(param_array->params[0], "grid") == 0)
        {
        }
        else if (g_strcmp0(param_array->params[0], "paned") == 0)
        {
        }
        else if (g_strcmp0(param_array->params[0], "flowbox") == 0)
        {
        }
        else if (g_strcmp0(param_array->params[0], "overlay") == 0)
        {
        }
        else if (g_strcmp0(param_array->params[0], "notebook") == 0)
        {
        }
        else if (g_strcmp0(param_array->params[0], "button") == 0)
        {
            parent_view = create_new_button_from_dialog(parent_view, is_relative_container);
            is_relative_container = FALSE;
            g_print("PARENT VIEW AFTER ===============> %s \n", parent_view->view_config->view_id);
        }

        // Add to content box
        add_view_to_content_box(parent_view);

        // Update the viewer
        gtk_widget_show_all(root_view_global->widget);
    }
    g_print("PARENT ==========> %s \n", parent_view->parent->view_config->view_id);

    sig_destroy_dialog(widget, NULL);
}

void connect_signals(View *view)
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

        else if (strcmp(view->view_config->signal.sig_handler,
                        "sig_generate_xml") == 0)
            callback_function = sig_generate_xml;
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
