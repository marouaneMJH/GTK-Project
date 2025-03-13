#include "./../../../include/builder.h"
#include "./../../../include/widgets/view/signals.h"
#include "./../../../include/widgets/view/view.h"
#include "./create_new_widget_from_dialog.h"
#include "./../../../include/widgets/View/widget_update.h"

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

// This function check if the previous widget is a container or not
gboolean check_relative_container(GtkWidget *widget)
{
    if (GTK_IS_BOX(widget) ||
        GTK_IS_FIXED(widget) ||
        GTK_IS_FRAME(widget) ||
        GTK_IS_SCROLLED_WINDOW(widget) ||
        GTK_IS_FLOW_BOX(widget) ||
        GTK_IS_OVERLAY(widget) ||
        GTK_IS_GRID(widget) ||
        GTK_IS_PANED(widget) ||
        GTK_IS_STACK(widget) ||
        GTK_IS_NOTEBOOK(widget) ||
        GTK_IS_MENU_BAR(widget) ||
        // GTK_IS_MENU_ITEM(widget) ||
        GTK_IS_MENU(widget))
        return TRUE;
    return FALSE;
}

void display_available_scopes_in_combo(GtkWidget *scope_combo, View *current)
{
    static gboolean is_menu_bar = FALSE;
    if (!current)
    {
        current = find_view_by_id("viewer", root_view_global);
        if (!current)
        {
            g_print("Error: ==> cannot find viewer\n");
            return;
        }

        if (stricmp(current->view_config->view_id, "viewer") == 0)
            current = current->child;

        if (!current)
            return;
    }

    if (GTK_IS_MENU_BAR(current))
        is_menu_bar = TRUE;

    g_print("PARENT SCOPE: %s\n", current->view_config->view_id);
    if (check_relative_container(current->widget) || GTK_IS_MENU_ITEM(current->widget))
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(scope_combo), current->view_config->view_id);

    if (is_menu_bar && !(GTK_IS_MENU_BAR(current->widget) || GTK_IS_MENU(current->widget) || GTK_IS_MENU_ITEM(current->widget)))
    {
        is_menu_bar = FALSE;
        return;
    }

    if (current->child)
        display_available_scopes_in_combo(scope_combo, current->child);
    if (current->next)
        display_available_scopes_in_combo(scope_combo, current->next);
}

