#include "./include/builder.h"

gboolean clicked = FALSE;
gboolean clicked1 = FALSE;

// static void click1(GtkWidget *widget, gpointer data)
// {
//     View *root = (View *)data;
//     g_print("Click1\n");

//     View *btn2 = find_view_by_id("bt2", root);
//     if (btn2)
//     {
//         if (clicked)
//             widget_set_colors(btn2->widget, "yellow", "white");
//         else
//             widget_set_colors(btn2->widget, "red", "white");

//         clicked = !clicked;
//     }

//     // GtkWidget *dialog = gtk_dialog_new_with_buttons(
//     //     "Standalone Dialog",   // Title
//     //     NULL,                  // No parent (NULL)
//     //     GTK_DIALOG_MODAL,      // Make it modal
//     //     "_OK", GTK_RESPONSE_OK,
//     //     "_Cancel", GTK_RESPONSE_CANCEL,
//     //     NULL
//     // );

//     // DialogConfig dc = DEFAULT_DIALOG;
//     // GtkWidget *dialog = create_dialog(dc);

//     // GtkWidget *dialog_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

//     // ButtonConfig btn_config = DEFAULT_BUTTON;
//     // GtkWidget *btn = create_button(btn_config);

//     // BoxConfig box_config = DEFAULT_BOX;
//     // GtkWidget *box = create_box(box_config);

//     // gtk_box_pack_end(GTK_BOX(box), btn, FALSE, FALSE, 0);
//     // gtk_widget_set_size_request(box, 400, 400);

//     // gtk_container_add(GTK_CONTAINER(dialog_area), box);

//     // show_dialog(dialog);
// }

// static void click2(GtkWidget *widget, gpointer data)
// {
//     View *root = (View *)data;
//     g_print("Click2\n");

//     View *btn1 = find_view_by_id("bt1", root);
//     if (btn1)
//     {
//         if (clicked1)
//             widget_set_colors(btn1->widget, "yellow", "white");
//         else
//             widget_set_colors(btn1->widget, "green", "white");

//         clicked1 = !clicked1;
//     }
// }

// Activate callback for GtkApplication
static void activate(GtkApplication *app, gpointer user_data)
{
    // Create a new window

   View *root_view = build_app(app, root_view, INDEX_TXT);
   GtkWidget *window = root_view->widget;
    
    
    build_app(app, NULL, DIALOG_TXT);
    // View *btn1 = find_view_by_id("bt1", root_view);
    // if (btn1)
    //     g_signal_connect(G_OBJECT(btn1->widget), "clicked", G_CALLBACK(click1), root_view);

    // View *btn2 = find_view_by_id("bt2", root_view);
    // if (btn2)
    //     g_signal_connect(G_OBJECT(btn2->widget), "clicked", G_CALLBACK(click2), root_view);

   // g_print("ROOT=> %s\n", root_view->view_config->view_id);
    // g_print("ROOT GLOBAL=> %s\n", root_view_gloabl->view_config->view_id);


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
