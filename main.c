#include "./include/index.h"


void exits(GtkWidget* button,gpointer user_data)
{
  g_print("\nHello");
}


static void activate(GtkApplication *app, gpointer user_data)
{


  Window* win1=init_window("window 1");
  GtkWindow *window=create_window(app, init_window("window 1"));
  
  Button button_struct=DEFAULT_BUTTON;
  g_strlcpy(button_struct.bg_color,"#FF0000",MAX_COLOR);
  GtkWidget* button=create_button(button_struct);
  GtkWidget* container= gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
  

  gtk_container_add(GTK_CONTAINER(window),container);
  gtk_container_add(GTK_CONTAINER(container),button);


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