void set_available_scopes(const gchar *widget_type)
{
    View *scope_combo = find_view_by_id("scope_back_combo", root_dialog_view_global);
    if (!scope_combo)
    {
        g_print("Error: ==> cannot find scop_back_combo\n");
        return;
    }

    GtkWidget *combo_text_box = scope_combo->widget;

    if (!parent_view)
    {
        // gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_text_box), "Default");
        // gtk_combo_box_set_active(GTK_COMBO_BOX(combo_text_box), 0);
        g_print("First element has no scope back\n");
        return;
    }

    View *temp = parent_view;
    g_print("WIDGET TYPE: %s\n", widget_type);

    // const gchar *current_scope = g_strconcat(parent_view->view_config->view_id, " (Default)", NULL);
    // g_print("CURENT SCOPE: %s\n", current_scope);
    // gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_text_box), current_scope);
    // gtk_combo_box_set_active(GTK_COMBO_BOX(combo_text_box), 0);
    if (stricmp(widget_type, "menu_item") == 0 || stricmp(widget_type, "menu") == 0)
    {
        while (!GTK_IS_MENU_BAR(temp->widget))
            temp = temp->parent;
        display_available_scopes_in_combo(combo_text_box, temp);
    }
    else
        display_available_scopes_in_combo(combo_text_box, NULL);
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
    else if (g_strcmp0(param_array->params[0], "flow_box") == 0)
        build_app(root_app, NULL, FLOW_BOX_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "frame") == 0)
        build_app(root_app, NULL, FRAME_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "grid") == 0)
        build_app(root_app, NULL, GRID_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "notebook") == 0)
        build_app(root_app, NULL, NOTEBOOK_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "overlay") == 0)
        build_app(root_app, NULL, OVERLAY_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "paned") == 0)
        build_app(root_app, NULL, PANED_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "stack") == 0)
        build_app(root_app, NULL, STACK_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "scrolled_window") == 0)
        build_app(root_app, NULL, SCROLLED_WINDOW_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "button") == 0)
        build_app(root_app, NULL, BUTTON_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "check_button") == 0)
        build_app(root_app, NULL, CHECK_BUTTON_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "color_button") == 0)
        build_app(root_app, NULL, COLOR_BUTTON_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "link_button") == 0)
        build_app(root_app, NULL, LINK_BUTTON_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "radio_button") == 0)
        build_app(root_app, NULL, RADIO_BUTTON_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "spin_button") == 0)
        build_app(root_app, NULL, SPIN_BUTTON_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "switch_button") == 0)
        build_app(root_app, NULL, SWITCH_BUTTON_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "toggle_button") == 0)
        build_app(root_app, NULL, TOGGLE_BUTTON_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "menu_bar") == 0)
        build_app(root_app, NULL, MENU_BAR_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "menu_item") == 0)
        build_app(root_app, NULL, MENU_ITEM_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "menu") == 0)
        build_app(root_app, NULL, MENU_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "entry") == 0)
        build_app(root_app, NULL, ENTRY_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "image") == 0)
        build_app(root_app, NULL, IMAGE_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "label") == 0)
        build_app(root_app, NULL, LABEL_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "progress_bar") == 0)
        build_app(root_app, NULL, PROGRESS_BAR_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "separator") == 0)
        build_app(root_app, NULL, SEPARATOR_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "text_area") == 0)
        build_app(root_app, NULL, TEXT_AREA_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "combo_text_box") == 0)
        build_app(root_app, NULL, COMBO_TEXT_BOX_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "event_box") == 0)
        build_app(root_app, NULL, EVENT_BOX_PROPERTIES_DIALOG_TXT);
    else if (g_strcmp0(param_array->params[0], "expander") == 0)
        build_app(root_app, NULL, EXPANDER_PROPERTIES_DIALOG_TXT);
    // else if (g_strcmp0(param_array->params[0], "list_box") == 0)
    //     build_app(root_app, NULL, LIST_BOX_PROPERTIES_DIALOG_TXT);

    GtkWidget *dialog = root_dialog_view_global->widget;

    set_available_scopes(param_array->params[0]);

    show_dialog(dialog);
}

void destroy_subgraph(View *root)
{
    if (root->next)
        destroy_subgraph(root->next);
    if (root->child)
        destroy_subgraph(root->child);

    gtk_widget_destroy(root->widget);
    g_free(root->view_config);
    g_free(root);
}

// This function check the scope before insert a new element for example MenuItem with Menu or MenuBar
gboolean check_scope_back(View *root)
{
    const gchar *scope_back = read_config_value_as_string("scope_back_combo");

    g_print("SCOPE BACK: %s\n", scope_back);

    // If it is the default one don't change anything
    if (stricmp(scope_back, "Default") == 0)
        return TRUE;

    // check the root if it is fixed on the viewer at the first time or not
    if (!root)
    {
        root = find_view_by_id("viewer", root_view_global);
        if (!root)
        {
            g_print("Error: ==> cannot find the viewer");
            return FALSE;
        }
    }

    g_print("TRACE MI: %s \n", root->view_config->view_id);

    // If I didn't found the scope target yet
    if (stricmp(root->parent->view_config->view_id, scope_back) != 0)
    {
        // Menu item case
        if (!root->child && GTK_IS_MENU_ITEM(root->widget) && stricmp(root->view_config->view_id, scope_back) == 0)
        {
            parent_view = root;
            is_relative_container = TRUE;
            return TRUE;
        }

        gboolean result = FALSE;
        if (root->next)
            result = check_scope_back(root->next);

        if (root->child && !result)
            result = check_scope_back(root->child);

        if (stricmp(root->view_config->view_id, scope_back) == 0 && !result)
        {
            parent_view = root;
            is_relative_container = TRUE;
            if (root)
            {
                g_print("I FOUND THE NEW PARENT FIRST VIEW %s\n", parent_view->view_config->view_id);
            }
            return TRUE;
        }
    }
    else
    {
        while (root->next)
            root = root->next;

        parent_view = root;
        is_relative_container = FALSE;

        if (root)
        {
            g_print("I FOUND THE NEW PARENT VIEW %s\n", parent_view->view_config->view_id);
        }
        return TRUE;
    }
    return FALSE;
}

