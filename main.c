#include "./include/builder.h"


// Activate callback for GtkApplication
static void activate(GtkApplication *app, gpointer user_data)
{
    root_app = app;
    // Create a new window

       View *root_view = build_app(app, root_view, INDEX_TXT);
       GtkWidget *window = root_view->widget;

    // WindowConfig window_config = DEFAULT_WINDOW;
    // GtkWidget *window = create_window(app, window_config);

    // // ColorButtonConfig button_config = DEFAULT_COLOR_BUTTON;
    // // GtkWidget *button = create_color_button(button_config);
    // GtkWidget *button=gtk_font_button_new();
    
    
    // // gtk_container_add(GTK_CONTAINER(expander), button);
    // gtk_container_add(GTK_CONTAINER(window), button);

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
