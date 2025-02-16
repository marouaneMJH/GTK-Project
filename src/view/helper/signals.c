#include "./../../../include/builder.h"
#include "./../../../include/widgets/view/signals.h"
#include "./../../../include/widgets/view/view.h"

/**
 * @brief structure for handle signales parametres
 * //todo variable: checck if on_cllick signal activate or not and also for other signales
 */
typedef struct
{
    gchar params[PARAM_COUNT][MAX_SIGNAL_NAME_SIZE]; // First function parameter

} ParamNode;

// for test
static void sig_hello(GtkWidget *widget, gpointer data)
{
    g_print("\nsignale: hello\n");
}

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

void show_img()
{
    // Set up dialog configuration
    DialogConfig dialog_config = DEFAULT_DIALOG;
    strcpy(dialog_config.title, "Image Viewer");

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
    strcpy(image_config.path, "./assets/images/smale/img1.jpg");
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
        show_img();
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
    gtk_color_button_get_rgba(GTK_COLOR_BUTTON(widget), &bg_color);

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
    gtk_color_button_get_rgba(GTK_COLOR_BUTTON(widget), &bg_color);

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
    else if (g_strcmp0(param_array->params[0], "button") == 0)
        build_app(root_app, NULL, BUTTON_PROPERTIES_DIALOG_TXT);

    GtkWidget *dialog = root_dialog_view_global->widget;

    show_dialog(dialog);
}

// Readers
gchar *read_config_value_as_string(gchar *view_id)
{
    View *input_view = find_view_by_id(view_id, root_dialog_view_global);
    if (!input_view)
    {
        g_print("Error: ==> Cannot find the %s\n", view_id);
        return NULL;
    }
    if (GTK_IS_COMBO_BOX(input_view->widget))
        return gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(input_view->widget));
    else if (GTK_IS_ENTRY(input_view->widget))
        return gtk_entry_get_text(GTK_ENTRY(input_view->widget));
    g_print("Error: => Widget type not compatible with the expected value\n");
    return NULL;
}

gint read_config_value_as_int(gchar *view_id)
{
    View *input_view = find_view_by_id(view_id, root_dialog_view_global);
    if (!input_view)
    {
        g_print("Error: ==> Cannot find the %s\n", view_id);
        return 0;
    }
    if (GTK_IS_SPIN_BUTTON(input_view->widget))
        return gtk_spin_button_get_value(GTK_SPIN_BUTTON(input_view->widget));

    g_print("Error: => Widget type not compatible with the expected value\n");
    return 0;
}

gdouble read_config_value_as_double(gchar *view_id)
{
    View *input_view = find_view_by_id(view_id, root_dialog_view_global);
    if (!input_view)
    {
        g_print("Error: ==> Cannot find the %s\n", view_id);
        return 0;
    }
    if (GTK_IS_SPIN_BUTTON(input_view->widget))
        return gtk_spin_button_get_value(GTK_SPIN_BUTTON(input_view->widget));

    g_print("Error: => Widget type not compatible with the expected value\n");
    return 0;
}

gboolean read_config_value_as_boolean(gchar *view_id)
{
    View *input_view = find_view_by_id(view_id, root_dialog_view_global);
    if (!input_view)
    {
        g_print("Error: ==> Cannot find the %s\n", view_id);
        return false;
    }
    if (GTK_IS_SWITCH(input_view->widget))
        return gtk_switch_get_active(GTK_SWITCH(input_view->widget));

    g_print("Error: => Widget type not compatible with the expected value\n");
    return false;
}

