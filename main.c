#include "./include/builder.h"

// Callback function for button click
static void on_button_clicked(GtkButton *button, gpointer user_data)
{
    g_print("Button clicked!\n");
}

// Activate callback for GtkApplication
static void activate(GtkApplication *app, gpointer user_data)
{
    // Create a new window

    View *root_view = build_app(app, root_view);
    GtkWidget *window = root_view->widget;

    // WindowConfig window_config = DEFAULT_WINDOW;
    // g_strlcpy(window_config.title, "Containers testing", MAX_WINDOW_TITLE_SIZE);
    // g_strlcpy(window_config.icon_name, "folder", MAX_ICON_NAME_SIZE);
    // g_strlcpy(window_config.bg_color, "#999999", MAX_COLOR_SIZE);
    // window_config.dimensions.width = 1000;
    // window_config.dimensions.height = 800;
    // GtkWidget *window = create_window(app, window_config);

    // // Create a button
    // GtkWidget *button = gtk_button_new_with_label("Click Me");
    // g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    // BoxConfig box_config = DEFAULT_BOX;
    // g_strlcpy(box_config.bg_color, "#ADD8E6", MAX_COLOR_SIZE);
    // GtkWidget *box = create_box(box_config);

    // gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 3);

    // // Add the button to the window
    // gtk_container_add(GTK_CONTAINER(window), box);

    // Show all widgets
    gtk_widget_show_all(window);
}

// Main function
int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    // Create a new application instance
    app = gtk_application_new("gtk.root.app", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // Run the application
    status = g_application_run(G_APPLICATION(app), argc, argv);

    // Clean up
    g_object_unref(app);

    return status;
}

// #include "./include/index.h"

// // Main activate function
// static void activate(GtkApplication *app, gpointer user_data)
// {
//     WindowConfig window_config = DEFAULT_WINDOW;
//     g_strlcpy(window_config.title, "Containers testing", MAX_WINDOW_TITLE_SIZE);
//     g_strlcpy(window_config.icon_name, "folder", MAX_ICON_NAME_SIZE);
//     g_strlcpy(window_config.bg_color, "#999999", MAX_COLOR_SIZE);
//     window_config.dimensions.width = 1000;
//     window_config.dimensions.height = 800;
//     GtkWidget *window = create_window(app, window_config);

//     ButtonConfig btn_config = DEFAULT_BUTTON;
//     g_strlcpy(btn_config.label, "Button 1", MAX_BUTTON_LABEL_SIZE);
//     GtkWidget *btn1 = create_button(btn_config);

//     g_strlcpy(btn_config.label, "Button 2", MAX_BUTTON_LABEL_SIZE);
//     GtkWidget *btn2 = create_button(btn_config);

//     g_strlcpy(btn_config.label, "Button 3", MAX_BUTTON_LABEL_SIZE);
//     GtkWidget *btn3 = create_button(btn_config);

//     // FlowBox container
//     FlowBoxConfig flow_box_config = DEFAULT_FLOW_BOX;
//     flow_box_config.max_childern_per_line = 1;
//     GtkWidget *flow_box = create_flow_box(flow_box_config);

//     gtk_flow_box_insert(GTK_FLOW_BOX(flow_box), btn1, 0);
//     gtk_flow_box_insert(GTK_FLOW_BOX(flow_box), btn2, 1);
//     gtk_flow_box_insert(GTK_FLOW_BOX(flow_box), btn3, 3);
//     for (int i = 4; i < 6; i++)
//     {
//         g_strlcpy(btn_config.label, g_strdup_printf("Button %d", i), MAX_BUTTON_LABEL_SIZE);
//         GtkWidget *btn = create_button(btn_config);
//         gtk_flow_box_insert(GTK_FLOW_BOX(flow_box), btn, i);
//     }

//     // Grid container
//     GridConfig grid_config = DEFAULT_GRID;
//     GtkWidget *grid = create_grid(grid_config);

//     gtk_grid_insert_row(GTK_GRID(grid), 0);
//     gtk_grid_insert_row(GTK_GRID(grid), 1);
//     gtk_grid_insert_row(GTK_GRID(grid), 2);
//     gtk_grid_insert_column(GTK_GRID(grid), 0);
//     gtk_grid_insert_column(GTK_GRID(grid), 1);

