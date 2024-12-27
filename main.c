#include "./include/index.h"


// Callback function for button click
static void run_run(GtkWidget *button, GtkWidget *spin_button) {
    gdouble value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button)); // Get current spin button value
    g_print("\nSpin button value: %f\n", value);
}

// Main activate function
static void activate(GtkApplication *app, gpointer user_data) {
    // Create spin button adjustment
    GtkAdjustment *adjustment = gtk_adjustment_new(50, 0, 100, 1, 1, 0);

    // Create window
    GtkWindow *window = create_window(app, init_window(NULL));
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Create spin button
    GtkWidget *spin_button = gtk_spin_button_new(adjustment, 1, 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button), 50);

    // Create button to check value
    GtkWidget *button_check = gtk_button_new_with_label("Check Value");
    g_signal_connect(button_check, "clicked", G_CALLBACK(run_run), spin_button); // Pass spin button to callback

    // Pack widgets into box and add to window
    gtk_box_pack_start(GTK_BOX(box), spin_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), button_check, FALSE, FALSE, 0);
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




