
#include "./include/builder.h"


// Activate callback for GtkApplication
static void activate(GtkApplication *app, gpointer user_data)
{
    root_app = app;

    // // Create a new window
    View *root_view = build_app(app, NULL, INDEX_TXT);
    GtkWidget *window = root_view->widget;

    // Test command creation

    View *commands_container = find_view_by_id("commands_container", root_view);
    if (!commands_container)
    {
        g_print("Error: ==> Cannot find the commands container\n");
        return;
    }

    add_command("Create path", 10, 10, "button", commands_container, root_view);

    // WindowConfig window_config = DEFAULT_WINDOW;
    // GtkWidget *window = create_window(app, window_config);

    // GtkWidget* box=gtk_box_new(10,10);
    // GtkWidget* button=gtk_button_new_with_label(NULL);

    // gboolean id=GTK_IS_CONTAINER(button);
    // g_print("\nis box container: %d",id);

    // gboolean id2=GTK_IS_EVENT_BOX(button);
    // g_print("\nbutton button container: %d",id2);

    // GtkWidget *label=gtk_label_new("hello");
    // GtkWidget *event_box = gtk_event_box_new();
    // gtk_container_add(GTK_CONTAINER(event_box), label);
    // gtk_widget_show(label);
    // gtk_widget_show(event_box);

    // g_signal_connect(event_box, "button-press-event",
    //                  G_CALLBACK(on_event_box_button_press), NULL);

    // GtkWidget *button=gtk_font_button_new();

    // // gtk_container_add(GTK_CONTAINER(expander), button);
    // gtk_container_add(GTK_CONTAINER(window), event_box);

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