//     CheckButtonConfig check_button_config = DEFAULT_CHECK_BUTTON;
//     g_strlcpy(check_button_config.label, "Check 1", MAX_BUTTON_LABEL_SIZE);
//     GtkWidget *check1 = create_check_button(check_button_config);

//     g_strlcpy(check_button_config.label, "Check 2", MAX_BUTTON_LABEL_SIZE);
//     GtkWidget *check2 = create_check_button(check_button_config);

//     g_strlcpy(btn_config.label, "Button 4", MAX_BUTTON_LABEL_SIZE);
//     GtkWidget *btn4 = create_button(btn_config);

//     g_strlcpy(btn_config.label, "Button 5", MAX_BUTTON_LABEL_SIZE);
//     GtkWidget *btn5 = create_button(btn_config);

//     gtk_grid_attach(GTK_GRID(grid), check1, 0, 0, 1, 1);
//     gtk_grid_attach(GTK_GRID(grid), check2, 1, 0, 1, 1);
//     gtk_grid_attach(GTK_GRID(grid), btn4, 0, 1, 1, 1);
//     gtk_grid_attach(GTK_GRID(grid), btn5, 1, 1, 1, 1);

//     SwitchButtonConfig switch_button_config = DEFAULT_SWITCH_BUTTON;
//     g_strlcpy(switch_button_config.label, "Switch Button", MAX_BUTTON_LABEL_SIZE);
//     GtkWidget *switch_button = create_switch_button(switch_button_config);

//     ProgressBarConfig progress_bar_config = DEFAULT_PROGRESS_BAR;
//     progress_bar_config.progress_fraction = 0.5;
//     GtkWidget *progress_bar = create_progress_bar(progress_bar_config);

//     SeparatorConfig separator_config = DEFAULT_SEPARATOR;
//     separator_config.orientation = GTK_ORIENTATION_HORIZONTAL;
//     GtkWidget *separator = create_separator(separator_config);

//     SpinButtonConfig spin_button_config = DEFAULT_SPIN_BUTTON;
//     spin_button_config.min = 0;
//     spin_button_config.max = 100;
//     spin_button_config.step = 1;
//     GtkWidget *spin_button = create_spin_button(spin_button_config);

//     RadioButtonConfig radio_button_config = DEFAULT_RADIO_BUTTON;
//     g_strlcpy(radio_button_config.label, "Radio Button 1", MAX_BUTTON_LABEL_SIZE);
//     GtkWidget *radio_button1 = create_radio_button(radio_button_config);

//     g_strlcpy(radio_button_config.label, "Radio Button 2", MAX_BUTTON_LABEL_SIZE);
//     GtkWidget *radio_button2 = create_radio_button(radio_button_config);
//     radio_button_set_group(radio_button2, radio_button1);

//     LinkButtonConfig link_button_config = DEFAULT_LINK_BUTTON;
//     g_strlcpy(link_button_config.label, "Link Button", MAX_BUTTON_LABEL_SIZE);
//     g_strlcpy(link_button_config.uri, "https://www.example.com", MAX_URI_SIZE);
//     GtkWidget *link_button = create_link_button(link_button_config);

//     g_strlcpy(check_button_config.label, "Check Button", MAX_BUTTON_LABEL_SIZE);
//     GtkWidget *check_button = create_check_button(check_button_config);

//     EntryConfig entry_config = DEFAULT_ENTRY;
//     g_strlcpy(entry_config.placeholder_text, "Enter text here", MAX_ENTRY_TEXT_SIZE);
//     GtkWidget *entry = create_entry(entry_config);

//     MenuBarConfig menu_bar_config = DEFAULT_MENU_BAR;
//     GtkWidget *menu_bar = create_menu_bar(menu_bar_config);

//     MenuConfig file_menu_config = DEFAULT_MENU;
//     GtkWidget *file_menu = create_menu(file_menu_config);

//     MenuItemConfig new_menu_item_config = DEFAULT_MENU_ITEM;
//     g_strlcpy(new_menu_item_config.label, "New", MAX_LABEL_SIZE);
//     GtkWidget *new_menu_item = create_menu_item(new_menu_item_config);

//     MenuItemConfig open_menu_item_config = DEFAULT_MENU_ITEM;
//     g_strlcpy(open_menu_item_config.label, "Open", MAX_LABEL_SIZE);
//     GtkWidget *open_menu_item = create_menu_item(open_menu_item_config);

