
#include "./include/builder.h"

void print_graph1(View *root)
{
    if (!root)
        return;
    g_print("WIDGET: ===> %s => PARENT ==> %s\n", root->view_config->view_id, root->parent->view_config->view_id);
    if (root->next || root->child)
        g_print("Has next or child\n");
    print_graph1(root->child);
    print_graph1(root->next);
}

// Activate callback for GtkApplication
static void activate(GtkApplication *app, gpointer user_data)
{
    root_app = app;
    // Create a new window

    View *root_view = build_app(app, root_view, INDEX_TXT);
    GtkWidget *window = root_view->widget;

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