// Remove a widget from the graph and the subgraph if exists
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
            // remove the child
            temp->child = temp->child->next;
        }
        else
        {
            g_print("REMOVE BROTHER\n");
            // Search the previous of the trget and remove it
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
        if (parent_view == target || check_relative_container(temp->widget))
        {
            parent_view = temp;
            is_relative_container = check_relative_container(parent_view->widget);
            g_print("PARENT AFTER REMOVE: %s\n", parent_view->view_config->view_id);
        }

        if (target->child)
            destroy_subgraph(target->child);
        gtk_widget_destroy(target->widget);

        free(target->view_config);
        free(target);
    }

    // gtk_widget_destroy(target->widget);
    gtk_widget_destroy(widget);

    View *root_v = find_view_by_id("viewer", root_view_global);
    print_graph_to_debug(root_v);
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

    if (!target_view)
    {
        g_print("TARGET IS NOT FOUND\n");
        return;
    }

    if (GTK_IS_BOX(target_view->widget))
    {
        dialog = prepare_update_box_config(target_view);
    }
    else if (GTK_IS_SCROLLED_WINDOW(target_view->widget))
    {
        dialog = prepare_update_scrolled_window_config(target_view);
    }
    else if (GTK_IS_FIXED(target_view->widget))
    {
        dialog = prepare_update_fixed_config(target_view);
    }
    else if (GTK_IS_FLOW_BOX(target_view->widget))
    {
        dialog = prepare_update_flow_box_config(target_view);
    }
    else if (GTK_IS_FRAME(target_view->widget))
    {
        dialog = prepare_update_frame_config(target_view);
    }
    else if (GTK_IS_GRID(target_view->widget))
    {
        dialog = prepare_update_grid_config(target_view);
    }
    else if (GTK_IS_NOTEBOOK(target_view->widget))
    {
        dialog = prepare_update_notebook_config(target_view);
    }
    else if (GTK_IS_OVERLAY(target_view->widget))
    {
        dialog = prepare_update_overlay_config(target_view);
    }
    else if (GTK_IS_PANED(target_view->widget))
    {
        dialog = prepare_update_paned_config(target_view);
    }
    else if (GTK_IS_STACK(target_view->widget))
    {
        dialog = prepare_update_stack_config(target_view);
    }
    else if (GTK_IS_CHECK_BUTTON(target_view->widget) && !GTK_IS_RADIO_BUTTON(target_view->widget))
    {
        dialog = prepare_update_check_button_config(target_view);
    }
    else if (GTK_IS_COLOR_BUTTON(target_view->widget) && !GTK_IS_LINK_BUTTON(target_view->widget))
    {
        dialog = prepare_update_color_button_config(target_view);
    }
    else if (GTK_IS_LINK_BUTTON(target_view->widget) && !GTK_IS_COLOR_BUTTON(target_view->widget))
    {
        dialog = prepare_update_link_button_config(target_view);
    }
    else if (GTK_IS_RADIO_BUTTON(target_view->widget))
    {
        dialog = prepare_update_radio_button_config(target_view);
    }
    else if (GTK_IS_SPIN_BUTTON(target_view->widget) && !GTK_IS_COLOR_BUTTON(target_view->widget) && !GTK_IS_SWITCH(target_view->widget))
    {
        dialog = prepare_update_spin_button_config(target_view);
    }
    else if (GTK_IS_SWITCH(target_view->widget) && !GTK_IS_TOGGLE_BUTTON(target_view->widget))
    {
        dialog = prepare_update_switch_button_config(target_view);
    }
    else if (GTK_IS_BUTTON(target_view->widget) && !GTK_IS_TOGGLE_BUTTON(target_view->widget))
    {
        dialog = prepare_update_button_config(target_view);
    }
    else if (GTK_IS_TOGGLE_BUTTON(target_view->widget))
    {
        g_print("TOGGLE PREP\n");
        dialog = prepare_update_toggle_button_config(target_view);
    }
    else if (GTK_IS_MENU_BAR(target_view->widget))
    {
        dialog = prepare_update_menu_bar_config(target_view);
    }
    else if (GTK_IS_MENU_ITEM(target_view->widget))
    {
        dialog = prepare_update_menu_item_config(target_view);
    }
    else if (GTK_IS_MENU(target_view->widget))
    {
        dialog = prepare_update_menu_config(target_view);
    }
    else if (GTK_IS_ENTRY(target_view->widget))
    {
        dialog = prepare_update_entry_config(target_view);
    }
    else if (GTK_IS_IMAGE(target_view->widget))
    {
        dialog = prepare_update_image_config(target_view);
    }
    else if (GTK_IS_LABEL(target_view->widget))
    {
        dialog = prepare_update_label_config(target_view);
    }
    else if (GTK_IS_PROGRESS_BAR(target_view->widget))
    {
        dialog = prepare_update_progress_bar_config(target_view);
    }
    else if (GTK_IS_SEPARATOR(target_view->widget))
    {
        dialog = prepare_update_separator_config(target_view);
    }
    else if (GTK_IS_TEXT_VIEW(target_view->widget))
    {
        // dialog = prepare_update_text_area_config(target_view);
    }
    else if (GTK_IS_COMBO_BOX_TEXT(target_view->widget))
    {
        // dialog = prepare_update_combo_text_box_config(target_view);
    }

    update_mode = TRUE;
    if (dialog)
        show_dialog(dialog);
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
        // g_signal_connect(G_OBJECT(content_btn), "clicked", G_CALLBACK(remove_widget_from_graph), NULL);
        gtk_box_pack_end(GTK_BOX(content_box_view->widget), content_btn, TRUE, FALSE, 0);
    }
}

