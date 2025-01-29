#include "./include/builder.h"

// // Callback function for button click
// static void on_button_clicked(GtkButton *button, gpointer user_data)
// {
//     g_print("Button clicked!\n");
// }

// // Activate callback for GtkApplication
// static void activate(GtkApplication *app, gpointer user_data)
// {
//     // Create a new window

//     View *root_view = build_app(app, root_view);
//     GtkWidget *window = root_view->widget;

//     // WindowConfig window_config = DEFAULT_WINDOW_CONFIG;
//     // GtkWidget *window = create_window(app,window_config);

//     // StackConfig stack_config = DEFAULT_STACK_CONFIG;
//     // GtkWidget* stack = create_stack(stack_config);

//     show_window(window);
// }

// // Main function
// int main(int argc, char **argv)
// {
//     GtkApplication *app;
//     int status;

//     // Create a new application instance
//     app = gtk_application_new("gtk.root.app", G_APPLICATION_DEFAULT_FLAGS);
//     g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

//     // Run the application
//     status = g_application_run(G_APPLICATION(app), argc, argv);

//     // Clean up
//     g_object_unref(app);

//     return status;
// }
// #include <gtk/gtk.h>

// static void on_button1_clicked(GtkWidget *widget, GtkWidget *stack,GtkWidget *page1)
// {
//     gtk_stack_set_visible_child(GTK_STACK(stack), page1);
// }



// static void on_button2_clicked(GtkWidget *widget, GtkWidget *stack,GtkWidget *page2)
// {
//     gtk_stack_set_visible_child(GTK_STACK(stack), page2);
// }

// static void activate(GtkApplication *app, gpointer user_data)
// {
//     GtkWidget *window;
//     GtkWidget *stack;
//     GtkWidget *page1, *page2;
//     GtkWidget *button1, *button2;
    
//     // Create a new window
//     window = gtk_application_window_new(app);
//     gtk_window_set_title(GTK_WINDOW(window), "GtkStack Example");
//     gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

//     // Create a GtkStack container
//     stack = gtk_stack_new();
//     gtk_stack_set_homogeneous(GTK_STACK(stack), TRUE);  // Make all pages the same size

//     // Create pages (simple labels for this example)
//     page1 = gtk_label_new("This is Page 1");
//     page2 = gtk_label_new("This is Page 2");

//     // Add pages to the stack with names
//     gtk_stack_add_named(GTK_STACK(stack), page1, "page1");
//     gtk_stack_add_named(GTK_STACK(stack), page2, "page2");

//     // Create buttons to navigate between pages
//     button1 = gtk_button_new_with_label("Go to Page 1");
//     button2 = gtk_button_new_with_label("Go to Page 2");

    
//     // Connect buttons to signals to change pages
//     g_signal_connect(button1, "clicked", G_CALLBACK(on_button1_clicked), stack,page1);
//     g_signal_connect(button2, "clicked", G_CALLBACK(on_button2_clicked), stack,page2);

//     // Arrange the buttons and stack in a vertical box container
//     GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
//     gtk_box_pack_start(GTK_BOX(vbox), button1, FALSE, FALSE, 0);
//     gtk_box_pack_start(GTK_BOX(vbox), button2, FALSE, FALSE, 0);
//     gtk_box_pack_start(GTK_BOX(vbox), stack, TRUE, TRUE, 0);

//     // Add the vbox to the window
//     gtk_container_add(GTK_CONTAINER(window), vbox);

//     // Show all widgets
//     gtk_widget_show_all(window);
// }

// int main(int argc, char *argv[])
// {
//     GtkApplication *app;
//     int status;

//     // Create a new GTK application
//     app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);

//     // Connect the "activate" signal of the application to the activate function
//     g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

//     // Run the GTK application
//     status = g_application_run(G_APPLICATION(app), argc, argv);

//     // Free the application object
//     g_object_unref(app);

//     return status;
// }
