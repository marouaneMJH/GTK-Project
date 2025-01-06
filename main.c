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

    //entry.completion = create_completion_system();

    GtkWidget *Myentry = create_entry(entry);
   // g_signal_connect(Myentry, "insert-text", G_CALLBACK(on_insert_textsss), NULL);
    widget_set_font(Myentry, "SansSerif", 20);

    /* Progress Bar Configuration */
    ProgressBarConfig progress_bar_data = DEFAULT_PROGRESS_BAR;
    progress_bar_data.progress_fraction = 0.5;
    progress_bar_data.is_text_visible = TRUE;

    GtkWidget *progress_bar = create_progress_bar(progress_bar_data);
    gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(progress_bar), 0.8);

    /* Image Configuration  Error for animations*/
    // ImageConfig image_data = DEFAULT_IMAGE;
    // image_data.type = IMAGE_FILE;
    // g_strlcpy(image_data.path, "./assets/images/giphy.gif", MAX_IMAGE_PATH_SIZE);

    // GdkPixbufAnimation *animation = gdk_pixbuf_animation_new_from_file("./assets/images/test_animation.webp", NULL);
    // if(!animation) {
    //     perror("Failed to load animation");
    //     exit(EXIT_FAILURE);
    // }
    // GtkWidget *image = create_image_from_animation(&image_data, animation);

    //================================================================================================
    /* Button Configuration */
    // GtkWidget *button = gtk_button_new_with_label("Click Me");
    // gtk_widget_override_background_color(button, GTK_STATE_FLAG_NORMAL, &(GdkRGBA){0.5, 0.5, 0.5, 1});
   // widget_set_background_color(button, "blue", GTK_STATE_FLAG_NORMAL);
    //================================================================================================
    // FrameConfig frame_config = DEFAULT_FRAME_CONFIG;
    // frame_config.margins.top = 50;
    // g_strlcpy(frame_config.text_color,"red",MAX_COLOR_SIZE);
    // GtkWidget *frame = create_frame(frame_config);
    // gtk_container_add(GTK_CONTAINER(frame), button);
    // gtk_box_pack_start(GTK_BOX(box), frame, FALSE, FALSE, 0);


    //================================================================================================
    // GtkCellArea *area = gtk_cell_area_box_new();
    // GtkWidget *combobox = gtk_combo_box_text_new();
    // gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combobox), "Option 1");
    // gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combobox), "Option 2");
    // gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combobox), "Option 3", "Option 3");
    // gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(combobox), 1, "Option 4", "Option 4");
    // gtk_combo_box_text_remove(GTK_COMBO_BOX_TEXT(combobox), 1);
    // gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(combobox));
    ComboTextBoxConfig combo_text_box_config = DEFAULT_COMBO_TEXT_BOX_CONFIG;
    ComboTextBoxOptions options[] = {
        {"Option 1", "Option 1"},
        {"Option 2", "Option 2"},
        {"Option 3", "Option 3"},
        {"Option 4", "Option 4"},
    };
    GPtrArray *options_array = g_ptr_array_new();
    for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++)
    {
        g_ptr_array_add(options_array, &options[i]);
    }
    combo_text_box_config.options = options_array;
    combo_text_box_config.has_entry = TRUE;
    GtkWidget *combobox = create_combo_text_box(combo_text_box_config);
   // GtkWidget *combobox = gtk_combo_box_text_new();
    // gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combobox), "Option 1");
    // gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combobox), "Option 2");
    // gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combobox), "Option 3");
    // gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combobox), "Option 4");
    gtk_box_pack_start(GTK_BOX(box), combobox, FALSE, FALSE, 0);
    //================================================================================================
    //widget_set_background_image_without_css(button, "programer.jpg");
    /* Packing Widgets into Box */
    //gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);
    //gtk_box_pack_start(GTK_BOX(box), Myentry, FALSE, FALSE, 0);
    //gtk_box_pack_start(GTK_BOX(box), progress_bar, FALSE, FALSE, 0);
   // gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 0);
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
