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
    // GtkWidget *window = create_window(app,window_config);

    // Gtk 


    // GtkWidget *button = gtk_button_new_with_label("Click me!");

    // FrameConfig config_frame = DEFAULT_FRAME; 
    // GtkWidget *frame = create_frame(config_frame);
    // LabelConfig label_config = DEFAULT_LABEL;
    // label_config.font_size=20;
    // GtkWidget *label = create_label(label_config);
    // gtk_container_add(GTK_CONTAINER(frame), button);
    // gtk_container_add(GTK_CONTAINER(window), frame);

    show_window(window);
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



