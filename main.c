#include "./include/index.h"

static void activate(GtkApplication *app, gpointer user_data) {
    /* Window Configuration */
    WindowConfig win1 = DEFAULT_WINDOW;
    g_strlcpy(win1.title, "Window 1", MAX_WINDOW_TITLE_SIZE);

    BoxConfig box_config = DEFAULT_BOX;
    GtkWidget *window = create_window(app, &win1);
    GtkWidget *box = create_box(box_config);

    /* Entry Configuration */
    EntryConfig entry = DEFAULT_ENTRY;
    entry.purpose = GTK_INPUT_PURPOSE_PIN;
    g_strlcpy(entry.placeholder_text, "Enter your name", entry.max_length);
    entry.margins.top = 50;
    entry.opacity = 1;
    g_strlcpy(entry.bg_color, "red", MAX_COLOR_SIZE);
    entry.completion = create_completion_system();

    GtkWidget *Myentry = create_entry(&entry);
    g_signal_connect(Myentry, "insert-text", G_CALLBACK(on_insert_textsss), NULL);
    widget_set_font(Myentry, "SansSerif", 20);

    /* Progress Bar Configuration */
    ProgressBarConfig progress_bar_data = DEFAULT_PROGRESS_BAR;
    progress_bar_data.progress_fraction = 0.5;
    progress_bar_data.is_text_visible = TRUE;

    GtkWidget *progress_bar = create_progress_bar(&progress_bar_data);
    gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(progress_bar), 0.8);
    g_timeout_add(100, (GSourceFunc)progress_pulse, progress_bar);

    /* Image Configuration */
    ImageConfig image_data = DEFAULT_IMAGE;
    image_data.type = IMAGE_ICON_NAME;
    g_strlcpy(image_data.path, "go-home", MAX_ICON_NAME_SIZE);

    GtkWidget *image = create_image_from_icon_name(&image_data, GTK_ICON_SIZE_DIALOG);

    /* Packing Widgets into Box */
    gtk_box_pack_start(GTK_BOX(box), Myentry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), progress_bar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    /* Show Window */
    show_window(window);
}

int main_window(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("gtk.app.root", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

int main(int argc, char *argv[]) {
    return main_window(argc, argv);
}
