#include "./include/index.h"



static void activate(GtkApplication *app, gpointer user_data)
{
    WindowConfig win1 = DEFAULT_WINDOW;
    g_strlcpy(win1.title, "Window 1", MAX_WINDOW_TITLE_SIZE);

    WindowConfig win2 = DEFAULT_WINDOW;
    BoxConfig box_config = DEFAULT_BOX;

    g_strlcpy(win2.bg_color, "#FF0000", sizeof(win2.bg_color));
    GtkWidget *box;      // the box container
    GtkWidget *window;    // the main window
    window = create_window(app, &win1);
    box = create_box(box_config);

    /* Structures Declaration */
    MessageDialogConfig dialog_config = DEFAULT_MESSAGE_DIALOG_CONFIG;
    
    dialog_config.parent = GTK_WINDOW(window);
    strcpy(dialog_config.message, "Hello! This is a message dialog.");

    /* Widget Declaration */
    GtkWidget *dialog;

    /* Widget creation */
    dialog = create_message_dialog(dialog_config);



    ButtonConfig button_config;
    strcpy(button_config.bg_color,"#FF0000");
    button_config.dimensions.height=20;
    button_config.dimensions.width=20;
    // GtkWidget* button = create_button(button_config);

    /* Widget packing */
    // gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,0);
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(box));


    show_window(window);
    show_dialog(dialog);
}



int main_window(int argc, char *argv[])
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("gtk.app.root", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);


    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);
    return status;
}


int main(int argc, char *argv[])
{
    return main_window(argc,argv);
}


// static void activate(GtkApplication *app, gpointer user_data)
// {
//     WindowConfig win1 = DEFAULT_WINDOW;
//     g_strlcpy(win1.title, "Window 1", MAX_WINDOW_TITLE_SIZE);

//     WindowConfig win2 = DEFAULT_WINDOW;
//     BoxConfig box_config = DEFAULT_BOX;

//     g_strlcpy(win2.bg_color, "#FF0000", sizeof(win2.bg_color));
//     GtkWidget *box;      // the box container
//     GtkWidget *window;    // the main window
//     window = create_window(app, &win1);
//     box = create_box(box_config);

//     /* Structures Declaration */
//     FileChooserDialogConfig dialog_config = DEFAULT_FILE_CHOOSER_DIALOG_CONFIG;
//     dialog_config.parent = GTK_WINDOW(window);
//     // strcpy(dialog_config.message, "Hello! This is a message dialog.");

//     /* Widget Declaration */
//     GtkWidget *dialog;

//     /* Widget creation */
//     dialog = create_file_chooser_dialog(dialog_config);

//     /* Run and destroy dialog */
//     gtk_widget_show_all(dialog);
//     gtk_dialog_run(GTK_DIALOG(dialog));
//     gtk_widget_destroy(dialog);

//     /* Widget packing */
//     gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(box));

//     show_window(window);
// }