//     MenuItemConfig save_menu_item_config = DEFAULT_MENU_ITEM;
//     g_strlcpy(save_menu_item_config.label, "Save", MAX_LABEL_SIZE);
//     GtkWidget *save_menu_item = create_menu_item(save_menu_item_config);

//     MenuItemConfig exit_menu_item_config = DEFAULT_MENU_ITEM;
//     g_strlcpy(exit_menu_item_config.label, "Exit", MAX_LABEL_SIZE);
//     GtkWidget *exit_menu_item = create_menu_item(exit_menu_item_config);

//     gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), new_menu_item);
//     gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_menu_item);
//     gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_menu_item);
//     gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), exit_menu_item);

//     MenuItemConfig file_menu_item_config = DEFAULT_MENU_ITEM;
//     g_strlcpy(file_menu_item_config.label, "File", MAX_LABEL_SIZE);
//     GtkWidget *file_menu_item = create_menu_item(file_menu_item_config);
//     menu_item_set_submenu(file_menu_item, file_menu);

//     gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file_menu_item);

//     MenuConfig edit_menu_config = DEFAULT_MENU;
//     GtkWidget *edit_menu = create_menu(edit_menu_config);

//     MenuItemConfig cut_menu_item_config = DEFAULT_MENU_ITEM;
//     g_strlcpy(cut_menu_item_config.label, "Cut", MAX_LABEL_SIZE);
//     GtkWidget *cut_menu_item = create_menu_item(cut_menu_item_config);

//     MenuItemConfig copy_menu_item_config = DEFAULT_MENU_ITEM;
//     g_strlcpy(copy_menu_item_config.label, "Copy", MAX_LABEL_SIZE);
//     GtkWidget *copy_menu_item = create_menu_item(copy_menu_item_config);

//     MenuItemConfig paste_menu_item_config = DEFAULT_MENU_ITEM;
//     g_strlcpy(paste_menu_item_config.label, "Paste", MAX_LABEL_SIZE);
//     GtkWidget *paste_menu_item = create_menu_item(paste_menu_item_config);

//     gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), cut_menu_item);
//     gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), copy_menu_item);
//     gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), paste_menu_item);

//     MenuItemConfig edit_menu_item_config = DEFAULT_MENU_ITEM;
//     g_strlcpy(edit_menu_item_config.label, "Edit", MAX_LABEL_SIZE);
//     GtkWidget *edit_menu_item = create_menu_item(edit_menu_item_config);
//     menu_item_set_submenu(edit_menu_item, edit_menu);

//     gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), edit_menu_item);

//     ComboTextBoxConfig combo_box_with_entry_config = DEFAULT_COMBO_TEXT_BOX_CONFIG;
//     combo_box_with_entry_config.has_entry = TRUE;
//     combo_box_with_entry_config.options = g_ptr_array_new();

//     ComboTextBoxOptions *combo_text_box_option1 = g_new(ComboTextBoxOptions, 1);
//     combo_text_box_option1->key = g_strdup("Option 1");
//     combo_text_box_option1->value = g_strdup("Value 1");
//     g_ptr_array_add(combo_box_with_entry_config.options, combo_text_box_option1);

//     ComboTextBoxOptions *combo_text_box_option2 = g_new(ComboTextBoxOptions, 1);
//     combo_text_box_option2->key = g_strdup("Option 2");
//     combo_text_box_option2->value = g_strdup("Value 2");
//     g_ptr_array_add(combo_box_with_entry_config.options, combo_text_box_option2);

//     ComboTextBoxOptions *combo_text_box_option3 = g_new(ComboTextBoxOptions, 1);
//     combo_text_box_option3->key = g_strdup("Option 3");
//     combo_text_box_option3->value = g_strdup("Value 3");
//     g_ptr_array_add(combo_box_with_entry_config.options, combo_text_box_option3);

//     GtkWidget *combo_box_with_entry = create_combo_text_box(combo_box_with_entry_config);

//     ImageConfig small_image_config = DEFAULT_IMAGE;
//     g_strlcpy(small_image_config.path, "./assets/images/programer.jpg", MAX_IMAGE_PATH_SIZE);
//     small_image_config.type = IMAGE_PIXBUF;
//     small_image_config.dimensions.width = 100;
//     small_image_config.dimensions.height = 100;
//     GtkWidget *small_image = create_image(small_image_config);