// Create a new box view config dynamically
View *create_new_box_from_dialog(View *parent_view, gboolean is_relative_container)
{
    BoxConfig button_config = DEFAULT_BOX;

    // Orientation
    gchar *selected_orientation = read_config_value_as_string("orientation_combo");
    g_print("SELECTED ORIENTATION: ===> %s \n", selected_orientation);
    if (stricmp(selected_orientation, "horizontal") == 0)
        button_config.orientation = GTK_ORIENTATION_HORIZONTAL;

    // Spacing
    gint spacing = read_config_value_as_int("spacing_spin");
    g_print("SELECTED SPACING: ===> %d \n", spacing);
    button_config.spacing = spacing;

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

    // Baseline
    gchar *baseline = read_config_value_as_string("baseline_combo");
    if (stricmp(selected_orientation, "top") == 0)
        button_config.baseline_position = GTK_BASELINE_POSITION_TOP;
    else if (stricmp(selected_orientation, "bottom") == 0)
        button_config.baseline_position = GTK_BASELINE_POSITION_BOTTOM;

    // HAlign
    gchar *halign = read_config_value_as_string("halign_combo");
    if (stricmp(halign, "start") == 0)
        button_config.halign = GTK_ALIGN_START;
    else if (stricmp(halign, "end") == 0)
        button_config.halign = GTK_ALIGN_END;
    else if (stricmp(halign, "baseline") == 0)
        button_config.halign = GTK_ALIGN_BASELINE;
    else if (stricmp(halign, "center") == 0)
        button_config.halign = GTK_ALIGN_CENTER;

    // VAlign
    gchar *valign = read_config_value_as_string("valign_combo");
    if (stricmp(valign, "start") == 0)
        button_config.valign = GTK_ALIGN_START;
    else if (stricmp(valign, "end") == 0)
        button_config.valign = GTK_ALIGN_END;
    else if (stricmp(valign, "baseline") == 0)
        button_config.valign = GTK_ALIGN_BASELINE;
    else if (stricmp(valign, "center") == 0)
        button_config.valign = GTK_ALIGN_CENTER;

    // Homogeneous
    gboolean homogeneous = read_config_value_as_boolean("homogeneous_switch");
    button_config.homogeneous = homogeneous;

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
    strcpy(button_config.text_color, text_color);

    // Background image
    const gchar *bg_image = read_config_value_as_string("bg_image_entry");
    strcpy(button_config.bg_image, bg_image);

    GtkWidget *new_box = create_box(button_config);

    // View config
    ViewConfig *view_config = NULL;
    SAFE_ALLOC(view_config, ViewConfig, 1);
    DFEAULT_VIEW_CONFIG(view_config);

    gchar *view_id = read_config_value_as_string("view_id_entry");
    strcpy(view_config->view_id, view_id);

    // Box config
    gboolean box_expand = read_config_value_as_boolean("box_expand_switch");
    view_config->box_expand = box_expand;

    gboolean box_fill = read_config_value_as_boolean("box_fill_switch");
    view_config->box_fill = box_fill;

    gint box_padding = read_config_value_as_int("box_padding_spin");
    view_config->box_padding = box_padding;

    gchar *pack_direction = read_config_value_as_string("pack_direction_combo");
    if (stricmp(pack_direction, "end") == 0)
        view_config->pack_direction = 0;
    else
        view_config->pack_direction = 1;

    // Fixed config
    gint position = read_config_value_as_int("position_x_spin");
    view_config->position_x = position;
    position = read_config_value_as_int("position_y_spin");
    view_config->position_y = position;

    // TODO: Complete other view config properties

    // Signals config
    // OnClick
    gchar *sig_on_click_handler = read_config_value_as_string("on_click_entry");
    view_config->signal.event_type = SIG_ON_BUTTON_PRESS;
    g_strlcpy(view_config->signal.sig_handler, sig_on_click_handler, MAX_SIGNAL_NAME_SIZE);

    View *new_box_view = create_view(new_box, view_config);

    g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
    add_view(new_box_view, parent_view, is_relative_container);

    return new_box_view;
}

// Create a new button view config dynamically
View *create_new_button_from_dialog(View *parent_view, gboolean is_relative_container)
{
    ButtonConfig button_config = DEFAULT_BUTTON;

    // Label
    gchar *label = read_config_value_as_string("label_entry");
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
    gchar *halign = read_config_value_as_string("halign_combo");
    if (stricmp(halign, "start") == 0)
        button_config.halign = GTK_ALIGN_START;
    else if (stricmp(halign, "end") == 0)
        button_config.halign = GTK_ALIGN_END;
    else if (stricmp(halign, "baseline") == 0)
        button_config.halign = GTK_ALIGN_BASELINE;
    else if (stricmp(halign, "center") == 0)
        button_config.halign = GTK_ALIGN_CENTER;

    // VAlign
    gchar *valign = read_config_value_as_string("valign_combo");
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

    GtkWidget *new_button = create_button(button_config);

    // View config
    ViewConfig *view_config = NULL;
    SAFE_ALLOC(view_config, ViewConfig, 1);
    DFEAULT_VIEW_CONFIG(view_config);

    gchar *view_id = read_config_value_as_string("view_id_entry");
    strcpy(view_config->view_id, view_id);

    // Box config
    gboolean box_expand = read_config_value_as_boolean("box_expand_switch");
    view_config->box_expand = box_expand;

    gboolean box_fill = read_config_value_as_boolean("box_fill_switch");
    view_config->box_fill = box_fill;

    gint box_padding = read_config_value_as_int("box_padding_spin");
    view_config->box_padding = box_padding;

    gchar *pack_direction = read_config_value_as_string("pack_direction_combo");
    if (stricmp(pack_direction, "end") == 0)
        view_config->pack_direction = 0;
    else
        view_config->pack_direction = 1;

    // Fixed config
    gint position = read_config_value_as_int("position_x_spin");
    view_config->position_x = position;
    position = read_config_value_as_int("position_y_spin");
    view_config->position_y = position;

    // TODO: Complete other view config properties

    // Signals config
    // OnClick
    gchar *sig_on_click_handler = read_config_value_as_string("on_click_entry");
    view_config->signal.event_type = SIG_ON_CLICK;
    g_strlcpy(view_config->signal.sig_handler, sig_on_click_handler, MAX_SIGNAL_NAME_SIZE);

    View *new_button_view = create_view(new_button, view_config);

    g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
    
    add_view(new_button_view, parent_view, is_relative_container);

    return new_button_view;
}

static void sig_create_new_view(GtkWidget *widget, gpointer data)
{

    static View *parent_view = NULL;
    static gboolean is_relative_container = TRUE;

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

    if (g_strcmp0(param_array->params[0], "box") == 0)
    {
        parent_view = create_new_box_from_dialog(parent_view, is_relative_container);
        is_relative_container = TRUE;
        g_print("PARENT VIEW AFTER ===============> %s \n", parent_view->view_config->view_id);
        gtk_widget_show_all(root_view_global->widget);
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
    else if (g_strcmp0(param_array->params[0], "button") == 0)
    {
        parent_view = create_new_button_from_dialog(parent_view, is_relative_container);
        is_relative_container = FALSE;
        gtk_widget_show_all(root_view_global->widget);
    }

    g_print("PARENT ==========> %s \n", parent_view->parent->view_config->view_id);

    sig_destroy_dialog(widget, NULL);
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
