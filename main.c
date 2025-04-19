
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

    add_command("label name", 10, 100, "label", commands_container, root_view);

    ParamNode node = {
        .params = {
            "param1",
            "param2",
            "param3",
            "param4",
        }};

    add_custom_command("hhhhhhh label_name", 100, 100, "sig_entry_activate", node, commands_container, root_view);
    add_custom_command("hhhhhhh label_name", 100, 100, "sig_hello", node, commands_container, root_view);


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
