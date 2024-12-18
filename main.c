#include <gtk/gtk.h>
#include "./include/index.h"
static void activate(GtkApplication *app, gpointer user_data)
{
  // Window *window_data = 


  Window* win1=init_window("window 1");
  Window* wn2=init_window("window 2");

  GtkWindow *window=create_window(app, init_window("window 1"));
  GtkWindow *window2=create_window(app, init_window("window 2"));
  
  gtk_widget_show_all(GTK_WIDGET(window));
  gtk_widget_show_all(GTK_WIDGET(window2));
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













// #include <gtk/gtk.h>



// /* the demention of Widget*/
// typedef struct 
// {
//   gint width;
//   gint gheight;
// }Demention;



// // the position of the widget in the window
// typedef struct 
// {              
//   gint x;
//   gint y;
// }Bound;

// // the start up position of the window
// typedef enum 
// {
//   GTK_WINDOW_CENTER,
//   GTK_WINDOW_POS_CENTER_ALWAYS,
//   GTK_WINDOW_POS_CENTER_ON_PARENT,
//   GTK_WINDOW_POS_MOUSE,
//   GTK_WINDOW_POS_NONE
// }GtkPosit;



// typedef struct window
// {
//   // title of the window 
//   gchar *title;
//   Demention demention;
//   // if it resizable or not
//   gboolean resizable;
//   // the start up position of the window
//   GtkPosit position;
//   // if the window is decorated or not (use it for gtk_window_set_decorated and gtk_window_get_decorated functions)
//   gboolean is_fullscreen;
//   // maximized the window or not (use it for gtk_window_maximize and gtk_window_unmaximize functions)
//   gboolean is_maximized;

//   // if the window is modal or not (we can use other windows in same time )
//   gboolean is_modal;  


//   // the parent window
//   GtkWindow* parent;

//   // functions
// }Window;


// // Callback function to print "Hello World"
// static void
// print_hello (GtkWidget *widget,
//              gpointer   data)
// {
//   g_print ("Hello World\n");
// }

// // Function to activate the application and create the main window
// static void
// activate (GtkApplication *app,
//           gpointer        user_data)
// {
//   GtkWidget *window;
//   GtkWidget *grid;
//   GtkWidget *button;

//   // Create a new window and set its title
//   window = gtk_application_window_new (app);
//   gtk_window_set_title (GTK_WINDOW (window), "Window");
//   gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_MOUSE);
//   gtk_container_set_border_width (GTK_CONTAINER (window), 10);

//   // Create a grid container for buttons
//   grid = gtk_grid_new ();

//   // Add the grid to the window
//   gtk_container_add (GTK_CONTAINER (window), grid);

//   // Add Button 1 to the grid
//   button = gtk_button_new_with_label ("Button 1");
//   g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
//   gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

//   // Add Button 2 to the grid
//   button = gtk_button_new_with_label ("Button 2");
//   g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
//   gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

//   // Add Quit button to the grid
//   button = gtk_button_new_with_label ("Quit");
//   g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
//   gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

//   // Show all widgets in the window
//   gtk_widget_show_all (window);
// }

// // Function to create and run the GTK application
// GtkApplication* Cree_Main_Window(const gchar *app_id, int *status, int argc, char **argv)
// {
//   GtkApplication *app = gtk_application_new (app_id, G_APPLICATION_DEFAULT_FLAGS);

//   g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
//   *status = g_application_run (G_APPLICATION (app), argc, argv);
//   g_object_unref (app);

//   return app;
// }



// int
// main (int    argc,
//       char **argv)
// {
//   GtkApplication *app;
//   int status;

//   // Create and run the GTK application
//   app = Cree_Main_Window ("org.gtk.example", &status, argc, argv);

//   return status;
// }
