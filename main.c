#include "./include/index.h"


// Callback function for button click
// static void run_run(GtkWidget *button, GtkWidget *toggle_button) {
//     gdouble value = gtk_toggle_button_get_value(GTK_SPIN_BUTTON(toggle_button)); // Get current spin button value
//     g_print("\nSpin button value: %f\n", value);
// }

// Main activate function
static void activate(GtkApplication *app, gpointer user_data) {
    // Create spin button adjustment
    GtkAdjustment *adjustment = gtk_adjustment_new(50, 0, 100, 1, 1, 0);

    // Create window
    GtkWindow *window = create_window(app, init_window(NULL));
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);


    // creat widget
    
    GtkWidget *toggle_button=gtk_toggle_button_new_with_label("Name of God") ;
    // gtk_toggle_button_toggled(GTK_TOGGLE_BUTTON(toggle_button));
    if(gtk_toggle_button_get_mode(GTK_TOGGLE_BUTTON(toggle_button)));
        g_print("\n button toggoled");

    // Pack widgets into box and add to window
    gtk_box_pack_start(GTK_BOX(box), toggle_button, FALSE, FALSE, 0);
    // gtk_box_pack_start(GTK_BOX(box), button_check, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Show all widgets
    gtk_widget_show_all(GTK_WIDGET(window));
}




//The main function


int main(int argc, char *argv[]) {

    GtkApplication *app;
    int status;

    app = gtk_application_new("gtk.app.root", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);


    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}