//     FixedConfig fixed_config = DEFAULT_FIXED;
//     g_strlcpy(fixed_config.bg_color, "#00FF00", MAX_COLOR_SIZE);
//     GtkWidget *fixed = create_fixed(fixed_config);

//     gtk_fixed_put(GTK_FIXED(fixed), switch_button, 20, 530);
//     gtk_fixed_put(GTK_FIXED(fixed), progress_bar, 10, 50);
//     gtk_fixed_put(GTK_FIXED(fixed), separator, 10, 90);
//     gtk_fixed_put(GTK_FIXED(fixed), spin_button, 10, 130);
//     gtk_fixed_put(GTK_FIXED(fixed), radio_button1, 10, 170);
//     gtk_fixed_put(GTK_FIXED(fixed), radio_button2, 10, 210);
//     gtk_fixed_put(GTK_FIXED(fixed), link_button, 10, 250);
//     gtk_fixed_put(GTK_FIXED(fixed), check_button, 10, 290);
//     gtk_fixed_put(GTK_FIXED(fixed), entry, 10, 330);
//     gtk_fixed_put(GTK_FIXED(fixed), combo_box_with_entry, 10, 380);
//     gtk_fixed_put(GTK_FIXED(fixed), small_image, 10, 420);

//     NotebookConfig notebook_config = DEFAULT_NOTEBOOK;
//     notebook_config.show_border = TRUE;
//     notebook_config.show_tabs = TRUE;
//     notebook_config.tab_position = GTK_POS_TOP;

//     GtkWidget *notebook1 = create_notebook(notebook_config);
//     notebook_config.tab_position = GTK_POS_TOP;
//     GtkWidget *notebook2 = create_notebook(notebook_config);

//     GtkWidget *tab2_label = gtk_label_new("Tab2");
//     GtkWidget *tab3_label = gtk_label_new("Tab3");
//     GtkWidget *note_label = gtk_label_new("NoteTab");

//     gtk_notebook_append_page(GTK_NOTEBOOK(notebook1), grid, tab2_label);
//     gtk_notebook_append_page(GTK_NOTEBOOK(notebook2), flow_box, tab3_label);
//     gtk_notebook_append_page(GTK_NOTEBOOK(notebook1), notebook2, note_label);

//     gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(notebook1), grid, TRUE);
//     gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(notebook2), flow_box, TRUE);
//     gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(notebook1), notebook2, TRUE);

//     PanedConfig paned_config = DEFAULT_PANED;
//     paned_config.is_wide = TRUE;
//     paned_config.orientation = GTK_ORIENTATION_HORIZONTAL;
//     paned_config.position = -1;
//     GtkWidget *paned = create_paned(paned_config);

//     gtk_paned_pack1(GTK_PANED(paned), fixed, TRUE, TRUE);
//     gtk_paned_pack2(GTK_PANED(paned), notebook1, TRUE, TRUE);

//     BoxConfig box_config = DEFAULT_BOX;
//     g_strlcpy(box_config.bg_color, "#ADD8E6", MAX_COLOR_SIZE);
//     GtkWidget *box = create_box(box_config);

//     gtk_box_pack_start(GTK_BOX(box), menu_bar, FALSE, FALSE, 3);
//     gtk_box_pack_start(GTK_BOX(box), paned, TRUE, TRUE, 3);

//     ScrolledWindowConfig scrolled_window_config = DEFAULT_SCROLLED_WINDOW;
//     GtkWidget *scrolled_window = create_scrolled_window(scrolled_window_config);

//     gtk_container_add(GTK_CONTAINER(scrolled_window), box);
//     gtk_container_add(GTK_CONTAINER(window), scrolled_window);

//     gtk_widget_show_all(GTK_WIDGET(window));
// }

// int main(int argc, char *argv[])
// {
//     GtkApplication *app;
//     int status;
//     app = gtk_application_new("gtk.root.app", G_APPLICATION_DEFAULT_FLAGS);

//     g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

//     status = g_application_run(G_APPLICATION(app), argc, argv);

//     g_object_unref(app);

//     return status;
// }