static void sig_create_new_view(GtkWidget *widget, gpointer data)
{
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

    if (update_mode)
    {
        g_print("UPDATE MODE\n");
        if (g_strcmp0(param_array->params[0], "scrolled_window") == 0)
        {
            parent_view = update_scrolled_window_config();
        }
        else if (g_strcmp0(param_array->params[0], "box") == 0)
        {
            parent_view = update_box_config();
        }
        else if (g_strcmp0(param_array->params[0], "fixed") == 0)
        {
            parent_view = update_fixed_config();
        }
        else if (g_strcmp0(param_array->params[0], "box") == 0)
        {
            parent_view = update_box_config();
        }
        else if (g_strcmp0(param_array->params[0], "fixed") == 0)
        {
            parent_view = update_fixed_config();
        }
        else if (g_strcmp0(param_array->params[0], "flow_box") == 0)
        {
            parent_view = update_flow_box_config();
        }
        else if (g_strcmp0(param_array->params[0], "frame") == 0)
        {
            parent_view = update_frame_config();
        }
        else if (g_strcmp0(param_array->params[0], "grid") == 0)
        {
            parent_view = update_grid_config();
        }
        else if (g_strcmp0(param_array->params[0], "notebook") == 0)
        {
            parent_view = update_notebook_config();
        }
        else if (g_strcmp0(param_array->params[0], "overlay") == 0)
        {
            parent_view = update_overlay_config();
        }
        else if (g_strcmp0(param_array->params[0], "paned") == 0)
        {
            parent_view = update_paned_config();
        }
        else if (g_strcmp0(param_array->params[0], "stack") == 0)
        {
            parent_view = update_stack_config();
        }
        else if (g_strcmp0(param_array->params[0], "button") == 0)
        {
            parent_view = update_button_config();
        }
        else if (g_strcmp0(param_array->params[0], "check_button") == 0)
        {
            parent_view = update_check_button_config();
        }
        else if (g_strcmp0(param_array->params[0], "color_button") == 0)
        {
            parent_view = update_color_button_config();
        }
        else if (g_strcmp0(param_array->params[0], "link_button") == 0)
        {
            parent_view = update_link_button_config();
        }
        else if (g_strcmp0(param_array->params[0], "radio_button") == 0)
        {
            parent_view = update_radio_button_config();
        }
        else if (g_strcmp0(param_array->params[0], "spin_button") == 0)
        {
            parent_view = update_spin_button_config();
        }
        else if (g_strcmp0(param_array->params[0], "switch_button") == 0)
        {
            parent_view = update_switch_button_config();
        }
        else if (g_strcmp0(param_array->params[0], "toggle_button") == 0)
        {
            parent_view = update_toggle_button_config();
        }
        else if (g_strcmp0(param_array->params[0], "menu_bar") == 0)
        {
            parent_view = update_menu_bar_config();
        }
        else if (g_strcmp0(param_array->params[0], "menu_item") == 0)
        {
            parent_view = update_menu_item_config();
        }
        else if (g_strcmp0(param_array->params[0], "menu") == 0)
        {
            parent_view = update_menu_config();
        }
        else if (g_strcmp0(param_array->params[0], "entry") == 0)
        {
            parent_view = update_entry_config();
        }
        else if (g_strcmp0(param_array->params[0], "image") == 0)
        {
            parent_view = update_image_config();
        }
        else if (g_strcmp0(param_array->params[0], "label") == 0)
        {
            parent_view = update_label_config();
        }
        else if (g_strcmp0(param_array->params[0], "progress_bar") == 0)
        {
            parent_view = update_progress_bar_config();
        }
        else if (g_strcmp0(param_array->params[0], "separator") == 0)
        {
            parent_view = update_separator_config();
        }
        else if (g_strcmp0(param_array->params[0], "text_area") == 0)
        {
            // parent_view = update_text_area_config();
        }
        else if (g_strcmp0(param_array->params[0], "combo_text_box") == 0)
        {
            // parent_view = update_combo_text_box_config();
        }
        update_mode = FALSE;
    }
    else
    {
        g_print("NORMAL MODE\n");
        g_print("PARENT BEFORE ==========> %s \n", parent_view->view_config->view_id);
        check_scope_back(viewer);
        g_print("PARENT AFTER CHECK ==========> %s \n", parent_view->view_config->view_id);
        if (g_strcmp0(param_array->params[0], "box") == 0)
        {
            parent_view = create_new_box_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "scrolled_window") == 0)
        {
            parent_view = create_new_scrolled_window_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "fixed") == 0)
        {
            parent_view = create_new_fixed_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "flow_box") == 0)
        {
            parent_view = create_new_flow_box_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "frame") == 0)
        {
            parent_view = create_new_frame_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "grid") == 0)
        {
            parent_view = create_new_grid_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "notebook") == 0)
        {
            parent_view = create_new_notebook_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "overlay") == 0)
        {
            parent_view = create_new_overlay_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "paned") == 0)
        {
            parent_view = create_new_paned_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "stack") == 0)
        {
            parent_view = create_new_stack_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "button") == 0)
        {
            parent_view = create_new_button_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "check_button") == 0)
        {
            parent_view = create_new_check_button_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "color_button") == 0)
        {
            parent_view = create_new_color_button_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "link_button") == 0)
        {
            parent_view = create_new_link_button_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "radio_button") == 0)
        {
            parent_view = create_new_radio_button_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "spin_button") == 0)
        {
            parent_view = create_new_spin_button_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "switch_button") == 0)
        {
            parent_view = create_new_switch_button_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "toggle_button") == 0)
        {
            parent_view = create_new_toggle_button_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "menu_bar") == 0)
        {
            parent_view = create_new_menu_bar_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "menu_item") == 0)
        {
            parent_view = create_new_menu_item_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "menu") == 0)
        {
            parent_view = create_new_menu_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "entry") == 0)
        {
            parent_view = create_new_entry_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "image") == 0)
        {
            parent_view = create_new_image_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "label") == 0)
        {
            parent_view = create_new_label_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "progress_bar") == 0)
        {
            parent_view = create_new_progress_bar_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "separator") == 0)
        {
            parent_view = create_new_separator_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "text_area") == 0)
        {
            parent_view = create_new_text_area_from_dialog(parent_view, is_relative_container);
        }
        else if (g_strcmp0(param_array->params[0], "combo_text_box") == 0)
        {
            parent_view = create_new_combo_text_box_from_dialog(parent_view, is_relative_container);
        }
        // else if (g_strcmp0(param_array->params[0], "event_box") == 0)
        // {
        //     parent_view = create_new_event_box_from_dialog(parent_view, is_relative_container);
        //     is_relative_container = TRUE;
        // }
        // else if (g_strcmp0(param_array->params[0], "expander") == 0)
        // {
        //     parent_view = create_new_expander_from_dialog(parent_view, is_relative_container);
        //     is_relative_container = TRUE;
        // }
        // print_graph_to_debug(viewer);
        add_view_to_content_box(parent_view);
        gtk_widget_show_all(root_view_global->widget);
    }

    is_relative_container = check_relative_container(parent_view->widget);

    if (GTK_IS_MENU_ITEM(parent_view->widget))
    {
        // Menu item case
        gboolean has_submenu = read_config_value_as_boolean("has_submenu_switch");
        if (has_submenu)
            is_relative_container = TRUE;
    }
    g_print("PARENT VIEW AFTER ==========> %s \n", parent_view->view_config->view_id);
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
