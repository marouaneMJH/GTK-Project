#include "./include/builder.h"

// Callback function for button click
static void on_button_clicked(GtkButton *button, gpointer user_data) {
    g_print("Button clicked!\n");
}

// Activate callback for GtkApplication
static void activate(GtkApplication *app, gpointer user_data) {
    // Create a new window

    View *root_view = build_app(app, root_view);
    GtkWidget *window = root_view->widget;

    // Create a button
    // GtkWidget *button = gtk_button_new_with_label("Click Me");
    // g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    // Add the button to the window
    // gtk_container_add(GTK_CONTAINER(window), button);

    // Show all widgets
    gtk_widget_show_all(window);
}

// Main function
int main(int argc, char **argv) {
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

//     // Create window
//     WindowConfig window_config = DEFAULT_WINDOW;
//     GtkWidget *window = create_window(app, window_config);

//     BoxConfig box_config = DEFAULT_BOX;
//     GtkWidget *box = create_box(box_config);
//     GtkWidget *box1 = create_box(box_config);

//     MenuBarConfig menu_bar_config = DEFAULT_MENU_BAR;
//     GtkWidget *menu_bar = create_menu_bar(menu_bar_config);

//     MenuConfig menu_config = DEFAULT_MENU;

//     GtkWidget *file_menu = create_menu(menu_config);

//     MenuItemConfig menu_item_config = DEFAULT_MENU_ITEM;

//     // g_strlcpy(menu_item_config.label, "File", MAX_LABEL_SIZE);
//     // GtkWidget *file_item = create_menu_item(menu_item_config);

//     // menu_item_set_submenu(file_item, file_menu);

//     g_strlcpy(menu_item_config.label, "About", MAX_LABEL_SIZE);
//     GtkWidget *about_item = create_menu_item(menu_item_config);

//     g_strlcpy(menu_item_config.label, "New", MAX_LABEL_SIZE);
//     GtkWidget *new_menu_item = create_menu_item(menu_item_config);

//     g_strlcpy(menu_item_config.label, "Exit", MAX_LABEL_SIZE);
//     GtkWidget *exit_menu_item = create_menu_item(menu_item_config);

//     ViewConfig *view_config = NULL;
//     SAFE_ALLOC(view_config, ViewConfig, 1);

//     // gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), new_menu_item);
//     // gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), exit_menu_item);

//     gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), new_menu_item);
//     view_config->group = menu_bar;

//     gtk_menu_shell_append(GTK_MENU_SHELL(view_config->group), exit_menu_item);
//     gtk_menu_shell_append(GTK_MENU_SHELL(view_config->group), about_item);

//     ButtonConfig btn_config = DEFAULT_BUTTON;
//     GtkWidget *btn = create_button(btn_config);

//     // Pack widgets into box and add to window
//     gtk_box_pack_start(GTK_BOX(box), menu_bar, FALSE, FALSE, 0);
//     gtk_box_pack_start(GTK_BOX(box), box1, FALSE, FALSE, 0);
//     gtk_box_pack_start(GTK_BOX(box1), btn, FALSE, FALSE, 0);

//     gtk_container_add(GTK_CONTAINER(window), box);

//     // Show all widgets
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
}
