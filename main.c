#include <gtk/gtk.h>
#include "./include/index.h"


void exits(GtkWidget* button,gpointer user_data)
{
  g_print("\nHello");
}


static void activate(GtkApplication *app, gpointer user_data)
{


  Window* win1=init_window("window 1");


  GtkWindow *window=create_window(app, init_window("window 1"));

    // button 

  GtkWidget *button1=gtk_button_new_with_label("ILISI1");
  GtkWidget *button2=gtk_button_new_with_label("ILISI2");
  GtkWidget *button3=gtk_button_new_with_label("ILISI3");

  // GtkWidget *button_icon=gtk_button_new_from_icon_name("go-home",GTK_ICON_SIZE_LARGE_TOOLBAR);
  
  gtk_widget_set_size_request(button1,1,50);
  gtk_widget_set_size_request(button2,1,200);
  gtk_widget_set_size_request(button3,900,100);
  // gtk_widget_set_size_request(button_icon,900,100);

  GtkWidget* box=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);

  // gtk_widget_set_size_request(box,900,900);
  gtk_box_pack_start(GTK_BOX(box),button3,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),button1,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),button2,TRUE,TRUE,0);
  // gtk_box_pack_start(GTK_BOX(box),button_icon,TRUE,TRUE,0);

  GtkWidget* label=create_label(init_label("Hello c'est marouane"));
  gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);

  


  // g_signal_connect(button_icon,"clicked",G_CALLBACK(exits),NULL);

  GtkWidget* fixed=gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed),box,20,40);

  // gtk_container_add(GTK_CONTAINER(window),fixed);
  gtk_container_add(GTK_CONTAINER(window),fixed);
  gtk_widget_show_all(GTK_WIDGET(window));
}








int main(int argc, char *argv[]) {

    GtkApplication *app;
    int status;

    app = gtk_application_new("gtk.app.root", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);


    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}




