#include "./include/builder.h"

// // Callback function for button click
// static void on_button_clicked(GtkWidget *button, gpointer user_data)
// {
//     DialogConfig dialog_config = DEFAULT_DIALOG_CONFIG;
//     GtkWidget *window_1 = create_dialog(dialog_config);

//     ButtonConfig button_config = DEFAULT_BUTTON;
//     GtkWidget *new_button = create_button(button_config);  // Rename the variable to avoid shadowing

//     widget_set_background_image(window_1, "team_working_on_xml.jpeg", NULL);

//     // Instead of connecting the same callback, use a different function or NULL if unnecessary
//     g_signal_connect(G_OBJECT(new_button), "clicked", G_CALLBACK(some_other_function), NULL);

//     show_dialog(window_1);
// }

// Activate callback for GtkApplication
static void activate(GtkApplication *app, gpointer user_data)
{
    // Create a new window

    View *root_view = build_app(app, root_view);
    GtkWidget *window = root_view->widget;

    // WindowConfig window_config = DEFAULT_WINDOW;
    // GtkWidget *window = create_window(app, window_config);

    // GtkWidget *button = gtk_button_new_with_label("Click me!");

    // FrameConfig config_frame = DEFAULT_FRAME;

    // GtkWidget *frame = create_frame(config_frame);
    // LabelConfig label_config = DEFAULT_LABEL;
    // label_config.font_size = 20;

    // g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_clicked), NULL);


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
